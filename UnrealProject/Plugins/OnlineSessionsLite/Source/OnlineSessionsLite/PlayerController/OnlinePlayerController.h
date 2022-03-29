#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OnlinePlayerController.generated.h"

UCLASS()
class ONLINESESSIONSLITE_API AOnlinePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AOnlinePlayerController();

	/** Property replication. DELETE if you are not replicating properties */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



};
