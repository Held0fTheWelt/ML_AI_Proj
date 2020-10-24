/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "NN/Structs/NNSynapseInformation.h"
#include "NNSpeciesInformation.generated.h"

USTRUCT(BlueprintType)
struct ARTIFICIALINTELLIGENCE_API FNNSpeciesInformation
{
	GENERATED_BODY()

public:
	FNNSpeciesInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GenerationBorn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastFitness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnderperformingForGeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NeuronBiases;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNNSynapseInformation> Synapses;

};