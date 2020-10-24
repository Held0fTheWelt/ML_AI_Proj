// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NN/Structs/SpeciesInformation.h"
#include "PopulationInformation.generated.h"

USTRUCT(BlueprintType)
struct ARTIFICIALINTELLIGENCE_API FPopulationInformation
{
	GENERATED_BODY()

public:
	FPopulationInformation();

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
	TArray<FSpeciesInformation> Species;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SynapseMutationChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NeuronMutationChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PerturbChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MutationStep;
};