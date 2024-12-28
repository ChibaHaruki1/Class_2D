//===========================================================================================================
//
//�L�����N�^�[�̊e�p�[�c�̏���[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================

//=============================
//�C���N���[�h
#include "enemycharacter.h"
#include "rendererh.h"
#include "manager.h"

//=============================
//static�ϐ��̏�����
int CEnemyCharacter::m_nMaxCreate = MAX_PRTS;

//======================
//�R���X�g���N�^
//=====================~
CEnemyCharacter::CEnemyCharacter(int nPriority) : CObjectX(nPriority)
{
	for (int nCount = 0; nCount < MAX_ENEMYPARTS; nCount++)
	{
		SaveMotionPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pSaveModelPrtInfo[nCount] = {};
		m_pSaveModelPrtUpdateInfo[nCount] = {};
	}

	for (int nCount1 = 0; nCount1 < MAX_ENEMYPARTS; nCount1++)
	{
		m_pModelPrtsEnemy[nCount1] = nullptr;
	}

	m_nFrame = 0;
	m_nMotionFrameBoss = 0;
	MotionCount = 0;
	MotionCountBoss = 0;
	m_bMotionType = false;
	m_bMotionBossType = false;
	m_MotionStateBoss = ENEMYJUMP;
	m_nMaxCreate = MAX_ENEMYPARTS;
}


//======================
//�f�X�g���N�^
//======================
CEnemyCharacter::~CEnemyCharacter()
{

}


//=======================
//����������
//=======================
HRESULT CEnemyCharacter::Init()
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
void CEnemyCharacter::Uninit()
{
	CObjectX::Uninit();
	
	for (int nCount1 = 0; nCount1 < MAX_ENEMYPARTS; nCount1++)
	{
		if (m_pModelPrtsEnemy[nCount1] != nullptr)
		{
			m_pModelPrtsEnemy[nCount1]->Uninit();
			delete m_pModelPrtsEnemy[nCount1];
			m_pModelPrtsEnemy[nCount1] = nullptr;
		}
	}
}

//========================
//�j������
//========================
void CEnemyCharacter::SelectUninitPrtas(TYPE type, int nNumber)
{
	CObjectX::Uninit();

	if (type == TYPE::ENEMY)
	{

		if (m_pModelPrtsEnemy[nNumber] != nullptr)
		{
			m_pModelPrtsEnemy[nNumber]->Uninit();
			delete m_pModelPrtsEnemy[nNumber];
			m_pModelPrtsEnemy[nNumber] = nullptr;
		}
	}
}


//========================
//�G�̍X�V����
//========================
void CEnemyCharacter::UpdateEnemy001()
{
	MotionInfoEnemy();

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = 0; nCount < MAX_ENEMYPARTS; nCount++)
	{
		if (nCount <= 7)
		{
			m_posPrtsEnemy[nCount] = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo[nCount].pos.x + GetPos().x,
				m_pSaveModelPrtUpdateInfo[nCount].pos.y + GetPos().y,
				m_pSaveModelPrtUpdateInfo[nCount].pos.z + GetPos().z);
		}

		if (nCount >= 8)
		{
			m_posPrtsEnemy[nCount] = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo[nCount].pos.x + GetPos().x,
				m_pSaveModelPrtUpdateInfo[nCount].pos.y + GetPos().y + 100.0f ,
				m_pSaveModelPrtUpdateInfo[nCount].pos.z + GetPos().z);
		}
	}
}


//========================
//�G�̕`�揈��
//========================
void CEnemyCharacter::DrawEnemy(int NumPrts, int nNumber)
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
		if (m_pModelPrtsEnemy[nCount] != nullptr)
		{
			m_pModelPrtsEnemy[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//======================
//�{�X�̃��[�h����
//======================
void CEnemyCharacter::LoodEnemy(const char* aSelect)
{
	int NumPrts = 0;
	int nCount = 0;
	int nKeyCount = 0;
	int nModelPrtsCount = 0;
	//char Simbol[256];  //=��ǂݎ��悤�ϐ�
	char aPrtsPass[100];
	char m_aDataSearch[2024];

	int nMotionCount = 0;
	int nKeySetCount = 0;
	FILE* m_pFile = nullptr;

	if (aSelect == "Enemy000")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy000.txt", "r");
	}
	else if (aSelect == "Enemy001")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy001.txt", "r");
	}

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

					if (nModelPrtsCount < MAX_ENEMYPARTS)
					{
						m_pModelPrtsEnemy[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());
						m_pModelPrtsEnemy[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), m_ModelSizePrtsEnemy[nModelPrtsCount]);
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
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->m_nIndexPrts);
								}

								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->m_nIndexModelPrts);

									if (m_pModelPrtsEnemy[nCount]->m_nIndexModelPrts == -1)
									{
										m_pModelPrtsEnemy[nCount]->SetParent(nullptr);
									}
									else
									{
										m_pModelPrtsEnemy[nCount]->SetParent(m_pModelPrtsEnemy[m_pModelPrtsEnemy[nCount]->m_nIndexModelPrts]);
									}
								}
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->m_pos.x, &m_pModelPrtsEnemy[nCount]->m_pos.y, &m_pModelPrtsEnemy[nCount]->m_pos.z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrtsEnemy[nCount]->m_pos;
									m_pSaveModelPrtInfo[nCount].pos += MotionSetEnemy[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->m_rot.x, &m_pModelPrtsEnemy[nCount]->m_rot.y, &m_pModelPrtsEnemy[nCount]->m_rot.z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrtsEnemy[nCount]->m_rot;
									m_pSaveModelPrtInfo[nCount].rot += MotionSetEnemy[0].KeySet[0].aKey[nCount].rot;
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
								MotionSetEnemy[nMotionCount].Loop = false;
							}
							else
							{
								MotionSetEnemy[nMotionCount].Loop = true;
							}
						}
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) //�L�[���̓ǂݍ���
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &MotionSetEnemy[nMotionCount].NumKey);
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
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].Frame); //
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
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //�ʒu�̓���
										}

										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //�����̓���
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

	if (aSelect == "Enemy001")
	{
		int RightnCount = 0; //for���p�̕ϐ�
		int LeftnCount = 0; //for���p�̕ϐ�

		for (int nCount = 0; nCount < MAX_ENEMYPARTS; nCount++)
		{
			m_pSaveModelPrtUpdateInfo[nCount].pos = m_pSaveModelPrtInfo[nCount].pos;
		}
		m_pSaveModelPrtUpdateInfo[2].pos += m_pModelPrtsEnemy[0]->m_pos;
		m_pSaveModelPrtUpdateInfo[5].pos += m_pModelPrtsEnemy[0]->m_pos;

		//�E�����玟�̃p�[�c�i�Q�̎����R�j����I���܂Łi�I���͕���܂Łi�S�ԁj�j
		for (RightnCount = 3; RightnCount < 5; RightnCount++)
		{
			//�����l�͌��݂�
			for (int nCount1 = RightnCount -1; nCount1 < RightnCount; nCount1++)
			{
				m_pSaveModelPrtUpdateInfo[RightnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo[nCount1].pos.x, m_pSaveModelPrtUpdateInfo[nCount1].pos.y, m_pSaveModelPrtUpdateInfo[nCount1].pos.z);
			}
		}

		//�������玟�̃p�[�c�i�T�̎����U�j����I���܂Łi�I���͕���܂Łi�V�ԁj�j
		for (LeftnCount = 6; LeftnCount < 8; LeftnCount++)
		{
			for (int nCount2 = LeftnCount - 1; nCount2 < LeftnCount; nCount2++)
			{
				m_pSaveModelPrtUpdateInfo[LeftnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo[nCount2].pos.x, m_pSaveModelPrtUpdateInfo[nCount2].pos.y, m_pSaveModelPrtUpdateInfo[nCount2].pos.z);
			}
		}
	}
}

