//==================================
//
//�G�̃N���X�Ǘ�[enemy.h]
//Auther:Chiba Haruki
//
//==================================

#pragma once

//==================================
//�C���N���[�h
#include "objectX.h"
#include "enemycharacter.h"


//==========================================================
//�G�̃}�l�[�W���[�Ǘ��N���X
class CManagerEnemy : public CObjectX
{
public:
	CManagerEnemy(int nPriority = DEFAULT_PRIORITY);   //�����t���R���X�g���N�^
	~CManagerEnemy()override;                          //�f�X�g���N�^
	HRESULT Init()override;                            //����������
	void Uninit()override;                             //�I������
	void Update() override;                            //�X�V����
	void Draw()override;                               //�`�揈��
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type); //��������
};


//==========================================================
//�G�̃N���X
class CEnemyX : public CManagerEnemy
{
public:
	CEnemyX(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemyX()override;                          //�f�X�g���N�^
	void Update()override;                       //�X�V����

private:
	//�}�N����`
	const float m_fMAX_SPPED = 2.0f; //�ړ����x
};


//==========================================================
//�G001�̃N���X
class CEnemy001X : public CManagerEnemy
{
public:
	CEnemy001X(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemy001X()override; 							//�f�X�g���N�^
	void Update()override;							//�X�V����
	
private:
	//�}�N����`
	constexpr static float MAX_DAMAGE = 0.005f; //�v���C���[�ɗ^����_���[�W��
};

