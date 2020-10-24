/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "NNSynapseInformation.generated.h"

USTRUCT(BlueprintType)
struct ARTIFICIALINTELLIGENCE_API FNNSynapseInformation
{
	GENERATED_BODY()

public:
	FNNSynapseInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SourceIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
};
