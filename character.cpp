//===========================================================================================================
//
//�L�����N�^�[�̊e�p�[�c�̏���[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================

//=============================
//�C���N���[�h
#include "character.h"
#include "rendererh.h"
#include "manager.h"

//=============================
//static�ϐ��̏�����

//======================
//�R���X�g���N�^
//=====================~
CCharacter::CCharacter(int nPriority) : CObjectX(nPriority)
{
	//�v���C���[�̃p�[�c������
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_pModelPrts[nCount] = nullptr;
		SaveMotionPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pSaveModelPrtInfo[nCount] = {};
	}

	//�{�X�̃p�[�c������
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_pModelPrtsBoss[nCount1] = nullptr;
		SaveMotionPosBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pSaveModelPrtInfoBoss[nCount1] = {};
	}
	SetFrame(0);
	m_nMotionFrameBoss = 0;
	MotionCount = 0;
	MotionCountBoss = 0;
	m_bMotionType = false;
	m_bMotionBossType = false;
	m_MotionState = NEUTRAL;
	m_MotionStateBoss = BOSSNEUTRAL;
}


//======================
//�f�X�g���N�^
//======================
CCharacter::~CCharacter()
{

}


//=======================
//����������
//=======================
HRESULT CCharacter::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}


//========================
//�j������
//========================
void CCharacter::Uninit()
{
	CObjectX::Uninit();
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Uninit();
			delete m_pModelPrts[nCount];
			m_pModelPrts[nCount] = nullptr;
		}
	}
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		if (m_pModelPrtsBoss[nCount1] != nullptr)
		{
			m_pModelPrtsBoss[nCount1]->Uninit();
			delete m_pModelPrtsBoss[nCount1];
			m_pModelPrtsBoss[nCount1] = nullptr;
		}
	}
}

//========================
//�j������
//========================
void CCharacter::SelectUninit(TYPE type)
{
	CObjectX::Uninit();
	if (type == TYPE::PLAYER)
	{
		for (int nCount = 0; nCount < MAX_PRTS; nCount++)
		{
			if (m_pModelPrts[nCount] != nullptr)
			{
				m_pModelPrts[nCount]->Uninit();
				delete m_pModelPrts[nCount];
				m_pModelPrts[nCount] = nullptr;
			}
		}
	}
	else if (type == TYPE::BOSS)
	{
		for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
		{
			if (m_pModelPrtsBoss[nCount1] != nullptr)
			{
				m_pModelPrtsBoss[nCount1]->Uninit();
				delete m_pModelPrtsBoss[nCount1];
				m_pModelPrtsBoss[nCount1] = nullptr;
			}
		}
	}
}

//========================
//�j������
//========================
void CCharacter::SelectUninitPrtas(TYPE type, int nNumber)
{
	CObjectX::Uninit();

	if (type == TYPE::PLAYER)
	{
		if (m_pModelPrts[nNumber] != nullptr)
		{
			m_pModelPrts[nNumber]->Uninit();
			delete m_pModelPrts[nNumber];
			m_pModelPrts[nNumber] = nullptr;
		}
	}
	else if (type == TYPE::BOSS)
	{

		if (m_pModelPrtsBoss[nNumber] != nullptr)
		{
			m_pModelPrtsBoss[nNumber]->Uninit();
			delete m_pModelPrtsBoss[nNumber];
			m_pModelPrtsBoss[nNumber] = nullptr;
		}
	}
}


//========================
//�X�V����
//========================
void CCharacter::UpdatePlayer()
{
	MotionInfo();
	//MotionSetBoss[WALK].KeySet[1].Frame = 60;

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = 0; nCount < MAX_PRTS-1; nCount++)
	{
		GetPosPrts(nCount) = D3DXVECTOR3(SaveMotionPos[nCount].x + GetPos().x, SaveMotionPos[nCount].y + GetPos().y, SaveMotionPos[nCount].z + GetPos().z);
	}
	
	//����̍X�V
	for (int nCount1 = 1; nCount1 < 4; nCount1++)
	{
		GetPosPrts(17) = D3DXVECTOR3(SaveMotionPos[nCount1 + 2].x + GetPos().x, SaveMotionPos[nCount1 + 2].y + GetPos().y, SaveMotionPos[nCount1 + 2].z + GetPos().z);
	}
}


