#pragma once

#include <stdint.h>
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	namespace Hooks_TPP {
		enum PHOTO_TYPE : unsigned char {
			photo_type_h = 0,
			photo_type_v = 1,
			photo_type_v2 = 2,
		};
		enum PHOTO_TEXT : unsigned char {
			target_type_rescue = 1,
			target_type_recovery = 2,
			target_type_exclusion = 3,
			target_type_destruction = 4,
			target_type_tracking = 5,
			target_type_tailing = 6,
		};

		struct PhotoInfo {
			unsigned short MissionCode;
			unsigned char PhotoId;
			PHOTO_TYPE PhotoType;
			unsigned long long TargetTypeLangId;
		};
		void CreateHooks();
		ChangeLocationMenuParameter* GetChangeLocationMenuParameterByLocationIdHook(MotherBaseMissionCommonData* This, unsigned short locationCode);
		unsigned long long __thiscall GetPhotoAdditionalTextLangIdHook(MotherBaseMissionCommonData* This, StringId* ret, unsigned short missionCode, unsigned char photoId, unsigned char photoType);
		/*uint ConvertRadioTypeToSpeechLabelHook(ubyte radioType);
		ubyte ConvertSpeechLabelToRadioTypeHook(uint speechLabel);*/
		//bool IsRainingHook(void* Solider2,uint param2);
		//uint ConvertToVoiceTypeHook(uint voiceTypeS32);
		void AddPhotoAdditionalText(unsigned short missionCode, unsigned char photoId, unsigned char photoType, const char* targetTypeLangIdStr);
	}//namespace Hooks_TPP
}//namespace IHHook