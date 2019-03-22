// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamPlusFriends.h"

void USteamPlusFriends::activateSteamOverlay(const ESteamOverlayDialog dialogToOpenTo)
{
	if (SteamAPI_Init())
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESteamOverlayDialog"), true);
		if (EnumPtr)
		{
			
			SteamFriends()->ActivateGameOverlay(TCHAR_TO_ANSI(*EnumPtr->GetNameStringByValue((int64)dialogToOpenTo)));
		}
	}
}

void USteamPlusFriends::activateSteamOverlayToInvite(const FSteamID64 lobbyToInviteTo)
{
	if (SteamAPI_Init())
	{
		SteamFriends()->ActivateGameOverlayInviteDialog(lobbyToInviteTo.value);
	}
}

void USteamPlusFriends::activateSteamOverlayToUser(const ESteamFriendOverlayDialog dialog, const FSteamID64 friendID)
{
	if (SteamAPI_Init())
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESteamFriendOverlayDialog"), true);
		if (EnumPtr)
		{
			SteamFriends()->ActivateGameOverlayToUser(TCHAR_TO_ANSI(*EnumPtr->GetNameStringByValue((int64)dialog)), friendID.value);
		}
	}
}

void USteamPlusFriends::activateSteamOverlayToWebsite(const FString url)
{
	if (SteamAPI_Init())
	{
		SteamFriends()->ActivateGameOverlayToWebPage(TCHAR_TO_ANSI(*url));
	}
}

void USteamPlusFriends::clearRichPresence()
{
	if (SteamAPI_Init())
	{
		SteamFriends()->ClearRichPresence();
	}
}

bool USteamPlusFriends::closeClanChatWindow(const FSteamID64 steamID)
{
	if (!SteamAPI_Init())
	{
		return false;
	}
	return SteamFriends()->CloseClanChatWindowInSteam(steamID.value);
}

/*void USteamPlusFriends::getFollowedUsers(FOnGetFollowedUsersSuccess onSuccess)
{
	if (!SteamAPI_Init())
	{
		return;
	}
	onFollowersEnumerateSuccess = onSuccess;
	m_nFollowersParsed = 0;
	l_FollowedUsers.Empty();

	SteamAPICall_t handle = SteamFriends()->EnumerateFollowingList(0);
	m_SteamCallResultFriendsEnumerateFollowingList.Set(handle, this, &USteamPlusFriends::onFriendsEnumerateFollowingList);
}

void USteamPlusFriends::onFriendsEnumerateFollowingList(FriendsEnumerateFollowingList_t *pCallback, bool bIOFailure)
{
	if (pCallback->m_eResult != k_EResultOK || bIOFailure)
	{
		// Failure!
		return;
	}
	for (int i = 0; i < pCallback->m_nResultsReturned; ++i)
	{
		// Create a new steam id, fill it with data from the callback and then add it to the array
		FSteamID64 tempID;
		tempID.value = pCallback->m_rgSteamID[i].ConvertToUint64();
		l_FollowedUsers.Add(tempID);
	}

	m_nFollowersParsed += pCallback->m_nResultsReturned;

	// There are more followers! Gets the next set of them!
	if (m_nFollowersParsed < pCallback->m_nTotalResultCount)
	{
		SteamAPICall_t handle = SteamFriends()->EnumerateFollowingList(pCallback->m_nResultsReturned);
		m_SteamCallResultFriendsEnumerateFollowingList.Set(handle, this, &USteamPlusFriends::onFriendsEnumerateFollowingList);
	}
	else
	{
		//onFollowersEnumerateSuccess = NULL;
		m_nFollowersParsed = 0;
		l_FollowedUsers.Empty();

		onFollowersEnumerateSuccess.ExecuteIfBound(l_FollowedUsers);
	}
}*/

TArray<FSteamID64> USteamPlusFriends::getAllChatMembers(const FSteamID64& chatID)
{
	TArray<FSteamID64> chatMembers;
	if (SteamAPI_Init())
	{
		int numMembers = SteamFriends()->GetClanChatMemberCount(chatID.value);

		for (int i = 0; i < numMembers; ++i)
		{
			FSteamID64 tempID;
			tempID.value = SteamFriends()->GetChatMemberByIndex(chatID.value, i).ConvertToUint64();
			chatMembers.Add(tempID);
		}
	}
	return chatMembers;
}

bool USteamPlusFriends::getGroupActivityCounts(const FSteamID64& groupID, int32& numOnline, int32& numInGame, int32& numChatting)
{
	if (SteamAPI_Init())
	{
		if (SteamFriends()->GetClanActivityCounts(groupID.value, &numOnline, &numInGame, &numChatting))
		{
			return true;
		}
	}
	return false;
}

TArray<FSteamGroup> USteamPlusFriends::getAllSteamGroups()
{
	TArray<FSteamGroup> allClans;

	if (SteamAPI_Init())
	{
		int numClans = SteamFriends()->GetClanCount();

		// Get the number of clans, then add each clan to the array.
		for (int i = 0; i < numClans; ++i)
		{
			FSteamGroup thisClan;
			thisClan.id = SteamFriends()->GetClanByIndex(i).ConvertToUint64();
			thisClan.index = i;
			thisClan.name = ANSI_TO_TCHAR(SteamFriends()->GetClanName(thisClan.id.value));
			thisClan.tag = ANSI_TO_TCHAR(SteamFriends()->GetClanTag(thisClan.id.value));
			allClans.Add(thisClan);
		}
	}

	return allClans;
}

int32 USteamPlusFriends::getNumChatMembers(FSteamID64 chatID)
{
	if (!SteamAPI_Init()) {
		return 0;
	}
	return SteamFriends()->GetClanChatMemberCount(chatID.value);
}

/*FSteamMessage USteamPlusFriends::onChatMessageRecieved(p_GameConnectedClanChatMsg_t) {
	char[8292] messageText;
	EChatEntryType messageType;
	CSteamID senderID;
	GetClanChatMessage(p_GameConnectedClanChatMsg_t->m_steamIDClanChat, p_GameConnectedClanChatMsg_t->m_iMessageID, &messageText, 8293, &messageType, &senderID);
}
*/