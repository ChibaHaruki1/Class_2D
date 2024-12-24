//===================================
//
//地面のプロトタイプ宣言をするファイル[field.h]
//Author:chiba haruki
//
//===================================

#ifndef _PARTICLES_H_  //このマグロ定義がされていなかったから
#define _PARTICLES_H_  //二重インクルード防止のマクロ定義

#include "object3D.h"

#define MAX_PARTICLES_LIFE (30)
#define MAX_PARTICLES001_LIFE (60)

class CParticles : public CObject3D
{
public:
	CParticles(int nPriority = DEFAULT_PRIORITY);
	~CParticles()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CParticles* Create(D3DXVECTOR3 pos);

private:
	float m_fSizeX;
	float PosX;

	int m_nRandom;
	int m_nLife;
};


class CParticles001 : public CObject3D
{
public:
	CParticles001(int nPriority = DEFAULT_PRIORITY);
	~CParticles001()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CParticles001* Create(D3DXVECTOR3 pos);

private:
	float m_fSizeX;
	float PosX;

	int m_nRandom;
	int m_nLife;
};
#endif 
