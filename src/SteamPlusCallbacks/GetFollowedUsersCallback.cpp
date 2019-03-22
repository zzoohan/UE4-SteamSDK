#include "GetFollowedUsersCallback.h"

// Steam SDK
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

UGetFollowedUsersProxy::UGetFollowedUsersProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	//, Delegate(FOnGetFollowedUsersCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
	//, bUseLAN(false)
{
}

UGetFollowedUsersProxy* UGetFollowedUsersProxy::getFollowedUsers(UObject* WorldContextObject, class APlayerController* PlayerController, int MaxResults, bool bUseLAN)
{
	UGetFollowedUsersProxy* Proxy = NewObject<UGetFollowedUsersProxy>();
	//Proxy->PlayerControllerWeakPtr = PlayerController;
	//Proxy->bUseLAN = bUseLAN;
	//Proxy->MaxResults = MaxResults;
	//Proxy->WorldContextObject = WorldContextObject;
	Proxy->allFollowers.Empty();
	Proxy->followersParsed = 0;
	return Proxy;
}

void UGetFollowedUsersProxy::Activate()
{
	// Reset all variables
	//allFollowers.Empty();
	//followersParsed = 0;

	if (!SteamAPI_Init())
	{
		// Fail immediately
		OnFailure.Broadcast(allFollowers);
		return;
	}

	SteamAPICall_t handle = SteamFriends()->EnumerateFollowingList(0);
	m_SteamCallResultFriendsEnumerateFollowingList.Set(handle, this, &UGetFollowedUsersProxy::OnFriendsEnumerateFollowingList);
	// Callback will get called on completion


	//----------------------- 
	/*
	FOnlineSubsystemBPCallHelper Helper(TEXT("FindSessions"), WorldContextObject);
	Helper.QueryIDFromPlayerController(PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		auto Sessions = Helper.OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			DelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(Delegate);

			SearchObject = MakeShareable(new FOnlineSessionSearch);
			SearchObject->MaxSearchResults = MaxResults;
			SearchObject->bIsLanQuery = bUseLAN;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

			Sessions->FindSessions(*Helper.UserID, SearchObject.ToSharedRef());

			// OnQueryCompleted will get called, nothing more to do now
			return;
		}
		else
		{
			FFrame::KismetExecutionMessage(TEXT("Sessions not supported by Online Subsystem"), ELogVerbosity::Warning);
		}
	}*/

}

void UGetFollowedUsersProxy::OnFriendsEnumerateFollowingList(FriendsEnumerateFollowingList_t *pCallback, bool bIOFailure)
{
	if (pCallback->m_eResult != k_EResultOK || bIOFailure)
	{
		// Failure!
		OnFailure.Broadcast(allFollowers);
		return;
	}
	for (int i = 0; i < pCallback->m_nResultsReturned; ++i)
	{
		// Create a new steam id, fill it with data from the callback and then add it to the array
		FSteamID64 tempID;
		tempID.value = pCallback->m_rgSteamID[i].ConvertToUint64();
		allFollowers.Add(tempID);
	}

	followersParsed += pCallback->m_nResultsReturned;

	// There are more followers! Gets the next set of them!
	if (followersParsed < pCallback->m_nTotalResultCount)
	{
		SteamAPICall_t handle = SteamFriends()->EnumerateFollowingList(pCallback->m_nResultsReturned);
		m_SteamCallResultFriendsEnumerateFollowingList.Set(handle, this, &UGetFollowedUsersProxy::OnFriendsEnumerateFollowingList);
	}
	else
	{
		//followersParsed = 0;
		//allFollowers.Empty();

		OnSuccess.Broadcast(allFollowers);
	}

	//----------------------- 
	/*

	FOnlineSubsystemBPCallHelper Helper(TEXT("FindSessionsCallback"), WorldContextObject);
	Helper.QueryIDFromPlayerController(PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		auto Sessions = Helper.OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(DelegateHandle);
		}
	}

	TArray<FSteamID64> Results;

	if (bSuccess && SearchObject.IsValid())
	{
		for (auto& Result : SearchObject->SearchResults)
		{
			FBlueprintSessionResult BPResult;
			BPResult.OnlineResult = Result;
			Results.Add(BPResult);
		}

		OnSuccess.Broadcast(Results);
	}
	else
	{
		OnFailure.Broadcast(Results);
	}*/
}