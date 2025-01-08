//====================================
//
//画面遷移処理[scene.cpp]
//Auther:Haruki Chiba
//
//====================================

#include "scene.h"
#include "manager.h"
#include "rendererh.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "efect.h"
#include "collision.h"
#include "score.h"
#include "objectX.h"
#include "stage_obj.h"
#include "block.h"
#include "gage.h"
#include "enemyinmotion.h"


//static変数の初期化
//CCamera* CScene::m_pCamera = nullptr;
//CLight* CScene::m_pLight = nullptr;
//CPlayerX* CScene::m_pPlayerX = nullptr;
//CTarget* CScene::m_pTragetUi = nullptr;
//CMPTargetReTime* CScene::pMPTargetReTime = nullptr;


//=======================
//コンストラクタ
//=======================
CScene::CScene()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_Mode = MODE_RESULT;
	m_pObjectSet = nullptr;
	m_pPlayerX = nullptr;
	m_bOneSound = false;
	//pMPTargetReTime = nullptr;
	//m_pOverhead_Processing = nullptr;
	//m_pPlayerX = nullptr;
	//m_pTragetUi = nullptr;

	//CObjectX::GetTragetNumberCount() = -1;
}


//=======================
//デストラクタ
//=======================
CScene::~CScene()
{

}


//=======================
//初期化処理
//=======================
HRESULT CScene::Init()
{
	m_pCamera = new CCamera(); //カメラの動的確保
	m_pLight = new CLight(); //光源の動的確保

	m_pCamera->Init(); //カメラの初期化
	m_pLight->Init(); //光源の初期化

	CManager::GetRenderer()->GetDrawShader() = false;
	return S_OK;
}


//=======================
//終了処理
//=======================
void CScene::Uninit()
{
	CObject::ReleaseAll(); //全てのUninit()を呼び、deleteする
	CObjectManagerX::ReleaseAll(); //全てのunitを呼び、deleteする

	if (m_pObjectSet != nullptr)
	{
		delete m_pObjectSet;
		m_pObjectSet = nullptr;
	}

	if (m_pPlayerX != nullptr)
	{
		m_pPlayerX = nullptr;
	}

	//カメラの情報がある時
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit(); //カメラの終了処理
		delete m_pCamera; //メモリの解放
		m_pCamera = nullptr; //情報を無くす
	}

	//光源の情報がある時
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit(); //光源の終了処理
		delete m_pLight; //メモリの解放
		m_pLight = nullptr; //情報を無くす
	}
}


//=======================
//更新処理
//=======================
void CScene::Update()
{
	
}

//=======================
//他の物のUpdateを呼ぶ
//=======================
void CScene::AnyUpdate()
{
	if (m_Mode == MODE_GAME02)
	{
		CManager::GetEvent()->Update();
	}
}


//=======================
//描画処理
//=======================
void CScene::Draw()
{

}


//=======================
//生成
//=======================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr; //基底クラスの動的確保

	//ゲームモードが１の時
	if (mode == MODE_GAME01)
	{
		pScene = new CGame01();
		pScene->m_Mode = MODE_GAME01;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//ゲームモードが２の時
	else if (mode == MODE_GAME02)
	{
		pScene = new CGame02();
		pScene->m_Mode = MODE_GAME02;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//タイトルの時
	else if (mode == MODE_TITLE)
	{
		pScene = new CTitle();
		pScene->m_Mode = MODE_TITLE;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//リザルトの時
	else if (mode == MODE_RESULT)
	{
		pScene = new CResult();
		pScene->m_Mode = MODE_RESULT;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//ゲームモードの時
	else if (mode == MODE_GAMEOVER)
	{
		pScene = new CGameOver();
		pScene->m_Mode = MODE_GAMEOVER;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	return nullptr; //
}

//CMP* CScene::GetMP()
//{
//	return m_pMP;
//}



//=======================
//カメラの情報を返す
//=======================
CCamera* CScene::GetCamera()
{
	return m_pCamera;
}


//=======================
//光源の情報を返す
//=======================
CLight* CScene::GetLight()
{
	return m_pLight;
}


//============================
//プレイヤーの情報を返す
//============================
CPlayerX* CScene::GetPlayerX()
{
	return m_pPlayerX;
}


//
//
//
CObjectSet* CScene::GetObjectSet()
{
	return m_pObjectSet;
}


//================================================================================================================================
//                                                    ゲームモードの処理
//================================================================================================================================


//================================================================================================================================
//                                                    ステージ１
//================================================================================================================================


//=======================
//コンストラクタ
//=======================
CGame01::CGame01()
{
	m_Mode = MODE_GAME01;
}


//=======================
//デストラクタ
//=======================
CGame01::~CGame01()
{

}


//=======================
//初期化処理
//=======================
HRESULT CGame01::Init()
{

	CScene::Init();

	m_pCamera->GetAdjustmentPosZ() = 700;

	CompileLood(); //Loodしたい物を関数化して呼ぶ

	CompileCreate(); //createしたいものを関数化して呼ぶ

	return S_OK;
}


//=======================
//終了処理
//=======================
void CGame01::Uninit()
{
	CScene::Uninit();

	//テクスチャの破棄
	CompileUnlood();
}


//=======================
//更新処理
//=======================
void CGame01::Update()
{
	m_pCamera->Update(); //カメラの更新処理
	m_pLight->Update(); //光源の更新処理

	//m_pOverhead_Processing->PlayerMPNumber();
}


//=======================
//描画処理
//=======================
void CGame01::Draw()
{

}


//=======================
//Lood関数を呼ぶ
//=======================
void CGame01::CompileLood()
{
	
}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame01::CompileCreate()
{
	//Xファイルのcreate

	m_pPlayerX = CPlayerX::Create(); //プレイヤーの生成

	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(12700.0f, 1900.0f, 0.0f));  //次のステージへ行くobjの生成
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 1);                                                                    //空の生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(1000.0f, 100.0f, 0.0f));     //モーション付きの敵の生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(2900.0f, 2000.0f, 0.0f));    //モーション付きの敵の生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(7000.0f, 2000.0f, 0.0f));    //モーション付きの敵の生成

	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE,0);                                            //スコアの生成
}


//=======================
//Unlood関数を呼ぶ
//=======================
void CGame01::CompileUnlood()
{
	
}


//================================================================================================================================
//                                                    ステージ2
//================================================================================================================================


//=======================
//コンストラクタ
//=======================
CGame02::CGame02()
{
	
}


//=======================
//デストラクタ
//=======================
CGame02::~CGame02()
{

}


//=======================
//初期化処理
//=======================
HRESULT CGame02::Init()
{
	CScene::Init();

	//CompileLood(); //Loodしたい物を関数化して呼ぶ

	CompileCreate(); //createしたいものを関数化して呼ぶ


	return S_OK;
}


//=======================
//終了処理
//=======================
void CGame02::Uninit()
{
	CScene::Uninit();

	//テクスチャの破棄
	CompileUnlood();
}


//=======================
//更新処理
//=======================
void CGame02::Update()
{
	m_pCamera->Update(); //カメラの更新処理
	m_pLight->Update(); //光源の更新処理
}


//=======================
//描画処理
//=======================
void CGame02::Draw()
{

}


//=======================
//Lood関数を呼ぶ
//=======================
void CGame02::CompileLood()
{

}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame02::CompileCreate()
{
	//Xファイルのcreate
	m_pPlayerX = CPlayerX::Create(); //プレイヤーの生成

	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));         //店の生成
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 0);                                                          //空の生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALBLOCK, D3DXVECTOR3(4335.0f, -200.0f, 0.0f));   //ボス戦の足場
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());                                            //スコアの生成
}


