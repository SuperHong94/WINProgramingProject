//-----------------------------------�ش����� ����
#pragma once
#include "global.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#pragma  comment( lib, "fmodex_vc.lib" )

enum ESOUNDKIND
{
	MainSound=0,
	Perion,
	STAGE2,
	YOUDIE,
	YOUWIN,
	SD_END,   //����Ʈ �� 
};
enum EFFOUNDKIND //����Ʈ ����
{
	jump = 0,
	click = 1,
	teleP,
	Damage,
	EFFSD_END
};


void soundSetup();
void effSoundSetup();
void playSound(ESOUNDKIND eSound);
void effSoundoff();
void effPlaySound(EFFOUNDKIND eSound);
void SoundPause();