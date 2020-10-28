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

	UFUNCTION(BlueprintCallable)
	TArray<class UNNBrainNeuron*> GetOutputs() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNNBrain* Brain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fitness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastFitness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GenerationBorn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	TArray<int32> NeuronCounts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStale;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UnderperformingForGenerations;

private:
	UFUNCTION()
	void EndSpeciesRun();
	UFUNCTION()
	void SetupSpeciesValues();
	UFUNCTION()
	void SetupSpeciesInputs(TArray<float> Inputs);
};
