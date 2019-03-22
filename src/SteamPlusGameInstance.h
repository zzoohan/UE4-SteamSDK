// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Steam SDK
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

#include "SteamPlusGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class TEMPTESTING_API USteamPlusGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	virtual void Shutdown() override;


	/* Steam Apps Callbacks */

	// Called whenever the overlay is opened or closed
	UFUNCTION(BlueprintImplementableEvent, Category = "Steam|Steam Apps", meta = (DisplayName = "On Game Overlay Toggled", Keywords = "on when game overlay toggled opened closed activated steam sdk"))
		void bpOnGameOverlayToggled(bool isOpen);

	// Triggered after the current user gains ownership of DLC and that DLC is installed.
	UFUNCTION(BlueprintImplementableEvent, Category = "Steam|Steam Apps", meta = (DisplayName = "On DLC Installed", Keywords = "on when dlc installed downloaded steam sdk"))
		void bpOnDLCInstalled(/*The App Id of the DLC to be installed*/int32 appId);

	/* Posted after the user executes a steam url with query parameters such as steam://run/<appid>//?param1=value1;param2=value2;param3=value3; while the game is already running.
You can then use Get Launch Parameters function to retrieve them.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Steam|Steam Apps", meta = (DisplayName = "On Launch Parameters Posted", Keywords = "on when launch parameters posted url web steam sdk"))
		void bpOnLaunchParametersPosted();

private:

	/* Steam Apps Callbacks */

	//void onGameOverlayActivated(GameOverlayActivated_t* pCallback);

	//void onDLCInstalled(DlcInstalled_t* pCallback);

	//void onLaunchParametersPosted(NewLaunchQueryParameters_t* pCallback);

	STEAM_CALLBACK(USteamPlusGameInstance, onGameOverlayActivated, GameOverlayActivated_t);

	STEAM_CALLBACK(USteamPlusGameInstance, onDLCInstalled, DlcInstalled_t);

	STEAM_CALLBACK(USteamPlusGameInstance, onLaunchParametersPosted, NewLaunchQueryParameters_t);

	//STEAM_CALLBACK(USteamPlusGameInstance, onDLCInstalled, DlcInstalled_t);
	
};
