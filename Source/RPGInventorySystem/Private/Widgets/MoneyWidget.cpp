// Copyright by liclem97.


#include "Widgets/MoneyWidget.h"

#include "Character/InventoryCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMoneyWidget::NativeConstruct()
{
	PlayerCharacter = PlayerCharacter == nullptr ? Cast<AInventoryCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) : PlayerCharacter;
	if (PlayerCharacter)
	{
		PlayerInventory = PlayerCharacter->GetInventoryComponent_Implementation();
		UpdateMoney();
	}
}

void UMoneyWidget::UpdateMoney()
{	
	Text_MoneyAmount->SetText(FText::AsNumber(PlayerInventory->GetMoney()));
}
