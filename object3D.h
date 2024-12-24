//====================================================
//
//3D�I�u�W�F�N�g�N���X�Ǘ�[object3D.h]
//Auther:Chiba Haruki
//
//====================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = DEFAULT_PRIORITY); //�R���X�g���N�^
	~CObject3D() override;                                   //�f�X�g���N�^
	HRESULT Init() override;                                 //����������
	HRESULT BillboardInit();                                 //�r���{�[�h���̏������ݒ�
	void Uninit() override;                                  //�j������
	void Update()override;                                   //�X�V����
	void Draw() override;                                    //�`�揈��
	void DrawNoml()override;                                 //�r���{�[�h�̕`�揈��
	void DrawEffect();                                       //�G�t�F�N�g�p�̕`�揈��
	void DrawEffect1();                                       //�G�t�F�N�g�p�̕`�揈��
	void SetPos(D3DXVECTOR3 pos);                            //�ʒu�̐ݒ菈��
	void SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z);  //polygon�̃T�C�Y�𒲐����鏈��
	void SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z);  //�G�t�F�N�g�ppolygon�̃T�C�Y�𒲐����鏈��
	void SetSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z);  //�G�t�F�N�g�ppolygon�̃T�C�Y�𒲐����鏈��
	void SetCol(int Red, int Green,int Blue,int& Alpha);     //�F�Ɋւ���ݒ�
	void SetTexture(float SizeX, float Size1X);              //�e�N�X�`���̃T�C�Y��ݒ肷��

	//�����蔻�菈��
	bool CollisionPrts1Right(float X, float Y, float Z);     //�p�[�c���̓����蔻��@�E��
	bool CollisionPrts1Left(float X, float Y, float Z);      //�p�[�c���̓����蔻��@����
	bool CollisionPrtsPlayer(float X, float Y, float Z);     //�p�[�c���̓����蔻��@�S��

	HRESULT Lood();                                          //�e�N�X�`���t�@�C���̓ǂݍ���

	//���̎擾
	D3DXVECTOR3& GetPos() { return m_pos; }                  //�ʒu�̎擾
	int& GetLife() { return m_nLife; }                       //���C�t�̎擾
	int& GetAlpha() { return m_nAlpha; }
	float& GetSizeY() { return m_fSizeY; }

protected:
	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_move; //�ړ���
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_col; //�F
	D3DXMATRIX m_mtxWorld; //�}�g���b�N�X

	int m_nLife;
	int m_nAlpha;
	int m_nFrame;
	float m_fSizeX;  //�����̃T�C�Y�̒����p�ϐ�
	float m_fSizeY;  //�����̃T�C�Y�̒����p�ϐ�
	const char* m_aFileName;
};

#endif // !_OBJECT3D_H_

