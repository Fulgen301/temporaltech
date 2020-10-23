#pragma once

using namespace System::Collections::Generic;

using namespace Vintagestory::API::Common;
using namespace Vintagestory::API::MathTools;

namespace TemporalTech
{
	public delegate void ModifyTemporalStabilityDelegate(double x, double y, double z, float %value);

	public ref class CoordinateModifier
	{
	public:
		ref class ByPriority : public IComparer<CoordinateModifier ^>
		{
		public:
			virtual int Compare(CoordinateModifier ^a, CoordinateModifier ^b)
			{
				if (int comp{a->priority.CompareTo(b->priority)}; comp == 0)
				{
					return !a->modifier->Equals(b->modifier);
				}
				else
				{
					return comp;
				}
			}
		};

	public:
		explicit CoordinateModifier(double priority, ModifyTemporalStabilityDelegate ^modifier) : priority{priority}, modifier{modifier} {}

		double priority;
		ModifyTemporalStabilityDelegate ^modifier;
	};

	public ref class Area abstract
	{
	public:
		virtual double InterpolationFactor(double x, double y, double z) = 0;
	};

	public ref class Cuboid : public Area
	{
	public:
		explicit Cuboid(IVec3 ^start, IVec3 ^end, double fade);
		double InterpolationFactor(double x, double y, double z) override;

	private:
		Cuboidd ^cuboid;
		double fade;
	};

	public ref class Sphere : public Area
	{
	public:
		explicit Sphere(BlockPos ^center, double radius) : center{center}, radiusSquared{radius * radius} {}
		double InterpolationFactor(double x, double y, double z) override;

	private:
		BlockPos ^center;
		double radiusSquared;
	};

	public ref class AreaModifier : public CoordinateModifier
	{
	public:
		explicit AreaModifier(BlockPos ^pos, Area ^area, ModifyTemporalStabilityDelegate ^modifier);
		void ModifyTemporalStability(double x, double y, double z, float %stability);

	public:
		static constexpr double DefaultPriority = 5.0;
		ModifyTemporalStabilityDelegate ^externalModifier;

	private:
		BlockPos ^pos;
		Area ^area;
	};
}