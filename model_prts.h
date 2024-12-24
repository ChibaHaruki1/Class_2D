//
//
//
//
//
//

#pragma once
#include "main.h"

#define MAX_MODEL_TEXTURE (50)

class CModelPrts
{
public:
	CModelPrts();                 //�R���X�g���N�^
	~CModelPrts();                                         //�f�X�g���N�^
	HRESULT Init();                                        //����������
	void Uninit();                                         //�j������
	void Update();                                        //�X�V����
	void Draw(D3DXMATRIX MtxWolrd);                                           //�`�揈��
	void Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat);                                          //X�t�@�C���̓ǂݍ���
	void BindSize(D3DXVECTOR3&max, D3DXVECTOR3&min, D3DXVECTOR3&ModelSize);
	void BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat);
	void BindPos(D3DXVECTOR3&pos);
	void SetParent(CModelPrts* pParent);
	void Size();
	D3DXMATRIX& GetWorldMtx() { return m_mtxWorld; }
	static CModelPrts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat); //��������

	int m_nIndexPrts;      //���Ԗڂ̃p�[�c
	int m_nIndexModelPrts; //�e�̃p�[�c
	
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld; //�}�g���b�N�X
	LPD3DXMESH m_pMesh; //���b�V���̂ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat; //�o�b�t�@�̃|�C���^
	DWORD m_nNumMat;

	//���f���T�C�Y�̎擾
	D3DXVECTOR3 m_min; //���_�̍ŏ��l
	D3DXVECTOR3 m_max; //���_�̍ő�l
	D3DXVECTOR3 m_ModelSize; //���f���̃T�C�Y���i�[

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEXTURE]; //�e�N�X�`���ւ̃|�C���^
	//D3DXMATERIAL* m_pMat; //�}�e���A���̃|�C���^
	bool m_bCreateGun;
private:
	CModelPrts* m_pParentlPrts;  //�����̃|�C���^�[
	int nNumTexture;
};
