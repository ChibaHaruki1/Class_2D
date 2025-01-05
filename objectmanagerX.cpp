//=========================================
//
//�S�I�u�W�F�N�g�̏���[object.cpp] 
//Auther:Chiba Haruki
//
//=========================================

#include "main.h"
#include "manager.h"
#include "objectmanagerX.h"

//�ÓI�����o�[�̏�����
int CObjectManagerX::m_nNumAll = 0;
CObjectManagerX* CObjectManagerX::m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX] = {};


//==========================
//�����t���R���X�g���N�^
//==========================
CObjectManagerX::CObjectManagerX(int nPriority)
{
	m_nPriority = nPriority; //�����Ɠ�������
	m_type = NONE; //����������
	m_ItemType = NONEITEM;
	m_GimmickType = NONEGIMMICK;
	m_nID = 0; //����������

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < MAX_OBJECTMANAGERX; nCnt++)
	{
		//��񂪂Ȃ��ꍇ
		if (m_apObjectManagerX[m_nPriority][nCnt] == nullptr)
		{//�󂢂Ă���ꏊ�Ɏ��M��ǉ�

			m_apObjectManagerX[m_nPriority][nCnt] = this; //�������g����
			m_nID = nCnt; //�������g��ID����
			m_nNumAll++; //�����J�E���g
			break; //������
		}
	}
}


//====================
//�f�X�g���N�^
//====================
CObjectManagerX::~CObjectManagerX()
{

}


//====================
//����������
//====================
HRESULT CObjectManagerX::Init()
{
	return S_OK; //����
}


//====================
//�I������
//====================
void CObjectManagerX::Uninit()
{
	m_nID = 0;
}


//====================
//�X�V����
//====================
void CObjectManagerX::Update()
{

}


//====================
//�`�揈��
//====================
void CObjectManagerX::Draw()
{

}


//====================
//�S�I�u�W�F�N�g�̉��
//====================
void CObjectManagerX::ReleaseAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Release(); //�폜�������Ă�
			}
		}
	}
}


//====================
//�S�I�u�W�F�N�g�̍X�V
//====================
void CObjectManagerX::UpdateAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Update(); //�X�V�������Ă�
			}
		}
	}

}


//====================
//�S�I�u�W�F�N�g�̕`��
//====================
void CObjectManagerX::DrawAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Draw(); //�`�揈�����Ă�
			}
		}
	}
}


//=====================
//�������g�̉��
//=====================
void CObjectManagerX::Release()
{
	int nID = m_nID; //���g��ID����
	int nPriority = m_nPriority; //���g��priority����

	//��񂪂���ꍇ
	if (m_apObjectManagerX[nPriority][nID] != nullptr)
	{
		m_apObjectManagerX[nPriority][nID]->Uninit(); //�I�������i�j���j���Ă�
		delete m_apObjectManagerX[nPriority][nID]; //�폜����
		m_apObjectManagerX[nPriority][nID] = nullptr; //���𖳂���
		m_nNumAll--; //�f�N�������g
	}
}


//=====================
//�I�u�W�F�N�g�̎���
//=====================
CObjectManagerX* CObjectManagerX::GetObjectManagerX(int nPri, int nIndex)
{
	return m_apObjectManagerX[nPri][nIndex];
}


//=====================
//�^�C�v�擾
//=====================
CObjectManagerX::TYPE CObjectManagerX::GetType()
{
	return m_type; //�^�C�v��Ԃ�
}

//=====================
//�A�C�e���^�C�v�擾
//=====================
CObjectManagerX::ITEMTYPE CObjectManagerX::GetItemType()
{
	return m_ItemType; //�^�C�v��Ԃ�
}


//===============================
//�M�~�b�N�^�C�v���擾
//===============================
CObjectManagerX::GIMMICKTYPE CObjectManagerX::GetGimmickType()
{
	return m_GimmickType;
}


//=====================
//�ݒ菈��
//=====================
void CObjectManagerX::SetType(TYPE type)
{
	m_type = type; //�����Ɠ�������
}


//==================================
//�A�C�e���̃^�C�v�ݒ菈��
//==================================
void CObjectManagerX::SetItemType(ITEMTYPE Itemtype)
{
	m_ItemType = Itemtype; //�����Ɠ�������
}


//==================================
//�M�~�b�N�̃^�C�v�ݒ菈��
//==================================
void CObjectManagerX::SetGimmickType(GIMMICKTYPE GimmickType)
{
	m_GimmickType = GimmickType; //�����Ɠ�������
}