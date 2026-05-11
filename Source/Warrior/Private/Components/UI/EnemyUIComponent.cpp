// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/WarriorWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UWarriorWidgetBase* InWidgetToRegister)
{
	if (!InWidgetToRegister)
	{
		return;
	}

	constexpr int32 EnemyDrawnWidgetZOrder = -10;

	InWidgetToRegister->RemoveFromParent();
	InWidgetToRegister->AddToViewport(EnemyDrawnWidgetZOrder);

	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if(EnemyDrawnWidgets.IsEmpty())
    {
        return;
    }

    for(UWarriorWidgetBase* DrawnWidget : EnemyDrawnWidgets)
    {
        if(DrawnWidget)
        {
            DrawnWidget->RemoveFromParent();
        }
    }

    EnemyDrawnWidgets.Empty();

}
