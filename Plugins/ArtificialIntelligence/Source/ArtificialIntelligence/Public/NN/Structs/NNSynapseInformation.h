// Fill out your copyright notice in the Description page of Project Settings.

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
