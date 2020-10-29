/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNPopulation.h"
#include "Containers/Map.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NN/Objects/NNBrain.h"
#include "NN/Objects/NNBrainNeuron.h"
#include "NN/Objects/NNBrainNode.h"
#include "NN/Objects/NNSpecies.h"
#include "NN/Objects/NNSynapse.h"

UNNPopulation::UNNPopulation()
{
	Species = TArray<UNNSpecies*>();

	Generation = 1;
	NumberOfSpecies = 10;
	NeuronCounts = TArray<int32>();
	FitnessOverTime = TArray<float>();
	SynapseMutationChance = .75f;
	NeuronMutationChance = .5f;
	PerturbChance = .1f;
	MutationStep = .1f;

	if (!Populate.IsBound())
		Populate.AddDynamic(this, &UNNPopulation::PopulateSpecies);

	if (!NextGeneration.IsBound())
		NextGeneration.AddDynamic(this, &UNNPopulation::MakeNextGeneration);

	if (!CreateNewSpecies.IsBound())
		CreateNewSpecies.AddDynamic(this, &UNNPopulation::CreateANewSpecie);
}

void UNNPopulation::Selection(int32 KillCount = 1, bool ElitistSelection = false)
{
	TMap<float, class UNNSpecies*> FitnessMap = TMap<float, class UNNSpecies*>();
	TArray<float> FitnessArray = TArray<float>();
	TArray<UNNSpecies*> SortedSpecies= TArray<UNNSpecies*>();
	float BelowZero = 0.f;

	// Map fitness values to species
	for (int32 i = 0; i < Species.Num(); i++)
	{
		FitnessMap.Add(Species[i]->LastFitness, Species[i]);
	}
		
	FitnessMap.GenerateKeyArray(FitnessArray);
		
	Quicksort(FitnessArray, 0, FitnessArray.Num() - 1);

	for (int32 i = 0; i < FitnessArray.Num(); i++)
	{
		if (FitnessMap.Contains(FitnessArray[i]))
		{
			SortedSpecies.Add(*FitnessMap.Find(FitnessArray[i]));
			SortedSpecies[SortedSpecies.Num() - 1]->Number = SortedSpecies.Num();
		}
		if (FitnessArray[i] < 0)
		{
			BelowZero++;
		}
	}

	Species.Empty();

	int32 MaxToAdd = (ElitistSelection == true) ? 1 : (SortedSpecies.Num() - 1) - UKismetMathLibrary::Max(KillCount, BelowZero);

	for (int32 i = 0; i < MaxToAdd; i++)
	{
		Species.Add(SortedSpecies[i]);
	}
}

void UNNPopulation::Swap(float* a, float* b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

/* This function partitions a[] in three parts
   a) a[l..i] contains all elements smaller than pivot
   b) a[i+1..j-1] contains all occurrences of pivot
   c) a[j..r] contains all elements greater than pivot */
void UNNPopulation::Partition(TArray<float> &a, int low, int high, float &i, float &j)
{
	// To handle 2 elements
	if (high - low <= 1) {
		if (a[high] < a[low])
			Swap(&a[high], &a[low]);
		i = low;
		j = high;
		return;
	}

	int mid = low;
	int pivot = a[high];
	while (mid <= high) {
		if (a[mid] < pivot)
			Swap(&a[low++], &a[mid++]);
		else if (a[mid] == pivot)
			mid++;
		else if (a[mid] > pivot)
			Swap(&a[mid], &a[high--]);
	}

	// update i and j
	i = low - 1;
	j = mid; // or high+1
}

// 3-way partition based quick sort
void UNNPopulation::Quicksort(TArray<float> &a, int32 low, int32 high)
{
	if (low >= high) // 1 or 0 elements
		return;

	float i = 0.f, j = 0.f;

	// Note that i and j are passed as reference
	Partition(a, low, high, i, j);

	// Recur two halves
	Quicksort(a, low, i);
	Quicksort(a, j, high);
}

void UNNPopulation::Crossover(int32 Offspring = 1)
{
	for (int32 i = 1; i < Offspring; i++)
	{
		UNNSpecies* Specie = NewObject<UNNSpecies>(UNNSpecies::StaticClass());

		if (Specie == nullptr)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), "Failed creating new specie!", true, true, FLinearColor::Red, 0.f);
		}
		else
		{
			Specie->NeuronCounts = NeuronCounts;
			Specie->GenerationBorn = Generation;
			if (Specie->SetupSpecies.IsBound())
			{
				Specie->SetupSpecies.Broadcast();
			}
			else
			{
				UKismetSystemLibrary::PrintString(GetWorld(), "Could not SetupSpecie because it is unbound!", true, true, FLinearColor::Red, 0.f);
			}

			for (int32 j = 0; j < Specie->Brain->Neurons.Num(); j++)
			{
				UNNBrainNeuron* BrainNeuron = Cast<UNNBrainNeuron>(Specie->Brain->Neurons[i]);

				if (BrainNeuron != nullptr)
				{
					if (UKismetMathLibrary::RandomFloat() > .5f)
					{
						UNNBrainNeuron* Adam = Cast<UNNBrainNeuron>(Species[0]->Brain->Neurons[j]);

						if (Adam != nullptr)
						{
							BrainNeuron->Bias = Adam->Bias;

							for (int32 k = 0; k < BrainNeuron->Synapses.Num(); k++)
							{
								BrainNeuron->Synapses[k]->Weight = Adam->Synapses[k]->Weight;
							}
						}
					}
					else
					{
						UNNBrainNeuron* Eve = Cast<UNNBrainNeuron>(Species[1]->Brain->Neurons[j]);

						if (Eve != nullptr)
						{
							BrainNeuron->Bias = Eve->Bias;

							for (int32 k = 0; k < BrainNeuron->Synapses.Num(); k++)
							{
								BrainNeuron->Synapses[k]->Weight = Eve->Synapses[k]->Weight;
							}
						}
					}
				}
			}
			Species.Add(Specie);
			Specie->Number = Species.Num();
		}
	}
}

