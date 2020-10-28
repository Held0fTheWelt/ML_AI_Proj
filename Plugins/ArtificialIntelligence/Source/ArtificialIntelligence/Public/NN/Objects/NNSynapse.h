/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "NNSynapse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetupSynapse, class UNNBrainNode*, Source, class UNNBrainNode*, Target);

/**
 * 
 */
UCLASS()
class ARTIFICIALINTELLIGENCE_API UNNSynapse : public UObject
{
	GENERATED_BODY()
	
public:
	UNNSynapse();

	FSetupSynapse SetupSynapse;

	void ReDoOnce();

	float GetWeightedValue();

public:
	UPROPERTY(VisibleAnywhere)
	class UNNBrainNode* Source;
	UPROPERTY(VisibleAnywhere)
	class UNNBrainNode* Target;
	UPROPERTY(VisibleAnywhere)
	float Weight;
	UPROPERTY(VisibleAnywhere)
	bool DoOnce;

private:
	void SetSynapseValues(class UNNBrainNode* Source, class UNNBrainNode* Target);

};
