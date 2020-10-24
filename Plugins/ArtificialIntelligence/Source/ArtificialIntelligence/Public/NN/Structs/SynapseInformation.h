// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SynapseInformation.generated.h"

USTRUCT(BlueprintType)
struct ARTIFICIALINTELLIGENCE_API FSynapseInformation
{
	GENERATED_BODY()

public:
	FSynapseInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SourceIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
};
