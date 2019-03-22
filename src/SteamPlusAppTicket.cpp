// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamPlusAppTicket.h"

void USteamPlusAppTicket::getAppOwnershipTicketData(const int32 steamAppID, FSteamID64& steamID, FString& signature)
{
	if (SteamAPI_Init())
	{
		ISteamAppTicket* SteamAppTicket = (ISteamAppTicket*)SteamClient()->GetISteamGenericInterface(SteamAPI_GetHSteamUser(), SteamAPI_GetHSteamPipe(), STEAMAPPTICKET_INTERFACE_VERSION);
		const int k_bufferLength = 256;
		const int k_signatureLength = 128;
		char buffer[k_bufferLength];
		uint32 iAppID;
		uint32 iSteamID;
		uint32 iSignature;
		uint32 cbSignature;
		uint32 ret = SteamAppTicket->GetAppOwnershipTicketData(steamAppID, buffer, k_bufferLength, &iAppID, &iSteamID, &iSignature, &cbSignature);

		if (ret > 0)
		{
			CSteamID lsteamID;
			memcpy(&steamID, &buffer[iSteamID], sizeof(CSteamID));

			char lsignature[k_signatureLength];
			memcpy_s(lsignature, k_signatureLength, &buffer[iSignature], cbSignature);

			//FSteamID64 lSteamId;
			steamID.value = lsteamID.ConvertToUint64();
			//steamID = lsteamID;
			signature = lsignature;
		}
	}
}