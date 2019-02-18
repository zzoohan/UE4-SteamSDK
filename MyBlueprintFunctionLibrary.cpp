// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"

// Include Steam SDK
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

bool UMyBlueprintFunctionLibrary::IsSteamAPIRunning()
{
	return SteamAPI_Init();
}

void UMyBlueprintFunctionLibrary::RestartAppIfNecessary(const int32 SteamAppID = 480)
{
	// Since we can only run a game through steam on a shipping build, this function should do nothing if it isn't a shipping build
	#if UE_BUILD_SHIPPING
	if (SteamAPI_RestartAppIfNecessary(SteamAppID))
	{
		FGenericPlatformMisc::RequestExit(true);
	}
	#endif
}

void UMyBlueprintFunctionLibrary::RunCallbacks()
{
	SteamAPI_RunCallbacks();
}

/* ------------------------------------------------------------ ISteamApps ------------------------------------------------------------ */

bool UMyBlueprintFunctionLibrary::GetAllDLCs(TArray<FSteamDLC>& allDLCs)
{
	bool wasSuccessful = true;
	// Get the total number of DLCs and iterate through them
	int32 DLCCount = SteamApps()->GetDLCCount();
	for (int i = 0; i < DLCCount; ++i)
	{
		// Request DLC at index i
		AppId_t appId;
		bool available;
		char name[128];

		// Run Query. If it was successful add it to the array to be returned, otherwise make sure we tell the user it was unsuccessful
		if (SteamApps()->BGetDLCDataByIndex(i, &appId, &available, name, 128))
		{
			allDLCs[i].DLCIndex = i;
			allDLCs[i].steamAppID = appId;
			allDLCs[i].isAvailable = available;
			allDLCs[i].DLCName = name;
		} else
		{
			wasSuccessful = false;
		}
	}
	return wasSuccessful;
}

bool UMyBlueprintFunctionLibrary::isAppInstalled(int steamAppID = 480)
{
	return SteamApps()->BIsAppInstalled(steamAppID);
}

bool UMyBlueprintFunctionLibrary::isDlcInstalled(int steamAppID)
{
	return SteamApps()->BIsDlcInstalled(steamAppID);
}

bool UMyBlueprintFunctionLibrary::isCybercafe() {
	return SteamApps()->BIsCybercafe();
}

bool UMyBlueprintFunctionLibrary::isLowViolence()
{
	return SteamApps()->BIsLowViolence();
}

int UMyBlueprintFunctionLibrary::getBuildId()
{
	return SteamApps()->GetAppBuildId();
}

FString UMyBlueprintFunctionLibrary::getAppInstallDir(int32 steamAppId)
{
	char directory[128];
	//SteamApps()->GetAppInstallDir(steamAppId, directory, 128);
	return directory;
}
