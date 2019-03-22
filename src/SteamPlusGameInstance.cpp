// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamPlusGameInstance.h"


// When the game starts up initialize steam
void USteamPlusGameInstance::Init()
{
	Super::Init();
	SteamAPI_Init();
	bpOnLaunchParametersPosted();
}

// When the game shuts down shutdown steam
void USteamPlusGameInstance::Shutdown()
{
	SteamAPI_Shutdown();
	Super::Shutdown();
}


/* Steam Apps Callbacks */

void USteamPlusGameInstance::onGameOverlayActivated(GameOverlayActivated_t* pCallback)
{
	bpOnGameOverlayToggled(pCallback->m_bActive);
}

void USteamPlusGameInstance::onDLCInstalled(DlcInstalled_t* pCallback)
{
	bpOnDLCInstalled(pCallback->m_nAppID);
}

void USteamPlusGameInstance::onLaunchParametersPosted(NewLaunchQueryParameters_t* pCallback)
{
	void bpOnLaunchParametersPosted();
}