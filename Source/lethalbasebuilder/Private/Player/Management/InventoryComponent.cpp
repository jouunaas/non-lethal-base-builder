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

    int32 openSlots = invSlots - inventoryItems.Num();
    if (openSlots > 0) {
        if (item->bStackable) {
            for (UItem* invItem : inventoryItems) {
                if (invItem && invItem->bStackable && IsItemStackable(invItem, item)) {
                    // if items can stack, calculate remaining space in the stack
                    int32 remainingSpace = invItem->maxItemCount - invItem->itemCount;

                    // add as many items as possible to the existing stack
                    int32 numItemsToAdd = FMath::Min(remainingSpace, item->itemCount);
                    invItem->itemCount += numItemsToAdd;

                    // if there are items remaining, add them as a new stack
                    int32 remainingItems = item->itemCount - numItemsToAdd;
                    if (remainingItems > 0) {
                        UItem* remainingItem = DuplicateObject(item, nullptr);
                        remainingItem->itemCount = remainingItems;
                        inventoryItems.Add(remainingItem);
                    }
                    return;
                }
            }
            //inventoryItems.Add(item);
        }
        else {
            // TODO: add the item to an empty slot
        }
    }
    else { return; } // TODO: make it swap the item on the ground with the item selected
}

void UInventoryComponent::RemoveItem(UItem* item) {
	inventoryItems.Remove(item);
}

TArray<UItem*> UInventoryComponent::GetInventoryItems() const {
	return inventoryItems;
}

UItem* UInventoryComponent::FindItemFromInventory(UItem* item){
    for (UItem* invItem : inventoryItems) {
        if (invItem == item) {
            return invItem;
        }
    }
    return nullptr; // item not found
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