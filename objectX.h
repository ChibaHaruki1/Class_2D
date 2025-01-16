
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
	CObjectX(int nPriority = CObjectManagerX::DEFAULT_PRIORITY1);            //�R���X�g���N�^
	~CObjectX() override;                                   //�f�X�g���N�^
	HRESULT Init()override;                                 //����������
	void Uninit() override;                                 //�j������
	void Update() override;                                 //�X�V����
	void Draw() override;                                   //�`�揈��
	void Size();                                            //�RD���f���̃T�C�Y���擾���邽�߂̊֐�
	void Gravity();                                         //�d�͏���
	void GravityTogether();                                 //�d�͂𓯊������鏈��
	void Junp(TYPE type, float fJumpPwer);                                   //��ԏ���
	void TargetHeadingTowards(CObjectX* pObject, float MAX_SPEED);           //�ڕW�Ɍ���������
	HRESULT Lood();                                                          //���t�@�C���̓ǂݍ��݊֐��i�����œǂݍ��ރt�@�C���p�X��n���j
	void ObjectArrangement(CObjectX::TYPE type, CUI* pUI1);                  //�z�u�c�[��
	void BindTexture(LPDIRECT3DTEXTURE9 pTex, LPD3DXMESH pMesh, LPD3DXBUFFER BuffMat, DWORD NumMat, D3DXMATERIAL* pMat); //�h���N���X�̏������炤���߂̊֐��i�RD���f���֘A�j

	bool CollisionBossPrts();                                                   //�v���C���[�ƃ{�X�̓����蔻��
	bool CollisionRightSelectPlayer(CObjectX* pObject);                         //�v���C���[�Ǝw�肵��obj�̓����蔻��i�P�́j�E��
	bool CollisionLeftSelectPlayer(CObjectX* pObject);                          //�v���C���[�Ǝw�肵��obj�̓����蔻��i�P�́j����
	bool CollisionPlayerSelect(CObjectX* pObject);                              //�v���C���[����obj�̓����蔻��
	bool CollisionPlayerInEnemy(CObjectX* pObject, float fMagnification);       //�v���C���[����obj�̓����蔻��+�����蔻��͈̔�

	//==================================================
	//���ꂼ��̏����ɕK�v�ȏ����擾����
	int& GetLife() { return m_nLife; }          //���C�t���擾
	int& GetRandom() { return m_nRandom; }      //�������擾
	int& GetFrame() { return m_nFrame; }        //�t���[�����擾
	int& GetDieFrame() { return m_nDieFrame; }  //���S���̃t���[�����ϑ�����p�̏����擾
	float& GetGravity() { return m_fGravity; }  //�d�͂̏�������
	bool& GetJumpFlag() { return m_bJumpFlag; }
	bool& GetOneFlag() { return m_bOneFlag; }
	const char* GetFileName() { return m_aFileName; }

	//==================================================
	//�e���̐ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }                                //�ʒu�������Ɠ���������
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }                                //�����������Ɠ���������
	void SetLife(int nLife) { m_nLife = nLife; }                                 //���C�t�������Ɠ���������
	void SetRandom(int nRandom) { m_nRandom = nRandom; }                         //�����������Ɠ���������	
	void SetFrame(int nFrame) { m_nFrame = nFrame; }                             //�t���[���������Ɠ���������
	void SetDieFrame(int nDieFrame) { m_nDieFrame = nDieFrame; }                 //���S���̃t���[���������Ɠ���������
	void SetGravity(float fGravity) { m_fGravity = fGravity; }                   //�d�͂̒l�������Ɠ���������
	void SetGravityFlag(bool bGravityFlag) { m_bGravityFlag = bGravityFlag; }    //�d�̓t���O�������Ɠ���������
	void SetJumpFlag(bool bJumpFlag) { m_bJumpFlag = bJumpFlag; }
	void SetOneFlag(bool bOneFlag) { m_bOneFlag = bOneFlag; }
	void SetFileName(const char* aFileName) { m_aFileName = aFileName; }

	//==================================================
	//�p�[�c���̈ʒu�̏����擾����
	inline D3DXVECTOR3& GetPosPrts(int nNumber) { return m_posPrts[nNumber]; }                       //�v���C���[�̊eparts��pos�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetPosPrtsBoss(int nNumber) { return m_posPrtsBoss[nNumber]; }               //�{�X�̊eparts��pos�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetPosPrtsEnemy(int nNumber) { return m_posPrtsEnemy[nNumber]; }             //�G�̊eparts��pos�̏���Ԃ��֐�

   //==================================================
   //�p�[�c���̃T�C�Y���擾����
	inline D3DXVECTOR3& GetModelSizePrts(int nNumber) { return m_ModelSizePrts[nNumber]; }           //�v���C���[�̃��f���̃T�C�Y���擾����
	inline D3DXVECTOR3& GetModelSizePrtsBoss(int nNumber) { return m_ModelSizePrtsBoss[nNumber]; }   //�{�X�̃��f���̃T�C�Y���擾����
	inline D3DXVECTOR3& GetModelSizePrtsEnemy(int nNumber) { return m_ModelSizePrtsEnemy[nNumber]; } //�G�̃��f���̃T�C�Y���擾����

   //==================================================
   //�v���C���[�̃��f���T�C�Y�̎擾
	inline D3DXVECTOR3& GetModelSize() { return m_ModelSize; }                                       //���f���̃T�C�Y���擾����

   //==================================================
   //�O���{���̎擾
	inline D3DXVECTOR3& GetPos() { return m_pos; }                                                   //�h���N���X��pos�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetRot() { return m_rot; }                                                   //�h���N���X��rot�̏���Ԃ��֐�
	inline D3DXVECTOR3& GetMove() { return m_move; }                                                 //�h���N���Xmove�̏���Ԃ�

   //==================================================
   //�����ɕK�v�ȕ��̏��̎擾
	inline LPD3DXMESH& GetMesh() { return m_pMesh; }                                                 //mesh�̏���Ԃ�
	inline LPD3DXBUFFER& GetBuffMat() { return m_pBuffMat; }                                         //BuffMat�̏���Ԃ�
	inline DWORD& GetdwNumMat() { return m_dwNumMat; }                                               //dwNumMat�̐��̏���Ԃ�
	inline D3DXMATERIAL* GetMat() { return m_pMat; }                                                 //Mat�̏���Ԃ�
	inline D3DXMATRIX& GetmtxWorld() { return m_mtxWorld; }                                          //���[���h�}�g���b�N�X�̏���Ԃ��֐�

	CCollision* GetCollision() { return m_pCollision; }                                       //�����蔻��̏���Ԃ��֐�

    //==================================================
    //�p�[�c���Ƃ̃T�C�Y�擾
	inline D3DXVECTOR3& GetMinPrts(int nNumber) { return m_minPrts[nNumber]; }
	inline D3DXVECTOR3& GetMaxPrts(int nNumber) { return m_maxPrts[nNumber]; }


	//==================================================
	//���̒l���v���Đݒ�
	int& SetAddjustLife() { return m_nLife; }                          //���C�t�̒l��ύX�������Ƃ��̐ݒ�


	//==================================================
	//�}�N����`
	constexpr static int MAX_PRTS = 19;          //�v���C���[�̃p�[�c��
	constexpr static int MAX_BOSSPARTS = 18;     //�{�X�̃p�[�c��
	constexpr static int MAX_ENEMYPARTS = 20;    //�G�̍ő�p�[�c��
	constexpr static int NUM_MOTION_KEY = 5;     //�L�[�̐�
	constexpr static float MAX_GRAVITY_G = 0.5f; //�d�͂̍ő�l

