// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
DECLARE_LOG_CATEGORY_EXTERN(WFCLog, Log, All);


#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
    #define FUNC_NAME    TEXT(__func__)
#endif

#define TRACE(Format, ...) \
{ \
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(WFCLog, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}

