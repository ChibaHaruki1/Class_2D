//==========================================================
//
//���[�V�����̊e�p�[�c���Ƃ̃N���X�Ǘ�[model_prts.h]
//Auther;Chiba Haruki
//
//==========================================================

#pragma once

//==========================================================
//�C���N���[�h
#include "main.h"

#define MAX_MODEL_TEXTURE (50)

class CModelPrts
{
public:
	CModelPrts();                    //�R���X�g���N�^
	~CModelPrts();                   //�f�X�g���N�^
	HRESULT Init();                  //����������
	void Uninit();                   //�j������
	void Update();                   //�X�V����
	void Draw(D3DXMATRIX MtxWolrd);  //�`�揈��
	void Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat);  //�e�N�X�`���̓ǂݍ���ObjectX�Ɠ��������邽�߂Ɉ���                                  //X�t�@�C���̓ǂݍ���
	void BindSize(D3DXVECTOR3&max, D3DXVECTOR3&min, D3DXVECTOR3&ModelSize); //�e���f���̃p�[�c�̑傫����n�������֐��iObjectX�Ɠ����̈׈����j
	void SetParent(CModelPrts* pParent);              //�e�p�[�c�̐ݒ�
	void Size();                                      //�e���f���̃p�[�c�̑傫�������߂鏈���֐�
	static CModelPrts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat); //��������

	//=================================================
	//���̎擾
	D3DXVECTOR3& GetPos() { return m_pos; }                  //�ʒu�̎擾
	D3DXVECTOR3& GetRot() { return m_rot; }                  //�����̎擾
	D3DXMATRIX& GetWorldMtx() { return m_mtxWorld; }         //�}�g���b�N�X�̎擾

	int& GetIndexPrts() { return m_nIndexPrts; }             //���Ԗڂ̃p�[�c���擾
	int& GetIndexModelPrts() { return m_nIndexModelPrts; }   //�e�p�[�c�̎擾


	//=================================================
	//���̐ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }            //�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }            //�����̐ݒ�

	LPD3DXMESH m_pMesh;       //���b�V���̂ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;  //�o�b�t�@�̃|�C���^
	DWORD m_nNumMat;          //�}�e���A����

	//���f���T�C�Y�̎擾
	D3DXVECTOR3 m_min;       //���_�̍ŏ��l
	D3DXVECTOR3 m_max;       //���_�̍ő�l
	D3DXVECTOR3 m_ModelSize; //���f���̃T�C�Y���i�[

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEXTURE];  //�e�N�X�`���ւ̃|�C���^
	bool m_bCreateGun;                                 //�e�����ꂽ���ǂ�������p�̕ϐ�

private:
	CModelPrts* m_pParentlPrts;  //�����̃|�C���^�[
	D3DXVECTOR3 m_pos;           //�ʒu
	D3DXVECTOR3 m_rot;           //����
	D3DXMATRIX m_mtxWorld;    //�}�g���b�N�X

	int m_nIndexPrts;            //���Ԗڂ̃p�[�c
	int m_nIndexModelPrts;       //�e�̃p�[�c
};
