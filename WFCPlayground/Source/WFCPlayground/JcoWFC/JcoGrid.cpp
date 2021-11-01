// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/JcoWFC/JcoGrid.h"

#include "JcoEDirection.h"
#include "JcoWFCPossibility.h"
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
                slot->coordinates = FVector(i, j, k);
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
        if (slot->possibilities.Num() > minEnthropySlots[0]->possibilities.Num() && slot->possibilities.Num() > 1)
        {
            minEnthropySlots.Empty();
            minEnthropySlots.Add(slot);
        }
        else if (slot->possibilities.Num() == minEnthropySlots[0]->possibilities.Num() && slot->possibilities.Num() > 1)
        {
            minEnthropySlots.Add(slot);
        }
    }

    return minEnthropySlots[FMath::RandRange(0, minEnthropySlots.Num() - 1)];
}

void AJcoGrid::getNeibourghs(AJcoGridSlot* collapsedSlot, Neighbours& neighbours)
{
    if (((int)collapsedSlot->coordinates.Z + 1) % sizeZ != 0)
        neighbours.Add(TPair<AJcoGridSlot*, Directions>(grid[collapsedSlot->gridIndex + 1], Directions::top));

    if (((int)collapsedSlot->coordinates.Z) % sizeZ != 0)
        neighbours.Add(TPair<AJcoGridSlot*, Directions>(grid[collapsedSlot->gridIndex - 1], Directions::bottom));

    if (((int)collapsedSlot->coordinates.Y + 1) % sizeY != 0)
        neighbours.Add(TPair<AJcoGridSlot*, Directions>(grid[collapsedSlot->gridIndex + sizeZ], Directions::front));

    if (((int)collapsedSlot->coordinates.Y) % sizeY != 0)
        neighbours.Add(TPair<AJcoGridSlot*, Directions>(grid[collapsedSlot->gridIndex - sizeZ], Directions::back));

    if (((int)collapsedSlot->coordinates.X + 1) % sizeX != 0)
        neighbours.Add(TPair<AJcoGridSlot*, Directions>(grid[collapsedSlot->gridIndex + (sizeY * sizeZ)], Directions::right));

    if (((int)collapsedSlot->coordinates.X) % sizeX != 0)
        neighbours.Add(TPair<AJcoGridSlot*, Directions>(grid[collapsedSlot->gridIndex - (sizeY * sizeZ)], Directions::left));
}


bool AJcoGrid::isCollapsed()
{
    for (auto element : grid)
    {
        if (element->possibilities.Num() > 1)
            return false;
    }

    return true;
}

void AJcoGrid::Collapse()
{
    TArray<AJcoGridSlot*> collapsedSlots;

    while (!isCollapsed())
    {
        AJcoGridSlot* slot = nullptr;
        
        if(collapsedSlots.IsEmpty())
        {
            collapsedSlots.Add(getMinEnthropySlot());
            TRACE("min entropy slot found !")
        }

        slot = collapsedSlots.Pop();
        TRACE("slot found : %s", *slot->GetName())


        UJcoWFCPossibility* possibility = slot->possibilities[FMath::RandRange(0, slot->possibilities.Num() - 1)];
        TRACE("collapsed slot value : %s", *possibility->GetName());
        slot->possibilities.Empty();
        slot->possibilities.Add(possibility);

        Neighbours neighbours;
        getNeibourghs(slot, neighbours);
        //ajoute la notion de direction
        //ce sont les voisins qui réstreignent leurs possibilités en fonction du slot que l'on vient de collapse
        //je regarde les contraintes de direction du slot collapsed
        //tout ce qui n'en fait pas partie est retiré de mes possibilités

        PrintNeighbours(neighbours);

        for (auto neighbour : neighbours)
        {
            bool restricted = neighbour.Key->RestrictPossibilities(slot, neighbour.Value);
            if(restricted)
            {
                collapsedSlots.Add(neighbour.Key);
            }
        }
    }

    TRACE("Grid is fully collapsed !")
    
    DisplaySlots();
}

void AJcoGrid::DisplaySlots()
{
    for (auto slot : grid)
    {
        slot->Display();
    }
}


void AJcoGrid::Print()
{
    for (auto slot : grid)
    {
        slot->Print();
    }
}

void AJcoGrid::PrintNeighbours(Neighbours neighbours)
{
    for (auto n : neighbours)
    {
        if (n.Key != nullptr)
        {
            FString EnumAsString = UEnum::GetValueAsString(n.Value.GetValue());
            TRACE("neighbout %s direction %s", *n.Key->GetName(), *EnumAsString);
        }
    }
}
