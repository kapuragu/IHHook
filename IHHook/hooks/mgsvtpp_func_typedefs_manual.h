#pragma once
//Not generated, manually managed version of the generated version
//for wrangling with stuff you skipped via exportFunc:False
//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)

#include "lua/lua.h"//l_StubbedOutFunc TODO: dont like this

typedef int (__fastcall l_StubbedOutFunc)(lua_State * L);
typedef void (__fastcall nullsub_2Func)(const char * unkSomeIdStr, longlong unkSomeIdNum);

//ZIP: Ghidra repo defines
#define PathCode64(str) PathCode64Ext(str)
typedef ulonglong PathCode64;
typedef uint64_t StrCode;
typedef uint StrCode32;
struct Path {
	PathCode64 Hash;
};
namespace fox {
	struct String {
		char* cString;
		uint64_t length;
		uint64_t hash;
		void* unknown;
	};
};

//CULL, handled in generated version
//tex the (extern of the) function pointers
//extern l_StubbedOutFunc* l_StubbedOut;//EXPORT_FUNC_FALSE
//extern nullsub_2Func* nullsub_2;//EXPORT_FUNC_FALSE

//joey's defs

//using long = int64_t;

using ubyte = uint8_t;
using ushort = uint16_t;
//using uint = uint32_t;
using ulong = uint64_t;

using StringId = ulong;
using PathId = ulong;
using StrCode32 = uint;

typedef uint64_t StringId;
typedef struct ChangeLocationMenuParameter {
	unsigned short LocationId;
	unsigned short MissionId;
	byte paddingA[0x4];
	StringId FreeMissionName;
	byte Flags;
	byte MbStageBaseId;
	byte paddingB[0x6];
};
typedef struct MotherBaseMissionCommonData {
	byte paddingA[0x111];
	byte ChangeLocationMenuParamCount;
	byte paddingB[0x6];
	ChangeLocationMenuParameter ChangeLocationMenuParams[12];
	byte paddingC[0x88];
};

static const enum TppLocationId : ushort {
	afgh = 10,
	mafr = 20,
	mtbs = 50,
};
