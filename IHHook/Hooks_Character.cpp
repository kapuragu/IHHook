//tex WIP exploring
// Extending vars.player* character change system

//GOTCHA: AVATAR player parts not being identical to SNAKE cause the change to fail to load in ACC
//something to do with 2nd player instance for the 'reflection' i guess
//does not seem to cause an issue in-mission where there is only the singular player instance


#include "Hooks_Character.h"
#include "spdlog/spdlog.h"
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_Character {
		bool overrideCharacterSystem = false;//tex TODO: dont know if I want just an overall 'using ih overrides' or per-type override values

		static const int MAX_HAND_TYPE = 8;//
		static const int MAX_HORN_LEVEL = 3;
		static const int MAX_SNAKE_FACEID = 3; //aka MAX_HORN_LEVEL
		static const int MAX_SNAKE_FACES = 2;//NORMAL/BANDANA
		struct Character {
			uint playerType = PlayerType_MAX;
			uint playerPartsType = PlayerPartsType_MAX;
			bool useHead = false;
			bool useBionicHand = false;
			bool useCamo = false;
			std::string playerPartsFpkPath = "";
			std::string playerPartsPartsPath = "";
			std::string skinToneFv2Path = "";
			std::string playerCamoFpkPath = "";
			std::string playerCamoFv2Path = "";
			std::string snakeFaceFpkPath = "";
			std::string snakeFaceFv2Path = "";
			std::string avatarHornFpkPath = "";
			std::string avatarHornFv2Path = "";
			std::string bionicHandFpkPath = "";
			std::string bionicHandFv2Path = "";

			//tex old/alt style of per-param settings
			//std::string snakeFaceFpks[MAX_SNAKE_FACEID * MAX_SNAKE_FACES]{
			//	"",//Horn 0
			//	"",//Horn 1
			//	"",//Horn 2
			//	"",//Horn 0 Bandana
			//	"",//Horn 1 Bandana
			//	"",//Horn 2 Bandana
			//};
			//std::string snakeFaceFv2s[MAX_SNAKE_FACEID * MAX_SNAKE_FACES]{
			//	"",
			//	"",
			//	"",
			//	"",
			//	"",
			//	"",
			//};
			//std::string bionicHandFpks[MAX_HAND_TYPE]{
			//	"",//NONE
			//	"",//NORMAL
			//	"",//STUN_ARM
			//	"",//JEHUTY
			//	"",//STUN_ROCKET
			//	"",//KILL_ROCKET
			//	"",//GOLD
			//	"",//SILVER
			//};
			//std::string bionicHandFv2s[MAX_HAND_TYPE]{
			//	"",
			//	"",
			//	"",
			//	"",
			//	"",
			//	"",
			//	"",
			//	"",
			//};
			//std::string avatarHornFpks[MAX_HORN_LEVEL]{
			//	"",
			//	"",
			//	"",
			//};
			//std::string avatarHornFv2s[MAX_HORN_LEVEL]{
			//	"",
			//	"",
			//	"",
			//};
		};//Character

		Character character;

		int l_SetOverrideCharacterSystem(lua_State* L) {
			overrideCharacterSystem = lua_toboolean(L, -1);

			spdlog::debug("l_SetOverrideCharacterSystem override:{}, ", overrideCharacterSystem);

			return 0;
		}//l_SetOverrideCharacterSystem
		//playerType 255 = none
		//lua l_SetPlayerTypeForPartsType(uint playerType)
		int l_SetPlayerTypeForPartsType(lua_State* L) {
			character.playerType = (uint)lua_tointeger(L, -1);

			spdlog::debug("l_SetPlayerTypeForPartsType playerType:{}, ", character.playerType);

			return 0;
		}//l_SetPlayerTypeForPartsType
		//lua l_SetPlayerTypeForPartsType(uint playerType)
		int l_SetPlayerPartsTypeForPartsType(lua_State* L) {
			character.playerPartsType = (uint)lua_tointeger(L, -1);

			spdlog::debug("l_SetPlayerPartsTypeForPartsType playerType:{}, ", character.playerPartsType);

			return 0;
		}//l_SetPlayerPartsTypeForPartsType
		//lua SetUseHeadForPlayerParts(bool override)
		int l_SetUseHeadForPlayerParts(lua_State* L) {
			character.useHead = lua_toboolean(L, -1);

			spdlog::debug("l_SetUseHeadForPlayerParts useHeadForPlayerParts:{}, ", character.useHead);

			return 0;
		}//l_SetUseHeadForPlayerParts
		//lua SetUseBionicHandForPlayerParts(bool override)
		int l_SetUseBionicHandForPlayerParts(lua_State* L) {
			character.useBionicHand = lua_toboolean(L, -1);

			spdlog::debug("l_SetUseBionicHandForPlayerParts useBionicHand:{}, ", character.useBionicHand);

			return 0;
		}//l_SetUseBionicHandForPlayerParts
		//lua SetUseCamoForPlayerParts(bool override)
		int l_SetUseCamoForPlayerParts(lua_State* L) {
			character.useCamo = lua_toboolean(L, -1);

			spdlog::debug("l_SetUseCamoForPlayerParts useCamo:{}, ", character.useCamo);

			return 0;
		}//l_SetUseCamoForPlayerParts


		int l_SetPlayerPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetPlayerPartsFpkPath {}, ", filePath);
			character.playerPartsFpkPath = filePath;

			return 0;
		}//l_SetPlayerPartsFpkPath

		int l_SetPlayerPartsPartsPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetPlayerPartsPartsPath {}, ", filePath);
			character.playerPartsPartsPath = filePath;

			return 0;
		}//l_SetPlayerPartsPartsPath

		int l_SetSkinToneFv2Path(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetSkinToneFv2Path {}, ", filePath);
			character.skinToneFv2Path = filePath;

			return 0;
		}//l_SetSkinToneFv2Path

		int l_SetPlayerCamoFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetPlayerCamoFpkPath {}, ", filePath);
			character.playerCamoFpkPath = filePath;

			return 0;
		}//l_SetPlayerCamoFpkPath

		int l_SetPlayerCamoFv2Path(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetPlayerCamoFv2Path {}, ", filePath);
			character.playerCamoFv2Path = filePath;

			return 0;
		}//l_SetPlayerCamoFv2Path

		//lua SetBionicHandFpkPath(int playerHandType, string fpkPath)
		int l_SetBionicHandFpkPath(lua_State* L) {
			uint playerHandType = (uint)lua_tointeger(L, -2);
			if (playerHandType == 0) {
				//spdlog::warn("l_SetBionicHandFpkPath cannot override playerHandType 0/NONE");
				//DEBUGNOW return 0;
			}

			if (playerHandType >= MAX_HAND_TYPE) {//SILVER
				spdlog::warn("l_SetBionicHandFpkPath playerHandType outside valid range: {}, ", playerHandType);
				return 0;
			}

			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetBionicHandFpkPath playerHandType:{} = {}, ", playerHandType, filePath);
			//CULL character.bionicHandFpks[playerHandType] = filePath;
			character.bionicHandFpkPath = filePath;

			return 0;
		}//l_SetBionicHandFpkPath
		//lua SetBionicHandFv2Path(int playerHandType, string fv2Path)
		int l_SetBionicHandFv2Path(lua_State* L) {
			uint playerHandType = (uint)lua_tointeger(L, -2);
			if (playerHandType == PlayerHandType_NONE) {
				spdlog::warn("l_SetBionicHandFv2Path cannot override playerHandType 0/NONE");
				//DEBUGNOW return 0;
			}

			if (playerHandType >= MAX_HAND_TYPE) {//SILVER
				spdlog::warn("l_SetBionicHandFv2Path playerHandType outside valid range: {}, ", playerHandType);
				return 0;
			}

			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetBionicHandFv2Path playerHandType:{} = {}, ", playerHandType, filePath);
			//CULL character.bionicHandFv2s[playerHandType] = filePath;
			character.bionicHandFv2Path = filePath;

			return 0;
		}//l_SetBionicHandFv2Path

		//lua SetSnakeFaceFpkPath(string fpkPath)
		int l_SetSnakeFaceFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}

			character.snakeFaceFpkPath = filePath;

			return 0;
		}//l_SetSnakeFaceFpkPath
		//lua SetSnakeFaceFv2Path(string fpkPath)
		int l_SetSnakeFaceFv2Path(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}

			character.snakeFaceFv2Path = filePath;

			return 0;
		}//l_SetSnakeFaceFv2Path

		//lua SetAvatarHornFpkPath(uint hornLevel, string fpkPath)
		int l_SetAvatarHornFpkPath(lua_State* L) {
			uint hornLevel = (uint)lua_tointeger(L, -2);

			if (hornLevel > MAX_HORN_LEVEL) {
				spdlog::debug("l_SetAvatarHornFpkPath hornLevel outside valid range: {}, ", hornLevel);
				return 0;
			}

			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetAvatarHornFpkPath hornLevel:{} = {}, ", hornLevel, filePath);
			//CULL character.avatarHornFpks[hornLevel] = filePath;
			character.avatarHornFpkPath = filePath;

			return 0;
		}//l_SetAvatarHornFpkPath
		//lua SetAvatarHornFv2Path(uint hornLevel, string fpkPath)
		int l_SetAvatarHornFv2Path(lua_State* L) {
			uint hornLevel = (uint)lua_tointeger(L, -2);

			if (hornLevel > MAX_HORN_LEVEL) {
				spdlog::debug("l_SetAvatarHornFv2Path hornLevel outside valid range: {}, ", hornLevel);
				return 0;
			}

			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetAvatarHornFv2Path hornLevel:{} = {}, ", hornLevel, filePath);
			//CULL character.avatarHornFv2s[hornLevel] = filePath;
			character.avatarHornFv2Path = filePath;

			return 0;
		}//l_SetAvatarHornFpkPath

		bool IsPlayerTypeValid(uint playerType) {
			spdlog::debug("IsPlayerTypeValid playerType:{}, character.playerType:{}", playerType, character.playerType);
			if (character.playerType == PlayerType_MAX) {
				return true;
			}

			if (character.playerType == playerType) {
				return true;
			}

			//WORKAROUND: vanilla treats SNAKE/AVATAR the same, and theres some oddness going on when they have different parts in helispace due to the mirror venom/other player instance
			if ((character.playerType == PlayerType_SNAKE && playerType == PlayerType_AVATAR) 
				|| (character.playerType == PlayerType_AVATAR && playerType == PlayerType_SNAKE)) {
				return true;
			}
			
			return false;
		}//IsPlayerTypeValid

		bool IsPlayerPartsTypeValid(uint playerPartsType) {
			if (character.playerPartsType == PlayerType_MAX) {
				return true;
			}

			if (character.playerPartsType == playerPartsType) {
				return true;
			}

			return false;
		}//IsPlayerPartsTypeValid
		
		bool isPlayerPartsFpkForAvatarRequested=false;

		uint64_t* GetPartsFpkPathHook(uint64_t* fileSlotIndex, uint playerType, uint playerPartsType) {
			spdlog::debug("GetPartsFpkPathHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
			isPlayerPartsFpkForAvatarRequested=false;

			if (!IsPlayerTypeValid(playerType) || character.playerPartsFpkPath == "") {
				//DEBUGNOW ASSUMPTION: this being the first extended function were hooking
				//tex turn it off entirely if it doesnt match
				//DEBUGNOW the funcs not gated by overrideCharacterSystem
				spdlog::debug("GetPartsFpkPathHook overrideCharacterSystem:{}, character.playerPartsPartsPath:{}", overrideCharacterSystem,character.playerPartsFpkPath);
				overrideCharacterSystem = false;
			}

			//tex fall back to original function
			if (!overrideCharacterSystem) {
				spdlog::debug("GetPartsFpkPathHook overrideCharacterSystem is false, use vanilla");
				return GetPartsFpkPath(fileSlotIndex, playerType, playerPartsType);
			}

			//tex HOSPITAL, AVATAR_EDIT_MAN too much going on with this to be safe
			if (playerPartsType == PlayerPartsType_HOSPITAL 
				|| playerPartsType == PlayerPartsType_AVATAR_EDIT_MAN) {
				spdlog::debug("GetPartsFpkPathHook is 3 or 14, use vanilla");
				return GetPartsFpkPath(fileSlotIndex, playerType, playerPartsType);
			}

			//DEBUGNOW (WORKAROUND breaks valid use of AVATAR plParts 0) trying to figure out crash problem https://github.com/TinManTex/InfiniteHeaven/issues/32
			//logging exec flow noticed that loading in to ACC there's an extra call to loadplayer for AVATAR only (before the expected calls to both player instance 0, and 1/AVATAR)
			//which is neither here not there, but for !needHead (talking about underlying property rather than IHH implementation) playerParts it always calls with playerPartsType 0 reguardless of actual playerPartsType. 
			//the calls following that have the correct playerPartsType, and playerParts with needHead have the correct playerPartsType
			if (playerType == PlayerType_AVATAR && playerPartsType == PlayerPartsType_NORMAL) {
				spdlog::debug("GetPartsFpkPathHook player type is 3 and parts is 0");
				spdlog::debug("GetPartsFpkPathHook isPlayerPartsFpkForAvatarRequested:{}",isPlayerPartsFpkForAvatarRequested);
				if (!isPlayerPartsFpkForAvatarRequested)
				{
					isPlayerPartsFpkForAvatarRequested=true;
					return GetPartsFpkPath(fileSlotIndex, playerType, playerPartsType);
				}
			}

			//TODO: if I ever get a 'does file exist' check
			spdlog::debug("character.playerPartsFpkPath: {}", character.playerPartsFpkPath);
			uint64_t filePath64 = PathCode64(character.playerPartsFpkPath.c_str());
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetPartsFpkPathHook

		uint64_t* GetPartsFilePathHook(uint64_t* fileSlotIndex, uint playerType, uint playerPartsType) {
			spdlog::debug("GetPartsFilePathHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
			
			if (!IsPlayerTypeValid(playerType) || character.playerPartsPartsPath == "") {
				//tex as above, but to catch odd cases (GetPartsFilePath is called on mission load without GetPartsFpkPath)
				spdlog::debug("GetPartsFilePathHook overrideCharacterSystem:{}, character.playerPartsPartsPath:{}", overrideCharacterSystem,character.playerPartsPartsPath);
				overrideCharacterSystem = false;
			}

			//tex fall back to original function
			if (!overrideCharacterSystem) {
				spdlog::debug("GetPartsFilePathHook overrideCharacterSystem is false, use vanilla");
				return GetPartsFilePath(fileSlotIndex, playerType, playerPartsType);			
			}

			//tex HOSPITAL, AVATAR_EDIT_MAN too much going on with this to be safe
			if (playerPartsType == PlayerPartsType_HOSPITAL 
				|| playerPartsType == PlayerPartsType_AVATAR_EDIT_MAN) {
				spdlog::debug("GetPartsFilePathHook is 3 or 14, use vanilla");
				return GetPartsFilePath(fileSlotIndex, playerType, playerPartsType);
			}

			//DEBUGNOW			
			if (playerType == PlayerType_AVATAR && playerPartsType == PlayerPartsType_NORMAL) {
				spdlog::debug("GetPartsFilePathHook player type is 3 and parts is 0");
				spdlog::debug("GetPartsFilePathHook isPlayerPartsFpkForAvatarRequested:{}",isPlayerPartsFpkForAvatarRequested);
				if (isPlayerPartsFpkForAvatarRequested) {
					spdlog::debug("GetPartsFilePathHook character.playerType:{} playerType:{} character.playerPartsType:{}",character.playerType,playerType);
					isPlayerPartsFpkForAvatarRequested=false;
					return GetPartsFilePath(fileSlotIndex, playerType, playerPartsType);
				}
			}

			//TODO: if I ever get a 'does file exist' check
			spdlog::debug("character.playerPartsPartsPath: {}", character.playerPartsPartsPath);
			uint64_t filePath64 = PathCode64(character.playerPartsPartsPath.c_str());
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetPartsFilePathHook

		//UNUSED parts/fpk alternate > 
		//[playerType][playerPartsType]=PathCodeExt64.
		std::map<uint, std::map<uint, std::string>> playerPartsFpk = {
			{PlayerType_SNAKE,{//SNAKE
					//manual tests
					//{4,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"},//4/MGS1 > ninja test swap
					//{24,"/Assets/tpp/pack/player/parts/plparts_ocelot.fpk"}//24/non existant partsTypeEnum test
				},//MGS snake
			},
			{PlayerType_DD_MALE,{//DD_MALE
					//{4,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"},
					//{24,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"}
				},//MGS snake
			},
			{PlayerType_DD_FEMALE,{}},//DD_FEMALE
			{PlayerType_AVATAR,{//AVATAR
					//{4,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"},
					//{24,"/Assets/tpp/pack/player/parts/plparts_ninja.fpk"}
				},//MGS snake
			},
			{PlayerType_LIQUID,{}},//LIQUID
			{PlayerType_OCELOT,{}},//OCELOT
			{PlayerType_QUIET,{}},//QUIET
		};
		std::map<uint, std::map<uint, std::string>> playerPartsParts = {
			{PlayerType_SNAKE,{//SNAKE
					//{4,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"},//MGS1 > ninja test swap
					//{284,"/Assets/tpp/parts/chara/ooc/ooc0_main1_def_v00.parts"}//28/non existant partsTypeEnum test
				},//MGS snake
			},
			{PlayerType_DD_MALE,{//DD_MALE
					//{4,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"},
					//{28,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"}
				},//MGS snake
			},
			{PlayerType_DD_FEMALE,{}},//DD_FEMALE
			{PlayerType_DD_FEMALE,{//AVAT
					//{4,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"},
					//{28,"/Assets/tpp/parts/chara/nin/nin0_main0_def_v00.parts"}
				},//MGS snake
			},
			{PlayerType_LIQUID,{}},//LIQUID
			{PlayerType_OCELOT,{}},//OCELOT
			{PlayerType_QUIET,{}},//QUIET
		};

		//input: uint playerType, uint playerPartsType, string fpkPath
		//REF IH InfMission.UpdateChangeLocationMenu //DEBUGNOW
		//int l_SetPlayerPartsFpk(lua_State* L) {
		//	spdlog::trace(__func__);

		//	//TODO: validate param types

		//	uint playerType = (uint)lua_tointeger(L, -3);
		//	uint playerPartsType = (uint)lua_tointeger(L, -2);
		//	const char* filePath = lua_tostring(L, -1);

		//	if (playerType > 255) {
		//		spdlog::error("l_SetPlayerPartsFpk set playerType > max value of 255");
		//		return 0;
		//	}
		//	if (playerPartsType > 255) {
		//		spdlog::error("l_SetPlayerPartsFpk set playerPartsType > max value of 255");
		//		return 0;
		//	}

		//	try {
		//		auto pathsForPlayerType = playerPartsFpk.at(playerType);
		//		//TODO: log existing path if its being overwritten
		//		//pathsForPlayerType[playerPartsType] = fpkPath;//tex i guess at is returning a new sub map or something because setting it like this doesnt actually change playerPartsFpk
		//		playerPartsFpk[playerType][playerPartsType] = std::string(filePath);
		//		
		//		spdlog::debug("l_SetPlayerPartsFpk set playerType: {} playerPartsType: {} to {}", playerType, playerPartsType, filePath);
		//	}
		//	catch (const std::out_of_range&) {
		//		spdlog::debug("l_SetPlayerPartsFpk playerPartsFpk could not find for playerType: {}", playerType);
		//	}

		//	return 0;
		//}//l_SetPlayerPartsFpk
		//REF IH InfMission.UpdateChangeLocationMenu //DEBUGNOW
		//int l_SetPlayerPartsPart(lua_State* L) {
		//	spdlog::trace(__func__);

		//	//TODO: validate param types

		//	uint playerType = (uint)lua_tointeger(L, -3);
		//	uint playerPartsType = (uint)lua_tointeger(L, -2);
		//	const char* filePath = lua_tostring(L, -1);

		//	if (playerType > 255) {
		//		spdlog::error("l_SetPlayerPartsPart set playerType > max value of 255");
		//		return 0;
		//	}
		//	if (playerPartsType > 255) {
		//		spdlog::error("l_SetPlayerPartsPart set playerPartsType > max value of 255");
		//		return 0;
		//	}

		//	try {
		//		auto pathsForPlayerType = playerPartsParts.at(playerType);
		//		//TODO: log existing path if its being overwritten
		//		playerPartsParts[playerType][playerPartsType] = std::string(filePath);
		//		spdlog::debug("l_SetPlayerPartsPart set playerType: {} playerPartsType: {} to {}", playerType, playerPartsType, filePath);
		//	}
		//	catch (const std::out_of_range&) {
		//		spdlog::debug("l_SetPlayerPartsPart playerPartsParts could not find for playerType: {}", playerType);
		//	}

		//	return 0;
		//}//l_SetPlayerPartsPart

		//tex OFF a better way to allow swapping and extending to other playerPartsType values
		//but because of that will hit the saved at no longer valid value if user uninstalls mod problem.
		//uint64_t* GetPartsFpkPathAlt(uint64_t* fileSlotIndex, uint playerType, uint playerPartsType) {
		//	spdlog::debug("GetPartsFpkPath playerType:{}, playerPartsType:{}", playerType, playerPartsType);
		//	uint64_t filePath64 = 0;

		//	//tex see GOTCHA: above
		//	if (playerType == 3) {
		//		playerType = 0;
		//	}

		//	try {
		//		auto pathsForPlayerType = playerPartsFpk.at(playerType);
		//		try {
		//			auto filePath = pathsForPlayerType.at(playerPartsType);
		//			filePath64 = PathCode64(filePath.c_str());
		//			//filePath64 = 0x522a5fbda65be993;
		//			foxPathPath(fileSlotIndex, filePath64);

		//			return fileSlotIndex;
		//		}
		//		catch (const std::out_of_range&) {
		//			spdlog::debug("GetPartsFpkPathHook pathsForPlayerType could not find for playerPartsType: {}", playerPartsType);
		//			filePath64 = 0;
		//		}		
		//	}
		//	catch (const std::out_of_range&) {
		//		spdlog::debug("GetPartsFpkPathHook playerPartsFpk could not find for playerType: {}", playerType);
		//	}
		//	//tex fall back to original function
		//	GetPartsFpkPath(fileSlotIndex, playerType, playerPartsType);
		//	return fileSlotIndex;
		//}//GetPartsFpkPathAlt

		//uint64_t* GetPartsFilePathAlt(uint64_t* fileSlotIndex, uint playerType, uint playerPartsType) {
		//	spdlog::debug("GetPartsFilePathHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
		//	uint64_t filePath64 = 0;

		//	//tex see GOTCHA: above
		//	if (playerType == 3) {
		//		playerType = 0;
		//	}

		//	try {
		//		auto pathsForPlayerType = playerPartsParts.at(playerType);
		//		try {
		//			auto filePath = pathsForPlayerType.at(playerPartsType);
		//			filePath64 = PathCode64(filePath.c_str());
		//			foxPathPath(fileSlotIndex, filePath64);

		//			return fileSlotIndex;
		//		}
		//		catch (const std::out_of_range&) {
		//			spdlog::debug("GetPartsFilePathHook pathsForPlayerType could not find for playerPartsType: {}", playerPartsType);
		//			filePath64 = 0;
		//		}
		//	}
		//	catch (const std::out_of_range&) {
		//		spdlog::debug("GetPartsFilePathHook playerPartsParts could not find for playerType: {}", playerType);
		//	}
		//	//tex fall back to original function
		//	GetPartsFilePath(fileSlotIndex, playerType, playerPartsType);
		//	return fileSlotIndex;
		//}//GetPartsFilePathAlt
		//parts/fpk alternate<

		//OFF REF
		//ulonglong* GetCamoFpkPathORIG(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
		//	spdlog::debug("GetCamoFpkPathHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
		//	uint64_t fpkPath = 0;

		//	if ((playerType == 0) || (playerType == 3)) {//SNAKE, AVATAR
		//		//ORIG
		//		if ((20 < playerPartsType - 2) && (playerPartsType < 26)) {
		//		//playerPartsType - 2 means 0 NORMAL and 1 SCARF will underflow uint playerPartsType to FFFFF/E, 
		//		//so 20 < is true
		//		//and then on the other end of the range 23 SWIMWEAR (and above) - 2 == 21 which is 20 <
		//		//playerPartsType < 26 OCELLOT is current playerPartsType max
		//		//but after all that, snake/avat don't have swimsuit and just has default fatigues for those entries
		//		//DEBRAINTEASED
		//		//if ((playerPartsType < 2) || (playerPartsType > 22 && playerPartsType < 26)) {
		//			fpkPath = (&SnakeNormalCamoFpkArray_DAT_142a80a10)[(uint64_t)playerCamoType * 2];
		//			return GetCamoFpkPath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
		//		}

		//		if (playerPartsType == 7) {//NAKED
		//			fpkPath = (&SnakeNakedCamoFpkArray_DAT_142a81160)[(uint64_t)playerCamoType * 2];
		//			return GetCamoFpkPath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
		//		}
		//	}
		//	else {
		//		if (playerType == 1) {//DD_MALE
		//			fpkPath = (&DDMaleCamoFpkArray_DAT_142a818b0)[(uint64_t)playerCamoType * 2];
		//			return GetCamoFpkPath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
		//		}
		//		if (playerType == 2) {//DD_FEMALE
		//			fpkPath = (&DDFemaleCamoFpkArray_DAT_142a82000)[(uint64_t)playerCamoType * 2];
		//			return GetCamoFpkPath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
		//		}
		//	}

		//	foxPathPath(fileSlotIndex, fpkPath);
		//	return fileSlotIndex;
		//}//GetCamoFpkPathORIG
		bool IsValidPlayerCamo() {
			if (character.playerCamoFpkPath == "" || character.playerCamoFv2Path == "")
				return false;

			return true;
		}

		bool UseVanillaPlayerCamo(uint playerType, uint playerPartsType, uint playerCamoType) {
			if (playerCamoType == PlayerCamoType_MAX) {
				return false;
			}
			if (playerType == PlayerType_SNAKE
				|| playerType == PlayerType_AVATAR) {
				if (PlayerPartsType_SWIMWEAR <= playerPartsType 
					&& playerPartsType <= PlayerPartsType_SWIMWEAR_H) {
					return true;
				}
				if (playerPartsType == PlayerPartsType_NAKED) {
					return true;
				}
			}
			else {
				if (playerType == PlayerType_DD_MALE) {
					return true;
				}
				if (playerType == PlayerType_DD_FEMALE) {
					return true;
				}
			}
			return false;
		}

		ulonglong* GetCamoFpkPathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
			spdlog::debug("GetCamoFpkPathHook playerType:{}, playerPartsType:{}, playerCamoType:{}", playerType, playerPartsType, playerCamoType);

			if (!IsValidPlayerCamo()) {
				return GetCamoFpkPath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
			}

			//tex HOSPITAL, AVATAR_EDIT_MAN too much going on with this to be safe
			if (playerPartsType == PlayerPartsType_HOSPITAL 
				|| playerPartsType == PlayerPartsType_AVATAR_EDIT_MAN) {
				return GetCamoFpkPath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
			}

			if (playerCamoType == PlayerCamoType_MAX) {//tex I guess 255 is NONE/not set.
				foxPathPath(fileSlotIndex, 0);
				return fileSlotIndex;
			}

			bool useCamo = UseVanillaPlayerCamo(playerType, playerPartsType, playerCamoType);
			if (overrideCharacterSystem) {
				if (IsPlayerPartsTypeValid(playerPartsType)) {
					useCamo = character.useCamo;
				}
			}

			ulonglong filePath64 = 0;
			if (useCamo) {
				filePath64 = PathCode64(character.playerCamoFpkPath.c_str());
			}
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetCamoFpkPathHook

		ulonglong* GetCamoFilePathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
			spdlog::debug("GetCamoFilePathHook playerType:{}, playerPartsType:{}, playerCamoType:{}", playerType, playerPartsType, playerCamoType);
			
			if (!IsValidPlayerCamo()) {
				return GetCamoFilePath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
			}

			//tex HOSPITAL, AVATAR_EDIT_MAN too much going on with this to be safe
			if (playerPartsType == PlayerPartsType_HOSPITAL 
				|| playerPartsType == PlayerPartsType_AVATAR_EDIT_MAN) {
				return GetCamoFilePath(fileSlotIndex, playerType, playerPartsType, playerCamoType);
			}

			if (playerCamoType == PlayerCamoType_MAX) {//tex I guess 255 is NONE/not set.
				foxPathPath(fileSlotIndex, 0);
				return fileSlotIndex;
			}

			bool useCamo = UseVanillaPlayerCamo(playerType, playerPartsType, playerCamoType);
			if (overrideCharacterSystem) {
				if (IsPlayerPartsTypeValid(playerPartsType)) {
					useCamo = character.useCamo;
				}
			}

			ulonglong filePath64 = 0;
			if (useCamo) {
				filePath64 = PathCode64(character.playerCamoFv2Path.c_str());
			}
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetCamoFilePathHook

		//OFF REF
		//ulonglong* GetCamoFilePathHookORIG(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
		//	spdlog::debug("GetCamoFpkPathHook playerType:{}, playerPartsType:{}", playerType, playerPartsType);
		//	ulonglong fv2Path = 0;

		//	if (playerCamoType == 255) {//tex I guess 255 is NONE/not set.
		//		foxPathPath(fileSlotIndex, 0);
		//		return fileSlotIndex;
		//	}
		//	if ((playerType == 0) || (playerType == 3)) {//SNAKE,AVATAR
		//		//See GetCamoFpkPath
		//		if ((playerPartsType < 2) || (playerPartsType > 22 && playerPartsType < 26)) {
		//			//DEBUGNOW fv2Path = (&SnakeNormalCamoFv2Array_DAT_142a80a18)[(ulonglong)playerCamoType * 2];
		//		}
		//		if (playerPartsType == 7) {//NAKED
		//			//DEBUGNOW fv2Path = (&SnakeNakedCamoFv2Array_DAT_142a81168)[(ulonglong)playerCamoType * 2];
		//		}
		//	}
		//	else {
		//		if (playerType == 1) {//DD_MALE
		//			//DEBUGNOW fv2Path = (&DDMaleCamoFv2Array_DAT_142a818b8)[(ulonglong)playerCamoType * 2];
		//		}
		//		if (playerType == 2) {//DD_FEMALE
		//			//DEBUGNOW fv2Path = (&DDFemaleCamoFv2ArrayDAT_142a82008)[(ulonglong)playerCamoType * 2];
		//		}
		//	}

		//	foxPathPath(fileSlotIndex, fv2Path);
		//	return fileSlotIndex;
		//}//GetCamoFilePathORIG

		//TODO: there's also facialhelispace to deal with before I'm happy with extending this
		ulonglong* GetFacialMtarFpkPathHook(ulonglong* fileSlotIndex, uint playerType){
			spdlog::debug("GetFacialMtarFpkPathHook playerType:{}", playerType);
			
			long long filePath64 = 0x0;
			switch (PlayerType(playerType))
			{
			case PlayerType_DD_MALE:
				filePath64 = 0x522bba0fe696843e;	//	/Assets/tpp/pack/player/motion/player2_facial_dd_male.fpk
				break;
			case PlayerType_DD_FEMALE:
				filePath64 = 0x5228819af53ce132;	//	/Assets/tpp/pack/player/motion/player2_facial_dd_female.fpk
				break;
			case PlayerType_OCELOT:
				filePath64 = 0x522ad6eb108b656a;	//	/Assets/tpp/pack/player/motion/player2_facial_ocelot.fpk
				break;
			case PlayerType_QUIET:
				filePath64 = 0x522ad26ea9839391;	//	/Assets/tpp/pack/player/motion/player2_facial_quiet.fpk
				break;
			default:
				filePath64 = 0x522a1da4adfd5137;	//	SNAKE,AVATAR (default vanilla), LIQUID
				break;
			}
			foxPathPath(fileSlotIndex, filePath64);
			
			return fileSlotIndex;
		}//GetFacialMtarFpkPathHook

		//TODO: extend. just vanilla at the moment
		ulonglong* GetFacialMtarFilePathHook(ulonglong* fileSlotIndex, int playerType) {
			spdlog::debug("GetFacialMtarFilePathHook playerType:{}", playerType);
			
			long long filePath64 = 0x0;	//	/Assets/tpp/motion/mtar/player2/TppPlayer2Facial.mtar
			switch (PlayerType(playerType))
			{
			case PlayerType_DD_MALE:
				filePath64 = 0x67026b0d3dfd05e2;	//	/Assets/tpp/motion/mtar/player2/player2_ddm_facial.mtar
				break;
			case PlayerType_DD_FEMALE:
				filePath64 = 0x670245b34a1d710c;	//	/Assets/tpp/motion/mtar/player2/player2_ddf_facial.mtar
				break;
			case PlayerType_OCELOT:
				filePath64 = 0x6703e118275df4f2;	//	/Assets/tpp/motion/mtar/player2/player2_ocelot_facial.mtar
				break;
			case PlayerType_QUIET:
				filePath64 = 0x6701511616076078;	//	/Assets/tpp/motion/mtar/player2/player2_quiet_facial.mtar
				break;
			default:
				filePath64 = 0x67028b3526a03df4;	//	/Assets/tpp/motion/mtar/player2/TppPlayer2Facial.mtar
				break;
			}
			foxPathPath(fileSlotIndex, filePath64);
			
			return fileSlotIndex;
		}//GetFacialMtarFilePathHook

		//SNAKE/AVATAR only
		//indexed by playerHandType
		//SYNC exe
		std::string bionicHandFpkPaths[]{
			"",//NONE, 0 in exe
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm0_v00.fpk",//NORMAL
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm3_v00.fpk",//STUN_ARM
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm4_v00.fpk",//JEHUTY
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm2_v00.fpk",//STUN_ROCKET
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm1_v00.fpk",//KILL_ROCKET
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm6_v00.fpk",//GOLD
			"/Assets/tpp/pack/player/fova/plfova_sna0_arm7_v00.fpk",//SILVER
		};
		std::string bionicHandFv2Paths[]{
			"",
			"/Assets/tpp/fova/chara/sna/sna0_arm0_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_arm3_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_arm4_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_arm2_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_arm1_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_arm6_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_arm7_v00.fv2",
		};

		//tex default values from LoadPlayerBionicArm
		//SYNC vanilla
		bool UseBionicArmVanilla(uint playerType, uint playerPartsType, uint playerHandType) {
			//SNAKE,AVATAR
			if (playerType == 0 || playerType == 3) {
				switch (playerPartsType) {
				case PlayerPartsType_NORMAL://NORMAL
				case PlayerPartsType_NORMAL_SCARF://NORMAL_SCARF
				case PlayerPartsType_SNEAKING_SUIT://SNEAKING_SUIT
				case PlayerPartsType_NAKED://NAKED
				case PlayerPartsType_SNEAKING_SUIT_TPP://SNEAKING_SUIT_TPP
				case PlayerPartsType_BATTLEDRESS://BATTLEDRESS
				case PlayerPartsType_PARASITE://PARASITE
				case PlayerPartsType_LEATHER://LEATHER
				case PlayerPartsType_GOLD://GOLD
				case PlayerPartsType_SILVER://SILVER
				case PlayerPartsType_MGS3://MGS3
				case PlayerPartsType_MGS3_NAKED://MGS3_NAKED
				case PlayerPartsType_MGS3_SNEAKING://MGS3_SNEAKING
				case PlayerPartsType_MGS3_TUXEDO://MGS3_TUXEDO
				case PlayerPartsType_SWIMWEAR://SWIMWEAR
				case PlayerPartsType_SWIMWEAR_G://SWIMWEAR_G
				case PlayerPartsType_SWIMWEAR_H://SWIMWEAR_H
					return true;
				}
			}
			return false;
		}//UseBionicArmVanilla

		ulonglong* GetHandFpkPathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType){
			spdlog::debug("GetHandFpkPathHook playerPartsType:{} playerHandType:{}", playerPartsType, playerHandType);
			
			bool useBionicHand = UseBionicArmVanilla(playerType, playerPartsType, playerHandType);
			//tex useBionicHand is defined by the playerParts ..
			if (overrideCharacterSystem) {
				//ZIP: Validate player parts type
				if (IsPlayerPartsTypeValid(playerPartsType)) {
					useBionicHand = character.useBionicHand;
				}
			}

			ulonglong filePath64 = 0;//tex 0 acts as unload/no hand, vanilla has this for 0/NONE index in its fpk/fv2 path64 array
			if (useBionicHand) {
				//tex .. but the actual hand type is independant of overrideCharacterSystem 
				std::string filePath = character.bionicHandFpkPath;
				if ( filePath == "") {
					//tex vanilla paths
					//TODO: surface this information to player if nessesary
					//tex WORKAROUND: while turning hand off for partstypes that usually have them works, (ex playerPartsType NORMAL > playerPartsInfo MGS1)
					//setting a partsType to one that has no hand also sets playerHandType to 0 (ex playerPartsType MGS1 > playerPartsInfo NORMAL)
					//so there must be some other player it defines hand/not hand per playerType , if not right where the change to playerHandType then likely called there
					if (playerHandType == PlayerHandType_NONE) {
						if (overrideCharacterSystem) {
							playerHandType = PlayerHandType_NORMAL;//tex just default to NORMAL
						}
					}
					filePath = bionicHandFpkPaths[playerHandType];
				}					
				spdlog::debug("bionicHandFpkPath: {}", filePath);
				filePath64 = PathCode64(filePath.c_str());
			}
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetHandFpkPathHook

		ulonglong* GetHandFilePathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType) {
			spdlog::debug("GetHandFilePathHook playerPartsType:{} playerHandType:{}", playerPartsType, playerHandType);

			bool useBionicHand = UseBionicArmVanilla(playerType, playerPartsType, playerHandType);
			if (overrideCharacterSystem) {
				useBionicHand = character.useBionicHand;
			}

			ulonglong filePath64 = 0;
			if (useBionicHand) {
				std::string filePath = character.bionicHandFv2Path;
				if (filePath == "") {
					if (playerHandType == PlayerHandType_NONE) {
						if (overrideCharacterSystem) {
							playerHandType = PlayerHandType_NORMAL;
						}
					}
					filePath = bionicHandFv2Paths[playerHandType];
				}					
				spdlog::debug("bionicHandFv2Path: {}", filePath);
				filePath64 = PathCode64(filePath.c_str());
			}

			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetHandFilePathHook

		//DEBUGNOW see ORIG below
		bool _DoesNeedBodyFovaForDDHook(uint playerType, uint playerPartsType) {
			spdlog::debug("_DoesNeedBodyFovaForDDHook playerType:{} playerPartsType:{}", playerType, playerPartsType);
			return _DoesNeedBodyFovaForDD(playerType, playerPartsType);
		}
		//UNUSED REF
		//GOTCHA: since its only called in GetBodyFovaPath, so this isnt a hook, just calling this extended version from GetBodyFovaPathHook
		//only called for playerType 1 DD_MALE, 2 DD_FEMALE
		//bool _DoesNeedBodyFovaForDDORIG(uint playerType, uint playerPartsType) {
		//	spdlog::debug("_DoesNeedBodyFovaForDDHook playerType:{} playerPartsType:{}", playerType, playerPartsType);
		//	if (true) {
		//		switch (playerPartsType) {
		//		case 0://NORMAL
		//		case 1://NORMAL_SCARF
		//		case 2://SNEAKING_SUIT
		//		case 7://NAKED
		//		case 8://SNEAKING_SUIT_TPP
		//		case 9://BATTLEDRESS
		//		case 11://LEATHER
		//		case 12://GOLD
		//		case 13://SILVER
		//		case 14://AVATAR_EDIT_MAN
		//		case 15://MGS3
		//		case 16://MGS3_NAKED
		//		case 17://MGS3_SNEAKING
		//		case 18://MGS3_TUXEDO
		//		case 19://EVA_CLOSE
		//		case 20://EVA_OPEN
		//		case 21://BOSS_CLOSE
		//		case 22://BOSS_OPEN
		//		case 23://SWIMWEAR
		//		case 24://SWIMWEAR_G
		//		case 25://SWIMWEAR_H
		//			if (playerType == 1) {//DD_MALE
		//				if (playerPartsType != 17) {//MGS3_SNEAKING
		//					return true;
		//				}
		//			}
		//			else if (playerType == 2) {//DD_FEMALE
		//				if (playerPartsType != 21) {//BOSS_CLOSE
		//					return true;
		//				}
		//			} else {//tex not hit in vanilla
		//				return true;
		//			}
		//		}//switch
		//	}
		//	return false;
		//}//_DoesNeedBodyFovaForDDORIG

		//DEBUGNOW there's somewhere else filtering whether it's actually applied, ie it still will only apply if correct playerCamoType is set
		//you can test this by setting up char values to a normal camo that supports skintone fv2, and chaning between playerCamoId that supports it or not
		//you'll see this function runs reguardless yet the fv2 is applied or not tomehow
		//posbly theres a flag for that camoID somewhere to use the fv2 variable data 0x64 https://metalgearmodding.fandom.com/wiki/FV2#Variable_Data_Section or not
		//but since the foxPathPath file reference doesn't seem to be used past it's call, and there doesn't seem to be any setup function before it (theres other loadfv2 functions), I'm not sure how it would be handled
		//even then it seems to need litterally the exact playerCamoType range (or is it playerpartstype hmm) it was for anyway.
		//again test dd_male swimwear and change it to another skintone supported camo, it dont work.
		ulonglong* GetBodyFovaPathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType) {
			spdlog::trace(__func__);
			if (!overrideCharacterSystem) {
				return GetBodyFovaPath(fileSlotIndex, playerType, playerPartsType);
			}
		
			ulonglong filePath64 = 0;	
			if (character.skinToneFv2Path != "") {
				spdlog::debug("character.skinToneFv2Path: {}", character.skinToneFv2Path);
				filePath64 = PathCode64(character.skinToneFv2Path.c_str());
			}
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetBodyFovaPathHook

		//ORIG
		//tex these fv2s are in the playerparts fpk VERIFY
		//TODO: expand. fill out all the data taking _DoesNeedBodyFovaForDD into account 
		//then assume if value then apply and _DoesNeedBodyFovaForDD will no longer be nessesary
		//TODO: figure out how AVATAR is handled, inital look at LoadPlayerFv2s it doesnt seem to use this for AVAT, then what is its skin tone situation?
		//ulonglong* GetBodyFovaPathORIG(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType) {
		//	spdlog::debug("GetBodyFovaPathHook playerType:{} playerPartsType:{}", playerType, playerPartsType);
		//	bool shouldApplySkinToneFv2 = false;
		//	ulonglong filePath64 = 0;

		//	if (playerType == 0) {//SNAKE
		//		if (playerPartsType == 18) {//MGS3_TUXEDO
		//			filePath64 = 0x608961e868491c54;////"/Assets/tpp/fova/chara/dld/dld0_main0_sna.fv2";
		//		}
		//	} else if (playerType == 1) {//DD_MALE
		//		shouldApplySkinToneFv2 = _DoesNeedBodyFovaForDD(playerType, playerPartsType);
		//		if (shouldApplySkinToneFv2) {
		//			switch (playerPartsType) {
		//			case 8://SNEAKING_SUIT_TPP
		//				filePath64 = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
		//				break;
		//			case 9://BATTLEDRESS
		//				filePath64 = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
		//				break;
		//			case 15://MGS3
		//				filePath64 = 0x608b3a2e8398415b;// "/Assets/tpp/fova/chara/dla/dla0_plym0_v00.fv2";
		//				break;
		//			case 16://MGS3_NAKED
		//				filePath64 = 0x608bed35c90a314d;// "/Assets/tpp/fova/chara/dla/dla1_plym0_v00.fv2";
		//				break;
		//			case 18://MGS3_TUXEDO
		//				filePath64 = 0x608872bab5e53bc8; // "/Assets/tpp/fova/chara/dld/dld0_plym0_v00.fv2";
		//				break;
		//			case 23://SWIMWEAR
		//				filePath64 = 0x608aa0de59bf9572; // "/Assets/tpp/fova/chara/dlf/dlf1_main0_v00.fv2";
		//				break;
		//			case 24://SWIMWEAR_G
		//				filePath64 = 0x6088dd7cacaa3fd6; // "/Assets/tpp/fova/chara/dlg/dlg1_main0_v00.fv2";
		//				break;
		//			case 25://SWIMWEAR_H
		//				filePath64 = 0x60884821796ed8f0;// "/Assets/tpp/fova/chara/dlh/dlh1_main0_v00.fv2";
		//				break;
		//			default:
		//				filePath64 = 0x608882ccbb15c7ab;//"/Assets/tpp/fova/chara/sna/dds5_main0_ply_v00.fv2"
		//				break;
		//			}//switch(playerPartsType)
		//		}//shouldApplySkinToneFv2
		//	} else if (playerType == 2) {
		//		shouldApplySkinToneFv2 = _DoesNeedBodyFovaForDD(playerType, playerPartsType);
		//		if (shouldApplySkinToneFv2) {
		//			switch (playerPartsType) {
		//			case 8://SNEAKING_SUIT_TPP
		//				filePath64 = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
		//				break;
		//			case 9://BATTLEDRESS
		//				filePath64 = 0x608b9ec8eac8437b;// "/Assets/tpp/fova/chara/sna/sna4_plym0_def_v00.fv2";
		//				break;
		//			case 19://EVA_CLOSE
		//				filePath64 = 0x608bc54842becde0;// "/Assets/tpp/fova/chara/dle/dle0_plyf0_v00.fv2";
		//				break;
		//			case 20://EVA_OPEN
		//				filePath64 = 0x608a91e3d60c5980;// "/Assets/tpp/fova/chara/dle/dle1_plyf0_v00.fv2";
		//				break;
		//			case 22://BOSS_OPEN
		//				filePath64 = 0x6089e156b2cacad9;// "/Assets/tpp/fova/chara/dlc/dlc1_plyf0_v00.fv2";
		//				break;
		//			case 23://SWIMWEAR
		//				filePath64 = 0x6088fc6455404f89;// "/Assets/tpp/fova/chara/dlf/dlf1_main0_f_v00.fv2";
		//				break;
		//			case 24://SWIMWEAR_G
		//				filePath64 = 0x6089659d7ee7f080;// "/Assets/tpp/fova/chara/dlg/dlg1_main0_f_v00.fv2";
		//				break;
		//			case 25://SWIMWEAR_H
		//				filePath64 = 0x6089e8ede46843e9; // "/Assets/tpp/fova/chara/dlh/dlh1_main0_f_v00.fv2";
		//				break;
		//			default:
		//				filePath64 = 0x608a1c34fefc05c2;// "/Assets/tpp/fova/chara/sna/dds6_main0_ply_v00.fv2";
		//				break;
		//			}//switch(playerPartsType)
		//		}//shouldApplySkinToneFv2
		//	}//if playerType

		//	foxPathPath(fileSlotIndex, filePath64);
		//	return fileSlotIndex;
		//}//GetBodyFovaPathHook

		//DD_MALE/FEMALE only? VERIFY
		//tex ghidra doesn't like to decompile this, but except for ppt 3 / HOSPITAL it seems the same as DoesNeedFaceFovaForAvatarHook 
		//GOTCHA: is also called in a bunch of other places, aparently at least one constantly/in the update loop
		bool DoesNeedFaceFovaHook(uint playerPartsType){
			//DEBUG
			/*for (uint i = 0; i < 28; i++) {
				bool testHead = DoesNeedFaceFova(i);
				spdlog::debug("DoesNeedFaceFova {} = {}", i, testHead);
			}*/

			//ZIP: Validate player parts type
			if (!IsPlayerPartsTypeValid(playerPartsType)) {
				return DoesNeedFaceFova(playerPartsType);
			}

			bool headNeeded = false;

			if (overrideCharacterSystem) {
				headNeeded = character.useHead;
			}
			else {
				headNeeded = DoesNeedFaceFova(playerPartsType);//tex fall back to original
			}

			//OFF, see GOTCHA spdlog::debug("DoesNeedFaceFovaHook playerPartsType:{} headNeeded:{}", playerPartsType, headNeeded);
			//spdlog::debug("DoesNeedFaceFovaHook playerPartsType:{} headNeeded:{} overrideCharacterSystem:{}", playerPartsType, headNeeded,overrideCharacterSystem);
			return headNeeded;
		}//DoesNeedFaceFovaHook

		//AVATAR only? VERIFY
		bool DoesNeedFaceFovaForAvatarHook(uint playerPartsType){
			//DEBUGNOW
			/*for (uint i = 0; i < 28; i++) {
				bool testHead = DoesNeedFaceFova(i);
				spdlog::debug("DoesNeedFaceFovaForAvatarHook {} = {}", i, testHead);
			}*/

			//ZIP: Validate player parts type
			if (!IsPlayerPartsTypeValid(playerPartsType) || isPlayerPartsFpkForAvatarRequested) {
				if (character.playerType==PlayerType_SNAKE&&character.playerPartsType==PlayerPartsType_NORMAL)
				return DoesNeedFaceFovaForAvatar(playerPartsType);
			}

			bool headNeeded = false; 

			if (overrideCharacterSystem) {
				headNeeded = character.useHead;
			}
			else {
				headNeeded = DoesNeedFaceFovaForAvatar(playerPartsType);//tex fall back to original
			}

			spdlog::debug("DoesNeedFaceFovaForAvatarHook playerPartsType:{} headNeeded:{} overrideCharacterSystem:{}", playerPartsType, headNeeded,overrideCharacterSystem);

			return headNeeded;

			//ORIG
			//if (true) {
			//	switch (playerPartsType) {
			//	case 0:
			//	case 1:
			//	case 2:
			//	case 7:
			//	case 8:
			//	case 9:
			//	case 11:
			//	case 12:
			//	case 13:
			//	case 14:
			//	case 15:
			//	case 16:
			//	case 17:
			//	case 18:
			//	case 19:
			//	case 20:
			//	case 21:
			//	case 22:
			//	case 23:
			//	case 24:
			//	case 25:
			//		return true;
			//	}
			//}
			//if (playerPartsType == 3) {//HOSPITAL // why?
			//	return true;
			//}
			//return false;
		}//DoesNeedFaceFovaForAvatarHook

		//SYNC exe
		std::string snakeFaceFpksDefault[] {
			//head 0
			"/Assets/tpp/pack/player/fova/plfova_sna0_face0_v00.fpk",//Horn 0
			"/Assets/tpp/pack/player/fova/plfova_sna0_face1_v00.fpk",//Horn 1
			"/Assets/tpp/pack/player/fova/plfova_sna0_face2_v00.fpk",//Horn 2
			//head 1
			"/Assets/tpp/pack/player/fova/plfova_sna0_face4_v00.fpk",//Horn 0 Bandana
			"/Assets/tpp/pack/player/fova/plfova_sna0_face5_v00.fpk",//Horn 1 Bandana
			"/Assets/tpp/pack/player/fova/plfova_sna0_face6_v00.fpk",//Horn 2 Bandana
		};
		std::string snakeFaceFv2sDefault[] {
			"/Assets/tpp/fova/chara/sna/sna0_face0_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_face1_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_face2_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_face4_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_face5_v00.fv2",
			"/Assets/tpp/fova/chara/sna/sna0_face6_v00.fv2",
		};
		//ZIP: Gold/Silver head fix
		std::string snakeFaceFpksGoldSilver[]{
			//Gold
			"/Assets/tpp/pack/player/fova/plfova_sna9_face0_v00.fpk",//no 'dana
			"/Assets/tpp/pack/player/fova/plfova_sna9_face2_v00.fpk",//with 'dana
			//Silver
			"/Assets/tpp/pack/player/fova/plfova_sna9_face1_v00.fpk",//no 'dana
			"/Assets/tpp/pack/player/fova/plfova_sna9_face3_v00.fpk",//with 'dana
		};
		std::string snakeFaceFv2sGoldSilver[]{
			//Gold
			"/Assets/tpp/fova/chara/sna/sna9_face0_v00.fv2",//no 'dana
			"/Assets/tpp/fova/chara/sna/sna9_face2_v00.fv2",//with 'dana
			//Silver
			"/Assets/tpp/fova/chara/sna/sna9_face1_v00.fv2",//no 'dana
			"/Assets/tpp/fova/chara/sna/sna9_face3_v00.fv2",//with 'dana
		};

		//tex broken out from LoadPlayerSnakeFace
		//essentially DoesNeedFaceFovaAndSnake
		//REF UNUSED
		bool UsePlayerSnakeFaceVanilla(uint playerType, uint playerPartsType) {
			switch (playerPartsType) {
			case PlayerPartsType_NORMAL://NORMAL
			case PlayerPartsType_NORMAL_SCARF://NORMAL_SCARF
			case PlayerPartsType_SNEAKING_SUIT://SNEAKING_SUIT
			case PlayerPartsType_NAKED://NAKED
			case PlayerPartsType_SNEAKING_SUIT_TPP://SNEAKING_SUIT_TPP
			case PlayerPartsType_BATTLEDRESS://BATTLEDRESS
			case PlayerPartsType_LEATHER://LEATHER
			case PlayerPartsType_GOLD://GOLD
			case PlayerPartsType_SILVER://SILVER
			case PlayerPartsType_AVATAR_EDIT_MAN://AVATAR_EDIT_MAN
			case PlayerPartsType_MGS3://MGS3
			case PlayerPartsType_MGS3_NAKED://MGS3_NAKED
			case PlayerPartsType_MGS3_SNEAKING://MGS3_SNEAKING
			case PlayerPartsType_MGS3_TUXEDO://MGS3_TUXEDO
			case PlayerPartsType_EVA_CLOSE://EVA_CLOSE
			case PlayerPartsType_EVA_OPEN://EVA_OPEN
			case PlayerPartsType_BOSS_CLOSE://BOSS_CLOSE
			case PlayerPartsType_BOSS_OPEN://BOSS_OPEN
			case PlayerPartsType_SWIMWEAR://SWIMWEAR
			case PlayerPartsType_SWIMWEAR_G://SWIMWEAR_G
			case PlayerPartsType_SWIMWEAR_H://SWIMWEAR_H
				return true;
			}
			return false;
		}//UsePlayerSnakeFaceVanilla

		//tex vanilla does not have seperate DoesNeedFaceFovaSnake, is rolled into GetFaceFpkPath
		//for playerType SNAKE it uses playerFaceId for hornLevel
		ulonglong* GetFaceFpkPathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint hornLevel, char playerFaceEquipId) {
			spdlog::debug("GetFaceFpkPathHook playerPartsType:{} headNeeded:{}", playerPartsType, character.useHead);

			if (playerType != PlayerPartsType_NORMAL) {
				foxPathPath(fileSlotIndex, 0);
				return fileSlotIndex;
			}

			bool useHead = UsePlayerSnakeFaceVanilla(playerType, playerPartsType);
			//tex playerParts defines useHead ..
			if (overrideCharacterSystem) {
				useHead = character.useHead;
			}		

			ulonglong filePath64 = 0;
			if (useHead) {
				//tex .. but what face is used is independant from overrideCharacterSystem
				std::string filePath = character.snakeFaceFpkPath;
				if (filePath == "") {
					bool isBandana = playerFaceEquipId == PlayerFaceEquip_BANDANA || playerFaceEquipId == PlayerFaceEquip_MUGEN_BANDANA;
					if (playerPartsType == PlayerPartsType_GOLD) {
						filePath = !isBandana ? snakeFaceFpksGoldSilver[0] : snakeFaceFpksGoldSilver[1]; //Gold
					}
					else if (playerPartsType == PlayerPartsType_SILVER) {
						filePath = !isBandana ? snakeFaceFpksGoldSilver[2] : snakeFaceFpksGoldSilver[3]; //Silver
					}
					else {
						if (isBandana) {
							hornLevel = hornLevel + MAX_SNAKE_FACEID;//tex not really right descriptive wise, but we've only got two 'heads', normal/bandana (* 3 horn levels)
						}
						filePath = snakeFaceFpksDefault[hornLevel];
					}
				}
				spdlog::debug("snakeFaceFpkPath: {}", filePath);
				filePath64 = PathCode64(filePath.c_str());
			}				
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}//GetFaceFpkPathHook

		ulonglong* GetFaceFilePathHook(ulonglong* fileSlotIndex, uint playerType, uint playerPartsType, uint hornLevel, char playerFaceEquipId) {
			spdlog::debug("GetFaceFilePathHook playerPartsType:{} headNeeded:{}", playerPartsType, character.useHead);

			if (playerType != 0) {
				foxPathPath(fileSlotIndex, 0);
				return fileSlotIndex;
			}

			bool useHead = UsePlayerSnakeFaceVanilla(playerType, playerPartsType);
			if (overrideCharacterSystem) {
				useHead = character.useHead;
			}
			
			ulonglong filePath64 = 0;
			if (useHead) {
				std::string filePath = character.snakeFaceFv2Path;
				if (filePath == "") {
					bool isBandana = playerFaceEquipId == PlayerFaceEquip_BANDANA || playerFaceEquipId == PlayerFaceEquip_MUGEN_BANDANA;
					if (playerPartsType == PlayerPartsType_GOLD) {
						filePath = !isBandana ? snakeFaceFv2sGoldSilver[0] : snakeFaceFv2sGoldSilver[1]; //Gold
					}
					else if (playerPartsType == PlayerPartsType_SILVER) {
						filePath = !isBandana ? snakeFaceFv2sGoldSilver[2] : snakeFaceFv2sGoldSilver[3]; //Silver
					}
					else {
						if (isBandana) {
							hornLevel = hornLevel + MAX_SNAKE_FACEID;
						}
						filePath = snakeFaceFv2sDefault[hornLevel];
					}
				}
				spdlog::debug("snakeFaceFv2Path: {}", filePath);
				filePath64 = PathCode64(filePath.c_str());
			}
			foxPathPath(fileSlotIndex, filePath64);
			return fileSlotIndex;	
		}//GetFaceFilePathHook

		//SYNC exe
		std::string avatarHornFpksDefault[]{
			"/Assets/tpp/pack/player/avatar/hone/plfova_avm_hone_v00.fpk",//Horn 0
			"/Assets/tpp/pack/player/avatar/hone/plfova_avm_hone_v01.fpk",//Horn 1
			"/Assets/tpp/pack/player/avatar/hone/plfova_avm_hone_v02.fpk",//Horn 2
		};
		std::string avatarHornFv2sDefault[]{
			"/Assets/tpp/fova/chara/avm/avm_hone_v00.fv2",
			"/Assets/tpp/fova/chara/avm/avm_hone_v01.fv2",
			"/Assets/tpp/fova/chara/avm/avm_hone_v02.fv2",
		};
		ulonglong * GetAvatarHoneFpkPathHook(ulonglong *fileSlotIndex, uint ogreLevel) {
			ulonglong filePath64 = 0;
  
			std::string filePath = character.avatarHornFpkPath;
			if (filePath == "") {
				filePath = avatarHornFpksDefault[ogreLevel];
			}
			filePath64 = PathCode64(filePath.c_str());

			foxPathPath(fileSlotIndex,filePath64);
			return fileSlotIndex;
		}//GetAvatarHoneFpkPathHook
		ulonglong * GetAvatarHoneFilePathHook(ulonglong *fileSlotIndex, uint ogreLevel) {
			ulonglong filePath64 = 0;
  
			std::string filePath = character.avatarHornFv2Path;
			if (filePath == "") {
				filePath = avatarHornFv2sDefault[ogreLevel];
			}
			filePath64 = PathCode64(filePath.c_str());

			foxPathPath(fileSlotIndex,filePath64);
			return fileSlotIndex;
		}//GetAvatarHoneFilePathHook

		void CreateHooks() {
			spdlog::debug(__func__);

			CREATE_HOOK(GetPartsFpkPath)
			CREATE_HOOK(GetPartsFilePath)
			CREATE_HOOK(GetCamoFpkPath)
			CREATE_HOOK(GetCamoFilePath)
			CREATE_HOOK(GetHandFpkPath)
			CREATE_HOOK(GetHandFilePath)
			CREATE_HOOK(GetFacialMtarFpkPath)
			CREATE_HOOK(GetFacialMtarFilePath)
			CREATE_HOOK(GetBodyFovaPath)
			CREATE_HOOK(DoesNeedFaceFova)
			CREATE_HOOK(DoesNeedFaceFovaForAvatar)
			CREATE_HOOK(GetFaceFpkPath)
			CREATE_HOOK(GetFaceFilePath)
			CREATE_HOOK(_DoesNeedBodyFovaForDD)//DEBUGNOW
			CREATE_HOOK(GetAvatarHoneFpkPath)
			CREATE_HOOK(GetAvatarHoneFilePath)
					
			ENABLEHOOK(GetPartsFpkPath)
			ENABLEHOOK(GetPartsFilePath)
			ENABLEHOOK(GetCamoFpkPath)
			ENABLEHOOK(GetCamoFilePath)
			ENABLEHOOK(GetHandFpkPath)
			ENABLEHOOK(GetHandFilePath)
			//ENABLEHOOK(GetFacialMtarFpkPath)
			//ENABLEHOOK(GetFacialMtarFilePath)
			ENABLEHOOK(GetBodyFovaPath)
			ENABLEHOOK(DoesNeedFaceFova)
			ENABLEHOOK(DoesNeedFaceFovaForAvatar) 
			ENABLEHOOK(GetFaceFpkPath)
			ENABLEHOOK(GetFaceFilePath)
			ENABLEHOOK(_DoesNeedBodyFovaForDD)//DEBUGNOW
			ENABLEHOOK(GetAvatarHoneFpkPath)
			ENABLEHOOK(GetAvatarHoneFilePath)
		}//CreateHooks

		int CreateLibs(lua_State* L) {
			spdlog::debug(__func__);
			
			luaL_Reg libFuncs[] = {
				{ "SetOverrideCharacterSystem", l_SetOverrideCharacterSystem },
				{ "SetPlayerTypeForPartsType", l_SetPlayerTypeForPartsType },
				{ "SetPlayerPartsTypeForPartsType", l_SetPlayerPartsTypeForPartsType },
				{ "SetUseHeadForPlayerParts", l_SetUseHeadForPlayerParts },
				{ "SetUseBionicHandForPlayerParts", l_SetUseBionicHandForPlayerParts },
				{ "SetUseCamoForPlayerParts", l_SetUseCamoForPlayerParts },
				{ "SetPlayerPartsFpkPath", l_SetPlayerPartsFpkPath },
				{ "SetPlayerPartsPartsPath", l_SetPlayerPartsPartsPath },
				{ "SetSkinToneFv2Path", l_SetSkinToneFv2Path },
				{ "SetPlayerCamoFpkPath", l_SetPlayerCamoFpkPath },
				{ "SetPlayerCamoFv2Path", l_SetPlayerCamoFv2Path },
				{ "SetBionicHandFpkPath", l_SetBionicHandFpkPath },
				{ "SetBionicHandFv2Path", l_SetBionicHandFv2Path },
				{ "SetSnakeFaceFpkPath", l_SetSnakeFaceFpkPath },
				{ "SetSnakeFaceFv2Path", l_SetSnakeFaceFv2Path },
				{ "SetAvatarHornFpkPath", l_SetAvatarHornFpkPath },
				{ "SetAvatarHornFv2Path", l_SetAvatarHornFv2Path },
				
				//{ "SetPlayerPartsFpk", l_SetPlayerPartsFpk },//UNUSED
				//{ "SetPlayerPartsPart", l_SetPlayerPartsPart },//UNUSED
				{ NULL, NULL }//GOTCHA: crashes without
			};
			luaI_openlib(L, "IhkCharacter", libFuncs, 0);
			return 1;
		}//CreateLibs
	}//Hooks_Character
}//namespace IHHook