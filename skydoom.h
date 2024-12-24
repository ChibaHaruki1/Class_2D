//=========================================================
//
//ãÛÇÃîwåiópÉNÉâÉXä«óù[skydoom.h]
//Auther:HARUKI CHIBA
//
//=========================================================

#pragma once

#include "main.h"
#include "objectX.h"

class CSkyDoom : public CObjectX
{
public:
	CSkyDoom(int nPriority = DEFAULT_PRIORITY1);
	~CSkyDoom()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;

	static CSkyDoom* Create(D3DXVECTOR3 pos,int nNumber);
};