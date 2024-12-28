//==================================
//
//障害物の処理[block.cpp]
//Auther:Chiba Haruki
//
//==================================

//インクルード
#include"manager.h"
#include "rendererh.h"
#include "block.h"
#include <string>

//staticメンバー変数の初期化
int CManagerBlock::m_nCreateCount = 0; //初期化

//文字列の設定
std::string u8NormalBlockText = u8"ブロックの情報設定"; //日本語対応
std::string u8NormalBlockNumberText = u8"番目の"; //日本語対応

//============================
//ストラテジー基底クラス
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
//ブロック000
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
//ブロック001
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
//ブロック002
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
//ブロック003
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
//ブロック004
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
//ブロック005
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
//ブロック006
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
//次のステージへ行く用obj
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
//最終ステージ用のブロック
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
//ブロックの管理者処理
//============================================================================================================================================================

//============================
//コンストラクタ
//============================
CManagerBlock::CManagerBlock(int nPriority) : CObjectX(nPriority)
{
	m_pBlockXStrategy = nullptr;
}

//============================
//デストラクタ
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
//初期化処理
//============================
HRESULT CManagerBlock::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================
//破棄処理
//============================
void CManagerBlock::Uninit()
{
	CObjectX::Uninit();
}

//============================
//更新処理
//============================
void CManagerBlock::Update()
{
	CObjectX::Update();
}

//============================
//描画処理
//============================
void CManagerBlock::Draw()
{
	CObjectX::Draw();
}

//============================================================================
//各クラスの生成処理
//============================================================================
CManagerBlock* CManagerBlock::Create(D3DXVECTOR3 pos, STRATEGYTYPE type)
{
	CManagerBlock* pManagerBlock = nullptr; //自身のポインター

	if (type == STRATEGYTYPE::BLOCK000)
	{
		pManagerBlock = new CFiledBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock000();  //ストラテジー継承クラス
		}

	}
	else if (type==STRATEGYTYPE::BLOCK001)
	{
		pManagerBlock = new CGoUpBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock001();  //ストラテジー継承クラス
		}
	}
	else if (type == STRATEGYTYPE::BLOCK002)
	{
		pManagerBlock = new CRoadBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock002();  //ストラテジー継承クラス
		}
	}
	else if (type == STRATEGYTYPE::BLOCK003|| type == STRATEGYTYPE::BLOCK003_001)
	{
		pManagerBlock = new CWallRoadBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock003();  //ストラテジー継承クラス
		}
	}
	else if (type == STRATEGYTYPE::BLOCK004||type== STRATEGYTYPE::BLOCK004_001)
	{
		pManagerBlock = new CSmallBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock004();  //ストラテジー継承クラス
		}
	}
	else if (type == STRATEGYTYPE::BLOCK005)
	{
		pManagerBlock = new CUpWallBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock005();  //ストラテジー継承クラス
		}
	}

	else if (type == STRATEGYTYPE::BLOCK006)
	{
		pManagerBlock = new CUpWallBlock(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CBlock006();  //ストラテジー継承クラス
		}
	}

	else if (type == STRATEGYTYPE::SPECEBATTLESHIP000)
	{
		pManagerBlock = new CSpaceBattleShip000(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CSpaceBattleShip();  //ストラテジー継承クラス
		}
	}

	else if (type == STRATEGYTYPE::FINALBLOCK)
	{
		pManagerBlock = new CScaffold(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CFinalBlock();  //ストラテジー継承クラス
		}
	}

	else if (type == STRATEGYTYPE::FINALCEILLING)
	{
		pManagerBlock = new CCeiling(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CFinalBlock1();  //ストラテジー継承クラス
			pManagerBlock->m_pBlockXStrategy->m_aBlockFile = "data\\XFILE\\BLOCK\\FianlStageCeiling.x";
		}
	}

	else if (type == STRATEGYTYPE::WODDENBORAD)
	{
		pManagerBlock = new CWoodenBorad(); //継承クラスを動的確保する

		//初期化
		if (SUCCEEDED(pManagerBlock->Init()))
		{
			pManagerBlock->m_pBlockXStrategy = new CRubble();  //ストラテジー継承クラス
			pManagerBlock->m_pBlockXStrategy->m_aBlockFile = "data\\XFILE\\StageObj\\wooden_boards.x";
		}
	}

	//情報があるかどうかを判定する
	if (pManagerBlock != nullptr)
	{
		pManagerBlock->m_aFileName = pManagerBlock->m_pBlockXStrategy->m_aBlockFile; //ファイルパスをストラテジー基底クラスの物と同期させる
		pManagerBlock->GetPos() = pos; //位置の同期
		pManagerBlock->Lood();      //ｘファイルを読み込む
		pManagerBlock->Size();      //大きさの読み取り
		return pManagerBlock;       //情報を返す
	}

	return nullptr; //無を返す
}

