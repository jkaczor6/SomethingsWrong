#include "InteractableItem.h"
#include "Components/StaticMeshComponent.h"

AInteractableItem::AInteractableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableItem::HighlightItem()
{
	Mesh->SetRenderCustomDepth(true);
	Mesh->SetCustomDepthStencilValue(4);
}

void AInteractableItem::UnHighlightItem()
{
	Mesh->SetRenderCustomDepth(false);
	Mesh->SetCustomDepthStencilValue(4);
}

