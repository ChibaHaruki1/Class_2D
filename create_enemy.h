//================================================
//
//“G‚Ì¶¬ˆ—‚ğ‚·‚éƒNƒ‰ƒX[create_enemy]
//Auther:Haruki Chiba
//
//================================================

#pragma once
#include "character.h"

class CCreateEnemy
{
public:
	CCreateEnemy();
	~CCreateEnemy();
	static void CreateEnemy();

private:
	static int m_nRandom;
};