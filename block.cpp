//==================================
//
//��Q���̏���[block.cpp]
//Auther:Chiba Haruki
//
//==================================

//�C���N���[�h
#include"manager.h"
#include "rendererh.h"
#include "block.h"
#include <string>

//static�����o�[�ϐ��̏�����
int CManagerBlock::m_nCreateCount = 0; //������

//������̐ݒ�
std::string u8NormalBlockText = u8"�u���b�N�̏��ݒ�"; //���{��Ή�
std::string u8NormalBlockNumberText = u8"�Ԗڂ�"; //���{��Ή�

//============================
//�X�g���e�W�[���N���X
//============================
CBlockXStrategy::CBlockXStrategy()
{
	m_aBlockFile = nullptr;
}
CBlockXStrategy::~CBlockXStrategy()
{

}
void CBlockXStrategy::Block()
{

}

//============================
//�u���b�N000
//============================
CBlock000::CBlock000()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block002.x";
}
CBlock000::~CBlock000()
{

}
void CBlock000::Block()
{

}

//============================
//�u���b�N001
//============================
CBlock001::CBlock001()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block004.x";
}
CBlock001::~CBlock001()
{

}
void CBlock001::Block()
{

}

//============================
//�u���b�N002
//============================
CBlock002::CBlock002()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block005.x";
}
CBlock002::~CBlock002()
{

}
void CBlock002::Block()
{

}

//============================
//�u���b�N003
//============================
CBlock003::CBlock003()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block003.x";
}
CBlock003::~CBlock003()
{

}
void CBlock003::Block()
{

}

//============================
//�u���b�N004
//============================
CBlock004::CBlock004()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block006.x";
}
CBlock004::~CBlock004()
{

}
void CBlock004::Block()
{

}

//============================
//�u���b�N005
//============================
CBlock005::CBlock005()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block007.x";
}
CBlock005::~CBlock005()
{

}
void CBlock005::Block()
{

}

//============================
//�u���b�N006
//============================
CBlock006::CBlock006()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\Block008.x";
}
CBlock006::~CBlock006()
{

}
void CBlock006::Block()
{

}

//============================
//���̃X�e�[�W�֍s���pobj
//============================
CSpaceBattleShip::CSpaceBattleShip()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\SpaceBattleship000.x";
}
CSpaceBattleShip::~CSpaceBattleShip()
{

}
void CSpaceBattleShip::Block()
{

}

//============================
//�ŏI�X�e�[�W�p�̃u���b�N
//============================
CFinalBlock::CFinalBlock()
{
	m_aBlockFile = "data\\XFILE\\BLOCK\\FianlStage.x";
}
CFinalBlock::~CFinalBlock()
{

}
void CFinalBlock::Block()
{

}


//============================================================================================================================================================
//�u���b�N�̊Ǘ��ҏ���
//============================================================================================================================================================

//============================
//�R���X�g���N�^
//============================
CManagerBlock::CManagerBlock(int nPriority) : CObjectX(nPriority)
{
	m_pBlockXStrategy = nullptr;
}

//============================
//�f�X�g���N�^
//============================
CManagerBlock::~CManagerBlock()
{
	if (m_pBlockXStrategy != nullptr)
	{
		delete m_pBlockXStrategy;
		m_pBlockXStrategy = nullptr;
	}
}

//============================
//����������
//============================
HRESULT CManagerBlock::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================
//�j������
//============================
void CManagerBlock::Uninit()
{
	CObjectX::Uninit();
}

//============================
//�X�V����
//============================
void CManagerBlock::Update()
{
	CObjectX::Update();
}

//============================
//�`�揈��
//============================
void CManagerBlock::Draw()
{
	CObjectX::Draw();
}

//============================================================================
//�e�N���X�̐�������
//============================================================================
CManagerBlock* CManagerBlock::Create(D3DXVECTOR3 pos, STRATEGYTYPE type)
{
	CManagerBlock* pManagerBlock = nullptr; //���g�̃|�C���^�[

	if (type == STRATEGYTYPE::BLOCK000)
	{
		pManagerBlock = new CFiledBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock000();  //�X�g���e�W�[�p���N���X
		}

	}
	else if (type==STRATEGYTYPE::BLOCK001)
	{
		pManagerBlock = new CGoUpBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock001();  //�X�g���e�W�[�p���N���X
		}
	}
	else if (type == STRATEGYTYPE::BLOCK002)
	{
		pManagerBlock = new CRoadBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock002();  //�X�g���e�W�[�p���N���X
		}
	}
	else if (type == STRATEGYTYPE::BLOCK003|| type == STRATEGYTYPE::BLOCK003_001)
	{
		pManagerBlock = new CWallRoadBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock003();  //�X�g���e�W�[�p���N���X
		}
	}
	else if (type == STRATEGYTYPE::BLOCK004||type== STRATEGYTYPE::BLOCK004_001)
	{
		pManagerBlock = new CSmallBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock004();  //�X�g���e�W�[�p���N���X
		}
	}
	else if (type == STRATEGYTYPE::BLOCK005)
	{
		pManagerBlock = new CUpWallBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock005();  //�X�g���e�W�[�p���N���X
		}
	}

	else if (type == STRATEGYTYPE::BLOCK006)
	{
		pManagerBlock = new CUpWallBlock(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock006();  //�X�g���e�W�[�p���N���X
		}
	}

	else if (type == STRATEGYTYPE::SPECEBATTLESHIP000)
	{
		pManagerBlock = new CSpaceBattleShip000(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CSpaceBattleShip();  //�X�g���e�W�[�p���N���X
		}
	}

	else if (type == STRATEGYTYPE::FINALBLOCK)
	{
		pManagerBlock = new CScaffold(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CFinalBlock();  //�X�g���e�W�[�p���N���X
		}
	}

	else if (type == STRATEGYTYPE::FINALCEILLING)
	{
		pManagerBlock = new CCeiling(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CFinalBlock1();  //�X�g���e�W�[�p���N���X
			pManagerBlock->m_pBlockXStrategy->m_aBlockFile = "data\\XFILE\\BLOCK\\FianlStageCeiling.x";
		}
	}

	else if (type == STRATEGYTYPE::WODDENBORAD)
	{
		pManagerBlock = new CWoodenBorad(); //�p���N���X�𓮓I�m�ۂ���

		//������
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CRubble();  //�X�g���e�W�[�p���N���X
			pManagerBlock->m_pBlockXStrategy->m_aBlockFile = "data\\XFILE\\StageObj\\wooden_boards.x";
		}
	}

	//��񂪂��邩�ǂ����𔻒肷��
	if (pManagerBlock != nullptr)
	{
		pManagerBlock->m_aFileName = pManagerBlock->m_pBlockXStrategy->m_aBlockFile; //�t�@�C���p�X���X�g���e�W�[���N���X�̕��Ɠ���������
		pManagerBlock->GetPos() = pos; //�ʒu�̓���
		pManagerBlock->Lood();      //���t�@�C����ǂݍ���
		pManagerBlock->Size();      //�傫���̓ǂݎ��
		return pManagerBlock;       //����Ԃ�
	}

	return nullptr; //����Ԃ�
}

