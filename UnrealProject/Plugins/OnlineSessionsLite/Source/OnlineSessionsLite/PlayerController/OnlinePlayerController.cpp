#include "OnlinePlayerController.h"



/** Property replication. DELETE if you are not replicating properties */
#include "Net/UnrealNetwork.h"
// Sets default values
AOnlinePlayerController::AOnlinePlayerController()
{

}

/** Property replication. DELETE if you are not replicating properties */
void AOnlinePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(YourClassName, variable);
	
}


