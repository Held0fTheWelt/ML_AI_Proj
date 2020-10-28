/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNBrain.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NN/Objects/NNBrainNode.h"
#include "NN/Objects/NNBrainNeuron.h"
#include "NN/Objects/NNSynapse.h"

UNNBrain::UNNBrain()
{
	NeuronCounts = TArray<int32>();
	Neurons = TArray<UNNBrainNode*>();

	if(!SetupBrain.IsBound())
		SetupBrain.AddDynamic(this, &UNNBrain::SetupBrainValues);

	if(!Fire.IsBound())
		Fire.AddDynamic(this, &UNNBrain::FireNeuronEvents);

	bDoOnce = true;
}

TArray<class UNNBrainNeuron*> UNNBrain::GetOutputs() const
{
	TArray<class UNNBrainNeuron*> Outputs = TArray<class UNNBrainNeuron*>();

	int32 StartIndex = Neurons.Num() - NeuronCounts[NeuronCounts.Num() - 1];
	int32 EndIndex = Neurons.Num() - 1;

	for (int32 i = StartIndex; i < EndIndex; i++)
	{
		UNNBrainNeuron* BrainNeuron = Cast<UNNBrainNeuron>(Neurons[i]);

		if (BrainNeuron == nullptr)
		{

		}
		else
		{
			Outputs.Add(BrainNeuron);
		}
	}

	return Outputs;
}

void UNNBrain::ReDoOnce()
{
	bDoOnce = true;
}

int32 UNNBrain::CountNeuronsInLayers(int32 StartLayer, int32 EndLayer)
{
	int32 NeuronCount = 0;
	// Watch this ! 
	for (int32 i = StartLayer; i <= EndLayer; i++)
	{
		NeuronCount += NeuronCounts[i];
	}

	return NeuronCount;
}

TArray<class UNNBrainNode*> UNNBrain::GetInputs()
{
	TArray<class UNNBrainNode*> Inputs = TArray<class UNNBrainNode*>();

	for (int32 i = 0; i < NeuronCounts[0] - 1; i++)
	{
		Inputs.Add(Neurons[i]);
	}

	return Inputs;
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

					for (int32 k = Count - NeuronCounts[i - 1]; k < Count - 1; k++)
					{
						UNNSynapse* BrainSynapse = NewObject<UNNSynapse>(UNNSynapse::StaticClass());

						if (BrainSynapse == nullptr)
						{
							UKismetSystemLibrary::PrintString(GetWorld(), "BrainSynapse could not be created by Brain !", true, true, FLinearColor::Red, 0.f);
						}
						else
						{
							if (BrainSynapse->SetupSynapse.IsBound())
							{
								BrainSynapse->SetupSynapse.Broadcast(Neurons[k], BrainNeuron);

								BrainNeuron->Synapses.Add(BrainSynapse);
							}
							else
							{
								UKismetSystemLibrary::PrintString(GetWorld(), "BrainSynapse could not be setup, because Event is not bound!", true, true, FLinearColor::Red, 0.f);
							}
						}
					}
				}
			}
		}
	}
}

void UNNBrain::FireNeuronEvents()
{
	if (Neurons.Num() == 0)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Brain has no neurons to activate!", true, true, FLinearColor::Red, 0.f);
		return;
	}

	for (int32 i = 0; i < Neurons.Num(); i++)
	{
		UNNBrainNeuron* BrainNeuron = Cast<UNNBrainNeuron>(Neurons[i]);

		if (BrainNeuron == nullptr)
		{

		}
		else
		{
			if (BrainNeuron->Activate.IsBound())
			{
				BrainNeuron->Activate.Broadcast();
			}
			else
			{
				UKismetSystemLibrary::PrintString(GetWorld(), "Neuron could not activate, because event is not bound!", true, true, FLinearColor::Red, 0.f);
			}
		}
	}
}
