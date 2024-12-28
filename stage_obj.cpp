//==================================================================
//
//�X�e�[�W�ɔz�u����I�u�W�F�N�g�̏����̏���[statge_obj.cpp]
//Auther:Chiba Haruki
//
//==================================================================

//===========================
//�C���N���[�h
#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "stage_obj.h"
#include <string>

std::string u8TelephonPoleText = u8"�d���̏��ݒ�"; //���{��Ή�
std::string u8TelephonPoleNumberText = u8"�Ԗڂ�"; //���{��Ή�

//===========================
//static�ϐ��̏�����
int CStageObj::m_nTelephonPoleCount = 0;

//============================
//�R���X�g���N�^
//============================
CStageObj::CStageObj(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = nullptr;
	m_pFile = nullptr;
}


//============================
//�f�X�g���N�^
//============================
CStageObj::~CStageObj()
{

}


//============================
//����������
//============================
HRESULT CStageObj::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================
//�I������
//==========================
void CStageObj::Uninit()
{
	if (m_pFile != nullptr)
	{
		m_pFile = nullptr;
	}
	CObjectX::Uninit();
}

//========================
//�X�V����
//========================
void CStageObj::Update()
{
	CObjectX::Update();
}

//======================================
//�e�L�X�g�t�@�C���ɏ������ޏ���
//======================================
void CStageObj::TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ)
{
	m_pFile = fopen("data\\TEXT\\OBJECT\\TelephonPole.txt", "a"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		m_nTelephonPoleCount++;
		fprintf(m_pFile, "%s", "\n\n"); //��������������
		fprintf(m_pFile, "%s", "#=====================================\n"); //��������������
		fprintf(m_pFile, "%s", "#"); //��������������
		fprintf(m_pFile, "%d", m_nTelephonPoleCount); //��������������
		fprintf(m_pFile, "%s", u8TelephonPoleNumberText.data()); //��������������
		fprintf(m_pFile, "%s", u8TelephonPoleText.data()); //��������������(�S�p����)
		fprintf(m_pFile, "%s", "\n"); //���s���s��
		fprintf(m_pFile, "%s", "#=====================================\n"); //��������������
		fprintf(m_pFile, "%s", "TELEPHONPOLESET\n"); //��������������
		fprintf(m_pFile, "%s", "		POS = "); //�uPOS�v�̕�������������
		fprintf(m_pFile, "%.1f ", m_fPosX); //�u�ʒu�v�̕�������������(�����_��P�܂�)
		fprintf(m_pFile, "%.1f ", m_fPosY); //�u�ʒu�v�̕�������������(�����_��P�܂�)
		fprintf(m_pFile, "%.1f ", m_fPosZ); //�u�ʒu�v�̕�������������(�����_��P�܂�)
		fprintf(m_pFile, "%s", "\n"); //���s���s��
		fprintf(m_pFile, "%s", "END_TELEPHONPOLESET\n"); //��������������
		//fprintf(m_pFile, "%s", "END_SCRIPT\n"); //��������������
		fclose(m_pFile); //�t�@�C�������
	}
}

//======================
//�`�揈��
//======================
void CStageObj::Draw()
{
	CObjectX::Draw();
}

//========================
//�����𐶐�
//========================
CStageObj* CStageObj::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CStageObj* pStageObj = nullptr; //���N���X�̃|�C���^�[������

	//�^�C�v���d���̎�
	if (type == CObjectX::TELEPHONPOLE)
	{
		pStageObj = new CTelephonPole(3);
		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\telephone_pole.x";
			pStageObj->SetType(TELEPHONPOLE);
		}
	}

	//�^�C�v���Ď��J�����̏㕔���̎�
	else if (type == CObjectX::SURVEILLANCECAMERAUP)
	{
		pStageObj = new CSurveillanceCameraUP(3);
		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\surveillance_cameraUP.x";
		}
	}

	//�^�C�v���Ď��J�����̉������̎�
	else if (type == CObjectX::SURVEILLANCECAMERADOWN)
	{
		pStageObj = new CSurveillanceCameraDown(3);
		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\surveillance_cameraDown.x";
		}
	}

	//�^�C�v���Ď��J�����̉������̎�
	else if (type == CObjectX::SHOP)
	{
		pStageObj = new CShop(3);
		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\Shop.x";
		}
	}

	//�^�C�v����ꂽ�Ƃ̎�
	else if (type == CObjectX::BREAKHOUSE)
	{
		pStageObj = new CBreakHouse(3);
		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\BreakHouse000.x";
		}
	}

	if (pStageObj != nullptr)
	{
		//�������ɐ���
		if (SUCCEEDED(pStageObj->Init()))
		{
			pStageObj->GetPos() = pos; //�ʒu�𓯊�������
			pStageObj->CObjectX::Lood(); //X�t�@�C����ǂݍ��ފ֐����Ă�
			pStageObj->Size();
			pStageObj->SetType(SHOP);
			return pStageObj; //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//==========================================================================================================================
//�d���̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CTelephonPole::CTelephonPole(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CTelephonPole::~CTelephonPole()
{

}


//==========================================================================================================================
//�Ď��J�����̏㕔���̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CSurveillanceCameraUP::CSurveillanceCameraUP(int nPriority) : CStageObj(nPriority)
{
	
}

//============================
//�f�X�g���N�^
//============================
CSurveillanceCameraUP::~CSurveillanceCameraUP()
{

}

//============================
//����������
//============================
HRESULT CSurveillanceCameraUP::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CStageObj::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================
//�I������
//==========================
void CSurveillanceCameraUP::Uninit()
{
	CStageObj::Uninit();
}

//========================
//�X�V����
//========================
void CSurveillanceCameraUP::Update()
{
	CStageObj::Update();


}

//======================
//�`�揈��
//======================
void CSurveillanceCameraUP::Draw()
{
	CStageObj::Draw();
}


//==========================================================================================================================
//�Ď��J�����̉������̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CSurveillanceCameraDown::CSurveillanceCameraDown(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSurveillanceCameraDown::~CSurveillanceCameraDown()
{

}

//==========================================================================================================================
//�X�̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CShop::CShop(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CShop::~CShop()
{

}


//==========================================================================================================================
//��ꂽ�Ƃ̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CBreakHouse::CBreakHouse(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CBreakHouse::~CBreakHouse()
{

}

//============================
//�X�V����
//============================
void CBreakHouse::Update()
{
	//��񂾂�������ʂ�
	if (m_bOneFlag == false)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::FIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //���G�t�F�N�g���Ă�
		CManager::GetInstance()->GetFire()->GetLife() = 60 * 3;                                               //���C�t��ݒ�
		CManager::GetInstance()->GetFire()->GetAlpha() = 150;                                                 //���C�t��ݒ�
		CManager::GetInstance()->GetFire()->SetSize(920.0f, 700.0f, 0.0f);                                    //�傫����ݒ�
		CManager::GetInstance()->GetFire()->SetEffect(D3DXVECTOR3(GetPos().x+200.0f, GetPos().y+600.0f, GetPos().z));    //���G�t�F�N�g���Ă�
		m_bOneFlag = true; //��x�ƒʂ�Ȃ�����
	}

	//�G�t�F�N�g�̃��C�t������̐��l�܂ōs������
	if (CManager::GetInstance()->GetFire()->GetLife() <= 10)
	{
		m_bOneFlag = false; //�܂��ʂ�悤�ɐݒ肷��
	}
}