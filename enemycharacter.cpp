//===========================================================================================================
//
//キャラクターの各パーツの処理[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================

//=============================
//インクルード
#include "enemycharacter.h"
#include "rendererh.h"
#include "manager.h"

//=============================
//static変数の初期化
int CEnemyCharacter::m_nMaxCreate = MAX_PRTS;

//======================
//コンストラクタ
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
//デストラクタ
//======================
CEnemyCharacter::~CEnemyCharacter()
{

}


//=======================
//初期化処理
//=======================
HRESULT CEnemyCharacter::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}


//========================
//破棄処理
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
//破棄処理
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
//敵の更新処理
//========================
void CEnemyCharacter::UpdateEnemy001()
{
	MotionInfoEnemy();

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
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
//敵の描画処理
//========================
void CEnemyCharacter::DrawEnemy(int NumPrts, int nNumber)
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;      //計算用マトリックス
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld(); //マトリックスを取得する
	D3DXVECTOR3 pos, rot;                      //位置と向きを取得する為の変数
	pos = GetPos(); //位置を取得する
	rot = GetRot(); //向きを取得する

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pMtx);

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//パーツ数分回す
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		if (m_pModelPrtsEnemy[nCount] != nullptr)
		{
			m_pModelPrtsEnemy[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}

//======================
//ボスのロード処理
//======================
void CEnemyCharacter::LoodEnemy(const char* aSelect)
{
	int NumPrts = 0;
	int nCount = 0;
	int nKeyCount = 0;
	int nModelPrtsCount = 0;
	//char Simbol[256];  //=を読み取るよう変数
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

	//開けなかった時
	if (m_pFile == nullptr)
	{
		return;
	}

	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

				//ｘファイル読み込み
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //パーツ数取得

					if (nModelPrtsCount < MAX_ENEMYPARTS)
					{
						m_pModelPrtsEnemy[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());
						m_pModelPrtsEnemy[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), m_ModelSizePrtsEnemy[nModelPrtsCount]);
						nModelPrtsCount++;
					}
				}

				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{// 読み込みを終了
					break;
				}

				//キャラクタパーツの情報を読み取る
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{// 読み込みを終了
							//fclose(pFile);
							break;
						}

						if (m_aDataSearch[0] == '#')
						{
							continue;
						}
						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &NumPrts); //パーツ数取得(ゴミ)
						}

						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索
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
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->m_pos.x, &m_pModelPrtsEnemy[nCount]->m_pos.y, &m_pModelPrtsEnemy[nCount]->m_pos.z); //位置の同期
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrtsEnemy[nCount]->m_pos;
									m_pSaveModelPrtInfo[nCount].pos += MotionSetEnemy[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->m_rot.x, &m_pModelPrtsEnemy[nCount]->m_rot.y, &m_pModelPrtsEnemy[nCount]->m_rot.z); //位置の同期
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrtsEnemy[nCount]->m_rot;
									m_pSaveModelPrtInfo[nCount].rot += MotionSetEnemy[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++;
						}

					}
				}

				//モーションの情報を読み込む処理
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0;
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索

						if (m_aDataSearch[0] == '#')
						{// 折り返す
							continue;
							fgets(m_aDataSearch, 40, m_pFile);
						}
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break;
						}
						else if (!strcmp(m_aDataSearch, "LOOP")) //ループの読み込み
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
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) //キー数の読み込み
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &MotionSetEnemy[nMotionCount].NumKey);
						}
						//パーツごとの位置関係を読み取る
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

								//コメントを読み込んだ時
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile);
									continue; //処理を続ける
								}

								//モーションの読み込み終了
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
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

										//コメントを読み込んだ時
										if (m_aDataSearch[0] == '#')
										{
											continue; //処理を続ける
											fgets(m_aDataSearch, 40, m_pFile);
										}

										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //位置の同期
										}

										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //向きの同期
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
							nKeySetCount++; //データの加算
						}
					}
					nKeySetCount = 0; //カウントの初期化
					nMotionCount++; //データの加算
				}
			}
			fclose(m_pFile);
			break;
		}
	}

	if (aSelect == "Enemy001")
	{
		int RightnCount = 0; //for分用の変数
		int LeftnCount = 0; //for分用の変数

		for (int nCount = 0; nCount < MAX_ENEMYPARTS; nCount++)
		{
			m_pSaveModelPrtUpdateInfo[nCount].pos = m_pSaveModelPrtInfo[nCount].pos;
		}
		m_pSaveModelPrtUpdateInfo[2].pos += m_pModelPrtsEnemy[0]->m_pos;
		m_pSaveModelPrtUpdateInfo[5].pos += m_pModelPrtsEnemy[0]->m_pos;

		//右肩から次のパーツ（２の次＝３）から終わりまで（終わりは武器まで（４番））
		for (RightnCount = 3; RightnCount < 5; RightnCount++)
		{
			//初期値は現在の
			for (int nCount1 = RightnCount -1; nCount1 < RightnCount; nCount1++)
			{
				m_pSaveModelPrtUpdateInfo[RightnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo[nCount1].pos.x, m_pSaveModelPrtUpdateInfo[nCount1].pos.y, m_pSaveModelPrtUpdateInfo[nCount1].pos.z);
			}
		}

		//左肩から次のパーツ（５の次＝６）から終わりまで（終わりは武器まで（７番））
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
//モーションを行う
//===============================
void CEnemyCharacter::MotionInfoEnemy()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < MAX_ENEMYPARTS; nModelCount++)
	{
		if (m_pModelPrtsEnemy[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;
			D3DXVECTOR3 Moverot = MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;

			//最初のキーじゃないなら差分を求める
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


			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;
			rot = Moverot / (float)MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;

			if (MotionSetEnemy[ENEMYJUMP].Loop == false)
			{
				//移動時の最後のキー
				if (m_MotionStateBoss == ENEMYJUMP && MotionCountBoss == 1)
				{
					MotionSetEnemy[ENEMYJUMP].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			if (MotionSetEnemy[ENEMYATTACK].Loop == false)
			{
				//移動時の最後のキー
				if (m_MotionStateBoss == ENEMYATTACK && MotionCountBoss == 2)
				{
					MotionSetEnemy[ENEMYATTACK].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			if (MotionSetEnemy[ENEMYDIE].Loop == false)
			{
				//死亡時の最後のキー
				if (m_MotionStateBoss == ENEMYDIE && MotionCountBoss == 3)
				{
					MotionSetEnemy[ENEMYDIE].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			//差分の分だけ加算
			m_pModelPrtsEnemy[nModelCount]->m_pos += pos;
			m_pModelPrtsEnemy[nModelCount]->m_rot += rot;
		}
	}
	//フレームの加算
	m_nMotionFrameBoss++;

	//終わりのフレームになったらカウントを最初からにする
	if (m_nMotionFrameBoss == MotionSetEnemy[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = 0; //カウントを初期化
		MotionCountBoss++; //モーションのカウントを増加

	//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountBoss == MotionSetEnemy[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = 0; //カウントを0にする
		}
		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountBoss + 1 == MotionSetEnemy[m_MotionStateBoss].NumKey && MotionSetEnemy[m_MotionStateBoss].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionBossType = false; //モーションの判定をoffにする
			//MotionCountBoss=1;
			//SetMotionBoss(NEUTRAL); //モーションの情報の切り替え
		}

	}
}


//
//
//
void CEnemyCharacter::SetMotionEnemy(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false) //現在のモーションと違ったら
	{
		//if (motiontype == WALK)

		m_MotionStateBoss = motiontype; //モーションを設定
		MotionCountBoss = 0; //モーションのカウントを初期化
		m_nMotionFrameBoss = 0;  //フレームのカウントの初期化
		//モデルのパーツ分繰り返す
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
