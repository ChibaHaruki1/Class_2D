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
	CBossEffectDirection();   //�R���X�g���N�^
	~CBossEffectDirection();  //�f�X�g���N�^

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                 //�e�N�X�`���̐ݒ�
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex); //�e�N�X�`���̍X�V

	const char* m_pEffectFileName; //�t�@�C���p�X

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //���g�̃o�b�t�@
	int m_nLife; //�A�j���[�V�����̃��C�t�p�̕ϐ�
};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@�Ռ��j
class CAttackEffect : public CBossEffectDirection
{
public:
	CAttackEffect();   //�R���X�g���N�^
	~CAttackEffect();  //�f�X�g���N�^
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
	CManagerBossEffect(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerBossEffect();								   //�f�X�g���N�^
	HRESULT Init()override;								   //����������
	void Uninit()override;								   //�j������
	void Update()override;								   //�X�V����
	void Draw()override;								   //�`�揈��
	void SetEffect(D3DXVECTOR3 pos);                       //�G�t�F�N�g�̈ʒu�̐ݒ�

	static CManagerBossEffect* Create(D3DXVECTOR3 pos, TYPE type);  //���������i�p���N���X��TYPE�Ő�������j

	bool& GetFly() { return m_bFly; }                 //�Ռ��g�ɓ����������ǂ�������p�̕ϐ��̎擾
	int& GetRotNumber() { return m_nBossRotNumber; }  //���E�ǂ���̌����ɂȂ��Ă��邩�����Ŕ��肷������擾

	CBossEffectDirection* m_pEffectDirection000;      //�X�g���e�W�[���N���X�̃|�C���^�[

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static float MAX_BOSSANIMETION_TEX = 0.125f;     //�A�j���[�V�����̕�����
	constexpr static float MAX_BOSSANIMATION_LIFE = 8;         //�A�j���[�V�����̍X�V���鎞�̃��C�t
	constexpr static float MAX_BOSSSPECIALATTACK_X = 200.0f;   //�{�X�̕K�E�Z��Y���̑傫��
	constexpr static float MAX_BOSSSPECIALATTACK_Y = 200.0f;   //�{�X�̕K�E�Z��Y���̑傫��
	constexpr static float PLUS_POS_Y = 100.0f;                //�K�E�Z��Y���̈ʒu�𑫂����킹��ׂ̃}�N��
	constexpr static float MAX_DAMAGE = 0.01f;                 //�{�X�̕K�E�Z��Y���̑傫��

protected://�p���N���X�̂݃A�N�Z�X�\
	double m_dLifeCount;  //�A�j���[�V�����̑��x
	bool m_bFly;          //������Ԃ��ǂ���

private://�O������̃A�N�Z�X�s�\
	int m_nEffectNumber;  //�Ō�ɃG�t�F�N�g���ĂԂ��ǂ���
	int m_nBossRotNumber; //�����ő傫����ς��邽�߂̕ϐ�
};


//========================================================================================================
//�Ռ��g�̃G�t�F�N�g����
class CImpact : public CManagerBossEffect
{
public:
	CImpact();              //�R���X�g���N�^
	~CImpact()override;     //�f�X�g���N�^
	void Update()override;  //�X�V����
};


//========================================================================================================
//�K�E�Z�̃G�t�F�N�g����
class CBossSpecialAttack : public CManagerBossEffect
{
public:
	CBossSpecialAttack();           //�R���X�g���N�^
	~CBossSpecialAttack()override;  //�f�X�g���N�^
	void Update()override;          //�X�V����

};