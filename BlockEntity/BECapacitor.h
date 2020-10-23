#pragma once

#include "../Modifier.h"

using namespace Vintagestory::API::Common;
using namespace Vintagestory::API::Datastructures;
using namespace Vintagestory::API::MathTools;
using Vintagestory::GameContent::SystemTemporalStability;

namespace TemporalTech
{
	public ref class BECapacitor : BlockEntity
	{
	public:
		void Initialize(ICoreAPI ^api) override;
		void ToTreeAttributes(ITreeAttribute ^tree) override;
		void FromTreeAtributes(ITreeAttribute ^tree, IWorldAccessor ^accessor) override;

		void OnBlockInteract(IPlayer ^player);
		void OnBlockPlaced(ItemStack ^byItemStack) override;
		void OnBlockRemoved() override;

		void ModifyTemporalStability(double x, double y, double z, float %stability);

	private:
		void OnGameTickListener(float dt);

	public:
		property bool On { bool get() { return charge > 0; }}
		property double Charge { double get() { return charge; }}

	private:
		double charge{0};
		static constexpr double MaxCharge{1000.0};
		double lastRequiredCharge{0};
		float targetStability{1.0f};
		SystemTemporalStability ^systemTemporalStability;
		AreaModifier ^modifier;
	};
}