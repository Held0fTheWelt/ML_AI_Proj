/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "NN/Objects/NNBrainNode.h"
#include "NNBrainNeuron.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivate);

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNBrainNeuron : public UNNBrainNode
{
	GENERATED_BODY()

public:
	UNNBrainNeuron();
	
	FActivate Activate;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<class UNNSynapse*> Synapses;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Bias;

private:
	void PerformActivate();

	float Sigmoid(float In);
};
