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

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                  //�e�N�X�`���i���W�j�̏��
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex);  //�G�t�F�N�g�̏���

	const char* GetEffectFileNamePass() { return m_aEffectFileName; }                               //�t�@�C���p�X���擾
	void SetEffectFileNamePass(const char* aEffectFieName) { m_aEffectFileName = aEffectFieName; }  //�t�@�C���p�X��ݒ�

private:
	//�}�N����`
	constexpr static float MAX_EXPLOSION_LIFE = 8;        //�A�j���[�V�����̍X�V���鎞�̃��C�t

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //���g�̃o�b�t�@�[
	int m_nLife;                            //�e�N�X�`���̃��C�t�i�A�j���[�V�����p�́j
	const char* m_aEffectFileName;          //�e�N�X�`���̃t�@�C���p�X

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
	CManagerEffect(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerEffect();								   //�f�X�g���N�^
	HRESULT Init()override;							   //����������
	void Uninit()override;							   //�j������
	void Update()override;							   //�X�V����
	void Draw()override;							   //�`�揈��
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerEffect* Create(D3DXVECTOR3 pos, TYPE type); //��������

	CEffectDirection* GetEffectDirection() { return m_pEffectDirection000; } //�X�g���e�W�[���N���X�̃|�C���^�[���擾

protected://�p���N���X�̂݃A�N�Z�X�\

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int SET_BULLET_LIFE = 42;          //���C�t�̍ő吔
	constexpr static float m_fPillarOfFireSizeX = 200.0f; //����̉���X���̑傫��
	constexpr static float m_fPillarOfFireSizeY = 600.0f; //����̉���Y���̑傫��
	constexpr static float m_fSepecialAttackX = 200.0f;   //�K�E�Z��X���̑傫��
	constexpr static float m_fSepecialAttackY = 200.0f;   //�K�E�Z��Y���̑傫��
	constexpr static float MAX_EXPLOSION_TEX = 0.125f;    //�A�j���[�V�����̕�����

private:
	int m_nEffectNumber;  //�Ō�ɃG�t�F�N�g���ĂԂ��ǂ���
	double m_dLifeCount; //�A�j���[�V�����̑��x
	float m_fMaxTex;     //�e�N�X�`���̍ő�̃T�C�Y
	CEffectDirection* m_pEffectDirection000;  //�X�g���e�W�[���N���X�̃|�C���^�[
};


//========================================================================================================
//����ꂽ�Ƃ��̃G�t�F�N�g����
class CBreakEffect : public CManagerEffect
{
public:
	CBreakEffect();            //�R���X�g���N�^
	~CBreakEffect()override;   //�f�X�g���N�^

};


//========================================================================================================
//1�ڂ̔����G�t�F�N�g
class CExplosion : public CManagerEffect
{
public:
	CExplosion();          //�R���X�g���N�^
	~CExplosion()override; //�f�X�g���N�^
};


//========================================================================================================
//��ڂ̔����G�t�F�N�g
class CExplosion001 : public CManagerEffect
{
public:
	CExplosion001();           //�R���X�g���N�^
	~CExplosion001()override;  //�f�X�g���N�^
};


//========================================================================================================
//���G�t�F�N�g
class CFire : public CManagerEffect
{
public:
	CFire();              //�R���X�g���N�^
	~CFire()override;	  //�f�X�g���N�^
	void Draw()override;  //�`�揈��

private:
	//�}�N����`
	constexpr static int FIRELIFE = 120; //�t�@�C�A�̃��C�t
};


//========================================================================================================
//����̉�
class CPillarOfFire : public CManagerEffect
{
public:
	CPillarOfFire();           //�R���X�g���N�^
	~CPillarOfFire()override;  //�f�X�g���N�^
	HRESULT Init()override;    //����������
	void Update()override;     //�X�V����

private:
	//�}�N����`
	constexpr static int PILLARFIRELIFE = 180; //�t�@�C�A�̃��C�t
};


//========================================================================================================
//�e�̋O���ɂ��G�t�F�N�g
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CEffect()override;							//�f�X�g���N�^
	HRESULT Init()override;						//����������
	void Uninit()override;						//�j������
	void Update()override;						//�X�V����
	void Draw()override;						//�`�揈��
	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);

	static CEffect* Create(D3DXVECTOR3 pos);    //��������

private:
	//�}�N����`
	constexpr static int SET_EFFECT_LIFE = 30; //���C�t�̍ő吔
};


//========================================================================================================
//�j�ЃG�t�F�N�g�̃N���X
class CDebris : public CManagerEffect
{
public:
	CDebris();              //�R���X�g���N�^
	~CDebris()override;     //�f�X�g���N�^
	void Update()override;  //�X�V����

private:
	//�}�N����`
	constexpr static int DEBRISLIFE = 10;
};


//========================================================================================================
//�K�E�Z�̃N���X
class CSpecialAttack : public CManagerEffect
{
public:
	CSpecialAttack();                               //�R���X�g���N�^
	~CSpecialAttack()override;                      //�f�X�g���N�^
	void Update()override;                          //�X�V����
	int& GetRotNumber() { return m_nRotNumber; }    //���݂̌�����ԍ��Ŏ擾����

private:
	//�}�N����`
	constexpr static int SPECIALATTACKLIFE = 180;

	int m_nRotNumber; //�����ő傫����ς��邽�߂̕ϐ�
};