//============================
//�{�X�̍X�V����
//============================
void CCharacter::UpdateBoss()
{
	MotionInfoBoss();

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = 0; nCount < MAX_BOSSPARTS; nCount++)
	{
		if (nCount <= 9)
		{
			GetPosPrtsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + GetPos().x, SaveMotionPosBoss[nCount].y + GetPos().y, SaveMotionPosBoss[nCount].z + GetPos().z);
		}
		if (nCount >= 10)
		{
			GetPosPrtsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + GetPos().x, SaveMotionPosBoss[nCount].y + GetPos().y + 200.0f, SaveMotionPosBoss[nCount].z + GetPos().z);
		}
	}

	for (int nCount1 = 0; nCount1 < 4; nCount1++)
	{
		GetPosPrtsBoss(17) = D3DXVECTOR3(SaveMotionPosBoss[nCount1 + 2].x + GetPos().x, SaveMotionPosBoss[nCount1 + 2].y + GetPos().y, SaveMotionPosBoss[nCount1 + 2].z + GetPos().z);
	}
}

//========================
//�v���C���[�̕`�揈��
//========================
void CCharacter::DrawPlayer(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld(); //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                      //�ʒu�ƌ������擾����ׂ̕ϐ�
	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//========================
//�{�X�̕`�揈��
//========================
void CCharacter::DrawBoss(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld(); //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                      //�ʒu�ƌ������擾����ׂ̕ϐ�
	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		if (m_pModelPrtsBoss[nCount] != nullptr)
		{
			m_pModelPrtsBoss[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}


//======================
//���[�h����
//======================
void CCharacter::Lood()
{
	int NumPrts = 0;
	int nCount = 0;
	int nKeyCount = 0;
	int nModelPrtsCount = 0;
	char aPrtsPass[100];
	char m_aDataSearch[2024];

	int nMotionCount = 0;
	int nKeySetCount = 0;
	FILE* m_pFile=nullptr;

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normal.txt", "r");

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return;
	}

	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					if (nModelPrtsCount < MAX_PRTS)
					{
						if (m_pModelPrts[nModelPrtsCount] == nullptr)
						{
							m_pModelPrts[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());
							m_pModelPrts[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrts(nModelPrtsCount));
						}
						nModelPrtsCount++;
					}
				}

				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{// �ǂݍ��݂��I��
					break;
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{// �ǂݍ��݂��I��
							//fclose(pFile);
							break;
						}

						if (m_aDataSearch[0] == '#')
						{
							continue;
						}
						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &NumPrts); //�p�[�c���擾(�S�~)
						}

						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break;
								}

								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->m_nIndexPrts);
								}

								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->m_nIndexModelPrts);

									if (m_pModelPrts[nCount]->m_nIndexModelPrts == -1)
									{
										m_pModelPrts[nCount]->SetParent(nullptr);
									}
									else
									{
										m_pModelPrts[nCount]->SetParent(m_pModelPrts[m_pModelPrts[nCount]->m_nIndexModelPrts]);
									}
								}
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->m_pos.x, &m_pModelPrts[nCount]->m_pos.y, &m_pModelPrts[nCount]->m_pos.z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrts[nCount]->m_pos;
									m_pSaveModelPrtInfo[nCount].pos += MotionSetPlayer[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->m_rot.x, &m_pModelPrts[nCount]->m_rot.y, &m_pModelPrts[nCount]->m_rot.z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrts[nCount]->m_rot;
									m_pSaveModelPrtInfo[nCount].rot += MotionSetPlayer[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++;
						}

					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0;
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						if (m_aDataSearch[0] == '#')
						{// �܂�Ԃ�
							continue;
							fgets(m_aDataSearch, 40, m_pFile);
						}
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break;
						}
						else if (!strcmp(m_aDataSearch, "LOOP")) //���[�v�̓ǂݍ���
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &LoopType);
							if (LoopType == 0)
							{
								MotionSetPlayer[nMotionCount].Loop = false;
							}
							else
							{
								MotionSetPlayer[nMotionCount].Loop = true;
							}
						} 
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) //�L�[���̓ǂݍ���
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &MotionSetPlayer[nMotionCount].NumKey);
						}
						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile);
									continue; //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									//nCount = 0;
									break;
								}

								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].Frame); //
								}

								if (!strcmp(m_aDataSearch, "KEY"))
								{
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[0] == '#')
										{
											continue; //�����𑱂���
											fgets(m_aDataSearch, 40, m_pFile);
										}

										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //�ʒu�̓���
											//m_pos = MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nCount].pos;
										}

										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //�����̓���
										}

										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break;
										}
									}
									nKeyCount++;
								}
							}
							nKeyCount = 0;
							nKeySetCount++; //�f�[�^�̉��Z
						}
					}
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++; //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile);
			break;
		}
	}

	//=================================================================================================================================================================
	//�e�p�[�c�̈ʒu�̎擾
	//=================================================================================================================================================================

	//�㔼�g�̈ʒu���擾����
	for (int nCount = 0; nCount < 4; nCount++)
	{
		for (int Next = 0; Next < nCount + 1; Next++)
		{
			SaveMotionPos[nCount + 2] += m_pModelPrts[Next + 2]->m_pos;  //�����̃p�[�c��
			SaveMotionPos[nCount + 6] += m_pModelPrts[Next + 6]->m_pos;  //�E���̃p�[�c��
		}
		SaveMotionPos[nCount + 6] += m_pModelPrts[0]->m_pos;
		SaveMotionPos[nCount + 2] += m_pModelPrts[0]->m_pos;
	}

	//�����g��parts�̈ʒu���擾
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPos[nCount1 + 11] += m_pModelPrts[nCount1 + 11]->m_pos; //�����g�̊e�p�[�c
		SaveMotionPos[nCount1 + 11] -= m_pModelPrts[10]->m_pos;     //���̕�����
	}

	//���Ƒ̂̈ʒu���擾����
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPos[nCount2] += m_pModelPrts[nCount2]->m_pos;
		GetPosPrts(nCount2) = D3DXVECTOR3(SaveMotionPos[nCount2].x + GetPos().x, SaveMotionPos[nCount2].y + GetPos().y + 20.0f, SaveMotionPos[nCount2].z + GetPos().z);
	}

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTS; nCount3++)
	{
		GetPosPrts(nCount3 + 2) = D3DXVECTOR3(SaveMotionPos[nCount3 + 2].x + GetPos().x, SaveMotionPos[nCount3 + 2].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 2].z + GetPos().z);
		GetPosPrts(nCount3 + 10) = D3DXVECTOR3(SaveMotionPos[nCount3 + 10].x + GetPos().x, SaveMotionPos[nCount3 + 10].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 10].z + GetPos().z);
	}
}

