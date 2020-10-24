/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NN/Objects/NNPopulation.h"
#include "NN/Structs/NNPopulationInformation.h"
#include "NNSaveGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSave, UNNPopulation*, Population);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoad);

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UNNSaveGame();

public:
	FSave Save;
	FLoad Load;

private:
	void ProcessPopulation(UNNPopulation* Population);
	void RestorePopulation();

public:
	UNNPopulation* Population;

	FNNPopulationInformation PopulationInformation;
};
