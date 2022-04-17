/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4

Changelog:
4/16
Added Level Select Changes
*/


#include "Online_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = TEXT("Game");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

UOnline_GameInstance::UOnline_GameInstance()
{

}

void UOnline_GameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("INIT"));
	//Get the Subsystem, If this variable is null, then the online configuration has not been setup in DefaultEngine.ini nor the .Build.cs file
	SubSystem = IOnlineSubsystem::Get();
	if (SubSystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: SubSystem was nullptr"));
		return;
	}

	//Get the Interface to the Online session from the Subsystem
	SessionInterface = SubSystem->GetSessionInterface();
	if (SessionInterface.IsValid())
	{
		/*Bind delegates to the session interface events, here we bind using AddUObject() to the delegate / event instead of AddDynamic().*/
		//SUBSCRIBE to the SessionInterface's OnCreateSessionCompleteDelegates event using the function &UOnline_GameInstance::OnCreateSessionComplete
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOnline_GameInstance::OnCreateSessionComplete);
		//SUBSCRIBE to the SessionInterface's OnDestroySessionCompleteDelegates event using the function &UOnline_GameInstance::OnDestroySessionComplete
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UOnline_GameInstance::OnDestroySessionComplete);
		//SUBSCRIBE to the SessionInterface's OnFindSessionsCompleteDelegates event using the function &UOnline_GameInstance::OnFindSessionsComplete
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UOnline_GameInstance::OnFindSessionsComplete);
		//SUBSCRIBE to the SessionInterface's OnJoinSessionCompleteDelegates event using the function &UOnline_GameInstance::OnJoinSessionComplete
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UOnline_GameInstance::OnJoinSessionComplete);
		//SUBSCRIBE to the SessionInterface's OnStartSessionCompleteDelegates event using the function &UOnline_GameInstance::OnStartSessionComplete
		SessionInterface->OnStartSessionCompleteDelegates.AddUObject(this, &UOnline_GameInstance::OnStartSessionComplete);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: SessionInterface was not valid"));
		return;
	}
}

void UOnline_GameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

//////////////////////////////////////HOSTING///////////////////////////////////////////////////////////////
void UOnline_GameInstance::Button_HostServer(FString levelName)
{
	if (SessionInterface.IsValid())
	{
		//Check if the Session already exists in the sub system. Is It already running
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			/*If it exists, then destroy it*/
			//CALL DestroySession() on the SessionInterface passing in SESSION_NAME
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
            LevelName = levelName;
			/*If it exists, then destroy it*/
			//CALL CreateSession()
			CreateSession();
		}
	}
}

void UOnline_GameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));

	/*Initialize the SessionSetting Object*/
	//SET SessionSettings to the return value of MakeShareable(new FOnlineSessionSettings())
	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	
	
//-------------------------------------------------------------------------------------------------------------
	////IF IOnlineSubsystem::Get()->GetSubsystemName() IS "NULL"
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		UE_LOG(LogTemp, Warning, TEXT("SUBSYSTEM WAS 'NULL'"));
		/*If we are not on any subsystem i.e Steam, PSN, XBox live then we are on the lan*/
		//SET SessionSettings->bIsLANMatch to true
		SessionSettings->bIsLANMatch = true;
	}
	//ELSE
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SUBSYSTEM WAS NOT NULL"));
		/*We are on a online subsystem i.e Steam, PSN, XBox live*/
		//SET SessionSettings->bIsLANMatch to false
		SessionSettings->bIsLANMatch = false;
	}
	//ENDIF

	//OR
	//SessionSettings->bIsLANMatch = bIsLANGame;
//-------------------------------------------------------------------------------------------------------------
	/*UNCOMMENT BELOW*/
	SessionSettings->bUsesPresence = true;
	SessionSettings->NumPublicConnections = 5;
	SessionSettings->NumPrivateConnections = 2;
	SessionSettings->bAllowInvites = true;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->Set(SERVER_NAME_SETTINGS_KEY, FString(TEXT("Game")), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	/*Get the Players Unique Net ID from the player controller*/
	FUniqueNetIdRepl wrapperNetId = GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId();
	//CALL SessionInterface->CreateSession() and pass in *wrapperNetId.GetUniqueNetId(), FName(SESSION_NAME), *SessionSettings
	SessionInterface->CreateSession(*wrapperNetId.GetUniqueNetId(), FName(SESSION_NAME), *SessionSettings);
	//OR
	//SessionInterface->CreateSession(0, FName(SESSION_NAME), *SessionSettings);
}

