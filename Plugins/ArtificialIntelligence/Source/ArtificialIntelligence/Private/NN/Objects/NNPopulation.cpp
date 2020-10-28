/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNPopulation.h"
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

}

void UNNPopulation::Crossover(int32 Offspring = 1)
{
}

void UNNPopulation::Mutation(UNNSpecies* Specie)
{
	Specie->bStale = false;

	for (int32 i = 0; i < Specie->Brain->Neurons.Num(); i++)
	{
		UNNBrainNeuron* BrainNeuron = Cast<UNNBrainNeuron>(Specie->Brain->Neurons[i]);
		if (BrainNeuron != nullptr)
		{
			// Mutate all synapses
			MutateAllSynapses(BrainNeuron);

			// Mutate all biases
			if (UKismetMathLibrary::RandomFloat() < NeuronMutationChance)
			{

			}
		}
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
