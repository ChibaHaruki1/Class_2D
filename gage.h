//=====================================
//
//�Q�[�W�Ɋւ���N���X[gage.h]
//Auther:Haruki Chiba
//
//=====================================

#pragma once

//=====================================
//�C���N���[�h
#include "object2D.h"
#include "object3D.h"

//==================================================
//�R���Q�[�W
class CFuelGage : public CObject3D
{
public:
	CFuelGage(int nPriority = DEFAULT_PRIORITY);          //�R���X�g���N�^;
	~CFuelGage();                                         //�R���X�g���N�^;
	HRESULT Init()override;                               //����������
	void Uninit()override;                                //�j������
	void Update()override;                                //�X�V����
	void Draw()override;                                  //�`�揈��
	void DrawNoml()override;                              //�ʏ�`�揈��

	static CFuelGage* Create();                           //��������

	inline bool& GetUse() { return m_bUse; }              //�g���Ă��邩�ǂ����̔�����擾����
private:
	//�}�N����`
	constexpr static float MAX_SIZEY = 100.0f;            //�Q�[�W�̑傫��
	constexpr static float MAX_MAINAS_GAGESPEED = 0.5f;   //�Q�[�W�̌��鑬��
	bool m_bUse;                                          //�Q�[�W�����炷���ǂ������肷�邽�߂̕ϐ�

};


//==================================================
//�Q�[�W�̊Ǘ��N���X
//==================================================
class CManagerGage : public CObject2D
{
public:  //�A�N�Z�X�\
	CManagerGage(int nPriority = DEFAULT_PRIORITY);           //�R���X�g���N�^;
	~CManagerGage()override;                                  //�f�X�g���N�^
	HRESULT Init()override;                                   //����������
	void Uninit()override;                                    //�j������
	void  Update()override;                                   //�X�V����
	void Draw()override;                                      //�`�揈��
	void DrawNoml()override;                                  //�ʏ�`�揈��
	static CManagerGage* Create(CObject2D::TYPE type);        //�Q�[�W�̐���
	static CManagerGage* CreateLeave(CObject2D::TYPE type);   //�c���Q�[�W�̐���

	float& GetPlayerHPSizeX() { return m_fHPSizeX; }          //�v���C���[��HP�Q�[�W���擾
	float& GetBossHPSizeX() { return m_fBossHPSizeX; }        //�{�X��HP�Q�[�W���擾
	float& GetSaveSizeX() { return m_fSaveSizeX; }            //�Q�[�W�̕ۊǂ��擾

protected://�p���N���X�̂݃A�N�Z�X�\
	float m_fSaveSizeX;

	//�}�N����`
	constexpr static float MAX_PLAYERGAGE_SIZE_Y = 40.0f; //�v���C���[�̃Q�[�W��Y���̑傫��
	constexpr static float MAX_PLAYERGAGE_SIZE_Z = 70.0f; //�v���C���[�̃Q�[�W��Z���̑傫��

private:  //�A�N�Z�X�s�\
	float m_fHPSizeX;      //�v���C���[��HP�Q�[�W�̑傫�����Ǘ�����p�̕ϐ�
	float m_fBossHPSizeX;  //�{�X��HP�Q�[�W�̑傫�����Ǘ�����p�̕ϐ�
};


//==================================================
//�v���C���[��HP�Q�[�W
class CPlayerHPGage : public CManagerGage
{
public:
	CPlayerHPGage(int nPriority = DEFAULT_PRIORITY);   //�R���X�g���N�^
	~CPlayerHPGage()override;                          //�f�X�g���N�^
	HRESULT Init()override;                            //����������
	void Update()override;                             //�X�V����
};
	

//==================================================
//�{�X��HP�Q�[�W
class CBossHPGage : public CManagerGage
{
public:
	CBossHPGage(int nPriority = DEFAULT_PRIORITY);     //�R���X�g���N�^
	~CBossHPGage()override;                            //�f�X�g���N�^
	HRESULT Init()override;                            //����������
	void Update()override;                             //�X�V����
};


//==================================================
//�v���C���[��HP�Q�[�W���c��
class CPlayerHPGageLeave : public CManagerGage
{
public:
	CPlayerHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CPlayerHPGageLeave()override;                         //�f�X�g���N�^
	HRESULT Init()override;                                //����������
};


//==================================================
//�{�X��HP�Q�[�W���c��
class CBossHPGageLeave : public CManagerGage
{
public:
	CBossHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CBossHPGageLeave()override;                         //�f�X�g���N�^
	HRESULT Init()override;                              //����������
};

