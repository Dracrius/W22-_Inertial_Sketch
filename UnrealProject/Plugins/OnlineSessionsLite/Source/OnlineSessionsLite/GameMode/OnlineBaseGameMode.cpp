#include "OnlineBaseGameMode.h"

#include "Online_GameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AOnlineBaseGameMode::AOnlineBaseGameMode()
{

}

void AOnlineBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}

APlayerController* AOnlineBaseGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{

	UOnline_GameInstance* GI = Cast<UOnline_GameInstance>(GetWorld()->GetGameInstance());
	if(GI)
	{
		
	}


	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AOnlineBaseGameMode::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);
}

