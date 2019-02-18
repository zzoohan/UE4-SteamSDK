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
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get DLC Data", Keywords = "get all dlc steam sdk"))
		static bool GetAllDLCs(TArray<FSteamDLC>& allDLCs);

	/* Checks if a specific app is installed.
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is App Installed", Keywords = "is app program game installed downloaded steam sdk"))
		static bool isAppInstalled(int steamAppID);

	/*Checks if the user owns a specific DLC and if the DLC is installed
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is DLC Installed", Keywords = "is DLC installed downloaded steam sdk"))
		static bool isDlcInstalled(int steamAppID);

	// Checks whether the current App ID is for Cyber Cafes.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is Cybercafe", Keywords = "is in at cybercafe license app id steam sdk"))
		static bool isCybercafe();

	// Checks if the license owned by the user provides low violence depots.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is Low Violence", Keywords = "is low violence license depot steam sdk"))
		static bool isLowViolence();

	/* Gets the buildid of this app, may change at any time based on backend updates to the game.
Defaults to 0 if you're not running a build downloaded from steam.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Build Id", Keywords = "get build id steam sdk"))
		static int getBuildId();
	
	/* Gets the install folder for a specific AppID.
This works even if the application is not installed, based on where the game would be installed with the default Steam library location.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get App Install Dir", Keywords = "get install directory file location game program app steam sdk"))
		static FString getAppInstallDir(int32 steamAppId);
};
