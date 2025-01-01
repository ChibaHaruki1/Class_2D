//========================================
//
//�J�����N���X�Ǘ�[camera.h]
//Auther:Haruki Chiba
//
//========================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//========================================
//�C���N���[�h
#include "main.h"
#include "input.h"

//==============================================================
//�J�����̃N���X
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();                                            //�J�����̏��̐ݒ�	
	D3DXVECTOR3& GetPosV() { return m_posV; }
	D3DXVECTOR3& GetPosR() { return m_posR; }
	D3DXVECTOR3& GetRot() { return rot; }
	int& GetAdjustmentPosZ() { return m_fAdjustmentPosZ; }
	float& GetSaveF() { return CountCamera; }

private:

	D3DXVECTOR3 m_posV; //���_
	D3DXVECTOR3 m_posR; //�����_
	D3DXVECTOR3 m_vecU; //�����
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V����
	D3DXMATRIX m_mtxView; //�r���[�s��
	D3DXVECTOR3 rot; //����
	CInputKeyBoard* pInputKeyBoard1;
	int  m_fDistance;
	float CountCamera;
	D3DXVECTOR3 m_fSavePosV;
	//int m_nDistance; //���_���璍���_�܂ł̋���
	int m_fAdjustmentPosZ;
};

#endif // !_CAMERA_H_

