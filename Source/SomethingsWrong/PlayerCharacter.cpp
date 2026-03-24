#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* APC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(APC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMC, 0);
		}
	}

	DefaultMaxWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveInput);

		// Looking
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookInput);
		
		// Interaction
		EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::InteractInput);

		// Crouching
		EIC->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CrouchInputBegin);
		EIC->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::CrouchInputEnd);

		// Sprinting
		EIC->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SprintInputBegin);
		EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SprintInputEnd);
	}

}

void APlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorRightVector(), MovementVector.X);
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
}

void APlayerCharacter::LookInput(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(-LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void APlayerCharacter::InteractInput(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Interact"));
}

void APlayerCharacter::CrouchInputBegin(const FInputActionValue& Value)
{
	Crouch();
}

void APlayerCharacter::CrouchInputEnd(const FInputActionValue& Value)
{
	UnCrouch();
}

void APlayerCharacter::SprintInputBegin(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkingSpeed * SprintMultiplier;
}

void APlayerCharacter::SprintInputEnd(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkingSpeed;
}

