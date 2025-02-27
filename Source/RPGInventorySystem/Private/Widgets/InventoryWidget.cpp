// Copyright by liclem97.


#include "Widgets/InventoryWidget.h"

#include "Kismet/GameplayStatics.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
}

void UInventoryWidget::CloseWidget()
{
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeGameOnly());
	RemoveFromParent();
}
