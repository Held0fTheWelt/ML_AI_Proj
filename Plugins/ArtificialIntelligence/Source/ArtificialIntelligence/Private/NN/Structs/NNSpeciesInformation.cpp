// Fill out your copyright notice in the Description page of Project Settings.


#include "NN/Structs/NNSpeciesInformation.h"

FNNSpeciesInformation::FNNSpeciesInformation()
{
	GenerationBorn = 0;
	Number = 0;
	LastFitness = 0.f;
	bStale = false;
	UnderperformingForGeneration = 0;
	NeuronBiases = 0.f;
	Synapses = TArray<FNNSynapseInformation>();
}
