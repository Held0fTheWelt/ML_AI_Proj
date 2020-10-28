/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNBrainNeuron.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "NN/Objects/NNSynapse.h"

UNNBrainNeuron::UNNBrainNeuron()
{
	Bias = 0.f;
	Synapses = TArray<UNNSynapse*>();
	Activate.AddDynamic(this, &UNNBrainNeuron::PerformActivate);
}

void UNNBrainNeuron::PerformActivate()
{
	Value = 0.f;

	for (auto Synapse : Synapses)
	{
		Value += Synapse->GetWeightedValue();
	}

	Value += Bias;

	Value = Sigmoid(Value);
}

float UNNBrainNeuron::Sigmoid(float In)
{
	In *= -1;

	In = UKismetMathLibrary::Exp(In);

	return 1.0f / (1.0f + In);
}
