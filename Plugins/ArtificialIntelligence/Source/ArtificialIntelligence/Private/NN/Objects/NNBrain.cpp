/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNBrain.h"
#include "NN/Objects/NNBrainNode.h"

UNNBrain::UNNBrain()
{
	NeuronCounts = TArray<int32>();
	Neurons = TArray<UNNBrainNode*>();
}

TArray<class UNNBrainNeuron*> UNNBrain::GetOutputs() const
{
	return TArray<class UNNBrainNeuron*>();
}
