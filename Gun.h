//======================================
//
//銃のクラス管理[block.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

#include "objectX.h"

#define SET_BULLET_LIFE (60)

//初期武器のクラス管理
class CInitGun : public  CObjectX
{
public:
	CInitGun(int nPriority = DEFAULT_PRIORITY1);
	~CInitGun()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;

	static CInitGun* Create(D3DXVECTOR3 pos);
};

//初期武器のクラス管理
class CInitGun001 : public  CObjectX
{
public:
	CInitGun001(int nPriority = DEFAULT_PRIORITY1);
	~CInitGun001()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;

	static CInitGun001* Create(D3DXVECTOR3 pos);
};