#pragma once

using namespace Vintagestory::API::Common;
using namespace Vintagestory::API::MathTools;

using System::String;

namespace TemporalTech
{
	public ref class BlockCapacitor : public Block
	{
	public:
		String ^GetPlacedBlockInfo(IWorldAccessor ^world, BlockPos ^pos, IPlayer ^forPlayer) override;
	};
}