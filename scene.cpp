//====================================
//
//画面遷移処理[scene.cpp]
//Auther:Haruki Chiba
//
//====================================


//====================================
//インクルード
#include "scene.h"
#include "manager.h"
#include "rendererh.h"
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
#include "bg.h"


//static変数の初期化
//CCamera* CScene::m_pCamera = nullptr;
//CLight* CScene::m_pLight = nullptr;
//CPlayerX* CScene::m_pPlayerX = nullptr;
//CTarget* CScene::m_pTragetUi = nullptr;
//CMPTargetReTime* CScene::pMPTargetReTime = nullptr;

CManagerBg* g_pBG; //背景のBGのグローバル変数


//=======================
//コンストラクタ
//=======================
CScene::CScene()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_Mode = MODE::MODE_RESULT;
	m_pPlayerX = nullptr;
	m_bOneSound = false;
	m_bOneScene = false;
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
	CObject::ReleaseAll();         //全てのUninit()を呼び、deleteする
	CObjectManagerX::ReleaseAll(); //全てのunitを呼び、deleteする


	m_pPlayerX = nullptr;          //情報を無くす

	//カメラの情報がある時
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit(); //カメラの終了処理
		delete m_pCamera;    //メモリの解放
		m_pCamera = nullptr; //情報を無くす
	}

	//光源の情報がある時
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit(); //光源の終了処理
		delete m_pLight;    //メモリの解放
		m_pLight = nullptr; //情報を無くす
	}
}


//=======================
//更新処理
//=======================
void CScene::Update()
{
	m_pCamera->Update(); //カメラの更新処理
	m_pLight->Update();  //光源の更新処理
}

//=======================
//他の物のUpdateを呼ぶ
//=======================
void CScene::AnyUpdate()
{
	if (m_Mode == MODE::MODE_GAME02)
	{
		CManager::GetEvent()->Update();
	}
}


//=======================
//生成
//=======================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr; //基底クラスの動的確保

	//ゲームモードが１の時
	if (mode == MODE::MODE_GAME01)
	{
		pScene = new CGame01();
		pScene->m_Mode = MODE::MODE_GAME01;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//ゲームモードが２の時
	else if (mode == MODE::MODE_GAME02)
	{
		pScene = new CGame02();
		pScene->m_Mode = MODE::MODE_GAME02;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//タイトルの時
	else if (mode == MODE::MODE_TITLE)
	{
		pScene = new CTitle();
		pScene->m_Mode = MODE::MODE_TITLE;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//リザルトの時
	else if (mode == MODE::MODE_RESULT)
	{
		pScene = new CResult();
		pScene->m_Mode = MODE::MODE_RESULT;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//ゲームモードの時
	else if (mode == MODE::MODE_GAMEOVER)
	{
		pScene = new CGameOver();
		pScene->m_Mode = MODE::MODE_GAMEOVER;

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
	m_pFade = nullptr;
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
	g_pBG = CManagerBg::Create(MODE::MODE_TITLE);             //背景のUI生成
	m_pFade = CFade::Create();                                //フェードの生成
												              
	CScene::Init();                                           //初期化処理
													          
	GetCamera()->GetAdjustmentPosZ() = 500;                   //カメラのZ軸の調整
	GetCamera()->SetRot(D3DXVECTOR3(0.0f,0.57f,0.0f));        //カメラの向きの設定
													          
	InitCreate();                                             //タイトルに必要な生成
	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING); //プレイヤーのモーションを探すに設定
	GetPlayerX()->SetRot(D3DXVECTOR3(0.0f,0.57f,0.0f));       //プレイヤーの向きを設定
	
	GetPlayerX()->GetPos().y = 2050.0f;                //プレイヤーのY軸の位置を設定
										               
	return S_OK;                                       //成功を返す
}


//=======================
//終了処理
//=======================
void CGame01::Uninit()
{
	CScene::Uninit(); //破棄処理
}


//=======================
//更新処理
//=======================
void CGame01::Update()
{
	if (GetOneScene() == true)
	{
		if (m_pFade != nullptr)
		{
			m_pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

			//フェードの処理が終わったら（完全に暗くなったら）
			if (m_pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
			{
				m_pFade->Release();
				g_pBG->Release();
				m_pFade = nullptr;
				g_pBG = nullptr;
				SetPlay(true);
				GetPlayerX()->SetGravityFlag(true);                                           //重力ON
				GetCamera()->GetAdjustmentPosZ() = 700;                                       //カメラのZ軸の調整
				GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP);
				CompileCreate();                        //createしたいものを関数化して呼ぶ
				return;
			}
		}
	}

	if (GetOneScene() == false)
	{
		GetPlayerX()->SetGravityFlag(false); //重力Off

		//Enterキーが押された時かAキーを押された時
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
		{
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING);    //指定の音源を止める
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);  //BDMを流す
			SetOneScene(true);
		}
	}

	//音源が流れていない時
	if (GetOneSound() == false)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDMを流す
		SetOneSound(true);                                                         //一度だけ流す
	}

	CScene::Update(); //更新処理
}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame01::InitCreate()
{
	GetPlayerX() = CPlayerX::Create();                                                                                     //プレイヤーの生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(0.0f, 2000.0f, 100.0f));  //次のステージへ行くobjの生成
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 1);                                                                  //空の生成
}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame01::CompileCreate()
{
	//Xファイルのcreate
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));         //店の生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(12700.0f, 1900.0f, 0.0f));        //次のステージへ行くobjの生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(1000.0f, 100.0f, 0.0f));     //モーション付きの敵の生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(2900.0f, 2000.0f, 0.0f));    //モーション付きの敵の生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(7000.0f, 2000.0f, 0.0f));    //モーション付きの敵の生成

	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE,0);                                                   //スコアの生成
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0); //プレイヤーのHPゲージの生成
}