//===============================
//���[�V�������s��
//===============================
void CEnemyCharacter::MotionInfoEnemy()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < MAX_ENEMYPARTS; nModelCount++)
	{
		if (m_pModelPrtsEnemy[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;
			D3DXVECTOR3 Moverot = MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountBoss != MotionSetEnemy[m_MotionStateBoss].NumKey - 1)
			{
				Movepos = MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;
				Moverot = MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;
			}
			else
			{
				Movepos = MotionSetEnemy[m_MotionStateBoss].KeySet[0].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateBoss].KeySet[MotionSetEnemy[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].pos;
				Moverot = MotionSetEnemy[m_MotionStateBoss].KeySet[0].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateBoss].KeySet[MotionSetEnemy[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].rot;
			}


			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;
			rot = Moverot / (float)MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;

			if (MotionSetEnemy[ENEMYJUMP].Loop == false)
			{
				//�ړ����̍Ō�̃L�[
				if (m_MotionStateBoss == ENEMYJUMP && MotionCountBoss == 1)
				{
					MotionSetEnemy[ENEMYJUMP].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			if (MotionSetEnemy[ENEMYATTACK].Loop == false)
			{
				//�ړ����̍Ō�̃L�[
				if (m_MotionStateBoss == ENEMYATTACK && MotionCountBoss == 2)
				{
					MotionSetEnemy[ENEMYATTACK].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			if (MotionSetEnemy[ENEMYDIE].Loop == false)
			{
				//���S���̍Ō�̃L�[
				if (m_MotionStateBoss == ENEMYDIE && MotionCountBoss == 3)
				{
					MotionSetEnemy[ENEMYDIE].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			//�����̕��������Z
			m_pModelPrtsEnemy[nModelCount]->m_pos += pos;
			m_pModelPrtsEnemy[nModelCount]->m_rot += rot;
		}
	}
	//�t���[���̉��Z
	m_nMotionFrameBoss++;

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_nMotionFrameBoss == MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = 0; //�J�E���g��������
		MotionCountBoss++; //���[�V�����̃J�E���g�𑝉�

	//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountBoss == MotionSetEnemy[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = 0; //�J�E���g��0�ɂ���
		}
		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountBoss + 1 == MotionSetEnemy[m_MotionStateBoss].NumKey && MotionSetEnemy[m_MotionStateBoss].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionBossType = false; //���[�V�����̔����off�ɂ���
			//MotionCountBoss=1;
			//SetMotionBoss(NEUTRAL); //���[�V�����̏��̐؂�ւ�
		}

	}
}


//
//
//
void CEnemyCharacter::SetMotionEnemy(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false) //���݂̃��[�V�����ƈ������
	{
		//if (motiontype == WALK)

		m_MotionStateBoss = motiontype; //���[�V������ݒ�
		MotionCountBoss = 0; //���[�V�����̃J�E���g��������
		m_nMotionFrameBoss = 0;  //�t���[���̃J�E���g�̏�����
		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = 0; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			if (m_pModelPrtsEnemy[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy[nModelCount]->m_pos = m_pSaveModelPrtInfo[nModelCount].pos;
				m_pModelPrtsEnemy[nModelCount]->m_rot = m_pSaveModelPrtInfo[nModelCount].rot;
				m_pModelPrtsEnemy[nModelCount]->m_pos += MotionSetEnemy[motiontype].KeySet[0].aKey[nModelCount].pos;
				m_pModelPrtsEnemy[nModelCount]->m_rot += MotionSetEnemy[motiontype].KeySet[0].aKey[nModelCount].rot;
			}
		}
	}
}
