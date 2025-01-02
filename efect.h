//=========================================
//
//�G�t�F�N�g�̃N���X�Ǘ�[efect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once
	
//=========================================
//�C���N���[�h
#include "object3D.h"
#include<memory>


//========================================================================================================
//�X�g���e�W�[�N���X���
class CEffectDirection
{
public:
	CEffectDirection();  //�R���X�g���N�^
	~CEffectDirection(); //�f�X�g���N�^

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                //�e�N�X�`���i���W�j�̏��
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,double dLifeCount,float fMaxTex);  //�G�t�F�N�g�̏���

	const char* m_pEffectFileName;          //�e�N�X�`���̃t�@�C���p�X
	int m_nLife;                            //�e�N�X�`���̃��C�t�i�A�j���[�V�����p�́j
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //���g�̃o�b�t�@�[
};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@��
class CThunder : public CEffectDirection
{
public:
	CThunder();   //�R���X�g���N�^
	~CThunder();  //�f�X�g���N�^			
};


//========================================================================================================
//�X�g���e�W�[�N���X�p���@����
class CExplotion : public CEffectDirection
{
public:
	CExplotion();   //�R���X�g���N�^
	~CExplotion();  //�f�X�g���N�^						  
};


//========================================================================================================
//��
class CExplotionPillar : public CEffectDirection
{
public:
	CExplotionPillar();   //�R���X�g���N�^
	~CExplotionPillar();  //�f�X�g���N�^
};


//========================================================================================================
//����̉�
class CExplotionPillar001 : public CEffectDirection
{
public:
	CExplotionPillar001();   //�R���X�g���N�^
	~CExplotionPillar001();	 //�f�X�g���N�^
};


//========================================================================================================
//�X�g���e�W�[�p���@�j��
class CFormerDebris : public CEffectDirection
{
public:
	CFormerDebris();   //�R���X�g���N�^
	~CFormerDebris();  //�f�X�g���N�^
};


//========================================================================================================
//�X�g���e�W�[�p���@�K�E�Z
class CSourceSpecialAttack : public CEffectDirection
{
public:
	CSourceSpecialAttack();   //�R���X�g���N�^
	~CSourceSpecialAttack();  //�f�X�g���N�^
};


//========================================================================================================
//�G�t�F�N�g�Ǘ��̊��N���X
//========================================================================================================
class CManagerEffect : public CObject3D
{
public:
	CManagerEffect(int nPriority=DEFAULT_PRIORITY);
	~CManagerEffect();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerEffect* Create(D3DXVECTOR3 pos, TYPE type);

	CEffectDirection* m_pEffectDirection000;

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static float m_fPillarOfFireSizeX = 200.0f; //����̉���X���̑傫��
	constexpr static float m_fPillarOfFireSizeY = 600.0f; //����̉���Y���̑傫��
	constexpr static float m_fSepecialAttackX = 200.0f;   //�K�E�Z��X���̑傫��
	constexpr static float m_fSepecialAttackY = 200.0f;   //�K�E�Z��Y���̑傫��
	constexpr static float MAX_EXPLOSION_TEX = 0.125f;    //�A�j���[�V�����̕�����
	constexpr static float MAX_EXPLOSION_LIFE = 8;        //�A�j���[�V�����̍X�V���鎞�̃��C�t

protected://�p���N���X�̂݃A�N�Z�X�\
	double m_dLifeCount; //�A�j���[�V�����̑��x
	float m_fMaxTex;     //�e�N�X�`���̍ő�̃T�C�Y

private:
	int m_nEffectNumber;  //�Ō�ɃG�t�F�N�g���ĂԂ��ǂ���

};


//========================================================================================================
//����ꂽ�Ƃ��̃G�t�F�N�g����
class CBreakEffect : public CManagerEffect
{
public:
	CBreakEffect();
	~CBreakEffect()override;
	
};


//========================================================================================================
//1�ڂ̔����G�t�F�N�g
class CExplosion : public CManagerEffect
{
public:
	CExplosion();
	~CExplosion()override;
};


//========================================================================================================
//��ڂ̔����G�t�F�N�g
class CExplosion001 : public CManagerEffect
{
public:
	CExplosion001();
	~CExplosion001()override;
};


//========================================================================================================
//���G�t�F�N�g
class CFire : public CManagerEffect
{
public:
	CFire();
	~CFire()override;
	void Draw()override;
};


//========================================================================================================
//����̉�
class CPillarOfFire : public CManagerEffect
{
public:
	CPillarOfFire();
	~CPillarOfFire();
	HRESULT Init()override;
	void Update()override;

private:
};


//========================================================================================================
//�e�̋O���ɂ��G�t�F�N�g
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = DEFAULT_PRIORITY);
	~CEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);

	static CEffect* Create(D3DXVECTOR3 pos);

private:
	int m_nLife;
};


//========================================================================================================
//�j�ЃG�t�F�N�g�̃N���X
class CDebris : public CManagerEffect
{
public:
	CDebris();
	~CDebris();
	void Update()override;

private:
	float m_fSiseX;
};


//========================================================================================================
//�K�E�Z�̃N���X
class CSpecialAttack : public CManagerEffect
{
public:
	CSpecialAttack();
	~CSpecialAttack();
	void Update()override;
	int& GetRotNumber() { return m_nRotNumber; }

private:
	int m_nRotNumber; //�����ő傫����ς��邽�߂̕ϐ�
};
