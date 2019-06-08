//-----------------------------------�ش����� ����
#pragma once
#include "global.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#pragma  comment( lib, "fmodex_vc.lib" )

enum ESOUNDKIND
{
	Perion = 0,
	Effect,  //����Ʈ
	SD_END   //����Ʈ �� 
};
enum EFFOUNDKIND //����Ʈ ����
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
