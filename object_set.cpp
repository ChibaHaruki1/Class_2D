//======================================================================
//
//�I�u�W�F�N�g�̏���Text�t�@�C������ǂݎ�鏈��
//Auther:Haruki Chiba[object_set.cpp]
//
//======================================================================

//============================
//�C���N���[�h
#include "object_set.h"
#include "manager.h"
#include "score.h"

//============================
//static�ϐ��̏�����
int CObjectSet::m_nClearScore = 0;

//=========================
//�R���X�g���N�^
//=========================
CObjectSet::CObjectSet()
{
	m_aFieldBlockStratName = "FIELDBLOCKSET";
	m_aGoUpBlockStratName = "GOUPBLOCKSET";
	m_aRoadBlockStratName = "ROADBLOCKSET";
	m_aWallRoadBlockStratName = "WALLROADBLOCKSET";
	m_aWallRoadBlock001StratName = "WALLROADBLOCK001SET";
	m_aSmallBlockStratName = "SMALLBLOCKSET";
	m_aSmallBlock001StratName = "SMALLBLOCK001SET";
	m_aUpWallBlockStratName = "UPWALLBLOCKSET";
	m_aBreakBlockStratName = "BREAKBLOCKSET";

	m_aFieldBlockEndName = "END_FIELDBLOCKSET";
	m_aGoUpBlockEndName = "END_GOUPBLOCKSET";
	m_aRoadBlockEndName = "END_ROADBLOCKSET";
	m_aWallRoadBlockEndName = "END_WALLROADBLOCKSET";
	m_aWallRoadBlock001EndName = "END_WALLROADBLOCK001SET";
	m_aSmallBlockEndName = "END_SMALLBLOCKSET";
	m_aSmallBlock001EndName = "END_SMALLBLOCK001SET";
	m_aUpWallBlockEndName = "END_UPWALLBLOCKSET";
	m_aBreakBlockEndName = "END_BREAKBLOCKSET";

	//�ǂݎ���ő吔����
	for (int nCount = 0; nCount < MAX_DATAMOJI; nCount++)
	{
		m_aData[nCount] = {}; //�����̓ǂݎ��z��̏�����
	}

	////�X�R�A�̍ő吔����
	//for (int nCount1 = 0; nCount1 <CManagerScore::MAX_SCORE; nCount1++)
	//{
	//	m_nResultScore[nCount1] = 0;
	//}
	//m_nClearScore += m_nSaveScore;
	//m_nResultScoreNumber = 0;
}


//=========================
//�f�X�g���N�^
//=========================
CObjectSet::~CObjectSet()
{
	m_nClearScore = 0;
}


//=========================
//����������
//=========================
HRESULT CObjectSet::Init()
{
	//���݂̃��[�h��ǂݎ��
	switch (CManager::GetScene()->GetMode())
	{
		//�X�e�[�W�P�̎�
	case CScene::MODE_GAME01:
		StageOneInformation("data\\TEXT\\OBJECT\\TelephonPole.txt");
		StageOneInformation("data\\TEXT\\OBJECT\\Block.txt");
		StageOneInformation("data\\TEXT\\OBJECT\\BreakHouse.txt");
		LoodEnemy1();
		return S_OK; //�����𔲂���

		//�X�e�[�W�Q�̎�
	case CScene::MODE_GAME02:
		StageOneInformation("data\\TEXT\\OBJECT\\Block1.txt");
		//LoodEnemy();
		
		CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALCEILLING, D3DXVECTOR3(4335.0f, 790.0f, 0.0f)); //�{�X��̑���

		return S_OK; //�����𔲂���

		//���U���g���̎�
	case CScene::MODE_RESULT:
		ResultScoreWrite("data\\TEXT\\ResultScore.txt");
		ResultScoreInformation("data\\TEXT\\ResultScore.txt");

		return S_OK;
	}
	return E_FAIL;
}

