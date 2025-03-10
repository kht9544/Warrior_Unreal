// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputAction(const FGameplayTag& InputTag) const
{
	for(const FWarriorInputAction& InputActionConfig : NativeInputActions)
    {
        if(InputActionConfig.InputTag == InputTag && InputActionConfig.InputAction)
        {
            return InputActionConfig.InputAction;
        }
    }

    return nullptr;
}
