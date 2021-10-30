// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JcoGridSlot.generated.h"

class UJcoWFCPossibility;

UCLASS()
class WFCPLAYGROUND_API AJcoGridSlot : public AActor
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this actor's properties
	AJcoGridSlot();

	void Print();

	UPROPERTY(VisibleAnywhere)
	int gridIndex = 0;

	UPROPERTY(VisibleAnywhere)
	FVector coordinates;

	UPROPERTY(VisibleAnywhere)
	TArray<UJcoWFCPossibility*> possibilities;
};
