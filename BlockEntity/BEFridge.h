#pragma once

#include "../Modifier.h"

using namespace System::Reflection;
using namespace Vintagestory::API::Common;
using Vintagestory::GameContent::BlockEntityGenericContainer;

namespace TemporalTech
{
	public ref class BEFridge : public BlockEntityGenericContainer
	{
	public:
		void Initialize(ICoreAPI ^api) override;
		void OnBlockRemoved() override;

	private:
		void ModifyTemporalStability(double x, double y, double z, float %stability);

	private:
		AreaModifier ^modifier;
		static constexpr float StabilityPerUnit = 0.005f;
		Dictionary<EnumFoodCategory, float> ^perishableFactorByFoodCategory;
	};
}