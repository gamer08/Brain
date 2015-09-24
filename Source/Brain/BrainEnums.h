#pragma once

#include "BrainEnums.generated.h"

UENUM(BlueprintType)
namespace EAction
{
	enum Type /*: uint8*/
	{
		ROTATE = 1,
		TRANSLATE = 2,
		SCALE = 4,
		SHEAR = 8,
		FASTFWRD = 16,
		SLOW = 32,
		STOP = 64,
		REVERSE = 128
	};
}