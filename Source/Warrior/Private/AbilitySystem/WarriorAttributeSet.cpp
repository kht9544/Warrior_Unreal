// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"

#include "WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
    InitMaxHealth(1.f);
    InitCurrentRage(1.f);
    InitMaxRage(1.f);
    InitAttackPower(1.f);
    InitDefensePower(1.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    if(!CachedPawnUIInterface.IsValid())
    {
        CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
    }

    checkf(CachedPawnUIInterface.IsValid(), TEXT("UWarriorAttributeSet::PostGameplayEffectExecute: CachedPawnUIInterface is invalid"));
    
    UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

    checkf(PawnUIComponent, TEXT("UWarriorAttributeSet::PostGameplayEffectExecute: PawnUIComponent is nullptr"));


    if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
       const float CurrentHealthValue = FMath::Clamp(GetCurrentHealth(),0.f, GetMaxHealth());
       SetCurrentHealth(CurrentHealthValue);

       PawnUIComponent->OnCurrentHealthChanged.Broadcast(CurrentHealthValue / GetMaxHealth());
    }

    if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
    {
        const float CurrentRageValue = FMath::Clamp(GetCurrentRage(),0.f, GetMaxRage());
        SetCurrentRage(CurrentRageValue);

        if(UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
        {
            HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
        }
        
    }

    if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
    {
        const float OldHealth = GetCurrentHealth();
        const float DamageDone = GetDamageTaken();

        const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone,0.f, GetMaxHealth());

        SetCurrentHealth(NewCurrentHealth);

        // const FString DebugString = FString::Printf
        // (
        //     TEXT("Old Health: %.1f, Damage Done: %.1f, New Health: %.1f"),
        //     OldHealth,
        //     DamageDone,
        //     NewCurrentHealth
        // );


        PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
        
        if(GetCurrentHealth() == 0.f)
        {
            UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead);
        }
    }
    
    

	
}

