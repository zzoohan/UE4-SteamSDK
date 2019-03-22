// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SteamPlusBase.h"
// Steam SDK
#include "ThirdParty/Steamworks/Steamv139/sdk/public/steam/steam_api.h"

#include "SteamPlusFriends.generated.h"

UENUM(BlueprintType)
enum class ESteamOverlayDialog : uint8
{
	friends,
	community,
	players,
	settings,
	officialgamegroup,
	stats,
	achievements
};

UENUM(BlueprintType)
enum class ESteamFriendOverlayDialog : uint8
{
	// Opens the overlay web browser to the specified user or groups profile.
	steamid,

	// Opens a chat window to the specified user, or joins the group chat.
	chat,

	// Opens a window to a Steam Trading session that was started with the ISteamEconomy/StartTrade Web API.
	jointrade,

	// Opens the overlay web browser to the specified user's stats.
	stats,

	// Opens the overlay web browser to the specified user's achievements.
	achievements,

	// Opens the overlay in minimal mode prompting the user to add the target user as a friend.
	friendadd,

	// Opens the overlay in minimal mode prompting the user to remove the target friend.
	friendremove,

	// Opens the overlay in minimal mode prompting the user to accept an incoming friend invite.
	friendrequestaccept,

	// Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite.
	friendrequestignore
};

USTRUCT(Blueprinttype)
struct FSteamMessage
{
	GENERATED_BODY()

public:
	// The Steam ID of the Steam group chat room.
	FSteamID64 chatRoomID;
	// The index of the message.
	int32 messageID;
	// The contents of the message.
	FString messageText;
	// The type of chat entry that was received.
	EChatEntryType messageType;
	// The Steam ID of the user that sent the message.
	FSteamID64 senderID;
};

USTRUCT(Blueprinttype)
struct FSteamGroup
{
	GENERATED_BODY()

public:
	// The Steam ID of the Steam group.
	FSteamID64 id;
	// The index of the group.
	int32 index;
	// The name of the group.
	FString name;
	// The tag of the group.
	FString tag;
};


UCLASS()
class TEMPTESTING_API USteamPlusFriends : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Activates the Steam Overlay to a specific dialog.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends|Overlay", meta = (DisplayName = "Open Steam Overlay", Keywords = "open toggle activate overlay in-game ingame friends community players settings officialgamegroup stats achievements steam sdk"))
		static void activateSteamOverlay(const ESteamOverlayDialog dialogToOpenTo);

	// Activates the Steam Overlay to invite a friend.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends|Overlay", meta = (DisplayName = "Open Steam Overlay to Invite", Keywords = "open toggle activate overlay in-game ingame friends players invite to lobby game server steam sdk"))
		static void activateSteamOverlayToInvite(const FSteamID64 lobbyToInviteTo);

	// Activates Steam Overlay to a specific dialog related to a user.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends|Overlay", meta = (DisplayName = "Open Steam Overlay to User", Keywords = "open toggle activate overlay in-game ingame user friend steam sdk"))
		static void activateSteamOverlayToUser(const ESteamFriendOverlayDialog dialog, const FSteamID64 friendID);

	/* Activates the Steam Overlay to a specified website.
A fully qualified address with the protocol is required, e.g. "http://www.steampowered.com"*/
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends|Overlay", meta = (DisplayName = "Open Steam Overlay to URL", Keywords = "open toggle activate overlay in-game ingame website webpage url steam sdk"))
		static void activateSteamOverlayToWebsite(const FString url);

	// Clears all of the current user's Rich Presence key/values.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends|Rich Presence", meta = (DisplayName = "Clear Rich Presence", Keywords = "clear rich presence key value steam sdk"))
		static void clearRichPresence();

	// Closes the specified Steam group chat room in the Steam UI.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends", meta = (DisplayName = "Close Clan Chat Window", Keywords = "close leave clan group chat window steam sdk"))
		static bool closeClanChatWindow(/*The Steam ID of the Steam group chat room to close*/const FSteamID64 steamID);

	// Download Clan Activity Counts
	
	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGetFollowedUsersSuccess, TArray<FSteamID64>, followedUsers);

	/* Gets the list of users that the current user is following.
You can be following people that are not your friends. Following allows you to receive updates when the person does things like post a new piece of content to the Steam Workshop.*/
	//UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends", meta = (DisplayName = "Get Followed Users", Keywords = "get followed following users steam sdk"))
		//void getFollowedUsers(FOnGetFollowedUsersSuccess onSuccess);

	/* Returns an array of all the users in the given Steam Chat.
Note: Large groups with too many users will fail.
The current user must be in the given chat. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends", meta = (DisplayName = "Get Chat Members", Keywords = "get chat clan members users group steam sdk"))
		TArray<FSteamID64> getAllChatMembers(const FSteamID64& chatID);

	/* Gets the most recent information we have about what the users in a Steam Group are doing. 
Returns whether it was successful as a bool. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends", meta = (DisplayName = "Get Chat Members", Keywords = "get clan group activity counts numbers steam sdk"))
		bool getGroupActivityCounts(/* The 64 bit Steam ID of the group */ const FSteamID64& groupID, int32& numOnline, int32& numInGame, /* The number of members in the group chat room */ int32& numChatting);

	/* Returns an array of all Steam Groups the current user is a member of. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends", meta = (DisplayName = "Get All Steam Groups", Keywords = "get all array list steam groups clans chats steam sdk"))
		TArray<FSteamGroup> getAllSteamGroups();

	/* Get the number of users in a Steam group chat. */
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Friends", meta = (DisplayName = "Get Number of Chat Members", Keywords = "get number count chat group clan members users steam sdk"))
		int32 getNumChatMembers(FSteamID64 chatID);

private:

	/* getFollowedUsers async callback
	void onFriendsEnumerateFollowingList(FriendsEnumerateFollowingList_t *pCallback, bool bIOFailure);
	CCallResult< USteamPlusFriends, FriendsEnumerateFollowingList_t > m_SteamCallResultFriendsEnumerateFollowingList;
	int m_nFollowersParsed;
	TArray<FSteamID64> l_FollowedUsers;
	FRemoteImageLoaderOnCompleteBP onFollowersEnumerateSuccess;

	// MSG recieved callback
	void onGameConnectedClanChatMsg(CSteamID m_steamIDClanChat, CSteamID m_steamIDUser, int m_iMessageID);
	CCallResult< USteamPlusFriends, GameConnectedClanChatMsg_t > m_SteamCallResultGameConnectedClanChatMsg;
	//int m_nFollowersParsed;
	//TArray<FSteamID64> l_FollowedUsers;
	FRemoteImageLoaderOnCompleteBP onFollowersEnumerateSuccess;
	*/
};