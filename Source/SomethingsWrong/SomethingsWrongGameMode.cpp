#include "SomethingsWrongGameMode.h"
#include "Engine/TimerHandle.h"

void ASomethingsWrongGameMode::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Round Started. 30 seconds for room inspection!"));
	GetWorldTimerManager().SetTimer(InspectionTimer, this, &ASomethingsWrongGameMode::OnInspectionTimerTimeout, 1.0f, false, InspectionTime);
}

void ASomethingsWrongGameMode::OnInspectionTimerTimeout()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inspection time is up! Proceed to finding anomaly!"));
	GetWorldTimerManager().SetTimer(RoundTimer, this, &ASomethingsWrongGameMode::OnRoundTimerTimeout, 1.0f, false, RoundTime);
}

void ASomethingsWrongGameMode::OnRoundTimerTimeout()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Time is up! Gather your information!"));
}
