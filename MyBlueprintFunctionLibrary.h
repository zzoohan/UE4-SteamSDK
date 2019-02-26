// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

// Define Structs

// Contains data about a given DLC
USTRUCT(BlueprintType, Category = "Steam|Steam Apps")
struct FSteamDLC
{
	GENERATED_USTRUCT_BODY();

public:

	// Index of the DLC between 0 and the total amount of DLCs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		int32 DLCIndex;

	// The App ID of the DLC.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		int32 steamAppID;

	// Whether the DLC is currently available.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		bool isAvailable;

	// The name of the DLC by copying it into this buffer.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam|Steam Apps")
		FString DLCName;
};

UENUM(BlueprintType)
enum class ESteamResult : uint8
{
	k_EResultOK													UMETA(DisplayName = "Success."),
	k_EResultFail												UMETA(DisplayName = "Generic failure."),
	k_EResultNoConnection										UMETA(DisplayName = "Your Steam client doesn't have a connection to the back-end."),
	k_EResultInvalidPassword									UMETA(DisplayName = "Password/ticket is invalid."),
	k_EResultLoggedInElsewhere									UMETA(DisplayName = "The user is logged in elsewhere."),
	k_EResultInvalidProtocolVer									UMETA(DisplayName = "Protocol version is incorrect."),
	k_EResultInvalidParam										UMETA(DisplayName = "A parameter is incorrect."),
	k_EResultFileNotFound										UMETA(DisplayName = "File was not found."),
	k_EResultBusy												UMETA(DisplayName = "Called method is busy - action not taken."),
	k_EResultInvalidState										UMETA(DisplayName = "Called object was in an invalid state."),
	k_EResultInvalidName										UMETA(DisplayName = "The name was invalid."),
	k_EResultInvalidEmail										UMETA(DisplayName = "The email was invalid."),
	k_EResultDuplicateName										UMETA(DisplayName = "The name is not unique."),
	k_EResultAccessDenied										UMETA(DisplayName = "Access is denied."),
	k_EResultTimeout											UMETA(DisplayName = "Operation timed out."),
	k_EResultBanned												UMETA(DisplayName = "The user is VAC2 banned."),
	k_EResultAccountNotFound									UMETA(DisplayName = "Account not found."),
	k_EResultInvalidSteamID										UMETA(DisplayName = "The Steam ID was invalid."),
	k_EResultServiceUnavailable									UMETA(DisplayName = "The requested service is currently unavailable."),
	k_EResultNotLoggedOn										UMETA(DisplayName = "The user is not logged on."),
	k_EResultPending											UMETA(DisplayName = "Request is pending, it may be in process or waiting on third party."),
	k_EResultEncryptionFailure									UMETA(DisplayName = "Encryption or Decryption failed."),
	k_EResultInsufficientPrivilege								UMETA(DisplayName = "Insufficient privilege."),
	k_EResultLimitExceeded										UMETA(DisplayName = "Too much of a good thing."),
	k_EResultRevoked											UMETA(DisplayName = "Access has been revoked (used for revoked guest passes.)"),
	k_EResultExpired											UMETA(DisplayName = "License/Guest pass the user is trying to access is expired."),
	k_EResultAlreadyRedeemed									UMETA(DisplayName = "Guest pass has already been redeemed by account, cannot be used again."),
	k_EResultDuplicateRequest									UMETA(DisplayName = "The request is a duplicate and the action has already occurred in the past, ignored this time."),
	k_EResultAlreadyOwned										UMETA(DisplayName = "All the games in this guest pass redemption request are already owned by the user."),
	k_EResultIPNotFound											UMETA(DisplayName = "IP address not found."),
	k_EResultPersistFailed										UMETA(DisplayName = "Failed to write change to the data store."),
	k_EResultLockingFailed										UMETA(DisplayName = "Failed to acquire access lock for this operation."),
	k_EResultLogonSessionReplaced								UMETA(DisplayName = "The logon session has been replaced."),
	k_EResultConnectFailed										UMETA(DisplayName = "Failed to connect."),
	k_EResultHandshakeFailed									UMETA(DisplayName = "The authentication handshake has failed."),
	k_EResultIOFailure											UMETA(DisplayName = "There has been a generic IO failure."),
	k_EResultRemoteDisconnect									UMETA(DisplayName = "The remote server has disconnected."),
	k_EResultShoppingCartNotFound								UMETA(DisplayName = "Failed to find the shopping cart requested."),
	k_EResultBlocked											UMETA(DisplayName = "A user blocked the action."),
	k_EResultIgnored											UMETA(DisplayName = "The target is ignoring sender."),
	k_EResultNoMatch											UMETA(DisplayName = "Nothing matching the request found."),
	k_EResultAccountDisabled									UMETA(DisplayName = "The account is disabled."),
	k_EResultServiceReadOnly									UMETA(DisplayName = "This service is not accepting content changes right now."),
	k_EResultAccountNotFeatured									UMETA(DisplayName = "Account doesn't have value, so this feature isn't available."),
	k_EResultAdministratorOK									UMETA(DisplayName = "Allowed to take this action, but only because requester is admin."),
	k_EResultContentVersion										UMETA(DisplayName = "A Version mismatch in content transmitted within the Steam protocol."),
	k_EResultTryAnotherCM										UMETA(DisplayName = "The current CM can't service the user making a request, user should try another."),
	k_EResultPasswordRequiredToKickSession						UMETA(DisplayName = "You are already logged in elsewhere, this cached credential login has failed."),
	k_EResultAlreadyLoggedInElsewhere							UMETA(DisplayName = "The user is logged in elsewhere. (Use k_EResultLoggedInElsewhere instead!)"),
	k_EResultSuspended											UMETA(DisplayName = "Long running operation has suspended/paused. (eg. content download.)"),
	k_EResultCancelled											UMETA(DisplayName = "Operation has been canceled, typically by user. (eg. a content download.)"),
	k_EResultDataCorruption										UMETA(DisplayName = "Operation canceled because data is ill formed or unrecoverable."),
	k_EResultDiskFull											UMETA(DisplayName = "Operation canceled - not enough disk space."),
	k_EResultRemoteCallFailed									UMETA(DisplayName = "The remote or IPC call has failed."),
	k_EResultPasswordUnset										UMETA(DisplayName = "Password could not be verified as it's unset server side."),
	k_EResultExternalAccountUnlinked							UMETA(DisplayName = "External account (PSN, Facebook...) is not linked to a Steam account."),
	k_EResultPSNTicketInvalid									UMETA(DisplayName = "PSN ticket was invalid."),
	k_EResultExternalAccountAlreadyLinked						UMETA(DisplayName = "External account (PSN, Facebook...) is already linked to some other account, must explicitly request to replace/delete the link first."),
	k_EResultRemoteFileConflict									UMETA(DisplayName = "The sync cannot resume due to a conflict between the local and remote files."),
	k_EResultIllegalPassword									UMETA(DisplayName = "The requested new password is not allowed."),
	k_EResultSameAsPreviousValue								UMETA(DisplayName = "New value is the same as the old one. This is used for secret question and answer."),
	k_EResultAccountLogonDenied									UMETA(DisplayName = "Account login denied due to 2nd factor authentication failure."),
	k_EResultCannotUseOldPassword								UMETA(DisplayName = "The requested new password is not legal."),
	k_EResultInvalidLoginAuthCode								UMETA(DisplayName = "Account login denied due to auth code invalid."),
	k_EResultAccountLogonDeniedNoMail							UMETA(DisplayName = "Account login denied due to 2nd factor auth failure - and no mail has been sent."),
	k_EResultHardwareNotCapableOfIPT							UMETA(DisplayName = "The users hardware does not support Intel's Identity Protection Technology (IPT)."),
	k_EResultIPTInitError										UMETA(DisplayName = "Intel's Identity Protection Technology (IPT) has failed to initialize."),
	k_EResultParentalControlRestricted							UMETA(DisplayName = "Operation failed due to parental control restrictions for current user."),
	k_EResultFacebookQueryError									UMETA(DisplayName = "Facebook query returned an error."),
	k_EResultExpiredLoginAuthCode								UMETA(DisplayName = "Account login denied due to an expired auth code."),
	k_EResultIPLoginRestrictionFailed							UMETA(DisplayName = "The login failed due to an IP restriction."),
	k_EResultAccountLockedDown									UMETA(DisplayName = "The current users account is currently locked for use. This is likely due to a hijacking and pending ownership verification."),
	k_EResultAccountLogonDeniedVerifiedEmailRequired			UMETA(DisplayName = "The logon failed because the accounts email is not verified."),
	k_EResultNoMatchingURL										UMETA(DisplayName = "There is no URL matching the provided values."),
	k_EResultBadResponse										UMETA(DisplayName = "Bad Response due to a Parse failure, missing field, etc."),
	k_EResultRequirePasswordReEntry								UMETA(DisplayName = "The user cannot complete the action until they re-enter their password."),
	k_EResultValueOutOfRange									UMETA(DisplayName = "The value entered is outside the acceptable range."),
	k_EResultUnexpectedError									UMETA(DisplayName = "Something happened that we didn't expect to ever happen."),
	k_EResultDisabled											UMETA(DisplayName = "The requested service has been configured to be unavailable."),
	k_EResultInvalidCEGSubmission								UMETA(DisplayName = "The files submitted to the CEG server are not valid."),
	k_EResultRestrictedDevice									UMETA(DisplayName = "The device being used is not allowed to perform this action."),
	k_EResultRegionLocked										UMETA(DisplayName = "The action could not be complete because it is region restricted."),
	k_EResultRateLimitExceeded									UMETA(DisplayName = "Temporary rate limit exceeded, try again later, different from k_EResultLimitExceeded which may be permanent."),
	k_EResultAccountLoginDeniedNeedTwoFactor					UMETA(DisplayName = "Need two-factor code to login."),
	k_EResultItemDeleted										UMETA(DisplayName = "The thing we're trying to access has been deleted."),
	k_EResultAccountLoginDeniedThrottle							UMETA(DisplayName = "Login attempt failed, try to throttle response to possible attacker."),
	k_EResultTwoFactorCodeMismatch								UMETA(DisplayName = "Two factor authentication (Steam Guard) code is incorrect."),
	k_EResultTwoFactorActivationCodeMismatch					UMETA(DisplayName = "The activation code for two-factor authentication (Steam Guard) didn't match."),
	k_EResultAccountAssociatedToMultiplePartners				UMETA(DisplayName = "The current account has been associated with multiple partners."),
	k_EResultNotModified										UMETA(DisplayName = "The data has not been modified."),
	k_EResultNoMobileDevice										UMETA(DisplayName = "The account does not have a mobile device associated with it."),
	k_EResultTimeNotSynced										UMETA(DisplayName = "The time presented is out of range or tolerance."),
	k_EResultSmsCodeFailed										UMETA(DisplayName = "SMS code failure - no match, none pending, etc."),
	k_EResultAccountLimitExceeded								UMETA(DisplayName = "Too many accounts access this resource."),
	k_EResultAccountActivityLimitExceeded						UMETA(DisplayName = "Too many changes to this account."),
	k_EResultPhoneActivityLimitExceeded							UMETA(DisplayName = "Too many changes to this phone."),
	k_EResultRefundToWallet										UMETA(DisplayName = "Cannot refund to payment method, must use wallet."),
	k_EResultEmailSendFailure									UMETA(DisplayName = "Cannot send an email."),
	k_EResultNotSettled											UMETA(DisplayName = "Can't perform operation until payment has settled."),
	k_EResultNeedCaptcha										UMETA(DisplayName = "The user needs to provide a valid captcha."),
	k_EResultGSLTDenied											UMETA(DisplayName = "A game server login token owned by this token's owner has been banned."),
	k_EResultGSOwnerDenied										UMETA(DisplayName = "Game server owner is denied for some other reason such as account locked, community ban, vac ban, missing phone, etc."),
	k_EResultInvalidItemType									UMETA(DisplayName = "The type of thing we were requested to act on is invalid."),
	k_EResultIPBanned											UMETA(DisplayName = "The IP address has been banned from taking this action."),
	k_EResultGSLTExpired										UMETA(DisplayName = "This Game Server Login Token (GSLT) has expired from disuse; it can be reset for use."),
	k_EResultInsufficientFunds									UMETA(DisplayName = "user doesn't have enough wallet funds to complete the action"),
	k_EResultTooManyPending										UMETA(DisplayName = "There are too many of this thing pending already")
};

