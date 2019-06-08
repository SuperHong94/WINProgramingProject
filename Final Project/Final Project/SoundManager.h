//-----------------------------------해더파일 시작
#pragma once
#include "global.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#pragma  comment( lib, "fmodex_vc.lib" )

enum ESOUNDKIND
{
	Perion = 0,
	Effect,  //이펙트
	SD_END   //이펙트 끝 
};
enum EFFOUNDKIND //이펙트 사운드
{
	EFFSD_1 = 0,
	EFFSD_2,
	EFFSD_END
};


void soundSetup();
void effSoundSetup();
void playSound(ESOUNDKIND eSound);
void effSoundoff();
void effPlaySound(EFFOUNDKIND eSound);
