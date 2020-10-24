// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NN/Structs/SynapseInformation.h"
#include "SpeciesInformation.generated.h"

USTRUCT(BlueprintType)
struct ARTIFICIALINTELLIGENCE_API FSpeciesInformation
{
	GENERATED_BODY()

public:
	FSpeciesInformation();

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
	TArray<FSynapseInformation> Synapses;

};