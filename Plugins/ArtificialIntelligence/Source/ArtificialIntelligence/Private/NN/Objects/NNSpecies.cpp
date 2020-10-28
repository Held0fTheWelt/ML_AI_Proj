/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNSpecies.h"
#include "Engine/World.h"
#include "NN/Objects/NNBrain.h"
#include "Kismet/KismetSystemLibrary.h"

UNNSpecies::UNNSpecies()
{
	Brain = nullptr;

	Fitness = 0.f;
	LastFitness = -99999.0f;
	UnderperformingForGenerations = 0.f;
	
	GenerationBorn = 0;
	Number = 0;
	NeuronCounts = TArray<int32>();	
	
	bStale = false;
	
	EndRun.AddDynamic(this, &UNNSpecies::EndSpeciesRun);
	SetupSpecies.AddDynamic(this, &UNNSpecies::SetupSpeciesValues);
	SetInputs.AddDynamic(this, &UNNSpecies::SetupSpeciesInputs);
}

TArray<class UNNBrainNeuron*> UNNSpecies::GetOutputs() const
{
	if (Brain == nullptr)
	{
		return TArray<class UNNBrainNeuron*>();
	}

	return Brain->GetOutputs();;
}

void UNNSpecies::EndSpeciesRun()
{
	if (Fitness < LastFitness)
	{
		UnderperformingForGenerations = 0;
	}
	else
	{
		UnderperformingForGenerations++;
	}
	LastFitness = Fitness;
}

void UNNSpecies::SetupSpeciesValues()
{
	Brain = NewObject<UNNBrain>(UNNBrain::StaticClass());

	if (Brain == nullptr)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Species could not create Brain !", true, true, FLinearColor::Red, 0.f);
	}
	else
	{
		Brain->NeuronCounts = NeuronCounts;
		if (Brain->SetupBrain.IsBound())
		{
			Brain->SetupBrain.Broadcast();
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), "Setup Brain is unbound !", true, true, FLinearColor::Red, 0.f);
		}
	}
}

void UNNSpecies::SetupSpeciesInputs(TArray<float> Inputs)
{
	if (Brain == nullptr)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Species could not find Brain !", true, true, FLinearColor::Red, 0.f);
		return;
	}




	if (Brain->Fire.IsBound())
	{
		Brain->Fire.Broadcast();
	}
}
