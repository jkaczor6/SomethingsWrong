#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class SOMETHINGSWRONG_API AInteractableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableItem();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void HighlightItem();
	void UnHighlightItem();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
};
