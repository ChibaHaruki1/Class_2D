//===================================
//
//�n�ʂ̃v���g�^�C�v�錾������t�@�C��[field.h]
//Author:chiba haruki
//
//===================================

#ifndef _FIELD_H_  //���̃}�O����`������Ă��Ȃ���������
#define _FIELD_H_  //��d�C���N���[�h�h�~�̃}�N����`

#include "object3D.h"
#include <cstdio>

//�}�N����`
#define MAX_FIELD_SIZE_X (200.0f)
#define MAX_FIELD_SIZE_Z (200.0f)
#define FIELD_TEXTURE_SIZE_X (1.0f)
#define FIELS_TEXTURE_SIZE_Y (0.0f)


class CField : public CObject3D
{
public:
	CField(int nPriority = DEFAULT_PRIORITY);
	~CField()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	void TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ);

	static CField* Create(D3DXVECTOR3 pos);

private:
	FILE* m_pFile;
	float m_fSizeX;
	float PosX;
	static int m_nCountField;
};
#endif 
