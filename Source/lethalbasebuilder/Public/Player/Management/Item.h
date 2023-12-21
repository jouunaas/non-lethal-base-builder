// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETHALBASEBUILDER_API UItem : public UActorComponent
{
	GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UItem();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    UTexture2D* itemImage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString itemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float weight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    bool bStackable;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    int32 itemCount;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    int32 maxItemCount;
};
