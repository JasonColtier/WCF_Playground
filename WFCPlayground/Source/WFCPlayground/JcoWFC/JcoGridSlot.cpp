// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCPlayground/JcoWFC/JcoGridSlot.h"
#include "WFCPlayground/TRACE.h"

// Sets default values
AJcoGridSlot::AJcoGridSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AJcoGridSlot::Print()
{
	TRACE("print grid slot : index = %d",gridIndex);
}

