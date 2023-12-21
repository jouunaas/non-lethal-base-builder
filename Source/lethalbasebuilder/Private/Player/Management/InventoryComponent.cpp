// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Management/InventoryComponent.h"
#include "UObject/UObjectGlobals.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::AddItem(UItem* item) {
	if (!item) { return; }

    for (UItem* invItem : inventoryItems) {
        if (invItem && invItem->bStackable && IsItemStackable(invItem, item)) {
            // If the items can be stacked, calculate the remaining space in the stack
            int32 remainingSpace = invItem->maxItemCount - invItem->itemCount;

            // Add as many items as possible to the existing stack
            int32 numItemsToAdd = FMath::Min(remainingSpace, item->itemCount);
            invItem->itemCount += numItemsToAdd;

            // If there are remaining items, add them as a new stack
            int32 remainingItems = item->itemCount - numItemsToAdd;
            if (remainingItems > 0) {
                UItem* remainingItem = DuplicateObject(item, nullptr);
                remainingItem->itemCount = remainingItems;
                inventoryItems.Add(remainingItem);
            }
            return;
        }
    }
}

void UInventoryComponent::RemoveItem(UItem* item) {
	inventoryItems.Remove(item);
}

TArray<UItem*> UInventoryComponent::GetInventoryItems() const {
	return inventoryItems;
}

bool UInventoryComponent::IsItemStackable(const UItem* a, const UItem* b) const {
    // TODO: maybe implement logic for comparing item properties like weight, name etc.

    // check if items are same category and are stackable
    bool bSameCategory = a->itemName == b->itemName;
    bool bBothStackable = a->bStackable && b->bStackable;

    // check if stacking exceeds the maximum stack count
    bool bBelowMaxStackCount = (a->itemCount + b->itemCount) <= a->maxItemCount;

    return bSameCategory && bBothStackable && bBelowMaxStackCount;
}