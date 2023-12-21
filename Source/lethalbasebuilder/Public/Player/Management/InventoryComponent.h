// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETHALBASEBUILDER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UItem* item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<UItem*> GetInventoryItems() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItem* FindItemFromInventory(UItem* item);
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 invSlots;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UItem*> inventoryItems;

	bool IsItemStackable(const UItem* Item1, const UItem* Item2) const;
};