//==================================
//text�t�@�C���ɏ������ޏ���
//==================================
void CManagerBlock::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ,CObjectX::TYPE type)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\TEXT\\OBJECT\\Block.txt", "a"); //�t�@�C����ǂݍ���
	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	m_nCreateCount++;
	fprintf(pFile, "%s", "#=====================================\n"); //��������������
	fprintf(pFile, "%s", "#"); //��������������
	fprintf(pFile, "%d", m_nCreateCount); //��������������
	fprintf(pFile, "%s", u8NormalBlockNumberText.data()); //��������������
	fprintf(pFile, "%s", u8NormalBlockText.data()); //��������������(�S�p����)
	fprintf(pFile, "%s", "\n"); //���s���s��
	fprintf(pFile, "%s", "#=====================================\n"); //��������������
	fprintf(pFile, "%s", CManager::GetObjectSet()->GetStratBlockName(type)); //��������������
	fprintf(pFile, "%s", "\n"); //���s���s��
	fprintf(pFile, "%s", "		POS = "); //�uPOS�v�̕�������������
	fprintf(pFile, "%.1f ", m_fPosX); //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(pFile, "%.1f ", m_fPosY); //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(pFile, "%.1f ", m_fPosZ); //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(pFile, "%s", "\n"); //���s���s��
	fprintf(pFile, "%s", CManager::GetObjectSet()->GetEndBlockName(type)); //��������������
	fprintf(pFile, "%s", "\n"); //���s���s��
	fclose(pFile); //�t�@�C�������
}

//=============================================================================================================================================================
//�p���N���X�̏���
//=============================================================================================================================================================

//============================================
//�n�ʗp�u���b�N�̏���
//============================================

//============================
//�R���X�g���N�^
//============================
CFiledBlock::CFiledBlock()
{
	//m_aFileName = "data\\XFILE\\BLOCK\\Block002.x";
}

//============================
//�f�X�g���N�^
//============================
CFiledBlock::~CFiledBlock()
{

}

//============================================
//�オ��p�̏���
//============================================
 
//============================
//�R���X�g���N�^
//============================
CGoUpBlock::CGoUpBlock()
{

}

//============================
//�f�X�g���N�^
//============================
CGoUpBlock::~CGoUpBlock()
{

}


//============================================
//���p�̏���
//============================================

//============================
//�R���X�g���N�^
//============================
CRoadBlock::CRoadBlock()
{

}
//============================
//�f�X�g���N�^
//============================
CRoadBlock::~CRoadBlock()
{

}

//============================================
//�ǌ����p�̏���
//============================================

//============================
//�R���X�g���N�^
//============================
CWallRoadBlock::CWallRoadBlock()
{

}

//============================
//�f�X�g���N�^
//============================
CWallRoadBlock::~CWallRoadBlock()
{

}

//============================================
//�������u���b�N
//============================================

//============================
//�R���X�g���N�^
//============================
CSmallBlock::CSmallBlock()
{

}

//============================
//�f�X�g���N�^
//============================
CSmallBlock::~CSmallBlock()
{

}

//============================================
//��p�̕ǃu���b�N
//============================================

//============================
//�R���X�g���N�^
//============================
CUpWallBlock::CUpWallBlock()
{
	
}
//============================
//�f�X�g���N�^
//============================
CUpWallBlock::~CUpWallBlock()
{

}

//============================================
//���̃X�e�[�W�֍s���pobj
//============================================

//============================
//�R���X�g���N�^
//============================
CSpaceBattleShip000::CSpaceBattleShip000()
{
	GetRot() = D3DXVECTOR3(-0.3f, 1.0f, 0.0f);  //�����𒲐�
}

//============================
//�f�X�g���N�^
//============================
CSpaceBattleShip000::~CSpaceBattleShip000()
{

}

//============================================
//����
//============================================

//============================
//�R���X�g���N�^
//============================
CScaffold::CScaffold()
{
	
}

//============================
//�f�X�g���N�^
//============================
CScaffold::~CScaffold()
{

}

//============================================
//�V��
//============================================

//============================
//�R���X�g���N�^
//============================
CCeiling::CCeiling()
{

}

//============================
//�f�X�g���N�^
//============================
CCeiling::~CCeiling()
{

}


