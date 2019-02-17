// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	// Returns whether the Steam SDK is initialized and if not starts it up
	UFUNCTION(BlueprintPure, Category = "C++ Function Library|Online|Steam", meta = (DisplayName = "Is Steam Running", Keywords = "is steam api sdk cleint running launched"))
		static bool IsSteamAPIRunning();
	
};
