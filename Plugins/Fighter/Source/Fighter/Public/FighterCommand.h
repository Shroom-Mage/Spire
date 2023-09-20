#pragma once

#include "FighterCommand.generated.h"

UENUM(BlueprintType)
enum class FighterCommand
{
	EMPTY = -1,
	ATTACK_NORMAL = 0,
	ATTACK_SPECIAL,
	FORWARD,
	BACKWARD,
	DASH_FORWARD,
	DASH_BACKWARD,
	JUMP,
	CROUCH,
	DODGE,
	GROUND,
	END
};