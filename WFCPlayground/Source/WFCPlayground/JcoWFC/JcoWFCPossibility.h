// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JcoWFCPossibility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)

class WFCPLAYGROUND_API UJcoWFCPossibility : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FString AssetName;

    UPROPERTY(EditAnywhere)
    bool symetryX;

    UPROPERTY(EditAnywhere)
    bool symetryY;

    UPROPERTY(EditAnywhere)
    bool symetryZ;

    UPROPERTY(EditAnywhere)
    TArray<UJcoWFCPossibility*> possibilities_left;

    UPROPERTY(EditAnywhere)
    TArray<UJcoWFCPossibility*> possibilities_right;

    UPROPERTY(EditAnywhere)
    TArray<UJcoWFCPossibility*> possibilities_front;

    UPROPERTY(EditAnywhere)
    TArray<UJcoWFCPossibility*> possibilities_back;

    UPROPERTY(EditAnywhere)
    TArray<UJcoWFCPossibility*> possibilities_top;

    UPROPERTY(EditAnywhere)
    TArray<UJcoWFCPossibility*> possibilities_bottom;
};
