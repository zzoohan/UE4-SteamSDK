
#pragma once


#include "Net/OnlineBlueprintCallProxyBase.h"

#include "SteamPlusBase.h"

#include "GetFollowedUsersCallback.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFollowedUsersDelegate, const TArray<FSteamID64> &, FollowedUsers);


UCLASS(MinimalAPI)
class UGetFollowedUsersProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

public:
	
	/* Gets the list of users that the current user is following.
You can be following people that are not your friends. Following allows you to receive updates when the person does things like post a new piece of content to the Steam Workshop.*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Steam|Steam Friends")
		UGetFollowedUsersProxy* getFollowedUsers(UObject* WorldContextObject, class APlayerController* PlayerController, int32 MaxResults, bool bUseLAN);
	
	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface
	
	// Called when there is a successful results return
	UPROPERTY(BlueprintAssignable)
		FFollowedUsersDelegate OnSuccess;

	// Called when there is an unsuccessful results return
	UPROPERTY(BlueprintAssignable)
		FFollowedUsersDelegate OnFailure;

private:

	void OnFriendsEnumerateFollowingList(FriendsEnumerateFollowingList_t *pCallback, bool bIOFailure);

	// Internal callback when the session search completes, calls out to the public success/failure callbacks
	void OnCompleted(bool bSuccess);

	// The player controller triggering things
	//TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;

	// The delegate executed by the online subsystem
	//FOnGetFollowedUsersCompleteDelegate Delegate;

	// Handle to the registered OnFindSessionsComplete delegate
	FDelegateHandle DelegateHandle;

	// Object to track search results
	//TSharedPtr<FOnlineSessionSearch> SearchObject;

	// Whether or not to search LAN
	//bool bUseLAN;

	// Maximum number of results to return
	//int MaxResults;

	// The number of followers that we have retrieved so far - if this is lower than the total amount of followers then we have some further work to do
	int followersParsed;

	// The array of all followers that will be returned
	TArray<FSteamID64> allFollowers;

	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	CCallResult< UGetFollowedUsersProxy, FriendsEnumerateFollowingList_t > m_SteamCallResultFriendsEnumerateFollowingList;
};