//======================
//�{�X�̃��[�h����
//======================
void CCharacter::LoodBoss()
{
	int NumPrts = 0;
	int nCount = 0;
	int nKeyCount = 0;
	int nModelPrtsCount = 0;
	//char Simbol[256];  //=��ǂݎ��悤�ϐ�
	char aPrtsPass[100];
	char m_aDataSearch[1024];

	int nMotionCount = 0;
	int nKeySetCount = 0;
	FILE* m_pFile = nullptr;

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normalBoss.txt", "r");

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return;
	}

	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					if (nModelPrtsCount < MAX_BOSSPARTS)
					{
						m_pModelPrtsBoss[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());
						m_pModelPrtsBoss[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrtsBoss(nModelPrtsCount));
						nModelPrtsCount++;
					}
				}

				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{// �ǂݍ��݂��I��
					break;
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{// �ǂݍ��݂��I��
							//fclose(pFile);
							break;
						}

						if (m_aDataSearch[0] == '#')
						{
							continue;
						}
						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &NumPrts); //�p�[�c���擾(�S�~)
						}

						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break;
								}

								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->m_nIndexPrts);
								}

								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->m_nIndexModelPrts);

									if (m_pModelPrtsBoss[nCount]->m_nIndexModelPrts == -1)
									{
										m_pModelPrtsBoss[nCount]->SetParent(nullptr);
									}
									else
									{
										m_pModelPrtsBoss[nCount]->SetParent(m_pModelPrtsBoss[m_pModelPrtsBoss[nCount]->m_nIndexModelPrts]);
									}
								}
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->m_pos.x, &m_pModelPrtsBoss[nCount]->m_pos.y, &m_pModelPrtsBoss[nCount]->m_pos.z); //�ʒu�̓���
									m_pSaveModelPrtInfoBoss[nCount].pos = m_pModelPrtsBoss[nCount]->m_pos;
									m_pSaveModelPrtInfoBoss[nCount].pos += MotionSetBoss[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->m_rot.x, &m_pModelPrtsBoss[nCount]->m_rot.y, &m_pModelPrtsBoss[nCount]->m_rot.z); //�ʒu�̓���
									m_pSaveModelPrtInfoBoss[nCount].rot = m_pModelPrtsBoss[nCount]->m_rot;
									m_pSaveModelPrtInfoBoss[nCount].rot += MotionSetBoss[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++;
						}

					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0;
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						if (m_aDataSearch[0] == '#')
						{// �܂�Ԃ�
							continue;
							fgets(m_aDataSearch, 40, m_pFile);
						}
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break;
						}
						else if (!strcmp(m_aDataSearch, "LOOP")) //���[�v�̓ǂݍ���
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &LoopType);
							if (LoopType == 0)
							{
								MotionSetBoss[nMotionCount].Loop = false;
							}
							else
							{
								MotionSetBoss[nMotionCount].Loop = true;
							}
						}
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) //�L�[���̓ǂݍ���
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &MotionSetBoss[nMotionCount].NumKey);
						}
						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile);
									continue; //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									//nCount = 0;
									break;
								}

								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].Frame); //
								}

								if (!strcmp(m_aDataSearch, "KEY"))
								{
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[0] == '#')
										{
											continue; //�����𑱂���
											fgets(m_aDataSearch, 40, m_pFile);
										}

										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //�ʒu�̓���
										}

										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //�����̓���
										}

										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break;
										}
									}
									nKeyCount++;
								}
							}
							nKeyCount = 0;
							nKeySetCount++; //�f�[�^�̉��Z
						}
					}
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++; //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile);
			break;
		}
	}

	//=================================================================================================================================================================
	//�e�p�[�c�̈ʒu�̎擾
	//=================================================================================================================================================================
	
	//�㔼�g�̈ʒu���擾����
	for (int nCount = 0; nCount < 4; nCount++)
	{
		for (int nNext = 0; nNext < nCount + 1; nNext++)
		{
			//�e�p�[�c�̈ʒu�𑫂����킹��
			SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[nNext + 2]->m_pos;  //�����̃p�[�c��
			SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[nNext + 6]->m_pos;  //�E���̃p�[�c��
		}

		//�̂̈ʒu�𑫂����킹��
		SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[0]->m_pos;
		SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[0]->m_pos;
	}

	//�����g��parts�̈ʒu���擾
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPosBoss[nCount1 + 11] += m_pModelPrtsBoss[nCount1 + 11]->m_pos; //�����g�̊e�p�[�c
		SaveMotionPosBoss[nCount1 + 11] -= m_pModelPrtsBoss[10]->m_pos;           //���̕�����
	}

	//���Ƒ̂̈ʒu���擾
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPosBoss[nCount2] += m_pModelPrtsBoss[nCount2]->m_pos;
		GetPosPrtsBoss(nCount2) = D3DXVECTOR3(SaveMotionPosBoss[nCount2].x, SaveMotionPosBoss[nCount2].y, SaveMotionPosBoss[nCount2].z);
	}

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTSBOSS; nCount3++)
	{
		GetPosPrtsBoss(nCount3 + 2) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 2].x + GetPos().x, SaveMotionPosBoss[nCount3 + 2].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 2].z + GetPos().z);
		GetPosPrtsBoss(nCount3 + 10) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 10].x + GetPos().x, SaveMotionPosBoss[nCount3 + 10].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 10].z + GetPos().z);
	}
}


