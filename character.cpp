//===========================================================================================================
//
//キャラクターの各パーツの処理[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================

//=============================
//インクルード
#include "character.h"
#include "rendererh.h"
#include "manager.h"

//=============================
//static変数の初期化

//======================
//コンストラクタ
//=====================~
CCharacter::CCharacter(int nPriority) : CObjectX(nPriority)
{
	//プレイヤーのパーツ数分回す
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_pModelPrts[nCount] = nullptr;
		SaveMotionPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pSaveModelPrtInfo[nCount] = {};
	}

	//ボスのパーツ数分回す
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
//デストラクタ
//======================
CCharacter::~CCharacter()
{

}


//=======================
//初期化処理
//=======================
HRESULT CCharacter::Init()
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
//破棄処理
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
//破棄処理
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
//更新処理
//========================
void CCharacter::UpdatePlayer()
{
	MotionInfo();
	//MotionSetBoss[WALK].KeySet[1].Frame = 60;

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount = 0; nCount < MAX_PRTS-1; nCount++)
	{
		GetPosPrts(nCount) = D3DXVECTOR3(SaveMotionPos[nCount].x + GetPos().x, SaveMotionPos[nCount].y + GetPos().y, SaveMotionPos[nCount].z + GetPos().z);
	}
	
	//武器の更新
	for (int nCount1 = 1; nCount1 < 4; nCount1++)
	{
		GetPosPrts(17) = D3DXVECTOR3(SaveMotionPos[nCount1 + 2].x + GetPos().x, SaveMotionPos[nCount1 + 2].y + GetPos().y, SaveMotionPos[nCount1 + 2].z + GetPos().z);
	}
}


//============================
//ボスの更新処理
//============================
void CCharacter::UpdateBoss()
{
	MotionInfoBoss();

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
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
//プレイヤーの描画処理
//========================
void CCharacter::DrawPlayer(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;      //計算用マトリックス
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
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}

//========================
//ボスの描画処理
//========================
void CCharacter::DrawBoss(int NumPrts)
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
		if (m_pModelPrtsBoss[nCount] != nullptr)
		{
			m_pModelPrtsBoss[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}


//======================
//ロード処理
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
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->m_pos.x, &m_pModelPrts[nCount]->m_pos.y, &m_pModelPrts[nCount]->m_pos.z); //位置の同期
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrts[nCount]->m_pos;
									m_pSaveModelPrtInfo[nCount].pos += MotionSetPlayer[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->m_rot.x, &m_pModelPrts[nCount]->m_rot.y, &m_pModelPrts[nCount]->m_rot.z); //位置の同期
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrts[nCount]->m_rot;
									m_pSaveModelPrtInfo[nCount].rot += MotionSetPlayer[0].KeySet[0].aKey[nCount].rot;
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
								MotionSetPlayer[nMotionCount].Loop = false;
							}
							else
							{
								MotionSetPlayer[nMotionCount].Loop = true;
							}
						} 
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) //キー数の読み込み
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &MotionSetPlayer[nMotionCount].NumKey);
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
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].Frame); //
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
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //位置の同期
											//m_pos = MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nCount].pos;
										}

										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //向きの同期
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

	//=================================================================================================================================================================
	//各パーツの位置の取得
	//=================================================================================================================================================================

	//上半身の位置を取得する
	for (int nCount = 0; nCount < 4; nCount++)
	{
		for (int Next = 0; Next < nCount + 1; Next++)
		{
			SaveMotionPos[nCount + 2] += m_pModelPrts[Next + 2]->m_pos;  //左側のパーツ数
			SaveMotionPos[nCount + 6] += m_pModelPrts[Next + 6]->m_pos;  //右側のパーツ数
		}
		SaveMotionPos[nCount + 6] += m_pModelPrts[0]->m_pos;
		SaveMotionPos[nCount + 2] += m_pModelPrts[0]->m_pos;
	}

	//下半身のpartsの位置を取得
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPos[nCount1 + 11] += m_pModelPrts[nCount1 + 11]->m_pos; //下半身の各パーツ
		SaveMotionPos[nCount1 + 11] -= m_pModelPrts[10]->m_pos;     //腰の分引く
	}

	//頭と体の位置を取得する
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPos[nCount2] += m_pModelPrts[nCount2]->m_pos;
		GetPosPrts(nCount2) = D3DXVECTOR3(SaveMotionPos[nCount2].x + GetPos().x, SaveMotionPos[nCount2].y + GetPos().y + 20.0f, SaveMotionPos[nCount2].z + GetPos().z);
	}

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTS; nCount3++)
	{
		GetPosPrts(nCount3 + 2) = D3DXVECTOR3(SaveMotionPos[nCount3 + 2].x + GetPos().x, SaveMotionPos[nCount3 + 2].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 2].z + GetPos().z);
		GetPosPrts(nCount3 + 10) = D3DXVECTOR3(SaveMotionPos[nCount3 + 10].x + GetPos().x, SaveMotionPos[nCount3 + 10].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 10].z + GetPos().z);
	}
}