void UOnline_GameInstance::OnCreateSessionComplete(FName ServerName, bool success)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete success=%d"), success);
	if (success)
	{
		//CALL StartSession() on the SessionInterface passing in SESSION_NAME
		SessionInterface->StartSession(SESSION_NAME/*SessionInfo.SessionName*/);
	}
}


void UOnline_GameInstance::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		/*Host Server Travels all connected players to the map*/
		//CALL GetWorld()->ServerTravel() passing in "/Game/Scenes/dev_scene?listen", true
		GetWorld()->ServerTravel(LevelName, true);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////


void UOnline_GameInstance::Button_JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Join server clicked"));

	
	/*UNCOMMENT BELOW*/
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 20;
	SessionSearch->PingBucketSize = 50;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
//-------------------------------------------------------------------------------------------------------------
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		UE_LOG(LogTemp, Warning, TEXT("SUBSYSTEM WAS 'NULL'"));
		/*If we are not on any subsystem i.e Steam, PSN, XBox live then we are on the lan*/
		//SET SessionSearch->bIsLanQuery to true
		SessionSearch->bIsLanQuery = true;
	}
	//ELSE
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SUBSYSTEM WAS NOT NULL"));
		/*We are on a online subsystem i.e Steam, PSN, XBox live*/
		//SET SessionSearch->bIsLanQuery to false
		SessionSearch->bIsLanQuery = false;
	}

	//OR
	//SessionSearch->bIsLanQuery = bIsLANGame;
//-------------------------------------------------------------------------------------------------------------

	/*Get the Players Unique Net ID from the player controller*/
	FUniqueNetIdRepl wrapperNetId = GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId();
	//CALL FindSessions() on SessionInterface passing in *wrapperNetId.GetUniqueNetId(), SessionSearch.ToSharedRef()
	SessionInterface->FindSessions(*wrapperNetId.GetUniqueNetId(), SessionSearch.ToSharedRef());
	//OR
	//SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

}

void UOnline_GameInstance::OnFindSessionsComplete(bool success)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete success=%d"), success);
	if (!success)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete failed"));
		return;
	}
	//DECLARE a TArray<FOnlineSessionSearchResult> called searchResults and assign to SessionSearch->SearchResults
	TArray<FOnlineSessionSearchResult> searchResults = SessionSearch->SearchResults;
	UE_LOG(LogTemp, Warning, TEXT("Sessions found=%d"), searchResults.Num());
	//IF We have search results i.e searchResults.Num() != 0
	if (searchResults.Num() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("attempting to join existing session"));

		/*Get the Players Unique Net ID from the player controller*/
		FUniqueNetIdRepl wrapperNetId = GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId();

		//SessionInterface->JoinSession(0, SESSION_NAME, searchResults[0]);
		//CALL JoinSession() on SessionInterface passing in *wrapperNetId.GetUniqueNetId(), SESSION_NAME, searchResults[0]
		SessionInterface->JoinSession(*wrapperNetId.GetUniqueNetId(), SESSION_NAME, searchResults[0]);
	}
	//ENDIF
}

void UOnline_GameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("JoinSession complete: %s"), *SessionName.ToString());

	if (Result == EOnJoinSessionCompleteResult::Type::Success)
		UE_LOG(LogTemp, Warning, TEXT("JOIN OK"));
	if (Result != EOnJoinSessionCompleteResult::Type::Success)
		UE_LOG(LogTemp, Warning, TEXT("JOIN NOT OK"));

	//IF APlayerController* playerController EQUAL GetFirstLocalPlayerController() ->>> Only one Equal = not ==
	if (APlayerController* playerController = GetFirstLocalPlayerController())
	{
		FString join_address;
		/*Get the resolved address to Join and return it to join_address*/
		//IF SessionInterface->GetResolvedConnectString(SESSION_NAME, join_address)
		if (SessionInterface->GetResolvedConnectString(SESSION_NAME, join_address))
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Purple, "Joining Address:" + join_address);
			UE_LOG(LogTemp, Warning, TEXT("joining SERVER: %s"), *join_address);
			//CALL ClientTravel() on playerController passing in join_address, ETravelType::TRAVEL_Absolute
			playerController->ClientTravel(join_address, ETravelType::TRAVEL_Absolute);
		}
		//ENDIF
	}
	//ENDIF
}