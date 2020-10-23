#include "ModSystem.h"
#include "SystemTemporalStabilityPatch.h"

namespace TemporalTech::Patch
{
	void SystemTemporalStability::Postfix(double x, double y, double z, float %__result, ICoreAPI ^___api)
	{
		___api->ModLoader->GetModSystem<SystemTemporalTech ^>()->ModifyTemporalStability(x, y, z, __result);
	}
}