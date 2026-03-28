#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SomethingsWrongGameMode.generated.h"

struct FTimerHandle;

UCLASS()
class SOMETHINGSWRONG_API ASomethingsWrongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void OnInspectionTimerTimeout();
	void OnRoundTimerTimeout();

	UPROPERTY(EditAnywhere)
	float InspectionTime = 30.0f;
	UPROPERTY(EditAnywhere)
	float RoundTime = 60.0f;

	FTimerHandle InspectionTimer;
	FTimerHandle RoundTimer;
};
