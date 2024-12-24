//=========================================
//
//�S�I�u�W�F�N�g�̏���[object.cpp] 
//Auther:Chiba Haruki
//
//=========================================

#include "main.h"
#include "object.h"
#include "object3D.h"
#include "manager.h"

//�ÓI�����o�[�̏�����
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT] = {};

//====================
//�R���X�g���N�^
//====================
CObject::CObject()
{
	m_nPriority = 0;
	m_nID = 0;
	m_type = NONE;
}


//==========================
//�����t���R���X�g���N�^
//==========================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority; //�����Ɠ�������
	m_type = NONE; //����������
	m_nID = 0; //����������

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//��񂪂Ȃ��ꍇ
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{//�󂢂Ă���ꏊ�Ɏ��M��ǉ�

			m_apObject[m_nPriority][nCnt] = this; //�������g����
			m_nID = nCnt; //�������g��ID����
			m_nNumAll++; //�����J�E���g
			break; //������
		}
	}
}


//====================
//�f�X�g���N�^
//====================
CObject::~CObject()
{

}


//====================
//����������
//====================
HRESULT CObject::Init()
{
	return S_OK; //����
}


//====================
//�I������
//====================
void CObject::Uninit()
{

}


//====================
//�X�V����
//====================
void CObject::Update()
{

}


//====================
//�`�揈��
//====================
void CObject::Draw()
{

}


//====================
//�`�揈��
//====================
void CObject::DrawNoml()
{

}


//====================
//�S�I�u�W�F�N�g�̉��
//====================
void CObject::ReleaseAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Release(); //�폜�������Ă�
			}
		}
	}
}


//====================
//�S�I�u�W�F�N�g�̍X�V
//====================
void CObject::UpdateAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Update(); //�X�V�������Ă�
			}
		}
	}

}


//====================
//�S�I�u�W�F�N�g�̕`��
//====================
void CObject::DrawAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Draw(); //�`�揈�����Ă�
			}
		}
	}
}


//====================
//�S�I�u�W�F�N�g�̕`��
//====================
void CObject::DrawNomlAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->DrawNoml(); //�`�揈�����Ă�
			}
		}
	}
}


//=====================
//�������g�̉��
//=====================
void CObject::Release()
{
	int nID = m_nID; //���g��ID����
	int nPriority = m_nPriority; //���g��priority����

	//��񂪂���ꍇ
	if (m_apObject[nPriority][nID] != nullptr)
	{
		m_apObject[nPriority][nID]->Uninit(); //�I�������i�j���j���Ă�
		delete m_apObject[nPriority][nID]; //�폜����
		m_apObject[nPriority][nID] = nullptr; //���𖳂���
		m_nNumAll--; //�f�N�������g
	}
}


//=====================
//�I�u�W�F�N�g�̎���
//=====================
CObject*CObject::GetObject1(int nPri,int nIndex)
{
	return m_apObject[nPri][nIndex];
}


//=====================
//�^�C�v�擾
//=====================
CObject::TYPE CObject::GetType()
{
	return m_type; //�^�C�v��Ԃ�
}


//=====================
//�ݒ菈��
//=====================
void CObject::SetType(TYPE type)
{
	m_type = type; //�����Ɠ�������
}