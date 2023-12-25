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

    if (item->bStackable) {
        // find existing stack to stack the item
        for (const FSlot& slot : invSlots) {
            if (slot.item && IsItemStackable(slot.item, item)) {
                // calculate remaining space in the stack
                int32 remainingSpace = slot.item->maxItemCount - slot.item->itemCount;

                // add as many items as possible to the existing stack
                int32 numItemsToAdd = FMath::Min(remainingSpace, item->itemCount);

                // update item counts
                slot.item->itemCount += numItemsToAdd;
                item->itemCount -= numItemsToAdd;

                // if items left, recursively call func again
                if (item->itemCount > 0) { AddItem(item); }
                return; // item has been stacked, exit the function
            }
        }
    }

    // if item isnt stackable or no stackable slot found, try to find empty slot
    for (FSlot& slot : invSlots) {
        if (slot.item == nullptr) {
            slot.item = item;
        }
    }
}

void UInventoryComponent::RemoveItem(UItem* item) {
	//TODO: REMOVE ITEM
}

bool UInventoryComponent::IsItemStackable(const UItem* a, const UItem* b) const {
    // logic for comparing item properties like weight, name etc.
    bool bSameItem = a->itemName == b->itemName;
    bool bBothStackable = a->bStackable && b->bStackable;
    // just checking if the stack is full or not
    bool bBelowMaxStackCount = a->itemCount < a->maxItemCount;

    return bSameItem && bBothStackable && bBelowMaxStackCount;
}