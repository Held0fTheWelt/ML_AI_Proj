/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


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
