/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNBrain.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NN/Objects/NNBrainNode.h"
#include "NN/Objects/NNBrainNeuron.h"

UNNBrain::UNNBrain()
{
	NeuronCounts = TArray<int32>();
	Neurons = TArray<UNNBrainNode*>();

	SetupBrain.AddDynamic(this, &UNNBrain::SetupBrainValues);
	Fire.AddDynamic(this, &UNNBrain::FireNeuronEvents);

	bDoOnce = true;
}

TArray<class UNNBrainNeuron*> UNNBrain::GetOutputs() const
{
	return TArray<class UNNBrainNeuron*>();
}

void UNNBrain::ReDoOnce()
{
	bDoOnce = true;
}

int32 UNNBrain::CountNeuronsInLayers(int32 StartLayer, int32 EndLayer)
{
	return int32();
}

TArray<class UNNBrainNode*> UNNBrain::GetInputs()
{
	return TArray<class UNNBrainNode*>();
}

void UNNBrain::SetupBrainValues()
{
	if (bDoOnce == false)
	{
		return;
	}
	bDoOnce = false;

	if (NeuronCounts.Num() == 0)
	{
		return;
	}

	for (int32 i = 0; i < NeuronCounts.Num(); i++)
	{
		for (int32 j = 0; j < NeuronCounts[i] - 1; j++)
		{
			if (i == 0)
			{
				UNNBrainNode* BrainNode = NewObject<UNNBrainNode>(UNNBrainNode::StaticClass());

				if (BrainNode == nullptr)
				{
					UKismetSystemLibrary::PrintString(GetWorld(), "BrainNode Layer 0 could not be created by Brain !", true, true, FLinearColor::Red, 0.f);
				}
				else
				{
					Neurons.Add(BrainNode);
				}
			}
			else
			{
				UNNBrainNeuron* BrainNeuron = NewObject<UNNBrainNeuron>(UNNBrainNeuron::StaticClass());

				if (BrainNeuron == nullptr)
				{
					UKismetSystemLibrary::PrintString(GetWorld(), "BrainNeuron could not be created by Brain !", true, true, FLinearColor::Red, 0.f);
				}
				else
				{
					Neurons.Add(BrainNeuron);

					int32 Count = CountNeuronsInLayers(0, i - 1);
				}
			}
		}
	}
}

void UNNBrain::FireNeuronEvents()
{
}
