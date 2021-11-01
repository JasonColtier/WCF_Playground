// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/JcoWFC/JcoGridSlot.h"

#include "JcoEDirection.h"
#include "JcoWFCPossibility.h"
#include "Engine/StaticMeshActor.h"
#include "WFCPlayground/TRACE.h"

// Sets default values
AJcoGridSlot::AJcoGridSlot()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void AJcoGridSlot::Print()
{
    TRACE("print grid slot : index = %d", gridIndex);
}

bool AJcoGridSlot::RestrictPossibilities(AJcoGridSlot* collapsedSlot, TEnumAsByte<Directions> dir)
{
    //je compare chacune de mes possibilités avec celles autorisées par le slot collapsed dans la bonne direction

    TArray<UJcoWFCPossibility*> autorisations;
    bool restricted = false;

    switch (dir)
    {
    case Directions::back:
        autorisations = collapsedSlot->possibilities[0]->possibilities_back; //autorisations
        break;

    case Directions::front:
        autorisations = collapsedSlot->possibilities[0]->possibilities_front; //autorisations
        break;

    case Directions::top:
        autorisations = collapsedSlot->possibilities[0]->possibilities_top; //autorisations
        break;

    case Directions::bottom:
        autorisations = collapsedSlot->possibilities[0]->possibilities_bottom; //autorisations
        break;

    case Directions::left:
        autorisations = collapsedSlot->possibilities[0]->possibilities_left; //autorisations
        break;

    case Directions::right:
        autorisations = collapsedSlot->possibilities[0]->possibilities_right; //autorisations
        break;

    default:
        break;
    }

    for (int j = 0; j < possibilities.Num(); ++j)
    {
        //si ma possibilité ne fait pas partie de celles autorisées dans cette direction je la supprime
        if (!autorisations.Contains(possibilities[j]))
        {
            if (possibilities.Num() > 1)
            {
                TRACE("restrict possibility %s", *possibilities[j]->GetName())
                restricted = true;
                possibilities.RemoveAt(j);
            }
            else
            {
                TRACE_ERROR("Error : tried to remove possibility but there was only 1 remaining")
            }
        }
    }

    return restricted;
}

void AJcoGridSlot::Display()
{
    auto meshActor = GetWorld()->SpawnActor<AStaticMeshActor>(GetActorLocation(), GetActorRotation());
    meshActor->GetStaticMeshComponent()->SetStaticMesh(possibilities[0]->staticMesh);
}
