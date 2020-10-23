#include "BECapacitor.h"
#include "../ModSystem.h"

using namespace System;
using namespace Vintagestory::API::Client;

namespace TemporalTech
{
	void BECapacitor::Initialize(ICoreAPI ^api)
	{
		BlockEntity::Initialize(api);

		systemTemporalStability = api->ModLoader->GetModSystem<SystemTemporalStability ^>();
		api->World->RegisterGameTickListener(gcnew Vintagestory::API::Common::Action<float>(this, &BECapacitor::OnGameTickListener), 5000);

		modifier = gcnew AreaModifier{Pos, gcnew Sphere{Pos, 20}, gcnew ModifyTemporalStabilityDelegate(this, &BECapacitor::ModifyTemporalStability)};
		api->ModLoader->GetModSystem<SystemTemporalTech ^>()->RegisterTemporalStabilityModifier(modifier);
	}

	void BECapacitor::ToTreeAttributes(ITreeAttribute ^tree)
	{
		tree->SetDouble("charge", charge);
	}

	void BECapacitor::FromTreeAtributes(ITreeAttribute ^tree, IWorldAccessor ^accessor)
	{
		charge = tree->GetDouble("charge", 0.0);
	}

	void BECapacitor::OnBlockInteract(IPlayer ^player)
	{
	}

	void BECapacitor::OnBlockPlaced(ItemStack ^byItemStack)
	{
		BlockEntity::OnBlockPlaced(byItemStack);
	}

	void BECapacitor::OnBlockRemoved()
	{
		BlockEntity::OnBlockRemoved();

		Api->ModLoader->GetModSystem<SystemTemporalTech ^>()->UnregisterTemporalStabilityModifier(modifier);
	}
	
	void BECapacitor::OnGameTickListener(float dt)
	{
		//charge = Math::Min(charge - lastRequiredCharge, MaxCharge);
		charge = MaxCharge;
	}

	void BECapacitor::ModifyTemporalStability(double x, double y, double z, float %stability)
	{
		float difference{targetStability - stability};
		double requiredCharge{100 * difference};

		if (requiredCharge > 0 && charge < requiredCharge)
		{
			return;
		}

		stability = targetStability;
		lastRequiredCharge = requiredCharge;
	}
}