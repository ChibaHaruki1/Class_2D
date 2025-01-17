//================================
//
//�G�̏���[enemy.cpp]
//Auther:Chiba Haruki
//
//================================


//================================
//�C���N���[�h
#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "player.x.h"


//=========================
//�R���X�g���N�^
//=========================
CManagerEnemy::CManagerEnemy(int Priority) : CObjectX(Priority)
{

}


//=========================
//�f�X�g���N�^
//=========================
CManagerEnemy::~CManagerEnemy()
{

}


//=========================
//����������
//=========================
HRESULT CManagerEnemy::Init()
{
	//�������ɐ���������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}


//=========================
//�I������
//=========================
void CManagerEnemy::Uninit()
{
	CObjectX::Uninit(); //�j������
}


//=========================
//�X�V����
//=========================
void CManagerEnemy::Update()
{
	
}

//==========================
//�`�揈��
//==========================
void CManagerEnemy::Draw()
{
	CObjectX::Draw(); //�`�揈��
}

//==========================
//3D���f���̓G�̍쐬
//==========================
CManagerEnemy* CManagerEnemy::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemy* pManagerEnemy = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���G�̎�
	if (type == TYPE::ENEMY)
	{
		pManagerEnemy = new CEnemyX(); //���I�m��

		//������������������
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy000.x"); //�t�@�C���p�X�̐ݒ�
		}
	}

	//�^�C�v���G001�̎�
	else if (type == TYPE::ENEMY001)
	{
		pManagerEnemy = new CEnemy001X(); //���I�m��

		//������������������
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy001.x"); //�t�@�C���p�X�̐ݒ�
		}
	}

	//��񂪂��鎞
	if (pManagerEnemy != nullptr)
	{
		pManagerEnemy->SetPos(pos); //�ʒu�������Ɠ���������
		pManagerEnemy->Lood();      //X�t�@�C���̓ǂݍ���
		pManagerEnemy->Size();      //�T�C�Y�̎擾
		return pManagerEnemy;       //����Ԃ�
	}

	return nullptr;                 //����Ԃ�
}


//=====================================================================================================================================
//�G�̏���
//=====================================================================================================================================

//=========================
//�R���X�g���N�^
//=========================
CEnemyX::CEnemyX(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//�f�X�g���N�^
//=========================
CEnemyX::~CEnemyX()
{

}

//=========================
//�X�V����
//=========================
void CEnemyX::Update()
{
	TargetHeadingTowards(CManager::GetScene()->GetPlayerX(),2.0f);  //�v���C���[�Ɍ����������֐����Ă�

	//�v���C���[�Ɠ���������
	if (CollisionPlayerSelect(this) == true)
	{
		//�v���C���[��HP�����炷
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * CManagerBossEffect::MAX_DAMAGE;
	}

	//���C�t���s������
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj
		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));            //�����G�t�F�N�g�̈ʒu��ݒ�
		CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));         //�����G�t�F�N�g�̈ʒu��ݒ�
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);                                                          //�X�R�A�����Z
		CObjectX::Release(); //���g�̍폜
		return;              //�����𔲂���
	}

	CObjectX::Update();      //�X�V����
}


//=====================================================================================================================================
//�G001�̏���
//=====================================================================================================================================

//=========================
//�R���X�g���N�^
//=========================
CEnemy001X::CEnemy001X(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//�f�X�g���N�^
//=========================
CEnemy001X::~CEnemy001X()
{

}

//=========================
//�X�V����
//=========================
void CEnemy001X::Update()
{
	SetAddjustRot().y += PLUS_ROTY; //Y���̌��������Z

	//�v���C���[�Ɠ���������
	if (CollisionPlayerSelect(this) == true)
	{
		//�v���C���[��HP�����
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
	}

	//���C�t���s������
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //�����G�t�F�N�g���Ăԁi1�ځj

		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y+50.0f, GetPos().z));      //�����G�t�F�N�g�̈ʒu��ݒ�
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);                                                  //�X�R�A�����Z
		CObjectX::Release(); //���g�̍폜
		return;              //�����𔲂���
	}
}