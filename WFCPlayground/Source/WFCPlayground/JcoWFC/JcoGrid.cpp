// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/JcoWFC/JcoGrid.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "WFCPlayground/TRACE.h"
#include "WFCPlayground/JcoWFC/JcoGridSlot.h"

// Sets default values
AJcoGrid::AJcoGrid()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJcoGrid::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AJcoGrid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AJcoGrid::InitGrid()
{
    TRACE("init grid of size %d %d %d", sizeX, sizeY, sizeZ);

    int count = 0;

    //on spawn dans notre grille les slots
    for (int i = 0; i < sizeX; ++i)
    {
        for (int j = 0; j < sizeY; ++j)
        {
            for (int k = 0; k < sizeZ; ++k)
            {
                AJcoGridSlot* slot = GetWorld()->SpawnActor<AJcoGridSlot>(gridSlot);

                //rangé dans un joli dossier
#if WITH_EDITOR
                slot->SetFolderPath("/WFC");
#endif

                slot->SetActorLocation(FVector(i * 100, j * 100, k * 100));
                slot->gridIndex = count;
                slot->coordinates = FVector(i,j,k);
                count ++;
                grid.Add(slot);
            }
        }
    }
}

void AJcoGrid::InitAllPossibilities()
{
    //on récupère tous les Assets du projet de type "UJcoWFCPossibility"
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FAssetData> AssetData;
    const UClass* Class = UJcoWFCPossibility::StaticClass();
    AssetRegistryModule.Get().GetAssetsByClass(Class->GetFName(), AssetData);

    TArray<UJcoWFCPossibility*> allPossibilities;

    //ces assets deviennent nos possibilités
    for (auto element : AssetData)
    {
        UJcoWFCPossibility* possibility = Cast<UJcoWFCPossibility>(element.GetAsset());
        TRACE("aset name : %s", *possibility->AssetName)
        allPossibilities.Add(possibility);
    }

    //une fois toutes les possibilités découvertes, on les renseignes à tous les slots
    for (auto element : grid)
    {
        element->possibilities = allPossibilities;
    }
}

AJcoGridSlot* AJcoGrid::get(unsigned x, unsigned y, unsigned z)
{
    TRACE("returning grid slot at : %d", sizeX*x + sizeY*y + z);
    return grid[sizeX * x + sizeY * y + z];
}

AJcoGridSlot* AJcoGrid::getMinEnthropySlot()
{

    TArray<AJcoGridSlot*> minEnthropySlots;

    minEnthropySlots.Add(grid[0]);
    
    for (auto slot : grid)
    {
        if(slot->possibilities.Num() < minEnthropySlots[0]->possibilities.Num())
        {
            minEnthropySlots.Empty();
            minEnthropySlots.Add(slot);
        }else if(slot->possibilities.Num() == minEnthropySlots[0]->possibilities.Num())
        {
            minEnthropySlots.Add(slot);
        } 
    }

    return minEnthropySlots[FMath::RandRange(0,minEnthropySlots.Num() -1)];
}

void AJcoGrid::getNeibourghs(FVector coordinates, TArray<AJcoGridSlot*>& neighbours)
{
    if(coordinates.Z+1 < grid.Num())
        neighbours.Add(grid[coordinates.Z+1]);

    if(coordinates.Z-1 > 0)
        neighbours.Add(grid[coordinates.Z-1]);

    if(coordinates.Y + sizeZ < grid.Num())
        neighbours.Add(grid[coordinates.Y + sizeZ]);

    if(coordinates.Y - sizeZ > 0)
        neighbours.Add(grid[coordinates.Y - sizeZ]);

    if(coordinates.X + sizeZ * sizeY < grid.Num())
        neighbours.Add(grid[coordinates.X + sizeZ * sizeY]);

    if(coordinates.X - sizeZ * sizeY > 0)
        neighbours.Add(grid[coordinates.X - sizeZ * sizeY]);
}


bool AJcoGrid::isCollapsed()
{
    for (auto element : grid)
    {
        if(element->possibilities.Num() > 1)
            return  false;
    }

    return true;
}

void AJcoGrid::Collapse()
{
    AJcoGridSlot* slot = getMinEnthropySlot();
    UJcoWFCPossibility* possibility = slot->possibilities[FMath::RandRange(0,slot->possibilities.Num())];
    slot->possibilities.Empty();
    slot->possibilities.Add(possibility);

    //todo getCoo in slot;
    TArray<AJcoGridSlot*> neighbours;
    getNeibourghs(slot->coordinates,neighbours);
    //ajoute la notion de direction
    //ce sont les voisins qui réstreignent leurs possibilités en fonction du slot que l'on vient de collapse
    //je regarde les contraintes de direction du slot collapsed
    //tout ce qui n'en fait pas partie est retiré de mes possibilités

    for (auto neighbour : neighbours)
    {
        // neighbour->possibilities.
    }
}


void AJcoGrid::Print()
{
    for (auto slot : grid)
    {
        slot->Print();
    }
}