void UNNPopulation::Mutation(UNNSpecies* Specie)
{
	Specie->bStale = false;

	for (int32 i = 0; i < Specie->Brain->Neurons.Num(); i++)
	{
		UNNBrainNeuron* BrainNeuron = Cast<UNNBrainNeuron>(Specie->Brain->Neurons[i]);
		if (BrainNeuron != nullptr)
		{
			MutateAllSynapses(BrainNeuron);
			MutateAllBiases(BrainNeuron);
		}
	}
}

void UNNPopulation::MutateAllBiases(UNNBrainNeuron* BrainNeuron)
{
	if (UKismetMathLibrary::RandomFloat() < NeuronMutationChance)
	{
		BrainNeuron->Bias = (UKismetMathLibrary::RandomFloat() < PerturbChance) ? UKismetMathLibrary::RandomFloatInRange(-5.f, 5.f)
			: BrainNeuron->Bias + UKismetMathLibrary::SignOfFloat(UKismetMathLibrary::RandomFloatInRange(-1.f, 1.f)) * MutationStep;
	}
}

void UNNPopulation::MutateAllSynapses(UNNBrainNeuron* BrainNeuron)
{
	for (int32 j = 0; j < BrainNeuron->Synapses.Num(); j++)
	{
		if (UKismetMathLibrary::RandomFloat() < SynapseMutationChance)
		{
			BrainNeuron->Synapses[j]->Weight = (UKismetMathLibrary::RandomFloat() < PerturbChance) ? UKismetMathLibrary::RandomFloatInRange(-5.f, 5.f) :
				BrainNeuron->Synapses[j]->Weight + UKismetMathLibrary::SignOfFloat(UKismetMathLibrary::RandomFloatInRange(-1.f, 1.f)) * MutationStep;
		}
	}
}

float UNNPopulation::AverageFitness()
{
	float FitnessSum = 0.f;

	for (auto Specie : Species)
	{
		FitnessSum += Specie->Fitness;
	}

	FitnessSum /= Species.Num();

	return FitnessSum;
}

void UNNPopulation::PopulateSpecies()
{
	if (CreateNewSpecies.IsBound())
	{
		CreateNewSpecies.Broadcast(NumberOfSpecies);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Population could not create new species, becouse it is unbound!", true, true, FLinearColor::Red, 0.f);
	}
}

void UNNPopulation::MakeNextGeneration()
{
	Generation++;
	FitnessOverTime.Add(AverageFitness());
	Selection(NumberOfSpecies / 2, true);
	Crossover(NumberOfSpecies - Species.Num());
	for (int32 i = 0; i < Species.Num(); i++)
	{
		if (Species[i]->bStale == true || i > 1)
		{
			Mutation(Species[i]);
		}
	}

	for (int32 i = 0; i < Species.Num(); i++)
	{
		Species[i]->Fitness = 0.f;
	}

	if (PopulationChanged.IsBound())
	{
		PopulationChanged.Broadcast();
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Could not broadcast Population change, because it is unbound!", true, true, FLinearColor::Red, 0.f);
	}
}

void UNNPopulation::CreateANewSpecie(int32 n)
{
	for (int32 i = 1; i <= n; i++)
	{
		UNNSpecies* Specie = NewObject<UNNSpecies>(UNNSpecies::StaticClass());

		if (Specie == nullptr)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), "Failed creating new specie!", true, true, FLinearColor::Red, 0.f);
		}
		else
		{
			Specie->NeuronCounts = NeuronCounts;
			Specie->GenerationBorn = Generation;
			Specie->Number = i;

			if (Specie->SetupSpecies.IsBound())
			{
				Specie->SetupSpecies.Broadcast();
			}
			else
			{
				UKismetSystemLibrary::PrintString(GetWorld(), "Could not SetupSpecie because it is unbound!", true, true, FLinearColor::Red, 0.f);
			}

			Species.Add(Specie);
		}
	}
}
