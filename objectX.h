
//====================================================
//
//X�t�@�C���ǂݍ��݃N���X�Ǘ�[objectX.h]
//Auther:Chiba Haruki
//
//====================================================

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "objectmanagerX.h"
#include "input.h"
#include "collision.h"
#include "ui.h"

#define MAX_TEXTURE (64) //�ۊǂł���ő�̃e�N�X�`���[��
#define MAX_OBJECTSPEED (2.0f)

class CObjectX : public CObjectManagerX
{
public://�O������̃A�N�Z�X�\
	CObjectX(int nPriority = DEFAULT_PRIORITY1);            //�R���X�g���N�^
	~CObjectX() override;                                   //�f�X�g���N�^
	HRESULT Init()override;                                 //����������
	void Uninit() override;                                 //�j������
	void Update() override;                                 //�X�V����
	void Draw() override;                                   //�`�揈��
	void Size();                                            //�RD���f���̃T�C�Y���擾���邽�߂̊֐�
	void Gravity();                                         //�d�͏���
	void GravityTogether();                                 //�d�͂𓯊������鏈��
	void Junp(TYPE type,float fJumpPwer);                                   //��ԏ���
	void TargetHeadingTowards(CObjectX*pObject,float MAX_SPEED);            //�ڕW�Ɍ���������
	HRESULT Lood();                                         //���t�@�C���̓ǂݍ��݊֐��i�����œǂݍ��ރt�@�C���p�X��n���j
	void ObjectArrangement(CObjectX::TYPE type, CUI* pUI1); //�z�u�c�[��
	void BindTexture(LPDIRECT3DTEXTURE9 pTex, LPD3DXMESH pMesh, LPD3DXBUFFER BuffMat, DWORD NumMat, D3DXMATERIAL* pMat); //�h���N���X�̏������炤���߂̊֐��i�RD���f���֘A�j

	bool CollisionBossPrts();                                                   //�v���C���[�ƃ{�X�̓����蔻��
	bool CollisionRightSelectPlayer(CObjectX* pObject);                         //�v���C���[�Ǝw�肵��obj�̓����蔻��i�P�́j�E��
	bool CollisionLeftSelectPlayer(CObjectX* pObject);                          //�v���C���[�Ǝw�肵��obj�̓����蔻��i�P�́j����
	bool CollisionPlayerSelect(CObjectX* pObject);                              //�v���C���[����obj�̓����蔻��
	bool CollisionPlayerInEnemy(CObjectX* pObject,float fMagnification);        //�v���C���[����obj�̓����蔻��+�����蔻��͈̔�

	int& GetLife() { return m_nLife; }      //���C�t���擾
	int& GetRandom() { return m_nRandom; }  //�������擾
	float& GetAngle() { return m_fAngle; }  //�Ίp���̊p�x���擾

	D3DXVECTOR3& GetModelSize() { return m_ModelSize; }                                       //���f���̃T�C�Y���擾����
	D3DXVECTOR3& GetModelSizePrts(int nNumber) { return m_ModelSizePrts[nNumber]; }           //�v���C���[�̃��f���̃T�C�Y���擾����
	D3DXVECTOR3& GetPosPrts(int nNumber) { return m_posPrts[nNumber]; }                       //�v���C���[�̊eparts��pos�̏���Ԃ��֐�
	D3DXVECTOR3& GetModelSizePrtsBoss(int nNumber) { return m_ModelSizePrtsBoss[nNumber]; }   //�{�X�̃��f���̃T�C�Y���擾����
	D3DXVECTOR3& GetPosPrtsBoss(int nNumber) { return m_posPrtsBoss[nNumber]; }               //�{�X�̊eparts��pos�̏���Ԃ��֐�
	D3DXVECTOR3& GetModelSizePrtsEnemy(int nNumber) { return m_ModelSizePrtsEnemy[nNumber]; } //�G�̃��f���̃T�C�Y���擾����
	D3DXVECTOR3& GetPosPrtsEnemy(int nNumber) { return m_posPrtsEnemy[nNumber]; }             //�G�̊eparts��pos�̏���Ԃ��֐�

