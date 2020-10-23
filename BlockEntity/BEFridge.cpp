#include "BEFridge.h"
#include "../ModSystem.h"

using namespace System;
using namespace System::Linq;

namespace TemporalTech
{
	void BEFridge::Initialize(ICoreAPI ^api)
	{
		BlockEntityGenericContainer::Initialize(api);

		modifier = gcnew AreaModifier{Pos, gcnew Sphere{Pos, 50}, gcnew ModifyTemporalStabilityDelegate(this, &BEFridge::ModifyTemporalStability)};
		api->ModLoader->GetModSystem<SystemTemporalTech ^>()->RegisterTemporalStabilityModifier(modifier);

		if (auto dict = safe_cast<InventoryGeneric ^>(Inventory)->PerishableFactorByFoodCategory; !dict)
		{
			safe_cast<InventoryGeneric ^>(Inventory)->PerishableFactorByFoodCategory = gcnew Dictionary<EnumFoodCategory, float>{};
		}

		perishableFactorByFoodCategory = gcnew Dictionary<EnumFoodCategory, float>{safe_cast<InventoryGeneric ^>(Inventory)->PerishableFactorByFoodCategory};
	}

	void BEFridge::OnBlockRemoved()
	{
		BlockEntityGenericContainer::OnBlockRemoved();
		Api->ModLoader->GetModSystem<SystemTemporalTech ^>()->UnregisterTemporalStabilityModifier(modifier);
	}

	void BEFridge::ModifyTemporalStability(double x, double y, double z, float %stability)
	{
		float neededStability{0.0f};

		auto inventory = safe_cast<InventoryGeneric ^>(Inventory);

		auto dict = gcnew Dictionary<EnumFoodCategory, float>{};

		for each (ItemSlot ^slot in inventory)
		{
			if (!slot->Itemstack)
			{
				continue;
			}

			if (FoodNutritionProperties ^nutritionProps{slot->Itemstack->Collectible->NutritionProps}; nutritionProps)
			{
				EnumFoodCategory foodCategory{slot->Itemstack->Collectible->NutritionProps->FoodCategory};

				float perishableFactor = 1.0f;
				if (!perishableFactorByFoodCategory->TryGetValue(foodCategory, perishableFactor))
				{
					perishableFactorByFoodCategory[foodCategory] = 1.0f;
				}
				
				dict[foodCategory] = perishableFactor;
				neededStability += perishableFactor * slot->StackSize * StabilityPerUnit;
			}
		}

		if (neededStability)
		{
			float percentage{Math::Min(stability / neededStability, 1.0f)};

			for each (auto key in Enumerable::ToList(dict->Keys))
			{
				dict[key] -= perishableFactorByFoodCategory[key] * percentage;
			}

			inventory->PerishableFactorByFoodCategory = gcnew Dictionary<EnumFoodCategory, float>{dict};

			stability = Math::Max(stability - neededStability, 0.0f);
		}
	}
}