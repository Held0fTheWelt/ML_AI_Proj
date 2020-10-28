/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NNPopulation.generated.h"

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNPopulation : public UObject
{
	GENERATED_BODY()
	
public:
	UNNPopulation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UNNSpecies*> Species;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Generation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	int32 NumberOfSpecies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	TArray<int32> NeuronCounts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> FitnessOverTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float SynapseMutationChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float NeuronMutationChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float PerturbChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	float MutationStep;
};