	D3DXVECTOR3& GetPos() { return m_pos; }                                                   //�h���N���X��pos�̏���Ԃ��֐�
	D3DXVECTOR3& GetRot() { return m_rot; }                                                   //�h���N���X��rot�̏���Ԃ��֐�
	D3DXVECTOR3& GetMove() { return m_move; }                                                 //�h���N���Xmove�̏���Ԃ�
	CCollision* GetCollision() { return m_pCollision; }                                       //�����蔻��̏���Ԃ��֐�
	D3DXMATRIX& GetmtxWorld() { return m_mtxWorld; }                                          //���[���h�}�g���b�N�X�̏���Ԃ��֐�

	//�}�N����`
	constexpr static int MAX_PRTS = 19;          //�v���C���[�̃p�[�c��
	constexpr static int MAX_BOSSPARTS = 18;     //�{�X�̃p�[�c��
	constexpr static int MAX_ENEMYPARTS = 20;    //�G�̍ő�p�[�c��
	constexpr static float MAX_GRAVITY_G = 0.5f; //�d�͂̍ő�l

protected://�p���N���X�̂݃A�N�Z�X�\

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE]; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         //���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;                          //�ʒu
	D3DXVECTOR3 m_move;                         //�ړ���
	D3DXVECTOR3 m_rot;                          //����
	D3DXVECTOR3 m_col;                          //�F
	D3DXMATRIX m_mtxWorld;                      //�}�g���b�N�X
	LPD3DXMESH m_pMesh;                         //���b�V���̂ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;                    //�o�b�t�@�ւ̃|�C���^
	DWORD m_dwNumMat;                           //�}�e���A���̐�
	D3DXMATERIAL* m_pMat;                       //�}�e���A���̃|�C���^
	CCollision* m_pCollision;                   //�����蔻��֐��̃|�C���^�[

	//���f���T�C�Y�̎擾
	D3DXVECTOR3 min; //���_�̍ŏ��l
	D3DXVECTOR3 max; //���_�̍ő�l
	D3DXVECTOR3 m_ModelSize; //���f���̃T�C�Y���i�[

	//�p�[�c���Ƃ̃T�C�Y�擾
	D3DXVECTOR3 m_minPrts[MAX_PRTS]; //���_�̍ŏ��l
	D3DXVECTOR3 m_maxPrts[MAX_PRTS]; //���_�̍ő�l

	D3DXVECTOR3 m_ModelSizePrts[MAX_PRTS];            //���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_posPrts[MAX_PRTS];                  //���f���̈ʒu���i�[
	D3DXVECTOR3 m_ModelSizePrtsBoss[MAX_BOSSPARTS];   //�{�X���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_posPrtsBoss[MAX_BOSSPARTS];         //�{�X���f���̈ʒu���i�[
	D3DXVECTOR3 m_ModelSizePrtsEnemy[MAX_ENEMYPARTS]; //�G���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_posPrtsEnemy[MAX_ENEMYPARTS];       //�G���f���̈ʒu���i�[

	int m_nLife;              //Life���i�[����ϐ��iHP�j
	int m_nRandom;            //�������i�[����ϐ�
	int m_nFrame;
	int m_nDieFrame;           //���S�J�E���^�[
	float m_Gravity;           //�d�͉����x������
	float m_fAngle;            //�p�x���璷�������߂�p�̕ϐ�
	bool m_GravityFlag;        //�d�͂�ON�ɂ��邩�ǂ���
	bool m_JumpFlag;           //�W�����v�����Ă��邩�ǂ���
	bool m_bOneFlag;           //��񂾂�������ʂ��������p�̕ϐ�
	const char* m_aFileName;   //x�t�@�C���̃p�X�n���悤�̕ϐ�

	//�}�N����`
	constexpr static float D3DX_PI_ORI = 1.57f; //�ڕW�Ɍ��������̑���
	
private:
	CUI* pUI;
};

#endif // !_OBJECT3D_H_