//=======================
//Unlood関数を呼ぶ
//=======================
void CGame02::CompileUnlood()
{
	
}


//================================================================================================================================
//                                                    タイトルモードの処理
//================================================================================================================================

//======================
//コンストラクタ
//======================
CTitle::CTitle()
{
	Count = false;
	pFade = nullptr;
}


//======================
//デストラクタ
//======================
CTitle::~CTitle()
{

}


//======================
//初期化
//======================
HRESULT CTitle::Init()
{
	CManagerBg::Create(MODE_TITLE);
	////CBgText::Create();
	pFade = CFade::Create();
	return S_OK;
}


//======================
//終了処理
//======================
void CTitle::Uninit()
{
	CObject::ReleaseAll();
	//CObjectManagerX::ReleaseAll(); //全てのunitを呼び、deleteする
}


//=======================
//更新処理
//=======================
void CTitle::Update()
{
	if (Count == true)
	{
		pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

		//フェードの処理が終わったら（完全に暗くなったら）
		if (pFade->GetCountAlpha() >= 255)
		{
			CManager::SetMode(CScene::MODE_GAME01);
			//CManager::UninitKey();
			return; //処理を抜ける
		}

		//CManager::SetMode(CScene::MODE_GAME01);
	}

	//Enterキーが押されたとき
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A) == true && pFade->GetCountAlpha() <= 245)
	{
		Count = true;
	}

	if (m_bOneSound == false)
	{
		CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_WING); //BDMを流す
		m_bOneSound = true;
	}
}


//=======================
//描画処理
//=======================
void CTitle::Draw()
{

}


//================================================================================================================================
//                                                   リザルトモードの処理
//================================================================================================================================


//======================
//コンストラクタ
//======================
CResult::CResult()
{
	Count = false;
}


//======================
//デストラクタ
//======================
CResult::~CResult()
{

}


//======================
//初期化
//======================
HRESULT CResult::Init()
{
	//m_pResultScore = CResultScore::Create();
	CManagerBg::Create(MODE_RESULT);
	return S_OK;
}


//======================
//終了処理
//======================
void CResult::Uninit()
{
	CScene::Uninit();
}


//=======================
//更新処理
//=======================
void CResult::Update()
{
	//Enterキーが押されたとき
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A) == true)
	{
		Count = true;
	}

	else if (Count == true)
	{
		CManager::SetMode(CScene::MODE_TITLE);
		//CManager::UninitKey();
		return; //処理を抜ける
	}
}


//=======================
//描画処理
//=======================
void CResult::Draw()
{

}


//================================================================================================================================
//                                                   ゲームオーバーモードの処理
//================================================================================================================================


//======================
//コンストラクタ
//======================
CGameOver::CGameOver()
{
	Count = false;
}


//======================
//デストラクタ
//======================
CGameOver::~CGameOver()
{

}


//======================
//初期化
//======================
HRESULT CGameOver::Init()
{
	CManagerBg::Create(MODE_GAMEOVER);
	return S_OK;
}


//======================
//終了処理
//======================
void CGameOver::Uninit()
{
	CScene::Uninit();
	//CObjectManagerX::ReleaseAll(); //全てのunitを呼び、deleteする
}


//=======================
//更新処理
//=======================
void CGameOver::Update()
{
	//Enterキーが押されたとき
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true|| CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A)==true)
	{
		Count = true;
	}

	if (Count == true)
	{
		CManager::SetMode(CScene::MODE_RESULT);
		//CManager::UninitKey();
		return; //処理を抜ける
	}
}


//=======================
//描画処理
//=======================
void CGameOver::Draw()
{

}