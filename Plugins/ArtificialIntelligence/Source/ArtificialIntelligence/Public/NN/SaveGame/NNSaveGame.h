/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NN/Objects/NNPopulation.h"
#include "NN/Structs/NNPopulationInformation.h"
#include "NNSaveGame.generated.h"

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
	UNNPopulation Population;

	FNNPopulationInformation PopulationInformation;
};
