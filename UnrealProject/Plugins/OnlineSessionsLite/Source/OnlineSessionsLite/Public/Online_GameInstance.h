/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Online_GameInstance.generated.h"


USTRUCT()
struct FCharacterData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		TSubclassOf<class ACharacter> Character;

	/*UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerController> CharacterController;*/

	UPROPERTY(EditAnywhere)
		FString CharacterName;

	inline bool operator==(const FCharacterData& other) const
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "OPERATOR OVERLOADED!");
		return other.CharacterName == CharacterName;// && other.UserUUID == UserUUID;
	}
};

/**
 *
 */
UCLASS()
class ONLINESESSIONSLITE_API UOnline_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UOnline_GameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LAN")
		bool bIsLANGame = false;

	UPROPERTY(EditDefaultsOnly, Category = "Player Characters")
		TArray<FCharacterData> GameCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Characters")
		int CharacterChoice = 0;

    FString LevelName = FString("/Game/Maps/ParkFullScale?listen");

	FORCEINLINE  TSubclassOf<class ACharacter> GetCharacterChoice() { return GameCharacters[CharacterChoice].Character; }

protected:
	virtual void Init();

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
	/*
	  Pointer to the Session Interface
	 */
	IOnlineSessionPtr SessionInterface;

	/*
	  Pointer to the Session Search, this will contain our search results
	 */
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	/**
	* Function fired when a session create request has completed.
	*
	* @param ServerName: the name of the session this callback is for.
	* @param Succeeded: true if the async action completed without error, false if there was an error.
	*/
	void OnCreateSessionComplete(FName ServerName, bool Succeeded);
	/**
	* Delegate fired when a destroying an online session has completed.
	*
	* @param SessionName: the name of the session this callback is for.
	* @param Success: true if the async action completed without error, false if there was an error.
	*/
	void OnDestroySessionComplete(FName SessionName, bool Success);
	/**
	* Delegate fired when a session search query has completed.
	*
	* @param success: true if the async action completed without error, false if there was an error.
	*/
	void OnFindSessionsComplete(bool success);

	/**
	* Delegate fired when a session join request has completed.
	*
	* @param SessionName: the name of the session this callback is for.
	* @param Result: true if the async action completed without error, false if there was an error.
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	/**
	* Function fired when a session start request has completed.
	*
	* @param SessionName: the name of the session this callback is for.
	* @param bWasSuccessful: true if the async action completed without error, false if there was an error.
	*/
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

	/*
	  Called to Create a new online session when hosting a new session
	 */
	void CreateSession();

public:
	/*
	   Called when the Create Server button is pressed in the menu
	 */
	UFUNCTION(BlueprintCallable)
		void Button_HostServer(FString levelName);

	/*
	   Called when the Create Join button is pressed in the menu
	 */
	UFUNCTION(BlueprintCallable)
		void Button_JoinServer();

	class IOnlineSubsystem* SubSystem;

};
