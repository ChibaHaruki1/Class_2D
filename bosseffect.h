//=========================================
//
//�{�X�p�G�t�F�N�g�̃N���X�Ǘ�[efect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once

//=========================
//�C���N���[�h
#include "object3D.h"


//========================================================================================================
//�X�g���e�W�[�N���X���
class CBossEffectDirection
{
public:
	CBossEffectDirection();
	~CBossEffectDirection();

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                //�e�N�X�`���̐ݒ�
	 void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,double dLifeCount,float fMaxTex); //�e�N�X�`���̍X�V

	 const char* m_pEffectFileName;

protected:
	int m_nCount;
	int m_nLife;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine;
};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@�Ռ��j
class CAttackEffect : public CBossEffectDirection
{
public:
	CAttackEffect();
	~CAttackEffect();
};

//========================================================================================================
//�K�E�Z
class CSourceSpecialAttackBoss : public CBossEffectDirection
{
public:
	CSourceSpecialAttackBoss();   //�R���X�g���N�^
	~CSourceSpecialAttackBoss();  //�f�X�g���N�^
};


//========================================================================================================
//�{�X�G�t�F�N�g�Ǘ��̊��N���X
class CManagerBossEffect : public CObject3D
{
public: //�O������A�N�Z�X�\
	CManagerBossEffect(int nPriority = DEFAULT_PRIORITY);
	~CManagerBossEffect();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerBossEffect* Create(D3DXVECTOR3 pos, TYPE type);
	bool& GetFly() { return m_bFly; }
	int& GetRotNumber() { return m_nBossRotNumber; }

	CBossEffectDirection* m_pEffectDirection000;  //�X�g���e�W�[���N���X�̃|�C���^�[

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static float MAX_BOSSANIMETION_TEX = 0.125f;     //�A�j���[�V�����̕�����
	constexpr static float MAX_BOSSANIMATION_LIFE = 8;         //�A�j���[�V�����̍X�V���鎞�̃��C�t
	constexpr static float MAX_BOSSSPECIALATTACK_X = 200.0f;   //�{�X�̕K�E�Z��Y���̑傫��
	constexpr static float MAX_BOSSSPECIALATTACK_Y = 200.0f;   //�{�X�̕K�E�Z��Y���̑傫��
	constexpr static float PLUS_POS_Y = 100.0f;                //�K�E�Z��Y���̈ʒu�𑫂����킹��ׂ̃}�N��
	constexpr static float MAX_DAMAGE = 0.01f;                 //�{�X�̕K�E�Z��Y���̑傫��

protected://�p���N���X�̂݃A�N�Z�X�\
	int m_nBossRotNumber; //�����ő傫����ς��邽�߂̕ϐ�
	float fMaxTex;        //�e�N�X�`���̍ő�̃T�C�Y
	double m_dLifeCount;  //�A�j���[�V�����̑��x
	bool m_bFly;          //������Ԃ��ǂ���

private://�O������̃A�N�Z�X�s�\
	int m_nEffectNumber;  //�Ō�ɃG�t�F�N�g���ĂԂ��ǂ���
	int m_nFrame;
};


//========================================================================================================
//�Ռ��g�̃G�t�F�N�g����
class CImpact : public CManagerBossEffect
{
public:
	CImpact();
	~CImpact()override;
	void Update()override;
};


//========================================================================================================
//�K�E�Z�̃G�t�F�N�g����
class CBossSpecialAttack : public CManagerBossEffect
{
public:
	CBossSpecialAttack();
	~CBossSpecialAttack()override;
	void Update()override;

};