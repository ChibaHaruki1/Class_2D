//===================================
//
//�n�ʂ̐ݒ�����鏈��[field.cpp]
//Author:chiba haruki
//
//===================================

#include "main.h"
#include "field.h"
#include "rendererh.h"
#include "manager.h"
#include <iostream>
#include <DxLib.h>
using namespace std; //c++�̊�b�̏ȗ�
std::string u8FieldText = u8"�n�ʂ̏��ݒ�"; //���{��Ή�

int CField::m_nCountField = 0;

//============================
//�R���X�g���N�^
//============================
CField::CField(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 200.0f;
	m_aFileName = "data\\TEXTURE\\bg101.jpg";
	m_pFile = nullptr;
	PosX = 0.0f;
}


//============================
//�f�X�g���N�^
//============================
CField::~CField()
{

}


//============================
//�|���S���̏���������
//============================
HRESULT CField::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================
//�|���S���̏I������
//==========================
void CField::Uninit()
{
	CObject3D::Uninit();
}

//========================
//�|���S���̍X�V����
//========================
void CField::Update()
{
	SetSize(m_fSizeX, 0.0f, m_fSizeX);

	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_1) == true)
	//{
	//	m_fSizeX += 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_2) == true)
	//{
	//	m_fSizeX -= 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_O) == true)
	//{
	//	//TextFileWrite();
	//}
}


//======================================
//�e�L�X�g�t�@�C���ɏ������ޏ���
//======================================
void CField::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ)
{
	m_pFile = fopen("data\\TEXT\\ResultScore.txt", "a"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}
	m_nCountField++;
	fprintf(m_pFile, "%s", "\n\n"); //��������������
	fprintf(m_pFile, "%s", "#=====================================\n"); //��������������
	fprintf(m_pFile, "%s", "#"); //��������������
	fprintf(m_pFile, "%d", m_nCountField); //��������������
	fprintf(m_pFile, "%s", u8FieldText.data()); //��������������(�S�p����)
	fprintf(m_pFile, "%s", "\n"); //���s���s��
	fprintf(m_pFile, "%s", "#=====================================\n"); //��������������
	fprintf(m_pFile, "%s", "FILED\n"); //��������������
	fprintf(m_pFile, "%s", "		POS = "); //�uPOS�v�̕�������������
	fprintf(m_pFile, "%.1f ", m_fPosX); //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(m_pFile, "%.1f ", m_fPosY); //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(m_pFile, "%.1f ", m_fPosZ); //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(m_pFile, "%s", "\n"); //���s���s��
	fprintf(m_pFile, "%s", "END_FILED\n"); //��������������
	fclose(m_pFile); //�t�@�C�������
}


//======================
//�|���S���̕`�揈��
//======================
void CField::Draw()
{
	CObject3D::Draw(); //���N���X�̕`�揈�����Ă�
}


//======================
//�|���S���̕`�揈��
//======================
void CField::DrawNoml()
{
	
}


//========================
//���𐶐�
//========================
CField* CField::Create(D3DXVECTOR3 pos)
{
	CField* pCField = new CField(2); //���I�m��

	if (SUCCEEDED(pCField->Init()))
	{
		if (pCField != nullptr)
		{
			pCField->m_pos = pos;
			pCField->Lood();
			return pCField;
		}
	}

	return nullptr;
}