// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamPlusBase.h"



FSteamID64 USteamPlusBase::stringToFSteamId(const FString& String)
{
	FSteamID64 SteamId;
	uint64 i64 = 0;
	int temp = sscanf_s(TCHAR_TO_ANSI(*String), "%llu", &i64);
	SteamId.value = i64;
	return SteamId;
}

FString USteamPlusBase::fSteamIdToFString(const FSteamID64& steamID)
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

/*FSteamID64 USteamPlusBase::uint32ToFSteamId(const int32& low, const int32& mid, const int32& high) {
	FSteamID64 SteamId;
	// Thank you https://github.com/Daekesh/KeshUE4FundamentalTypeWrapperPlugin/blob/master/Source/KeshUE4FundamentalTypeWrapperPlugin/Classes/KeshUE4FundamentalTypeWrapperPlugin/KeshUE4FundamentalTypeWrapper.h#LC64
	uint64 i64 = static_cast<uint64>(abs(Low) > 0 ? abs(Low) : 0) +
		(static_cast<uint64>(abs(Mid) > 0 ? abs(Mid) : 0) << 31) +
		(static_cast<uint64>((abs(High) > 0 ? abs(High) : 0) & 3) << 62);
	SteamId.value = i64;
	return SteamId;
}

void USteamPlusBase::fSteamIdToUint32(const FSteamID64 SteamId, int32& low, int32& high) {
	uint64 i64 = SteamId.value;
	low = (u32)((i64 & 0xFFFFFFFF00000000LL) >> 32);
	high = (u32)(v & 0xFFFFFFFFLL);
	low = 0;
	high = 0;
}*/

// BP Functions

bool USteamPlusBase::IsSteamAPIRunning()
{
	return SteamAPI_Init();
}

void USteamPlusBase::RestartAppIfNecessary(const int32 SteamAppID = 480)
{
	// Since we can only run a game through steam on a shipping build, this function should do nothing if it isn't a shipping build
#if UE_BUILD_SHIPPING
	if (SteamAPI_RestartAppIfNecessary(SteamAppID))
	{
		FGenericPlatformMisc::RequestExit(true);
	}
#endif
}

void USteamPlusBase::RunCallbacks()
{
	if (SteamAPI_Init())
	{
		SteamAPI_RunCallbacks();
	}
}

void USteamPlusBase::shutdownSteam()
{
	if (SteamAPI_Init())
	{
		SteamAPI_Shutdown();
	}
}
