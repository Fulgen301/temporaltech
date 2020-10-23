#pragma once

using namespace HarmonyLib;
using namespace System;

using namespace Vintagestory::API::Common;

namespace TemporalTech::Patch
{
	[HarmonyPatch(Vintagestory::GameContent::SystemTemporalStability::typeid, "GetTemporalStability")]
	[HarmonyPatch(gcnew array<Type ^>{double::typeid, double::typeid, double::typeid})]
	ref class SystemTemporalStability
	{
	public:
		static void Postfix(double x, double y, double z, float %__result, ICoreAPI ^___api);
	};
}