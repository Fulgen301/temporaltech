#include "Modifier.h"

namespace TemporalTech
{
	Cuboid::Cuboid(IVec3 ^start, IVec3 ^end, double fade) : cuboid{gcnew Cuboidd{start->XAsDouble, start->YAsDouble, start->ZAsDouble, end->XAsDouble, end->YAsDouble, end->ZAsDouble}}, fade{fade}
	{
	}

	double Cuboid::InterpolationFactor(double x, double y, double z)
	{
		return GameMath::Clamp(1.0 - cuboid->ShortestDistanceFrom(x, y, z) / fade, 0.0, 1.0);
	}

	double Sphere::InterpolationFactor(double x, double y, double z)
	{
		double distance{
		(x - center->X) * (x - center->X)
		+ (y - center->Y) * (y - center->Y)
		+ (z - center->Z) * (z - center->Z)
		};

		return GameMath::Clamp(1.0 - distance / radiusSquared, 0.0, 1.0);
	}

	AreaModifier::AreaModifier(BlockPos ^pos, Area ^area, ModifyTemporalStabilityDelegate ^modifier)
		: CoordinateModifier{DefaultPriority, gcnew ModifyTemporalStabilityDelegate(this, &AreaModifier::ModifyTemporalStability)},
		pos{pos}, area{area}, externalModifier{modifier}
	{
	}

	void AreaModifier::ModifyTemporalStability(double x, double y, double z, float %stability)
	{
		double interpolationFactor{area->InterpolationFactor(x, y, z)};

		if (interpolationFactor)
		{
			float s{stability};
			externalModifier(x, y, z, s);

			stability = stability + interpolationFactor * (s - stability);
		}
	}
}