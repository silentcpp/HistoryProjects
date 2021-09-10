#include "ChipBurn.h"

BaseBurn* ChipBurn::allocBurn(ChipType type)
{
	BaseBurn* base = nullptr;
	switch (type)
	{
	case CT_ASX340_EEPROM_GEELY_BX11:
	case CT_ASX340_EEPROM_UNIVERSAL_SET:
	case CT_ASX340_FLASH_UNIVERSAL_SET:
		base = new(std::nothrow) Asx340;
		break;
	case CT_OV7958_FLASH_UNIVERSAL_SET:
		base = new(std::nothrow) Ov7958;
		break;
	case CT_OVX1E_FLASH_UNIVERSAL_SET:
		base = new(std::nothrow) Ovx1e;
		break;
	case CT_SONY016_EEPROM_UNIVERSAL_SET:
		base = new(std::nothrow) Sony016;
		break;
	case CT_SONY019_FLASH_UNIVERSAL_SET:
	case CT_SONY019_FLASH_CHANGAN_IMS:
	case CT_SONY019_FLASH_EP30TAP_DMS:
		base = new(std::nothrow) Sony019;
		break;
	default:
		type = CT_UNKNOWN;
		break;
	}
	if (base)
	{
		base->setChipType(type);
	}
	return base;
}

BaseBurn* ChipBurn::reallocBurn(ChipType type, BaseBurn* base)
{
	if (!base)
	{
		base = allocBurn(type);
	}
	else
	{
		if (base->getChipType() != type)
		{
			freeBurn(base);
			base = allocBurn(type);
		}
	}
	return base;
}

void ChipBurn::freeBurn(BaseBurn*& base)
{
	if (base)
	{
		delete base;
		base = nullptr;
	}
}
