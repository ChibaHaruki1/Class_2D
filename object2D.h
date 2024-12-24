//===============================================
//
//�Q�c�I�u�W�F�N�g�̃N���X�Ǘ�[object.h]
//Auther:Chiba Haruki
//
//===============================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"
#include "input.h"

//�}�N����`
#define MAX_LIFE (40) //�e�ƒe�ɂ��G�t�F�N�g��Life

class CObject2D : public CObject
{
public:
	CObject2D(int nPriority=DEFAULT_PRIORITY); //�R���X�g���N�^
	~CObject2D() override; //�f�X�g���N�^
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void DrawNoml()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSIze(float SIZE_X,float SIZE1_X, float SIZE_Y, float SIZE1_Y); //polygon�̃T�C�Y�𒲐����鏈��
	void SetCol(int Alph,int Alph1);

	D3DXVECTOR3& GetPos() {return g_pos;}
	HRESULT Lood(); //�e�N�X�`���t�@�C���̓ǂݍ���
	static CObject2D* Create();
	//LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; }

protected:
	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 g_pos; //�ʒu
	D3DXVECTOR3 g_move; //�ړ���
	D3DXVECTOR3 g_rot; //����
	D3DXVECTOR3 m_col; //�F
	float g_fLength; //�Ίp���̒���
	float g_fAngle; //�Ίp���̊p�x

	int m_nLife;
	int m_fAlph;
	int m_fAlph1;
	int m_nRandom;
	int m_nFrame;

	bool m_bUse;
	const char* m_aFileName;

private:
	static CObject2D* m_apObject2D[DEFAULT_PRIORITY][MAX_OBJECT];
};

#endif // !_OBJECT2D_H_
