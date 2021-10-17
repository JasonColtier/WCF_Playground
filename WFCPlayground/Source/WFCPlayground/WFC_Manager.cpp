// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/WFC_Manager.h"
#include "WCF3D.h"

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

	solve3D();
}

// Called every frame
void AWFC_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

