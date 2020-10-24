/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/SaveGame/NNSaveGame.h"

UNNSaveGame::UNNSaveGame()
{
	Save.AddDynamic(this, &UNNSaveGame::ProcessPopulation);
	Load.AddDynamic(this, &UNNSaveGame::RestorePopulation);
}

void UNNSaveGame::ProcessPopulation(UNNPopulation* CurrentPopulation)
{
	Population = CurrentPopulation;
}

void UNNSaveGame::RestorePopulation()
{
}
