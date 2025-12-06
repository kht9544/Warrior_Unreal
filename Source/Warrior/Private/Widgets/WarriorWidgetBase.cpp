// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WarriorWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(IPawnUIInterface * PawnUiInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
    {
       if(UHeroUIComponent* HeroUIComponent = PawnUiInterface->GetHeroUIComponent())
       {
            BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
       }

    }
}


void UWarriorWidgetBase::InitEnemyCreateWidget(AActor* OwningEnemyActor)
{
	if(IPawnUIInterface * PawnUiInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
    {
        UEnemyUIComponent* EnemyUIComponent = PawnUiInterface->GetEnemyUIComponent();

        checkf(EnemyUIComponent, TEXT("UWarriorWidgetBase::InitEnemyCreateWidget: EnemyUIComponent is nullptr"));
    
        BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);    
    }
}