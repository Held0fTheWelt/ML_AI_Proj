// Fill out your copyright notice in the Description page of Project Settings.


#include "NN/Structs/NNPopulationInformation.h"

FNNPopulationInformation::FNNPopulationInformation()
{
	Generation = 0;
	NumberOfSpecies = 0;
	NeuronCounts = TArray<int32>();
	FitnessOverTime = 0.f;
	Species = TArray<FNNSpeciesInformation>();
	SynapseMutationChange = 0.f;
	NeuronMutationChange = 0.f;
	PerturbChange = 0.f;
	MutationStep = 0.f;
}
