// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamGameInstance.h"

//#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"


void USteamGameInstance::OnGameOverlayActivated(GameOverlayActivated_t* pCallback)
{
	bpOnGameOverlayToggled(pCallback->m_bActive);
}

//void USteamGameInstance::bpOnGameOverlayToggled_Implementation(bool isOpen)
//{
//}