//======================
//ボスのロード処理
//======================
void CCharacter::LoodBoss()
{
	int NumPrts = 0;
	int nCount = 0;
	int nKeyCount = 0;
	int nModelPrtsCount = 0;
	//char Simbol[256];  //=を読み取るよう変数
	char aPrtsPass[100];
	char m_aDataSearch[1024];

	int nMotionCount = 0;
	int nKeySetCount = 0;
	FILE* m_pFile = nullptr;

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normalBoss.txt", "r");

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

					if (nModelPrtsCount < MAX_BOSSPARTS)
					{
						m_pModelPrtsBoss[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());
						m_pModelPrtsBoss[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrtsBoss(nModelPrtsCount));
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
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->m_pos.x, &m_pModelPrtsBoss[nCount]->m_pos.y, &m_pModelPrtsBoss[nCount]->m_pos.z); //位置の同期
									m_pSaveModelPrtInfoBoss[nCount].pos = m_pModelPrtsBoss[nCount]->m_pos;
									m_pSaveModelPrtInfoBoss[nCount].pos += MotionSetBoss[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->m_rot.x, &m_pModelPrtsBoss[nCount]->m_rot.y, &m_pModelPrtsBoss[nCount]->m_rot.z); //位置の同期
									m_pSaveModelPrtInfoBoss[nCount].rot = m_pModelPrtsBoss[nCount]->m_rot;
									m_pSaveModelPrtInfoBoss[nCount].rot += MotionSetBoss[0].KeySet[0].aKey[nCount].rot;
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
								MotionSetBoss[nMotionCount].Loop = false;
							}
							else
							{
								MotionSetBoss[nMotionCount].Loop = true;
							}
						}
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) //キー数の読み込み
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);
							(void)fscanf(m_pFile, "%d", &MotionSetBoss[nMotionCount].NumKey);
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
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].Frame); //
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
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //位置の同期
										}

										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //向きの同期
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

	//=================================================================================================================================================================
	//各パーツの位置の取得
	//=================================================================================================================================================================
	
	//上半身の位置を取得する
	for (int nCount = 0; nCount < 4; nCount++)
	{
		for (int nNext = 0; nNext < nCount + 1; nNext++)
		{
			//各パーツの位置を足し合わせる
			SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[nNext + 2]->m_pos;  //左側のパーツ数
			SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[nNext + 6]->m_pos;  //右側のパーツ数
		}

		//体の位置を足し合わせる
		SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[0]->m_pos;
		SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[0]->m_pos;
	}

	//下半身のpartsの位置を取得
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPosBoss[nCount1 + 11] += m_pModelPrtsBoss[nCount1 + 11]->m_pos; //下半身の各パーツ
		SaveMotionPosBoss[nCount1 + 11] -= m_pModelPrtsBoss[10]->m_pos;           //腰の分引く
	}

	//頭と体の位置を取得
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPosBoss[nCount2] += m_pModelPrtsBoss[nCount2]->m_pos;
		GetPosPrtsBoss(nCount2) = D3DXVECTOR3(SaveMotionPosBoss[nCount2].x, SaveMotionPosBoss[nCount2].y, SaveMotionPosBoss[nCount2].z);
	}

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTSBOSS; nCount3++)
	{
		GetPosPrtsBoss(nCount3 + 2) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 2].x + GetPos().x, SaveMotionPosBoss[nCount3 + 2].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 2].z + GetPos().z);
		GetPosPrtsBoss(nCount3 + 10) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 10].x + GetPos().x, SaveMotionPosBoss[nCount3 + 10].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 10].z + GetPos().z);
	}
}


