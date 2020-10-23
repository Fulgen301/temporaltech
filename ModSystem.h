#pragma once

#include "Modifier.h"

using namespace System::Collections::Generic;

using namespace Vintagestory::API::Common;
using namespace Vintagestory::API::MathTools;

namespace TemporalTech
{
	public ref class SystemTemporalTech : public ModSystem
	{
	public:
		bool ShouldLoad(EnumAppSide forSide) override;
		void Start(ICoreAPI ^api) override;

		void RegisterTemporalStabilityModifier(AreaModifier ^modifier);
		void UnregisterTemporalStabilityModifier(AreaModifier ^modifier);

		void RegisterTemporalStabilityModifier(double priority, ModifyTemporalStabilityDelegate ^modifier);
		void UnregisterTemporalStabilityModifier(double priority, ModifyTemporalStabilityDelegate ^modifier);

	internal:
		void ModifyTemporalStability(double x, double y, double z, float %original);

	private:
		ICoreAPI ^api;
		SortedSet<CoordinateModifier ^> ^modifiers;
	};
}