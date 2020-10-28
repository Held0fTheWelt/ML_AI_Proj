/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NNSpecies.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndRun);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetupSpecies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetInputs, TArray<float>, Inputs);

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNSpecies : public UObject
{
	GENERATED_BODY()

public:
	UNNSpecies();
	
	FEndRun EndRun;
	FSetupSpecies SetupSpecies;
	FSetInputs SetInputs;

	TArray<class UNNBrainNeuron*> GetOutputs() const;

public:
	UPROPERTY(VisibleAnywhere)
	class UNNBrain* Brain;
	UPROPERTY(VisibleAnywhere)
	float Fitness;
	UPROPERTY(VisibleAnywhere)
	float LastFitness;
	UPROPERTY(VisibleAnywhere)
	int32 GenerationBorn;
	UPROPERTY(VisibleAnywhere)
	int32 Number;
	UPROPERTY(VisibleAnywhere)
	TArray<int32> NeuronCounts;
	UPROPERTY(VisibleAnywhere)
	bool bStale;

protected:
	UPROPERTY(VisibleAnywhere)
	float UnderperformingForGenerations;

private:
	void EndSpeciesRun();
	void SetupSpeciesValues();

	void SetupSpeciesInputs(TArray<float> Inputs);
};
