// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FSlot {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	UItem* item;

	FSlot()
		: item(nullptr) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETHALBASEBUILDER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FSlot> invSlots;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeInventory(int32 numberOfSlots) {
		invSlots.SetNum(numberOfSlots);
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UItem* item);

	// Function to check if a specific slot is occupied
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsSlotOccupied(int32 slotIndex) const
	{
		return slotIndex >= 0 && slotIndex < invSlots.Num() && invSlots.IsValidIndex(slotIndex) && invSlots[slotIndex].item;
	}

	// Function to get the item in a specific slot (if occupied)
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItem* GetItemInSlot(int32 slotIndex) const
	{
		return IsSlotOccupied(slotIndex) ? invSlots[slotIndex].item : nullptr;
	}

private:
	//UPROPERTY(EditAnywhere, Category = "Inventory")
	//int32 invSlots;
	
	//UPROPERTY(VisibleAnywhere)
	//TArray<UItem*> inventoryItems;

	bool IsItemStackable(const UItem* Item1, const UItem* Item2) const;
};