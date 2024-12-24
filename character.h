//============================================
//
//character�N���X�Ǘ�[character.h]
//Ajther: Chiba haruki
//
//============================================

#pragma once

//============================================
//�C���N���[�h
#include "objectX.h"
#include "model_prts.h"


//======================================================
//�L�����N�^�[�̊e�p�[�c�N���X
class CCharacter : public CObjectX
{
public://�O������̃A�N�Z�X�\
	////���ʉ��ł���������
	//typedef enum
	//{
	//	NEUTRAL = 0, //�ҋ@
	//	WALK,        //����
	//	ACTION,      //
	//	JUMP,
	//}COMMON;

	//typedef enum
	//{
	//	BOSSJUMP1=4,
	//}BOSSMOTIONSTATE;

	//typedef enum
	//{
	//	BLOWAWAY=4,
	//}MOTIONSTATE;

	//�{�X�̃��[�V�����̎��
	typedef enum
	{
		BOSSNEUTRAL = 0, //�ҋ@
		BOSSWALK,        //����
		BOSSACTION,      //����
		BOSSJUMP,        //���
		BOSSIMPACT,       //���001
		BOSSATTACK,      //�U��
		BOSSDIE,         //���S
	}BOSSMOTIONSTATE;

	//�v���C���[�̃��[�V�����̎��
	typedef enum
	{
		NEUTRAL = 0, //�ҋ@
		WALK,        //����
		ACTION,      //����
		JUMP,        //���
		BLOWAWAY,    //�������
		DIE,         //���S
	}MOTIONSTATE;

	CCharacter(int nPriority = DEFAULT_PRIORITY1);         //�R���X�g���N�^
	~CCharacter();                                         //�f�X�g���N�^
	HRESULT Init();                                        //����������
	void Uninit();                                         //�j������
	void SelectUninit(TYPE type);                          //����j�����邩�I������j������
	void SelectUninitPrtas(TYPE type,int nNumber);         //����j�����邩�I������j������

	//�v���C���[
    void Lood();
	void UpdatePlayer();                                   //�v���C���[�̍X�V����
	void DrawPlayer(int NumPrts);                          //�v���C���[�̕`�揈��
	void MotionInfo();                                     //���[�V�����̏�����������
	void SetMotion(MOTIONSTATE motiontype);                //���[�V�������Ƃ̏���
	
	//�{�X
	void LoodBoss();
	void UpdateBoss();                                     //�{�X�̍X�V����
	void DrawBoss(int NumPrts);                            //�`�揈��
	void MotionInfoBoss();                                 //�{�X���[�V�����̏�����������
	void SetMotionBoss(BOSSMOTIONSTATE motiontype);        //�{�X���[�V�������Ƃ̏���

	CModelPrts* GetModelPrtasBoss(int nNumber) { return m_pModelPrtsBoss[nNumber]; }

	bool m_bMotionType, m_bMotionBossType;       //����ȃ��[�V�������ǂ����𔻒肷��ׂ̕ϐ�
	MOTIONSTATE m_MotionState;                   //�v���C���[�̃��[�V�����̎�ނ̏�������
	BOSSMOTIONSTATE m_MotionStateBoss;           //�{�X�̃��[�V�����̎�ނ̏�������
	CModelPrts* m_pModelPrts[MAX_PRTS];          //���f���p�[�c�̏��̃|�C���^�[
	CModelPrts* m_pModelPrtsBoss[MAX_BOSSPARTS]; //���f���p�[�c�̏��̃|�C���^�[

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_KEYSET = 5;        //���[�V�����Ɏg���L�[�̐�
	constexpr static int NUM_MOTION = 10;       //�v���C���[���[�V�����̑���
	constexpr static int NUM_RIGHTPRTS = 8;     //�v���C���[�̑��̃p�[�c��
	constexpr static int NUM_MOTIONBOSS = 10;   //�{�X�̃��[�V�����̑���
	constexpr static int NUM_RIGHTPRTSBOSS = 8; //�{�X�̑��̃p�[�c��

private://�O������̃A�N�Z�X�s�\

	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}Key;

	//�L�[�Z�b�g�̍\����
	typedef struct
	{
		int Frame;
		Key aKey[MAX_PRTS];
	}KeySet;

	//���[�V�����̍\����
	typedef struct
	{
		bool Loop;
		int NumKey;
		KeySet KeySet[MAX_KEYSET];
	}MotionSet;

	//���[�V���������m�ۂ���\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}SAVEMODELINFO;

	//�L�����N�^�[�̏���ۊǂ���ϐ�
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_PRTS], m_pSaveModelPrtInfoBoss[MAX_BOSSPARTS];   //���f���p�[�c�̏��̃|�C���^�[
	D3DXVECTOR3 SaveMotionPos[MAX_PRTS], SaveMotionPosBoss[MAX_BOSSPARTS];                 //�e�p�[�c�̈ʒu�����m�ۂ���ϐ�
	D3DXVECTOR3 SaveMotionRot[MAX_PRTS], SaveMotionRotBoss[MAX_BOSSPARTS];                 //�e�p�[�c�̌��������l������ϐ�
	MotionSet MotionSetPlayer[NUM_MOTION], MotionSetBoss[NUM_MOTIONBOSS];                       //�e���[�V�����̎�ނ��i�[����ϐ�

	int m_nMotionFrameBoss;        //���[�V�������̃t���[�����J�E���g���邽�߂̕ϐ�
	int MotionCount, MotionCountBoss;  //���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)
};