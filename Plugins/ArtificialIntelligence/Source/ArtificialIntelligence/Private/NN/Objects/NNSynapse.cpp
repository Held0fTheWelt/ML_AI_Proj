/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "NN/Objects/NNSynapse.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/Object.h"
#include "NN/Objects/NNBrainNode.h"

UNNSynapse::UNNSynapse()
{
	SetupSynapse.AddDynamic(this, &UNNSynapse::SetSynapseValues);
	DoOnce = true;
}

void UNNSynapse::ReDoOnce()
{
	DoOnce = true;
}

float UNNSynapse::GetWeightedValue()
{
	if (Source != nullptr && Source->IsValidLowLevel())
	{

		return Source->Value * Weight;
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Synapse has no Source", true, true, FLinearColor::Red, 0.f);
		return 0.0f;
	}
}

void UNNSynapse::SetSynapseValues(UNNBrainNode* NewSource, UNNBrainNode* NewTarget)
{
	if (DoOnce == false)
	{
		return;
	}
	DoOnce = false;

	Source = NewSource;
	Target = NewTarget;
	Weight = FMath::RandRange(-5.f, 5.f);
}
