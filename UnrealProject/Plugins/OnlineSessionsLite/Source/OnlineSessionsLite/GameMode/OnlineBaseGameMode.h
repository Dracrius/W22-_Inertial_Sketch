#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineBaseGameMode.generated.h"

UCLASS()
class ONLINESESSIONSLITE_API AOnlineBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AOnlineBaseGameMode();

	virtual void BeginPlay() override;


	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController. */
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
