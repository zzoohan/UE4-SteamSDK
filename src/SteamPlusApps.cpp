// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamPlusApps.h"


TArray<FSteamDLC> USteamPlusApps::GetAllDLCs(bool& wasSuccessful)
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

bool USteamPlusApps::isAppInstalled(const int32 steamAppID = 480)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsAppInstalled(steamAppID);
}

bool USteamPlusApps::isDlcInstalled(const int32 steamAppID)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsDlcInstalled(steamAppID);
}

bool USteamPlusApps::isCybercafe() {
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsCybercafe();
}

bool USteamPlusApps::isLowViolence()
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->BIsLowViolence();
}

int32 USteamPlusApps::getBuildId()
{
	if (!SteamAPI_Init())
	{
		return 0;
	}
	return SteamApps()->GetAppBuildId();
}

FString USteamPlusApps::getAppInstallDir(const int32 steamAppId)
{
	if (!SteamAPI_Init())
	{
		return TEXT("");
	}
	char directory[128];
	SteamApps()->GetAppInstallDir(steamAppId, directory, 128);
	return FString(UTF8_TO_TCHAR(directory));
}

FSteamID64 USteamPlusApps::getAppOwner()
{
	FSteamID64 SteamID;
	if (SteamAPI_Init())
	{
		SteamID.value = SteamApps()->GetAppOwner().ConvertToUint64();
	}
	return SteamID;
}

FString USteamPlusApps::getSelectedBeta(bool& isOnBranch)
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

FString USteamPlusApps::getPreferredLanguage()
{
	if (!SteamAPI_Init())
	{
		return TEXT("");
	}
	return FString(UTF8_TO_TCHAR(SteamApps()->GetCurrentGameLanguage()));
}

void USteamPlusApps::getDLCDownloadProgress(const int32 steamAppId, float& mbDownloaded, float& totalMB)
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

int32 USteamPlusApps::getOriginalPurchaseDate(const int32 steamAppId)
{
	if (!SteamAPI_Init())
	{
		return 0;
	}
	return SteamApps()->GetEarliestPurchaseUnixTime(steamAppId);
}

FString USteamPlusApps::getLaunchQueryParam(const FString key)
{
	if (!SteamAPI_Init())
	{
		return TEXT("");
	}
	return SteamApps()->GetLaunchQueryParam(TCHAR_TO_UTF8(*key));
}

void USteamPlusApps::installDLC(const int32 steamAppId)
{
	if (SteamAPI_Init())
	{
		SteamApps()->InstallDLC(steamAppId);
	}
}

bool USteamPlusApps::markContentCorrupt(const bool missingFilesOnly)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamApps()->MarkContentCorrupt(missingFilesOnly);
}

void USteamPlusApps::uninstallDLC(int32 appID)
{
	if (SteamAPI_Init())
	{
		SteamApps()->UninstallDLC(appID);
	}
}