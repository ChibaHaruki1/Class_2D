//================================================================
//
//character�N���X�Ǘ�[character.h]
//Ajther: Chiba haruki
//
//================================================================

#pragma once

#include "objectX.h"
#include "model_prts.h"

//�G
#define MAX_ENEMYKEYSET (5)   //�L�[��
#define NUM_ENEMYMOTION (10)  //���[�V������

//�L�����N�^�[�̊e�p�[�c�N���X
class CEnemyCharacter : public CObjectX
{
public:

	//�G�̃��[�V�����̎��
	typedef enum
	{
		ENEMYWALK = 0,
		ENEMYJUMP,
		ENEMYATTACK,
		ENEMYDIE,

	}ENEMYMOTIONSTATE;

	CEnemyCharacter(int nPriority = DEFAULT_PRIORITY1);      //�R���X�g���N�^
	~CEnemyCharacter();                                      //�f�X�g���N�^
	HRESULT Init();                                          //����������
	void Uninit();                                           //�j������
	void SelectUninitPrtas(TYPE type, int nNumber);          //����j�����邩�I������j������
	void UpdateEnemy001();                                   //�G001�̍X�V����
	void DrawEnemy(int NumPrts ,int nNumber);                //�`�揈��
	void LoodEnemy(const char* aSelect);                     //���f����ǂݍ��ޏ����{�����擾���鏈��
	void MotionInfoEnemy();                                  //�{�X���[�V�����̏�����������
	void SetMotionEnemy(ENEMYMOTIONSTATE motiontype);        //�{�X���[�V�������Ƃ̏���

	CModelPrts* GetModelPrtasEnemy(int nNumber) { return m_pModelPrtsEnemy[nNumber]; }

	bool m_bMotionType, m_bMotionBossType;         //����ȃ��[�V�������ǂ���
	ENEMYMOTIONSTATE m_MotionStateBoss;            //�{�X�̃��[�V�����̎�ނ̏�������
	CModelPrts* m_pModelPrtsEnemy[MAX_ENEMYPARTS]; //���f���p�[�c�̏��̃|�C���^�[

	static int m_nMaxCreate;                       //���݂̃v���C���[��parts��

private:
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
		Key aKey[MAX_ENEMYPARTS];
	}KeySet;

	//���[�V�����̍\����
	typedef struct
	{
		bool Loop;
		int NumKey;
		KeySet KeySet[MAX_ENEMYKEYSET];
	}MotionSet;

	//���[�V���������m�ۂ���\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}SAVEMODELINFO;

	//�L�����N�^�[�̏���ۊǂ���ϐ�
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_ENEMYPARTS],m_pSaveModelPrtUpdateInfo[MAX_ENEMYPARTS];         //���f���p�[�c�̏��̃|�C���^�[
	D3DXVECTOR3 SaveMotionPos[MAX_ENEMYPARTS];                 //�e�p�[�c�̈ʒu�����m�ۂ���ϐ�
	D3DXVECTOR3 SaveMotionRot[MAX_ENEMYPARTS];                 //�e�p�[�c�̌��������l������ϐ�
	MotionSet MotionSetEnemy[NUM_ENEMYMOTION];                 //�e���[�V�����̎�ނ��i�[����ϐ�

	int m_nMotionFrameBoss;        //���[�V�������̃t���[�����J�E���g���邽�߂̕ϐ�
	int MotionCount, MotionCountBoss;  //���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)
};