//================================================================================================================================
//                                                    ステージ2
//================================================================================================================================


//=======================
//コンストラクタ
//=======================
CGame02::CGame02()
{
	SetPlay(true);
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
}


//=======================
//更新処理
//=======================
void CGame02::Update()
{
	CScene::Update();
}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame02::CompileCreate()
{
	//Xファイルのcreate
	GetPlayerX() = CPlayerX::Create(); //プレイヤーの生成

	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));         //店の生成
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 0);                                                          //空の生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALBLOCK, D3DXVECTOR3(4335.0f, -200.0f, 0.0f));   //ボス戦の足場
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());          //スコアの生成
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0); //プレイヤーのHPゲージの生成
}


//================================================================================================================================
//                                                    タイトルモードの処理
//================================================================================================================================

//======================
//コンストラクタ
//======================
CTitle::CTitle()
{
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
	//CManagerBg::Create(MODE::MODE_TITLE);
	//////CBgText::Create();
	//pFade = CFade::Create();

	CScene::Init();

	GetCamera()->GetAdjustmentPosZ() = 700;

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
	////Enterキーが押されたとき
	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true && pFade->GetAlph() <= 245)
	//{
	//	SetOneScene(true);
	//}

	//else if (GetOneScene() == true)
	//{
	//	pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

	//	//フェードの処理が終わったら（完全に暗くなったら）
	//	if (pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
	//	{
	//		CManager::SetMode(CScene::MODE::MODE_GAME01);
	//		return; //処理を抜ける
	//	}

	//	//CManager::SetMode(CScene::MODE_GAME01);
	//}

	//if (GetOneSound() == false)
	//{
	//	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDMを流す
	//	SetOneSound(true);
	//}

	CScene::Update();
}


//=============================
//タイトルゲーム画面処理
//=============================
void CTitle::Game()
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
	CManagerBg::Create(MODE::MODE_RESULT);
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
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetOneScene(true);
	}

	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_GAME01);
		//CManager::UninitKey();
		return; //処理を抜ける
	}
}


//================================================================================================================================
//                                                   ゲームオーバーモードの処理
//================================================================================================================================


//======================
//コンストラクタ
//======================
CGameOver::CGameOver()
{
	
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
	CManagerBg::Create(MODE::MODE_GAMEOVER);
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
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true|| CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A)==true)
	{
		SetOneScene(true);
	}

	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
		//CManager::UninitKey();
		return; //処理を抜ける
	}
}