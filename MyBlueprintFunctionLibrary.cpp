// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"


// Define Structs

// Contains data about a given DLC
USTRUCT(BlueprintType, Category = "Steam|Steam Apps")
struct FSteamDLC
{
	GENERATED_USTRUCT_BODY();

public:

	// Index of the DLC between 0 and the total amount of DLCs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		int32 DLCIndex;

	// The App ID of the DLC.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		int32 steamAppID;

	// Whether the DLC is currently available.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		bool isAvailable;

	// The name of the DLC by copying it into this buffer.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		FString DLCName;
};

// Define Functions
UCLASS()
class SHOOTER_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// Returns whether the Steam SDK is initialized and if not starts it up
	UFUNCTION(BlueprintCallable, Category = "Steam", meta = (DisplayName = "Is Steam Running", Keywords = "is steam api sdk cleint running launched initialize"))
		static bool IsSteamAPIRunning();
	
	// Checks if your executable was launched through Steam and relaunches it through Steam if it wasn't.
	UFUNCTION(BlueprintCallable, Category = "Steam", meta = (DisplayName = "Restart Through Steam", Keywords = "restart game through steam check running launched sdk"))
		static void RestartAppIfNecessary(const int32 SteamAppID);
	
	// Run any pending asynchronous callbacks. Best to run this function on Game State's tick
	UFUNCTION(BlueprintCallable, Category = "Steam", meta = (DisplayName = "Run Callbacks", Keywords = "run check refresh tick callbacks steam sdk"))
		static void RunCallbacks();


	/* ------------------------------------------------------------ ISteamApps ------------------------------------------------------------ */

	// Gets all registered DLCs and returns their metadata
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Apps", meta = (DisplayName = "Get DLC Data", Keywords = "run check refresh tick callbacks steam sdk"))
		static bool GetAllDLCs(TArray<FSteamDLC>& allDLCs);

	/*Checks if a specific app is installed.
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Apps", meta = (DisplayName = "Is App Installed", Keywords = "is app program game installed downloaded steam sdk"))
		static bool isAppInstalled(int steamAppID);
	
};
