#pragma once
#include "Burn/ASX340/ASX340.h"
#include "Burn/Sony016/Sony016.h"
#include "Burn/Sony019/Sony019.h"
#include "Burn/OV7958/OV7958.h"
#include "Burn/0VX1E/OVX1E.h"

namespace ChipBurn {
	BaseBurn* allocBurn(ChipType type);

	BaseBurn* reallocBurn(ChipType type, BaseBurn* base);

	void freeBurn(BaseBurn*& base);
}
