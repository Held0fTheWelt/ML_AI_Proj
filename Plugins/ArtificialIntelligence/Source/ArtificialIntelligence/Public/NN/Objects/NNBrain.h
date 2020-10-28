/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NNBrain.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetupBrain);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireEvents);

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNBrain : public UObject
{
	GENERATED_BODY()

public:
	UNNBrain();
	
	UFUNCTION(BlueprintCallable)
	TArray<class UNNBrainNeuron*> GetOutputs() const;

	FSetupBrain SetupBrain;

	FFireEvents Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	TArray<int32> NeuronCounts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UNNBrainNode*> Neurons;

	UFUNCTION(BlueprintCallable)
	void ReDoOnce();
public:
	UFUNCTION(BlueprintCallable)
	int32 CountNeuronsInLayers(int32 StartLayer, int32 EndLayer);
	UFUNCTION(BlueprintCallable)
	TArray<class UNNBrainNode*> GetInputs();

private:
	void SetupBrainValues();
	void FireNeuronEvents();

private:
	bool bDoOnce;
};