//===============================
//���[�V�������s��
//===============================
void CCharacter::MotionInfo()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
	{
		if (m_pModelPrts[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos;
			D3DXVECTOR3 Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot;

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCount != MotionSetPlayer[m_MotionState].NumKey - 1)
			{
				Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount + 1].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos;
				Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount + 1].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot;
			}
			else
			{
				Movepos = MotionSetPlayer[m_MotionState].KeySet[0].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - 1].aKey[nModelCount].pos;
				Moverot = MotionSetPlayer[m_MotionState].KeySet[0].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - 1].aKey[nModelCount].rot;
			}
			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame;
			rot = Moverot / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame;

			//�����̕��������Z
			m_pModelPrts[nModelCount]->m_pos += pos;
			m_pModelPrts[nModelCount]->m_rot += rot;
		}
	}
	//�t���[���̉��Z
	GetFrame()++;

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (GetFrame() == MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame)
	{
		SetFrame(0);
		MotionCount++; //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCount == MotionSetPlayer[m_MotionState].NumKey)
		{
			MotionCount = 0; //�J�E���g��0�ɂ���
		}
		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCount + 1 == MotionSetPlayer[m_MotionState].NumKey && MotionSetPlayer[m_MotionState].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionType = false; //���[�V�����̔����off�ɂ���
			SetMotion(NEUTRAL); //���[�V�����̏��̐؂�ւ�
		}
	}
}

