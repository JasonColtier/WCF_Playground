// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/JcoWFC/JcoGridSlot.h"

#include "JcoEDirection.h"
#include "JcoWFCPossibility.h"
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

void AJcoGridSlot::RestrictPossibilities(AJcoGridSlot* collapsedSlot, TEnumAsByte<Directions> dir)
{
    for (int j = 0; j < possibilities.Num(); ++j)
    {
        switch (dir)
        {
        case Directions::back:
            for (int i = 0; i < possibilities[j]->possibilities_back.Num(); ++i)
            {
                if (possibilities[j]->possibilities_back[i] != collapsedSlot->possibilities[0])
                {
                    possibilities.Remove(possibilities[j]->possibilities_back[i]);
                    TRACE("restrict possibility on back !")
                }
            }

        case Directions::front:
            for (int i = 0; i < possibilities[j]->possibilities_front.Num(); ++i)
            {
                if (possibilities[j]->possibilities_front[i] != collapsedSlot->possibilities[0])
                {
                    possibilities.Remove(possibilities[j]->possibilities_front[i]);
                    TRACE("restrict possibility on front !")
                }
            }

        case Directions::top:
            for (int i = 0; i < possibilities[j]->possibilities_top.Num(); ++i)
            {
                if (possibilities[j]->possibilities_top[i] != collapsedSlot->possibilities[0])
                {
                    possibilities.Remove(possibilities[j]->possibilities_top[i]);
                    TRACE("restrict possibility on top !")
                }
            }

        case Directions::bottom:
            for (int i = 0; i < possibilities[j]->possibilities_bottom.Num(); ++i)
            {
                if (possibilities[j]->possibilities_bottom[i] != collapsedSlot->possibilities[0])
                {
                    TRACE("restrict possibility on bottom !")
                    possibilities.Remove(possibilities[j]->possibilities_bottom[i]);
                }
            }

        case Directions::left:
            for (int i = 0; i < possibilities[j]->possibilities_left.Num(); ++i)
            {
                if (possibilities[j]->possibilities_left[i] != collapsedSlot->possibilities[0])
                {
                    TRACE("restrict possibility on left !")
                    possibilities.Remove(possibilities[j]->possibilities_left[i]);
                }
            }

        case Directions::right:
            for (int i = 0; i < possibilities[j]->possibilities_right.Num(); ++i)
            {
                if (possibilities[j]->possibilities_right[i] != collapsedSlot->possibilities[0])
                {
                    TRACE("restrict possibility on right !")
                    possibilities.Remove(possibilities[j]->possibilities_right[i]);
                }
            }

        default:
            return;
        }
    }
}
