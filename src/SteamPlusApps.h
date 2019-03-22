// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SteamPlusBase.h"

#include "SteamPlusApps.generated.h"


UCLASS()
class TEMPTESTING_API USteamPlusApps : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/* ------------------------------------------------------------ ISteamApps ------------------------------------------------------------ */

	// Gets all registered DLCs and returns their metadata
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get DLC Data", Keywords = "get all dlc steam sdk"))
		static TArray<FSteamDLC> GetAllDLCs(bool& wasSuccessful);

	/* Checks if a specific app is installed.
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is App Installed", Keywords = "is app program game installed downloaded steam sdk"))
		static bool isAppInstalled(int32 steamAppID);

	/*Checks if the user owns a specific DLC and if the DLC is installed
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is DLC Installed", Keywords = "is DLC installed downloaded steam sdk"))
		static bool isDlcInstalled(int32 steamAppID);

	// Checks whether the current App ID is for Cyber Cafes.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is Cybercafe", Keywords = "is in at cybercafe license app id steam sdk"))
		static bool isCybercafe();

	// Checks if the license owned by the user provides low violence depots.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is Low Violence", Keywords = "is low violence license depot steam sdk"))
		static bool isLowViolence();

	/* Gets the buildid of this app, may change at any time based on backend updates to the game.
Defaults to 0 if you're not running a build downloaded from steam.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Build Id", Keywords = "get build id steam sdk"))
		static int32 getBuildId();

	/* Gets the install folder for a specific AppID.
This works even if the application is not installed, based on where the game would be installed with the default Steam library location.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get App Install Dir", Keywords = "get install directory file location game program app steam sdk"))
		static FString getAppInstallDir(int32 steamAppId);

	/* Gets the Steam ID of the original owner of the current app.
If it's different from the current user then it is borrowed.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get App Owner", Keywords = "get game program app owner user steam sdk"))
		static FSteamID64 getAppOwner();

	// Checks if the user is running from a beta branch, and returns the name of the branch if they are.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Selected Beta", Keywords = "get game program app owner user steam sdk"))
		static FString getSelectedBeta(bool & isOnBranch);

	/*Gets the current language that the user has set as preferred.
This falls back to the Steam UI language if the user hasn't explicitly picked a language for the title.
This will comply to the language codes here: https://partner.steamgames.com/doc/store/localization#supported_languages */
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Preferred Language", Keywords = "get game program app preferred selected chosen language localization country user steam sdk"))
		static FString getPreferredLanguage();

	/*Gets the download progress for optional DLC in MegaBytes.
Defaults to 0 if the DLC does not exist or isn't downloading.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get DLC Download Progress", Keywords = "get dlc download progress steam sdk"))
		static void getDLCDownloadProgress(const int32 steamAppId, float& mbDownloaded, float& totalMB);

	/*Gets the time of purchase of the specified app in Unix epoch format.
Steam is not clear on this, however I believe that this is the date for the first purchase, so a refund and then re-purchase will not modify it.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Original Purchase Date", Keywords = "get app program game original earliest purchase buy date steam sdk"))
		static int32 getOriginalPurchaseDate(const int32 steamAppId);

	/*Gets the value for the launch parameter with the given key if the game is run via steam://run/<appid>/?param1=value1;param2=value2;param3=value3 etc.
Keys beginning with @ or _ should not be used.
Will default to an empty string if the key does not exist.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Launch Parameter", Keywords = "get app program game launch parameter query key value date steam sdk"))
		static FString getLaunchQueryParam(const FString key);

	// Starts installing the given DLC.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Apps", meta = (DisplayName = "Install DLC", Keywords = "install dlc start download content steam sdk"))
		static void installDLC(const int32 steamAppId);

	/*Allows you to force verify game content on next launch.
If you detect the game is out-of-date (for example, by having the client detect a version mismatch with a server),
you can call use MarkContentCorrupt to force a verify, show a message to the user, and then quit.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Mark Content Corrupt", Keywords = "mark content dlc program app files corrupt outdated old steam sdk"))
		static bool markContentCorrupt(const bool missingFilesOnly);

	// Will ask steam to start uninstalling the DLC at the given app ID
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Apps", meta = (DisplayName = "Uninstall DLC", Keywords = "uninstall delete remove dlc steam sdk"))
		static void uninstallDLC(int32 appID);

};