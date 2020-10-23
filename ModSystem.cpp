#include "ModSystem.h"
#include "SystemTemporalStabilityPatch.h"

#include "Block/BlockCapacitor.h"
#include "BlockEntity/BECapacitor.h"
#include "BlockEntity/BEFridge.h"

namespace TemporalTech
{
	bool SystemTemporalTech::ShouldLoad(EnumAppSide)
	{
		return true;
	}

	void SystemTemporalTech::Start(ICoreAPI ^api)
	{
		this->api = api;
		modifiers = gcnew SortedSet<CoordinateModifier ^>{gcnew CoordinateModifier::ByPriority{}};

		auto harmony = gcnew Harmony{"fulgen.temporaltech"};
		harmony->PatchAll();

		api->RegisterBlockClass("capacitor", BlockCapacitor::typeid);

		api->RegisterBlockEntityClass("capacitor", BECapacitor::typeid);
		api->RegisterBlockEntityClass("fridge", BEFridge::typeid);
	}

	void SystemTemporalTech::RegisterTemporalStabilityModifier(AreaModifier ^modifier)
	{
		modifiers->Add(modifier);
	}

	void SystemTemporalTech::UnregisterTemporalStabilityModifier(AreaModifier ^modifier)
	{
		modifiers->Remove(modifier);
	}

	void SystemTemporalTech::RegisterTemporalStabilityModifier(double priority, ModifyTemporalStabilityDelegate ^modifier)
	{
		modifiers->Add(gcnew CoordinateModifier{priority, modifier});
	}

	void SystemTemporalTech::UnregisterTemporalStabilityModifier(double priority, ModifyTemporalStabilityDelegate ^modifier)
	{
		for each (auto mod in modifiers)
		{
			if (mod->priority == priority && mod->modifier == modifier)
			{
				modifiers->Remove(mod);
				break;
			}
		}
	}

	void SystemTemporalTech::ModifyTemporalStability(double x, double y, double z, float %original)
	{
		float stability{original};

		for each (auto modifier in modifiers)
		{
			modifier->modifier(x, y, z, original);
#ifdef DEBUG
			if (original < 0.0f || original > 1.5f)
			{
				throw gcnew System::InvalidOperationException{"Temporal stability out of range"};
			}
#endif
		}

		original = GameMath::Clamp(original, 0.0f, 1.5f);
	}
}
