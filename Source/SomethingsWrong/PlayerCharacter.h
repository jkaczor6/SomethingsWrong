#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class AInteractableItem;
struct FInputActionValue;

UCLASS()
class SOMETHINGSWRONG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Functions
	void MoveInput(const FInputActionValue& Value);
	void LookInput(const FInputActionValue& Value);
	void InteractInput(const FInputActionValue& Value);
	void CrouchInputBegin(const FInputActionValue& Value);
	void CrouchInputEnd(const FInputActionValue& Value);
	void SprintInputBegin(const FInputActionValue& Value);
	void SprintInputEnd(const FInputActionValue& Value);


	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintMultiplier = 2.0f;
	float DefaultMaxWalkingSpeed;
	UPROPERTY(EditAnywhere, Category = "Raycast")
	float MaxInteractionDistance = 300.0f;
	bool CanInteract = false;
	AInteractableItem* CurrentItem;
};
