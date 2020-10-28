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
	
	TArray<class UNNBrainNeuron*> GetOutputs() const;

	FSetupBrain SetupBrain;

	FFireEvents Fire;

	TArray<int32> NeuronCounts;
	TArray<class UNNBrainNode*> Neurons;
};
