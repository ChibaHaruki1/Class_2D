//============================================================
//
//�X�e�[�W�ɒu���I�u�W�F�N�g�̃N���X�Ǘ�[statge_obj.h]
//Auther:Chiba Haruki
//
//============================================================

#pragma once

//===========================
//�C���N���[�h
#include "objectX.h"
#include <cstdio>

//�X�e�[�W�ɒu���I�u�W�F�N�g�̊��N���X�Ǘ�
class CStageObj : public  CObjectX
{
public:
	CStageObj(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CStageObj()override;                         //�f�X�g���N�^
	HRESULT Init()override;                       //����������
	void Uninit()override;                        //�j������
	void Update() override;                       //�X�V����
	void Draw()override;                          //�`�揈��

	void TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ);

	static CStageObj* Create(D3DXVECTOR3 pos,CObjectX::TYPE type); //�p���N���X���^�C�v���Ƃɐ���
private:
	static int m_nTelephonPoleCount;
	FILE* m_pFile;
};


//�d���̃N���X�Ǘ�
class CTelephonPole : public CStageObj
{
public:
	CTelephonPole(int nPriority = DEFAULT_PRIORITY1);
	~CTelephonPole()override;
};


//�Ď��J�����̏�̕���
class CSurveillanceCameraUP : public CStageObj
{
public:
	CSurveillanceCameraUP(int nPriority = DEFAULT_PRIORITY1);
	~CSurveillanceCameraUP()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;
};

//�Ď��J�����̉��̕���
class CSurveillanceCameraDown : public CStageObj
{
public:
	CSurveillanceCameraDown(int nPriority = DEFAULT_PRIORITY1);
	~CSurveillanceCameraDown()override;
	
};

//�Ď��J�����̉��̕���
class CShop : public CStageObj
{
public:
	CShop(int nPriority = DEFAULT_PRIORITY1);
	~CShop()override;
};

//��ꂽ��
class CBreakHouse : public CStageObj
{
public:
	CBreakHouse(int nPriority = DEFAULT_PRIORITY1);
	~CBreakHouse()override;
	void Update()override;

private:
};
