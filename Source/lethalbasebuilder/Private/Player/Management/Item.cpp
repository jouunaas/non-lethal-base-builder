// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Management/Item.h"

// Sets default values for this component's properties
UItem::UItem()
{
	PrimaryComponentTick.bCanEverTick = false;

	bStackable = false;
	itemCount = 1;
	maxItemCount = 1;
}