void CObjectSet::LoodEnemy1()
{
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(700.0f, 40.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(1000.0f, 40.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(1500.0f, 40.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(3000.0f, 1800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(3500.0f, 1800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(5300.0f, 1800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(5500.0f, 1800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(6000.0f, 1800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(7000.0f, 3800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(5000.0f, 3800.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(8000.0f, 4400.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(12000.0f, 1800.0f, 0.0f));
}


void CObjectSet::LoodEnemy()
{
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(700.0f, 40.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(1000.0f, 40.0f, 0.0f));
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(1500.0f, 40.0f, 0.0f));
}


//================================================================================
//�X�e�[�W�P�Ԗڂ̃I�u�W�F�N�g�̏���ݒ�
//================================================================================
void CObjectSet::StageOneInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //�t�@�C����ǂݍ���
	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	//�O���t�@�C���ǂݍ��� (����)
	while (1)
	{
		fscanf(pFile, "%s", m_aData); //������ǂݎ��

		//�R�����g��ǂݍ��񂾎�
		if (m_aData[0] == '#')
		{
			continue; //���s
		}

		//���̕�������������
		if (!strcmp(m_aData, "END_SCRIPT"))
		{
			fclose(pFile); //�t�@�C�������
			pFile = nullptr;
			break; //�����𔲂���
		}

		LoodTelephonPole(pFile); //�d���̏���ǂݎ��
		LoodBlock(pFile);        //�u���b�N�̏���ǂݎ��
		LoodBreakHouse(pFile);   //��ꂽ�Ƃ̏���ǂݎ��
	}
}

//================================================================================
//���U���g�X�R�A�̏���ǂݍ���
//================================================================================
void CObjectSet::ResultScoreInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	LoodResultScore(pFile);

	fclose(pFile); //�t�@�C�������
}

//================================================================================
//���U���g�X�R�A�̏�����������
//================================================================================
void CObjectSet::ResultScoreWrite(const char* pFileName)
{
	//m_pFile = fopen("data\\TEXT\\ResultScore.txt", "w"); //�t�@�C����ǂݍ���
	FILE* pFile = fopen(pFileName, "w"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	int SaveScore = m_nClearScore;
	fprintf(pFile, "%d", SaveScore); //��������������

	fclose(pFile);
}


//=================================
//�d���̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodTelephonPole(FILE* pFile)
{
	float a, b, c = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	///���ꂪ������Ă�����
	if (!strcmp(m_aData, "TELEPHONPOLESET"))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_TELEPHONPOLESET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //�d���̔z���i�߂�
				CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //���ꂽ�S�̐����J�E���g����[�����₷

				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(a, b, c));
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(a + 20.0f, b + 180.0f, c - 50.0f));
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(a + 20.0f, b + 170.0f, c - 50.0f));
				CLaserCamare::Create(CObject3D::TYPE_UI::LASER);
			}
		}
	}
}

//=================================
//��ꂽ�Ƃ̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodBreakHouse(FILE* pFile)
{
	float a, b, c = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "BREAKHOUSESET"))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_BREAKHOUSESET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BREAKHOUSE, 0, D3DXVECTOR3(a, b, c));
			}
		}
	}
}


//========================================
//�u���b�N�̏���ǂݍ��ޏ���
//========================================
void CObjectSet::LoodBlock(FILE* pFile)
{
	float a, b, c = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, m_aFieldBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aFieldBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK000, D3DXVECTOR3(a,b,c));
			}
		}
	}

	// �オ��p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aGoUpBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aGoUpBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK001, D3DXVECTOR3(a,b,c));
			}
		}
	}
	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aRoadBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aRoadBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK002, D3DXVECTOR3(a, b, c));
			}
		}
	}
	//	�ǌ����p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aWallRoadBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aWallRoadBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK003, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aWallRoadBlock001StratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aWallRoadBlock001EndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK003_001, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aSmallBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aSmallBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK004, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aSmallBlock001StratName))
	{
	//���[�v(��������)
	while (1)
	{
		(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

		//�薼��END_TELEPHONPOLESET��������
		if (!strcmp(m_aData, m_aSmallBlock001EndName))
		{
			break; //�����𔲂���
		}

		//�薼��POS��������
		if (!strcmp(m_aData, "POS"))
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
			(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
			(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
			(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK004_001, D3DXVECTOR3(a,
				b,
				c));
		}
	}
	}
	// ��̕Ǘp�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aUpWallBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aUpWallBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK005, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// ��̕Ǘp�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aBreakBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aBreakBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &a); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &b); //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &c); //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK006, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}
}


//================================================
//result�X�R�A�̏���ǂݍ���
//================================================
void CObjectSet::LoodResultScore(FILE* pFile)
{
	(void)fscanf(pFile, "%d", &m_nClearScore); //��Ԗڂ̒l���i�[

	CManagerScore::Create(CScene::MODE::MODE_RESULT, m_nClearScore);
	//m_nResultScoreNumber++; //�z���i�߂�
}


//========================================
//text�t�@�C���̏��𐶐�
//========================================
CObjectSet* CObjectSet::Create()
{
	CObjectSet* m_pObjectSet = new CObjectSet(); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(m_pObjectSet->Init()))
	{
		return m_pObjectSet; //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//==========================================
//�u���b�N�̓ǂݍ��ޖ��O�̃p�X�̎擾����
//==========================================
const char* CObjectSet::GetStratBlockName(CObjectX::TYPE type)
{
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockStratName;
	}
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockStratName;
	}
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockStratName;
	}
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockStratName;
	}
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001StratName;
	}
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockStratName;
	}
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001StratName;
	}
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockStratName;
	}

	return nullptr;
}


//==========================================
//�u���b�N�̏I�����閼�O�̃p�X�̎擾����
//==========================================
const char* CObjectSet::GetEndBlockName(CObjectX::TYPE type)
{
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockEndName;
	}
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockEndName;
	}
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockEndName;
	}
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockEndName;
	}
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001EndName;
	}
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockEndName;
	}
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001EndName;
	}
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockEndName;
	}
	return nullptr;
}