protected://�p���N���X�̂݃A�N�Z�X�\

	//�}�N����`
	constexpr static float D3DX_PI_ORI = 1.57f; //�ڕW�Ɍ��������̑���

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE]; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         //���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;                      //�}�g���b�N�X

	D3DXMATERIAL* m_pMat;                       //�}�e���A���̃|�C���^
	LPD3DXMESH m_pMesh;                         //���b�V���̂ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;                    //�o�b�t�@�ւ̃|�C���^
	DWORD m_dwNumMat;                           //�}�e���A���̐�

	//���f���T�C�Y�̎擾
	D3DXVECTOR3 min;                            //���_�̍ŏ��l
	D3DXVECTOR3 max;                            //���_�̍ő�l
	D3DXVECTOR3 m_ModelSize;                    //���f���̃T�C�Y���i�[

	//�p�[�c���̈ʒu
	D3DXVECTOR3 m_posPrts[MAX_PRTS];            //���f���̈ʒu���i�[
	D3DXVECTOR3 m_posPrtsBoss[MAX_BOSSPARTS];         //�{�X���f���̈ʒu���i�[
	D3DXVECTOR3 m_posPrtsEnemy[MAX_ENEMYPARTS];       //�G���f���̈ʒu���i�[

	//�p�[�c���Ƃ̃T�C�Y
	D3DXVECTOR3 m_minPrts[MAX_PRTS];            //���_�̍ŏ��l
	D3DXVECTOR3 m_maxPrts[MAX_PRTS];            //���_�̍ő�l
	D3DXVECTOR3 m_ModelSizePrts[MAX_PRTS];      //���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_ModelSizePrtsBoss[MAX_BOSSPARTS];   //�{�X���f���̃T�C�Y���i�[
	D3DXVECTOR3 m_ModelSizePrtsEnemy[MAX_ENEMYPARTS]; //�G���f���̃T�C�Y���i�[

	CCollision* m_pCollision;                   //�����蔻��֐��̃|�C���^�[
	D3DXVECTOR3 m_col;                          //�F
	D3DXVECTOR3 m_pos;                          //�ʒu
	D3DXVECTOR3 m_rot;                          //����
	D3DXVECTOR3 m_move;                         //�ړ���
	CUI* pUI;

	int m_nLife;                //Life���i�[����ϐ��iHP�j
	int m_nRandom;              //�������i�[����ϐ�
	int m_nFrame;               //�t���[�����i�[����ϐ�
	int m_nDieFrame;            //���S�J�E���^�[
	float m_fGravity;           //�d�͉����x������
	float m_fAngle;             //�p�x���璷�������߂�p�̕ϐ�
	bool m_bGravityFlag;        //�d�͂�ON�ɂ��邩�ǂ���
	bool m_bJumpFlag;           //�W�����v�����Ă��邩�ǂ���
	bool m_bOneFlag;            //��񂾂�������ʂ��������p�̕ϐ�
	const char* m_aFileName;    //x�t�@�C���̃p�X�n���悤�̕ϐ�
};

#endif // !_OBJECT3D_H_

