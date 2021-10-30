// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "sstream"
#include "GameFramework/Actor.h"
#include "WFC_Manager.generated.h"


class AJcoGrid;

UCLASS()
class WFCPLAYGROUND_API AWFC_Manager : public AActor
{
	GENERATED_BODY()

	void GenerateWFC();
	
public:	
	// Sets default values for this actor's properties
	AWFC_Manager();

	//la taille de ma génération procédurale

	UPROPERTY(EditDefaultsOnly,Category = "WFC")
	TSubclassOf<AJcoGrid> gridClass;
	
	AJcoGrid* grid;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
