// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SteamPlusBase.h"

#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/isteamappticket.h"

#include "SteamPlusAppTicket.generated.h"

UCLASS()
class TEMPTESTING_API USteamPlusAppTicket : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/* Checks if a specific app is installed.
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam App Ticket", meta = (DisplayName = "Get App Ownership Ticket Data", Keywords = "get app program game ownership ticket data steam sdk"))
		static void getAppOwnershipTicketData(/*The App to get the data for*/const int32 steamAppID, FSteamID64& steamID, FString& signature);

};