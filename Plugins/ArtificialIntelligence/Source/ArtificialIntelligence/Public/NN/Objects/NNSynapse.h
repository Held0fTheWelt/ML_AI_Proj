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

	UFUNCTION(BlueprintCallable)
	void ReDoOnce();

	UFUNCTION(BlueprintCallable)
	float GetWeightedValue();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNNBrainNode* Source;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNNBrainNode* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoOnce;

private:
	UFUNCTION()
	void SetSynapseValues(class UNNBrainNode* NewSource, class UNNBrainNode* NewTarget);

};
