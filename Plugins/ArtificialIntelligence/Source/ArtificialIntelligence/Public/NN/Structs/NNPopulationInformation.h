// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NN/Structs/NNSpeciesInformation.h"
#include "NNPopulationInformation.generated.h"

USTRUCT(BlueprintType)
struct ARTIFICIALINTELLIGENCE_API FNNPopulationInformation
{
	GENERATED_BODY()

public:
	FNNPopulationInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Generation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfSpecies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NeuronCounts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FitnessOverTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNNSpeciesInformation> Species;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SynapseMutationChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NeuronMutationChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PerturbChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MutationStep;
};