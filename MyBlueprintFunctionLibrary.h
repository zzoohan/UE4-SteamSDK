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
	
public:

	// Returns whether the Steam SDK is initialized and if not starts it up
	UFUNCTION(BlueprintCallable, Category = "C++ Function Library|Online|Steam", meta = (DisplayName = "Is Steam Running", Keywords = "is steam api sdk cleint running launched"))
		static bool IsSteamAPIRunning();
	
	// If the game is not running through steam it will restart the game through steam
	UFUNCTION(BlueprintCallable, Category = "C++ Function Library|Online|Steam", meta = (DisplayName = "Restart Through Steam", Keywords = "restart game through steam check running launched sdk"))
		static void RestartAppIfNecessary(int32 AppID);
	
	// Run any pending asynchronous callbacks. Best to run this function on Game State's tick
	UFUNCTION(BlueprintCallable, Category = "C++ Function Library|Online|Steam", meta = (DisplayName = "Run Callbacks", Keywords = "run check refresh tick callbacks steam sdk"))
		static void RunCallbacks();
	
};