//===============================
//モーションを行う
//===============================
void CCharacter::MotionInfo()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
	{
		if (m_pModelPrts[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos;
			D3DXVECTOR3 Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot;

			//最初のキーじゃないなら差分を求める
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
			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame;
			rot = Moverot / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame;

			//差分の分だけ加算
			m_pModelPrts[nModelCount]->m_pos += pos;
			m_pModelPrts[nModelCount]->m_rot += rot;
		}
	}
	//フレームの加算
	GetFrame()++;

	//終わりのフレームになったらカウントを最初からにする
	if (GetFrame() == MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame)
	{
		SetFrame(0);
		MotionCount++; //モーションのカウントを増加

		//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCount == MotionSetPlayer[m_MotionState].NumKey)
		{
			MotionCount = 0; //カウントを0にする
		}
		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCount + 1 == MotionSetPlayer[m_MotionState].NumKey && MotionSetPlayer[m_MotionState].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionType = false; //モーションの判定をoffにする
			SetMotion(NEUTRAL); //モーションの情報の切り替え
		}
	}
}

//===============================
//モーションを行う
//===============================
void CCharacter::MotionInfoBoss()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
	{
		if (m_pModelPrtsBoss[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos;
			D3DXVECTOR3 Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot;

			//最初のキーじゃないなら差分を求める
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


			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;
			rot = Moverot / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame;

			if (MotionSetBoss[BOSSWALK].Loop == false)
			{
				//移動時の最後のキー
				if (m_MotionStateBoss == BOSSWALK && MotionCountBoss == 1)
				{
					MotionSetBoss[BOSSWALK].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			if (MotionSetBoss[BOSSDIE].Loop == false)
			{
				//死亡時の最後のキー
				if (m_MotionStateBoss == BOSSDIE && MotionCountBoss == 3)
				{
					MotionSetBoss[BOSSDIE].KeySet[MotionCountBoss].Frame = 0;
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			//差分の分だけ加算
			m_pModelPrtsBoss[nModelCount]->m_pos += pos;
			m_pModelPrtsBoss[nModelCount]->m_rot += rot;
		}
	}
	//フレームの加算
	m_nMotionFrameBoss++;

	//終わりのフレームになったらカウントを最初からにする
	if (m_nMotionFrameBoss == MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = 0; //カウントを初期化
		MotionCountBoss++; //モーションのカウントを増加

	//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = 0; //カウントを0にする
		}
		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountBoss + 1 == MotionSetBoss[m_MotionStateBoss].NumKey && MotionSetBoss[m_MotionStateBoss].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionBossType = false; //モーションの判定をoffにする
			//SetMotionBoss(BOS); //モーションの情報の切り替え
		}

	}
}


//
//
//
void CCharacter::SetMotion(MOTIONSTATE motiontype)
{
	if (m_MotionState != motiontype && m_bMotionType == false) //現在のモーションと違ったら
	{
		m_MotionState = motiontype; //モーションを設定
		MotionCount = 0; //モーションのカウントを初期化
		SetFrame(0);     //
		//モデルのパーツ分繰り返す
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
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false) //現在のモーションと違ったら
	{
		//if (motiontype == WALK)
		
		m_MotionStateBoss = motiontype; //モーションを設定
		MotionCountBoss = 0; //モーションのカウントを初期化
		m_nMotionFrameBoss = 0;  //フレームのカウントの初期化
		//モデルのパーツ分繰り返す
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