USTRUCT(Blueprinttype)
struct FSteamID64
{
	GENERATED_BODY()

public:

	uint64 value;

	FSteamID64() : value(0) {};

};

// Define Functions
UCLASS()
class SHOOTER_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Steam|Conversions", meta = (DisplayName = "SteamID to String", Keywords = "id 64 to string steam api sdk"))
		static FString fSteamIdToFString(const FSteamID64& steamID);

	UFUNCTION(BlueprintPure, Category = "Steam|Conversions", meta = (DisplayName = "String to SteamID", Keywords = "string to id 64 steam api sdk"))
		static FSteamID64 stringToFSteamId(const FString& String);
	/*
	UFUNCTION(BlueprintPure, Category = "Steam|Conversions", meta = (DisplayName = "Int to SteamID", Keywords = "int to id 64 steam api sdk"))
		static FSteamID64 uint32ToFSteamId(const int32& low, const int32& mid, const int32& high);

	UFUNCTION(BlueprintPure, Category = "Steam|Conversions", meta = (DisplayName = "SteamID to Int", Keywords = "id 64 to int steam api sdk"))
		static void fSteamIdToUint32(const FSteamID64 SteamId, int32& low, int32& high);
		*/
	// Returns whether the Steam SDK is initialized. Running a steam SDK function without checking this *will* result in a crash.
	UFUNCTION(BlueprintPure, Category = "Steam", meta = (DisplayName = "Is Steam Running", Keywords = "is steam api sdk client running launched initialize"))
		static bool IsSteamAPIRunning();

	// Checks if your executable was launched through Steam and relaunches it through Steam if it wasn't.
	UFUNCTION(BlueprintCallable, Category = "Steam", meta = (DisplayName = "Restart Through Steam", Keywords = "restart game through steam check running launched sdk"))
		static void RestartAppIfNecessary(const int32 SteamAppID);

	// Run any pending asynchronous callbacks. Best to run this function on Game State's tick
	UFUNCTION(BlueprintCallable, Category = "Steam", meta = (DisplayName = "Run Callbacks", Keywords = "run check refresh tick callbacks steam sdk"))
		static void RunCallbacks();

	/* ------------------------------------------------------------ ISteamApps ------------------------------------------------------------ */

	// Gets all registered DLCs and returns their metadata
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get DLC Data", Keywords = "get all dlc steam sdk"))
		static TArray<FSteamDLC> GetAllDLCs(bool& wasSuccessful);

	/* Checks if a specific app is installed.
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is App Installed", Keywords = "is app program game installed downloaded steam sdk"))
		static bool isAppInstalled(int steamAppID);

	/*Checks if the user owns a specific DLC and if the DLC is installed
Does NOT verify ownership
Does not work for DLCs*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is DLC Installed", Keywords = "is DLC installed downloaded steam sdk"))
		static bool isDlcInstalled(int steamAppID);

	// Checks whether the current App ID is for Cyber Cafes.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is Cybercafe", Keywords = "is in at cybercafe license app id steam sdk"))
		static bool isCybercafe();

	// Checks if the license owned by the user provides low violence depots.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Is Low Violence", Keywords = "is low violence license depot steam sdk"))
		static bool isLowViolence();

	/* Gets the buildid of this app, may change at any time based on backend updates to the game.
Defaults to 0 if you're not running a build downloaded from steam.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Build Id", Keywords = "get build id steam sdk"))
		static int getBuildId();

	/* Gets the install folder for a specific AppID.
This works even if the application is not installed, based on where the game would be installed with the default Steam library location.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get App Install Dir", Keywords = "get install directory file location game program app steam sdk"))
		static FString getAppInstallDir(int32 steamAppId);

	/* Gets the Steam ID of the original owner of the current app.
If it's different from the current user then it is borrowed.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get App Owner", Keywords = "get game program app owner user steam sdk"))
		static FSteamID64 getAppOwner();

	// Checks if the user is running from a beta branch, and returns the name of the branch if they are.
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Selected Beta", Keywords = "get game program app owner user steam sdk"))
		static FString getSelectedBeta(bool & isOnBranch);
	
	/*Gets the current language that the user has set as preferred.
This falls back to the Steam UI language if the user hasn't explicitly picked a language for the title.
This will comply to the language codes here: https://partner.steamgames.com/doc/store/localization#supported_languages */
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Preferred Language", Keywords = "get game program app preferred selected chosen language localization country user steam sdk"))
		static FString getPreferredLanguage();
	
	/*Gets the download progress for optional DLC in MegaBytes.
Defaults to 0 if the DLC does not exist or isn't downloading.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get DLC Download Progress", Keywords = "get dlc download progress steam sdk"))
		static void getDLCDownloadProgress(const int32 steamAppId, float& mbDownloaded, float& totalMB);
	
	/*Gets the time of purchase of the specified app in Unix epoch format.
Steam is not clear on this, however I believe that this is the date for the first purchase, so a refund and then re-purchase will not modify it.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Original Purchase Date", Keywords = "get app program game original earliest purchase buy date steam sdk"))
		static int32 getOriginalPurchaseDate(const int32 steamAppId);
	
	/*Gets the value for the launch parameter with the given key if the game is run via steam://run/<appid>/?param1=value1;param2=value2;param3=value3 etc.
Keys beginning with @ or _ should not be used.
Will default to an empty string if the key does not exist.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Get Launch Parameter", Keywords = "get app program game launch parameter query key value date steam sdk"))
		static FString getLaunchQueryParam(const FString key);
	
	// Starts installing the given DLC.
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Apps", meta = (DisplayName = "Install DLC", Keywords = "install dlc start download content steam sdk"))
		static void installDLC(const int32 steamAppId);
	
	/*Allows you to force verify game content on next launch.
If you detect the game is out-of-date (for example, by having the client detect a version mismatch with a server),
you can call use MarkContentCorrupt to force a verify, show a message to the user, and then quit.*/
	UFUNCTION(BlueprintPure, Category = "Steam|Steam Apps", meta = (DisplayName = "Mark Content Corrupt", Keywords = "mark content dlc program app files corrupt outdated old steam sdk"))
		static bool markContentCorrupt(const bool missingFilesOnly);
	
	// Will ask steam to start uninstalling the DLC at the given app ID
	UFUNCTION(BlueprintCallable, Category = "Steam|Steam Apps", meta = (DisplayName = "Uninstall DLC", Keywords = "uninstall delete remove dlc steam sdk"))
		static void uninstallDLC(int32 appID);

};
