/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/SaveGame/NNSimpleSaveGame.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UNNSimpleSaveGame::UNNSimpleSaveGame()
{
	if(!Save.IsBound())
		Save.AddDynamic(this, &UNNSimpleSaveGame::ProcessPopulation);
	if(!Load.IsBound())
		Load.AddDynamic(this, &UNNSimpleSaveGame::RestorePopulation);
}

void UNNSimpleSaveGame::ProcessPopulation(UNNPopulation* CurrentPopulation)
{
	Population = CurrentPopulation;

	//for (int32 i = 0; i < Population->Spec.Num(); i++)
	//{

	//}


	UGameplayStatics::SaveGameToSlot(this, "SlotOne", 0);

	Population = nullptr;
}

void UNNSimpleSaveGame::RestorePopulation()
{
}
