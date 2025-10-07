#pragma once

#include <stdint.h>
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	namespace Hooks_TPP {
		void CreateHooks();
		ChangeLocationMenuParameter* GetChangeLocationMenuParameterByLocationIdHook(MotherBaseMissionCommonData* This, unsigned short locationCode);
	}//namespace Hooks_TPP
}//namespace IHHook