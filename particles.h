//===================================
//
//�n�ʂ̃v���g�^�C�v�錾������t�@�C��[field.h]
//Author:chiba haruki
//
//===================================

#ifndef _PARTICLES_H_  //���̃}�O����`������Ă��Ȃ���������
#define _PARTICLES_H_  //��d�C���N���[�h�h�~�̃}�N����`

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
