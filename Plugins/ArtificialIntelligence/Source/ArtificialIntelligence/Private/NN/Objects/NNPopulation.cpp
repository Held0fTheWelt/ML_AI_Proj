/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNPopulation.h"
#include "NN/Objects/NNSpecies.h"

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
}