//==================================
//textファイルに書き込む処理
//==================================
void CManagerBlock::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ,CObjectX::TYPE type)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\TEXT\\OBJECT\\Block.txt", "a"); //ファイルを読み込む
	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	m_nCreateCount++;
	fprintf(pFile, "%s", "#=====================================\n"); //数字を書き込む
	fprintf(pFile, "%s", "#"); //数字を書き込む
	fprintf(pFile, "%d", m_nCreateCount); //数字を書き込む
	fprintf(pFile, "%s", u8NormalBlockNumberText.data()); //数字を書き込む
	fprintf(pFile, "%s", u8NormalBlockText.data()); //文字を書き込む(全角文字)
	fprintf(pFile, "%s", "\n"); //改行を行う
	fprintf(pFile, "%s", "#=====================================\n"); //数字を書き込む
	fprintf(pFile, "%s", CManager::GetObjectSet()->GetStratBlockName(type)); //数字を書き込む
	fprintf(pFile, "%s", "\n"); //改行を行う
	fprintf(pFile, "%s", "		POS = "); //「POS」の文字を書き込む
	fprintf(pFile, "%.1f ", m_fPosX); //「位置」の文字を書き込む(少数点第１まで)
	fprintf(pFile, "%.1f ", m_fPosY); //「位置」の文字を書き込む(少数点第１まで)
	fprintf(pFile, "%.1f ", m_fPosZ); //「位置」の文字を書き込む(少数点第１まで)
	fprintf(pFile, "%s", "\n"); //改行を行う
	fprintf(pFile, "%s", CManager::GetObjectSet()->GetEndBlockName(type)); //文字を書き込む
	fprintf(pFile, "%s", "\n"); //改行を行う
	fclose(pFile); //ファイルを閉じる
}

//=============================================================================================================================================================
//継承クラスの処理
//=============================================================================================================================================================

//============================================
//地面用ブロックの処理
//============================================

//============================
//コンストラクタ
//============================
CFiledBlock::CFiledBlock()
{
	//m_aFileName = "data\\XFILE\\BLOCK\\Block002.x";
}

//============================
//デストラクタ
//============================
CFiledBlock::~CFiledBlock()
{

}

//============================================
//上がる用の処理
//============================================
 
//============================
//コンストラクタ
//============================
CGoUpBlock::CGoUpBlock()
{

}

//============================
//デストラクタ
//============================
CGoUpBlock::~CGoUpBlock()
{

}


//============================================
//道用の処理
//============================================

//============================
//コンストラクタ
//============================
CRoadBlock::CRoadBlock()
{

}
//============================
//デストラクタ
//============================
CRoadBlock::~CRoadBlock()
{

}

//============================================
//壁兼道用の処理
//============================================

//============================
//コンストラクタ
//============================
CWallRoadBlock::CWallRoadBlock()
{

}

//============================
//デストラクタ
//============================
CWallRoadBlock::~CWallRoadBlock()
{

}

//============================================
//小さいブロック
//============================================

//============================
//コンストラクタ
//============================
CSmallBlock::CSmallBlock()
{

}

//============================
//デストラクタ
//============================
CSmallBlock::~CSmallBlock()
{

}

//============================================
//上用の壁ブロック
//============================================

//============================
//コンストラクタ
//============================
CUpWallBlock::CUpWallBlock()
{
	
}
//============================
//デストラクタ
//============================
CUpWallBlock::~CUpWallBlock()
{

}

//============================================
//次のステージへ行く用obj
//============================================

//============================
//コンストラクタ
//============================
CSpaceBattleShip000::CSpaceBattleShip000()
{
	GetRot() = D3DXVECTOR3(-0.3f, 1.0f, 0.0f);  //向きを調整
}

//============================
//デストラクタ
//============================
CSpaceBattleShip000::~CSpaceBattleShip000()
{

}

//============================================
//足場
//============================================

//============================
//コンストラクタ
//============================
CScaffold::CScaffold()
{
	
}

//============================
//デストラクタ
//============================
CScaffold::~CScaffold()
{

}

//============================================
//天井
//============================================

//============================
//コンストラクタ
//============================
CCeiling::CCeiling()
{

}

//============================
//デストラクタ
//============================
CCeiling::~CCeiling()
{

}


