// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"

// Include Steam SDK
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

// Start up the steam service
//SteamAPI_Init();

/*FString UMyBlueprintFunctionLibrary::cSteamIdToString(const FSteamID64& SteamID64)
{
	return FString::Printf(TEXT("%llu"), SteamID64.value.ConvertToUint64());
}

FSteamID64 UMyBlueprintFunctionLibrary::stringToSteamId(const FString& SteamID64)
{
	uint64 i64 = 0;
	int convCount = sscanf_s(TCHAR_TO_ANSI(*SteamID64), "%llu", &i64);
	return CSteamID(i64);
}*/

FSteamID64 UMyBlueprintFunctionLibrary::stringToFSteamId(const FString& String)
{
	FSteamID64 SteamId;
	uint64 i64 = 0;
	int temp = sscanf_s(TCHAR_TO_ANSI(*String), "%llu", &i64);
	SteamId.value = i64;
	return SteamId;
}

FString UMyBlueprintFunctionLibrary::fSteamIdToFString(const FSteamID64& steamID)
{
	return FString::Printf(TEXT("%llu"), steamID.value);
}

static CSteamID fSteamIdToCSteamId(const FSteamID64& steamID);
CSteamID fSteamIdToCSteamId(const FSteamID64& steamID)
{
	return steamID.value;
}

static uint64 fSteamIdToUint64(const FSteamID64& steamID);
uint64 fSteamIdToUint64(const FSteamID64& steamID)
{
	return steamID.value;
}

static FSteamID64 uintToFSteamId(const uint64& theint);
FSteamID64 uintToFSteamId(const uint64& theint)
{
	FSteamID64 SteamId;
	SteamId.value = theint;
	return SteamId;
}

static FSteamID64 cSteamIdToFSteamId(const CSteamID& Id);
FSteamID64 cSteamIdToFSteamId(const CSteamID& Id)
{
	FSteamID64 SteamId;
	SteamId.value = Id.ConvertToUint64();
	return SteamId;
}

/*FSteamID64 UMyBlueprintFunctionLibrary::uint32ToFSteamId(const int32& low, const int32& mid, const int32& high) {
	FSteamID64 SteamId;
	// Thank you https://github.com/Daekesh/KeshUE4FundamentalTypeWrapperPlugin/blob/master/Source/KeshUE4FundamentalTypeWrapperPlugin/Classes/KeshUE4FundamentalTypeWrapperPlugin/KeshUE4FundamentalTypeWrapper.h#LC64
	uint64 i64 = static_cast<uint64>(abs(Low) > 0 ? abs(Low) : 0) +
		(static_cast<uint64>(abs(Mid) > 0 ? abs(Mid) : 0) << 31) +
		(static_cast<uint64>((abs(High) > 0 ? abs(High) : 0) & 3) << 62);
	SteamId.value = i64;
	return SteamId;
}

void UMyBlueprintFunctionLibrary::fSteamIdToUint32(const FSteamID64 SteamId, int32& low, int32& high) {
	uint64 i64 = SteamId.value;
	low = (u32)((i64 & 0xFFFFFFFF00000000LL) >> 32);
	high = (u32)(v & 0xFFFFFFFFLL);
	low = 0;
	high = 0;
}*/

// BP Functions

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
	if (SteamAPI_Init())
	{
		SteamAPI_RunCallbacks();
	}
}

/* ------------------------------------------------------------ ISteamApps ------------------------------------------------------------ */

TArray<FSteamDLC> UMyBlueprintFunctionLibrary::GetAllDLCs(bool& wasSuccessful)
{
	TArray<FSteamDLC> allDLCs;
	if (!SteamAPI_Init())
	{
		wasSuccessful = false;
		return allDLCs;
	}
	wasSuccessful = true;
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
			allDLCs[i].DLCName = FString(UTF8_TO_TCHAR(name));
		}
		else
		{
			wasSuccessful = false;
		}
	}
	return allDLCs;
}

bool UMyBlueprintFunctionLibrary::isAppInstalled(const int32 steamAppID = 480)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsAppInstalled(steamAppID);
}

bool UMyBlueprintFunctionLibrary::isDlcInstalled(const int32 steamAppID)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsDlcInstalled(steamAppID);
}

bool UMyBlueprintFunctionLibrary::isCybercafe() {
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsCybercafe();
}

bool UMyBlueprintFunctionLibrary::isLowViolence()
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsLowViolence();
}

int UMyBlueprintFunctionLibrary::getBuildId()
{
	if (!SteamAPI_Init())
	{
		return 0;
	}
	return SteamApps()->GetAppBuildId();
}

FString UMyBlueprintFunctionLibrary::getAppInstallDir(const int32 steamAppId)
{
	if (!SteamAPI_Init())
	{
		return TEXT("");
	}
	char directory[128];
	SteamApps()->GetAppInstallDir(steamAppId, directory, 128);
	return FString(UTF8_TO_TCHAR(directory));
}

FSteamID64 UMyBlueprintFunctionLibrary::getAppOwner()
{
	FSteamID64 SteamID;
	if (SteamAPI_Init())
	{
		SteamID.value = SteamApps()->GetAppOwner().ConvertToUint64();
	}
	return SteamID;
}

FString UMyBlueprintFunctionLibrary::getSelectedBeta(bool& isOnBranch)
{
	char betaName[512];
	if (!SteamAPI_Init())
	{
		isOnBranch = false;
		return TEXT("");
	}
	else
	{
		isOnBranch = SteamApps()->GetCurrentBetaName(betaName, 512);
		return FString(UTF8_TO_TCHAR(betaName));
	}
}

FString UMyBlueprintFunctionLibrary::getPreferredLanguage()
{
	if (!SteamAPI_Init())
	{
		return TEXT("");
	}
	return FString(UTF8_TO_TCHAR(SteamApps()->GetCurrentGameLanguage()));
}

void UMyBlueprintFunctionLibrary::getDLCDownloadProgress(const int32 steamAppId, float& mbDownloaded, float& totalMB)
{
	mbDownloaded = 0;
	totalMB = 0;
	if (SteamAPI_Init())
	{
		const int32 mb = 1048576;
		uint64 bytesDownloaded, totalBytes;
		SteamApps()->GetDlcDownloadProgress(steamAppId, &bytesDownloaded, &totalBytes);

		//Convert Bytes to MB (as we only have 32 bits available)
		mbDownloaded = (float)bytesDownloaded / (float)mb;
		totalMB = (float)bytesDownloaded / (float)mb;
	}
}

int32 UMyBlueprintFunctionLibrary::getOriginalPurchaseDate(const int32 steamAppId)
{
	if (!SteamAPI_Init())
	{
		return 0;
	}
	return SteamApps()->GetEarliestPurchaseUnixTime(steamAppId);
}

FString UMyBlueprintFunctionLibrary::getLaunchQueryParam(const FString key)
{
	if (!SteamAPI_Init())
	{
		return TEXT("");
	}
	return SteamApps()->GetLaunchQueryParam(TCHAR_TO_UTF8(*key));
}

void UMyBlueprintFunctionLibrary::installDLC(const int32 steamAppId)
{
	if (SteamAPI_Init())
	{
		SteamApps()->InstallDLC(steamAppId);
	}
}

bool UMyBlueprintFunctionLibrary::markContentCorrupt(const bool missingFilesOnly)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->MarkContentCorrupt(missingFilesOnly);
}

void UMyBlueprintFunctionLibrary::uninstallDLC(int32 appID)
{
	if (SteamAPI_Init())
	{
		SteamApps()->UninstallDLC(appID);
	}
}