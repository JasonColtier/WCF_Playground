// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/WFC_Manager.h"
#include "LibSL/LibSL.h"
#include "TRACE.h"
#include "JcoWFC/JcoGrid.h"
DEFINE_LOG_CATEGORY(WFCLog);

void AWFC_Manager::GenerateWFC()
{
    TRACE("Begin WFC !");

    TRACE("Creating Grid");

    grid = GetWorld()->SpawnActor<AJcoGrid>(gridClass, GetActorLocation(),GetActorRotation());

#if WITH_EDITOR
    grid->SetFolderPath("/WFC");
#endif
    
    grid->InitGrid();
    grid->Print();

    grid->InitAllPossibilities();

    grid->Collapse();    
    
    //je remplie avec toutes les possibilités
}

// Sets default values
AWFC_Manager::AWFC_Manager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWFC_Manager::BeginPlay()
{
    Super::BeginPlay();

    GenerateWFC();
}

// Called every frame
void AWFC_Manager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
