//================================
//
//�G�̏���[enemy.cpp]
//Auther:Chiba Haruki
//
//================================

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
	SetLife(3);
	GetPos() = D3DXVECTOR3(700.0f, 50.0f, 0.0f); //�ʒu��ݒ�
	GetRot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}


//=========================
//�I������
//=========================
void CManagerEnemy::Uninit()
{
	CObjectX::Uninit();
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
	CObjectX::Draw();
}

//==========================
//3D���f���̓G�̍쐬
//==========================
CManagerEnemy* CManagerEnemy::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemy* pManagerEnemy = nullptr;

	if (type == TYPE::ENEMY)
	{
		pManagerEnemy = new CEnemyX();

		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy000.x");
		}
	}
	else if (type == TYPE::ENEMY001)
	{
		pManagerEnemy = new CEnemy001X();

		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy001.x");
		}
	}

	if (pManagerEnemy != nullptr)
	{
		pManagerEnemy->GetPos() = pos;
		pManagerEnemy->Lood();
		pManagerEnemy->Size();
		return pManagerEnemy;
	}

	return nullptr;
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

	if (CollisionPlayerSelect(this) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * CManagerBossEffect::MAX_DAMAGE;
	}

	//
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj
		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));               //�����G�t�F�N�g�̈ʒu��ݒ�
		CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));            //�����G�t�F�N�g�̈ʒu��ݒ�
		CManager::GetInstance()->GetGameScore()->AddScore(1000);                                                          //�X�R�A�����Z
		CObjectX::Release();
		return;
	}
	CObjectX::Update();
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
	GetRot().y += 0.1f;

	if (CollisionPlayerSelect(this) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
	}


	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj

		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y+50.0f, GetPos().z));                 //�����G�t�F�N�g�̈ʒu��ݒ�
		CManager::GetInstance()->GetGameScore()->AddScore(100);                                                           //�X�R�A�����Z
		CObjectX::Release();
		return;
	}
}