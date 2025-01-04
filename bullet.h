//======================================
//
//�e�̃N���X�Ǘ�[bullet.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

//======================================
//�C���N���[�h
#include "object3D.h"


//============================================================================
//�e�̊Ǘ��̊��N���X
//============================================================================
class CManagerBullet : public CObject3D
{
public: //�O������A�N�Z�X�\
	CManagerBullet(int nPriority = DEFAULT_PRIORITY);              //�����t���R���X�g���N�^
	~CManagerBullet()override;                                     //�f�X�g���N�^
	HRESULT Init()override;                                        //����������
	void Uninit()override;                                         //�I������
	void Update()override;                                         //�X�V����
	void Draw()override;                                           //�`�揈��
	void SetPos(D3DXVECTOR3 m_pos, D3DXVECTOR3 m_move, int nLife); //�e�̈ʒu�Ɋւ���ݒ菈��

	//�������z�֐��ɂ��邱�ƂŊ��N���X�̏��������̂܂܏�������
	virtual void CallEffect(bool bUse) = 0;  //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	virtual void CollisionOnObject() = 0; ;  //�I�u�W�F�N�g�Ƃ̓����蔻��

	static CManagerBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject3D::TYPE type); //3D�e�̐�������

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static float MAX_BULLET3D_SIZE_X = 40.0f; //3D�e��X���̑傫��
	constexpr static float MAX_BULLET3D_SIZE_Y = 40.0f; //3D�e��Y���̑傫��
	constexpr static float MAX_BULLET3D_SIZE_Z = 40.0f; //3D�e��Z���̑傫��
	constexpr static int SET_BULLET_LIFE = 60;          //���C�t�̍ő吔

private: //�A�N�Z�X�s�\

};

//�v���C���[�ʏ�e�̃N���X
class CBullet3D : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CBullet3D(int nPriority = DEFAULT_PRIORITY);   //�����t���R���X�g���N�^
	~CBullet3D()override;                          //�f�X�g���N�^
	//void Update()override;                        //�X�V����
	void CallEffect(bool bUse);                    //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                      //�I�u�W�F�N�g�Ƃ̓����蔻��

private: //�A�N�Z�X�s�\
};

//�v���C���[�K�E�Z�̃N���X
class CSpecialBullet : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CSpecialBullet(int nPriority = DEFAULT_PRIORITY);   //�����t���R���X�g���N�^
	~CSpecialBullet()override;                          //�f�X�g���N�^
	void Update()override;                              //�X�V����
	void CallEffect(bool bUse);                         //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                           //�I�u�W�F�N�g�Ƃ̓����蔻��

private: //�A�N�Z�X�s�\

};

//�G�̒ʏ�e�̃N���X
class CEnemyBullet : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CEnemyBullet(int nPriority = DEFAULT_PRIORITY);  //�����t���R���X�g���N�^
	~CEnemyBullet()override;                         //�f�X�g���N�^
	void Update()override;                          //�X�V����
	void CallEffect(bool bUse);                     //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                       //�I�u�W�F�N�g�Ƃ̓����蔻��

	static float m_fAdditionPosY;                   //rot.y�ɒl��ǉ����Ă������߂̕ϐ�

	//�}�N����c
	constexpr static float InitAddItion = 7.0f;

private: //�O������A�N�Z�X�s�\

};

//�{�X�̒ʏ�e�̃N���X
class CBossBullet : public CManagerBullet
{
public: //�O������A�N�Z�X�\
	CBossBullet(int nPriority = DEFAULT_PRIORITY);  //�����t���R���X�g���N�^
	~CBossBullet()override;                         //�f�X�g���N�^
	void Update()override;                          //�X�V����
	void CallEffect(bool bUse);                     //�G�t�F�N�g�̏������ĂԊ֐� (�����ŃG�t�F�N�g��ǉ����邩�ǂ�������)
	void CollisionOnObject();                       //�I�u�W�F�N�g�Ƃ̓����蔻��

private: //�O������A�N�Z�X�s�\

};

