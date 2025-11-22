// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"

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
    if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
       const float CurrentHealthValue = FMath::Clamp(GetCurrentHealth(),0.f, GetMaxHealth());
       SetCurrentHealth(CurrentHealthValue);
    }

    if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
    {
        const float CurrentRageValue = FMath::Clamp(GetCurrentRage(),0.f, GetMaxRage());
        SetCurrentRage(CurrentRageValue);
    }

    if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
    {
        const float OldHealth = GetCurrentHealth();
        const float DamageDone = GetDamageTaken();

        const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone,0.f, GetMaxHealth());

        SetCurrentHealth(NewCurrentHealth);

        if(NewCurrentHealth == 0.f)
        {
            UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead);

            
        }
    }
    
    

	
}