//===============================
//���[�V�������s��
//===============================
void CCharacter::MotionInfoBoss()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
	{
		if (m_pModelPrtsBoss[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;
			D3DXVECTOR3 Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountBoss != MotionSetBoss[m_MotionStateBoss].NumKey - 1)
			{
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;
			}
			else
			{
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[0].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].pos;
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[0].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].rot;
			}


			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;
			rot = Moverot / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;

			if (MotionSetBoss[BOSSWALK].Loop == false)
			{
				//�ړ����̍Ō�̃L�[
				if (m_MotionStateBoss == BOSSWALK && MotionCountBoss == 1)
				{
					MotionSetBoss[BOSSWALK].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			if (MotionSetBoss[BOSSDIE].Loop == false)
			{
				//���S���̍Ō�̃L�[
				if (m_MotionStateBoss == BOSSDIE && MotionCountBoss == 3)
				{
					MotionSetBoss[BOSSDIE].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			//�����̕��������Z
			m_pModelPrtsBoss[nModelCount]->m_pos += pos;
			m_pModelPrtsBoss[nModelCount]->m_rot += rot;
		}
	}
	//�t���[���̉��Z
	m_nMotionFrameBoss++;

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_nMotionFrameBoss == MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = 0; //�J�E���g��������
		MotionCountBoss++; //���[�V�����̃J�E���g�𑝉�

	//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = 0; //�J�E���g��0�ɂ���
		}
		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountBoss + 1 == MotionSetBoss[m_MotionStateBoss].NumKey && MotionSetBoss[m_MotionStateBoss].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionBossType = false; //���[�V�����̔����off�ɂ���
			//SetMotionBoss(BOS); //���[�V�����̏��̐؂�ւ�
		}

	}
}


//
//
//
void CCharacter::SetMotion(MOTIONSTATE motiontype)
{
	if (m_MotionState != motiontype && m_bMotionType == false) //���݂̃��[�V�����ƈ������
	{
		m_MotionState = motiontype; //���[�V������ݒ�
		MotionCount = 0; //���[�V�����̃J�E���g��������
		SetFrame(0);     //
		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
		{
			if (m_pModelPrts[nModelCount] != nullptr)
			{
				m_pModelPrts[nModelCount]->m_pos = m_pSaveModelPrtInfo[nModelCount].pos;
				m_pModelPrts[nModelCount]->m_rot = m_pSaveModelPrtInfo[nModelCount].rot;
				m_pModelPrts[nModelCount]->m_pos += MotionSetPlayer[motiontype].KeySet[0].aKey[nModelCount].pos;
				m_pModelPrts[nModelCount]->m_rot += MotionSetPlayer[motiontype].KeySet[0].aKey[nModelCount].rot;
			}
		}
	}
}


//
//
//
void CCharacter::SetMotionBoss(BOSSMOTIONSTATE motiontype)
{
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false) //���݂̃��[�V�����ƈ������
	{
		//if (motiontype == WALK)
		
		m_MotionStateBoss = motiontype; //���[�V������ݒ�
		MotionCountBoss = 0; //���[�V�����̃J�E���g��������
		m_nMotionFrameBoss = 0;  //�t���[���̃J�E���g�̏�����
		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
		{
			if (m_pModelPrtsBoss[nModelCount] != nullptr)
			{
				m_pModelPrtsBoss[nModelCount]->m_pos = m_pSaveModelPrtInfoBoss[nModelCount].pos;
				m_pModelPrtsBoss[nModelCount]->m_rot = m_pSaveModelPrtInfoBoss[nModelCount].rot;
				m_pModelPrtsBoss[nModelCount]->m_pos += MotionSetBoss[motiontype].KeySet[0].aKey[nModelCount].pos;
				m_pModelPrtsBoss[nModelCount]->m_rot += MotionSetBoss[motiontype].KeySet[0].aKey[nModelCount].rot;
			}
		}
	}
}
