#include "BlockCapacitor.h"
#include "../BlockEntity/BECapacitor.h"
#include "../ModSystem.h"

namespace TemporalTech
{

	String ^BlockCapacitor::GetPlacedBlockInfo(IWorldAccessor ^world, BlockPos ^pos, IPlayer ^forPlayer)
	{
		if (auto blockEntity = dynamic_cast<BECapacitor ^>(api->World->BlockAccessor->GetBlockEntity(pos)); blockEntity)
		{
			return String::Format("On: {0}\nCharge: {0}", blockEntity->On, blockEntity->Charge.ToString());
		}

		return "";
	}
}