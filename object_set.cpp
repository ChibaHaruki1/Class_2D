//======================================================================
//
//オブジェクトの情報をTextファイルから読み取る処理
//Auther:Haruki Chiba[object_set.cpp]
//
//======================================================================

//============================
//インクルード
#include "object_set.h"
#include "manager.h"
#include "score.h"

//============================
//static変数の初期化
int CObjectSet::m_nClearScore = 0;

//=========================
//コンストラクタ
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

	//読み取れる最大数分回す
	for (int nCount = 0; nCount < MAX_DATAMOJI; nCount++)
	{
		m_aData[nCount] = {}; //文字の読み取り配列の初期化
	}

	////スコアの最大数分回す
	//for (int nCount1 = 0; nCount1 <CManagerScore::MAX_SCORE; nCount1++)
	//{
	//	m_nResultScore[nCount1] = 0;
	//}
	//m_nClearScore += m_nSaveScore;
	//m_nResultScoreNumber = 0;
}


//=========================
//デストラクタ
//=========================
CObjectSet::~CObjectSet()
{
	m_nClearScore = 0;
}


//=========================
//初期化処理
//=========================
HRESULT CObjectSet::Init()
{
	//現在のモードを読み取る
	switch (CManager::GetScene()->GetMode())
	{
		//ステージ１の時
	case CScene::MODE_GAME01:
		StageOneInformation("data\\TEXT\\OBJECT\\TelephonPole.txt");
		StageOneInformation("data\\TEXT\\OBJECT\\Block.txt");
		StageOneInformation("data\\TEXT\\OBJECT\\BreakHouse.txt");
		LoodEnemy1();
		return S_OK; //処理を抜ける

		//ステージ２の時
	case CScene::MODE_GAME02:
		StageOneInformation("data\\TEXT\\OBJECT\\Block1.txt");
		//LoodEnemy();
		
		CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALCEILLING, D3DXVECTOR3(4335.0f, 790.0f, 0.0f)); //ボス戦の足場

		return S_OK; //処理を抜ける

		//リザルト時の時
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
//ステージ１番目のオブジェクトの情報を設定
//================================================================================
void CObjectSet::StageOneInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //ファイルを読み込む
	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	//外部ファイル読み込み (無限)
	while (1)
	{
		fscanf(pFile, "%s", m_aData); //文字を読み取る

		//コメントを読み込んだ時
		if (m_aData[0] == '#')
		{
			continue; //続行
		}

		//この文字を見つけた時
		if (!strcmp(m_aData, "END_SCRIPT"))
		{
			fclose(pFile); //ファイルを閉じる
			pFile = nullptr;
			break; //処理を抜ける
		}

		LoodTelephonPole(pFile); //電柱の情報を読み取る
		LoodBlock(pFile);        //ブロックの情報を読み取る
		LoodBreakHouse(pFile);   //壊れた家の情報を読み取る
	}
}

//================================================================================
//リザルトスコアの情報を読み込む
//================================================================================
void CObjectSet::ResultScoreInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	LoodResultScore(pFile);

	fclose(pFile); //ファイルを閉じる
}

//================================================================================
//リザルトスコアの情報を書き込む
//================================================================================
void CObjectSet::ResultScoreWrite(const char* pFileName)
{
	//m_pFile = fopen("data\\TEXT\\ResultScore.txt", "w"); //ファイルを読み込む
	FILE* pFile = fopen(pFileName, "w"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	int SaveScore = m_nClearScore;
	fprintf(pFile, "%d", SaveScore); //文字を書き込む

	fclose(pFile);
}


//=================================
//電柱の情報を読み込む処理
//=================================
void CObjectSet::LoodTelephonPole(FILE* pFile)
{
	float a, b, c = 0.0f; //posの位置を保管するための変数

	///これが書かれていた時
	if (!strcmp(m_aData, "TELEPHONPOLESET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_TELEPHONPOLESET"))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //電柱の配列を進める
				CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //作られた全体数もカウントするー＞増やす

				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(a, b, c));
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(a + 20.0f, b + 180.0f, c - 50.0f));
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(a + 20.0f, b + 170.0f, c - 50.0f));
				CLaserCamare::Create(CObject3D::TYPE_UI::LASER);
			}
		}
	}
}

//=================================
//壊れた家の情報を読み込む処理
//=================================
void CObjectSet::LoodBreakHouse(FILE* pFile)
{
	float a, b, c = 0.0f; //posの位置を保管するための変数

	//これが書かれていた時
	if (!strcmp(m_aData, "BREAKHOUSESET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_BREAKHOUSESET"))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BREAKHOUSE, 0, D3DXVECTOR3(a, b, c));
			}
		}
	}
}


//========================================
//ブロックの情報を読み込む処理
//========================================
void CObjectSet::LoodBlock(FILE* pFile)
{
	float a, b, c = 0.0f; //posの位置を保管するための変数

	//これが書かれていた時
	if (!strcmp(m_aData, m_aFieldBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aFieldBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK000, D3DXVECTOR3(a,b,c));
			}
		}
	}

	// 上がる用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aGoUpBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aGoUpBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK001, D3DXVECTOR3(a,b,c));
			}
		}
	}
	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aRoadBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aRoadBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK002, D3DXVECTOR3(a, b, c));
			}
		}
	}
	//	壁兼道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aWallRoadBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aWallRoadBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK003, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aWallRoadBlock001StratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aWallRoadBlock001EndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK003_001, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aSmallBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aSmallBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK004, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aSmallBlock001StratName))
	{
	//ループ(無限月読)
	while (1)
	{
		(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

		//題名がEND_TELEPHONPOLESETだった時
		if (!strcmp(m_aData, m_aSmallBlock001EndName))
		{
			break; //処理を抜ける
		}

		//題名がPOSだった時
		if (!strcmp(m_aData, "POS"))
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
			(void)fscanf(pFile, "%f", &a); //一番目の値を格納
			(void)fscanf(pFile, "%f", &b); //二番目の値を格納
			(void)fscanf(pFile, "%f", &c); //三番目の値を格納

			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK004_001, D3DXVECTOR3(a,
				b,
				c));
		}
	}
	}
	// 上の壁用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aUpWallBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aUpWallBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK005, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}

	// 上の壁用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aBreakBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aBreakBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &a); //一番目の値を格納
				(void)fscanf(pFile, "%f", &b); //二番目の値を格納
				(void)fscanf(pFile, "%f", &c); //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK006, D3DXVECTOR3(a,
					b,
					c));
			}
		}
	}
}


//================================================
//resultスコアの情報を読み込む
//================================================
void CObjectSet::LoodResultScore(FILE* pFile)
{
	(void)fscanf(pFile, "%d", &m_nClearScore); //一番目の値を格納

	CManagerScore::Create(CScene::MODE::MODE_RESULT, m_nClearScore);
	//m_nResultScoreNumber++; //配列を進める
}


//========================================
//textファイルの情報を生成
//========================================
CObjectSet* CObjectSet::Create()
{
	CObjectSet* m_pObjectSet = new CObjectSet(); //動的確保

	//初期化に成功
	if (SUCCEEDED(m_pObjectSet->Init()))
	{
		return m_pObjectSet; //情報を返す
	}

	return nullptr; //無を返す
}


//==========================================
//ブロックの読み込む名前のパスの取得処理
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
//ブロックの終了する名前のパスの取得処理
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
