// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "JcoEDirection.generated.h"


UENUM()
enum Directions
{
	left       UMETA(DisplayName = "left"),
	right      UMETA(DisplayName = "right"),
	front      UMETA(DisplayName = "front"),
	back       UMETA(DisplayName = "back"),
	top        UMETA(DisplayName = "top"),
	bottom     UMETA(DisplayName = "bottom"),
};
