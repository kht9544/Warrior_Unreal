#pragma once

namespace Debug
{
    static void Print(const FString& Msg,const FColor& Color = FColor::MakeRandomColor(),int32 InKey = -1)
    {
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Msg);

            UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
        }
    }

    static void Print(const FString& FloatTitle,float FloatValuePrint, int32 InKey = -1, const FColor& Color = FColor::MakeRandomColor(), float Duration = 7.f)
    {
        if (GEngine)
        {
            const FString FinalMsg = FloatTitle + FString::SanitizeFloat(FloatValuePrint);

            GEngine->AddOnScreenDebugMessage(InKey, Duration, Color, FinalMsg);

            UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
        }
    }
}