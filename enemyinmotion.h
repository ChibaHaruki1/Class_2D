//============================================================================
//
//���[�V�����t���̓G�̃N���X�Ǘ�[enemyinmotion.h]
//Auther;Haruki Chiba
//
//============================================================================

#pragma once

#include "enemycharacter.h"

class CManagerEnemyInMotion : public CEnemyCharacter
{
public: //�A�N�Z�X�\

	CManagerEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CManagerEnemyInMotion()override;                           //�f�X�g���N�^
	HRESULT Init()override;                                     //����������
	void Uninit()override;                                      //�j������
	void Update() override;                                     //�X�V����
	void Draw()override;                                        //�`�揈��

	static CManagerEnemyInMotion* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);      //��������

	//�}�N����`
	constexpr static float MAX_SPEED = 2.0f; //�ǂ������鑬�x

protected:
	int m_nJumpFrame;    //��Ԃ܂ł̎���
	int JumpNumber;      //�s��������Ԃ悤�ɔԍ�������ׂ̕ϐ�
	int JumpRecastTime;  //��Ԉׂ̃��L���X�g�^�C���i�A���ŐG��Ă��锻��ɂȂ�ׂ��̏C���j
};

//���[�V�����t���̓G�i�ʏ�j
class CEnemyInMotion : public CManagerEnemyInMotion
{
public: //�A�N�Z�X�\
	CEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CEnemyInMotion()override;                           //�f�X�g���N�^
	void Update() override;                              //�X�V����
	
private:
};

//���[�V�����t���̓G�i����j
class CEnemyInMotion001 : public CManagerEnemyInMotion
{
public: //�A�N�Z�X�\
	CEnemyInMotion001(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CEnemyInMotion001()override;                           //�f�X�g���N�^
	void Update() override;                                 //�X�V����
	void AdjustmentBulletAndRot();                          //�v���C���[�ɑ΂���@�̂ƒe�̒�������
	void WhenCollisionBlock();                              //�n�ʗp�u���b�N�ɐG��Ă��鎞�̏���
	void Correctionrot();                                   //�������C������֐�
	void PlayerBloWwaway();


private:
	int m_nHitFrame;
	bool m_bHit;
};
