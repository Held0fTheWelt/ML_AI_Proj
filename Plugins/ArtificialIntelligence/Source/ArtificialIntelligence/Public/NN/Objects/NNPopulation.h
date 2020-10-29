/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NNPopulation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPopulate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPopulationChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNextGeneration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMakeNewSpecies, int32, n);

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNPopulation : public UObject
{
	GENERATED_BODY()
	
public:
	UNNPopulation();

	FPopulate Populate;
	FNextGeneration NextGeneration;
	FMakeNewSpecies CreateNewSpecies;
	FPopulationChanged PopulationChanged;

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

public:
	UFUNCTION(BlueprintCallable)
	void Selection(int32 KillCount, bool ElitistSelection);
	UFUNCTION(BlueprintCallable)
	void Crossover(int32 Offspring);
	UFUNCTION(BlueprintCallable)
	void Mutation(class UNNSpecies* Specie);
	UFUNCTION(BlueprintCallable)
	float AverageFitness();

private:
	UFUNCTION()
	void MutateAllSynapses(class UNNBrainNeuron* BrainNeuron);
	UFUNCTION()
	void MutateAllBiases(UNNBrainNeuron* BrainNeuron);
	UFUNCTION()
	void PopulateSpecies();
	UFUNCTION()
	void MakeNextGeneration();
	UFUNCTION()
	void CreateANewSpecie(int32 n);
	UFUNCTION()
	void Quicksort(TArray<float> &a, int32 low, int32 high);
	UFUNCTION()
	void Partition(TArray<float> &a, int32 low, int32 high, float&i, float&j);
	
	void Swap(float* a, float* b);
};
