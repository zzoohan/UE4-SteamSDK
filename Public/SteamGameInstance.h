// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

#include "SteamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USteamGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	// Called whenever the overlay is opened or closed
	UFUNCTION(BlueprintImplementableEvent, Category = "Steam|Steam Apps", meta = (DisplayName = "On Game Overlay Toggled", Keywords = "on when game overlay toggled opened closed activated steam sdk"))
		void bpOnGameOverlayToggled(bool isOpen);
	//virtual void bpOnGameOverlayToggled_Implementation(bool isOpen);

	//void onGameOverlayToggled(GameOverlayActivated_t* pCallback);
private:

	STEAM_CALLBACK(USteamGameInstance, OnGameOverlayActivated, GameOverlayActivated_t);
	
};
