//===========================================
//
//全体を管理する処理[manager.cpp]
//Auther:Chiba Haruki
//
//===========================================


#include "manager.h"
#include "rendererh.h"

CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyBoard* CManager::m_pKeyBoard = nullptr;
CInputJoyPad* CManager::m_pJyoPad = nullptr;
CSound* CManager::m_pSound = nullptr;
CScene* CManager::m_pScene = nullptr;
CInstance* CManager::m_pInstance = nullptr;
CObjectSet* CManager::m_pObjectSet = nullptr;
CEvent* CManager::m_pEvent = nullptr;
CMain* CManager::m_pMain = nullptr;


//===================
//コンストラクタ
//===================
CManager::CManager()
{

}

//===================
//デストラクタ
//===================
CManager::~CManager()
{

}

//==================
//初期化処理
//==================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの情報がない時
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer(); //レンダラーの動的確保をする
	}

	//キーボードの情報がない時
	if (m_pKeyBoard == nullptr)
	{
		m_pKeyBoard = new CInputKeyBoard(); //キーボードの動的確保
	}

	//ジョイパットの情報がない時
	if (m_pJyoPad == nullptr)
	{
		m_pJyoPad = new CInputJoyPad(); //ジョイパットの動的確保
	}

	//音源の情報がない時
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound(); //サウンドの動的確保
	}

	if (m_pMain == nullptr)
	{
		m_pMain = new CMain();
	}

	m_pRenderer->Init(hInstance,hWnd, bWindow); //レンダラーのWindowの処理を呼び出す

	//CBlockManager::DataLood();


	//キーボードの初期化処理
	if (FAILED(m_pKeyBoard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパットの初期化処理
	if (FAILED(m_pJyoPad->Init()))
	{
		return E_FAIL;
	}


	m_pSound->InitSound(hWnd); //音源の初期化

	return S_OK;
}

//==================
//終了処理
//==================
void CManager::Uninit()
{
	//レンダラーの情報がある時
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit(); //頂点バッファの破棄
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//キーボードの情報がある時
	if (m_pKeyBoard != nullptr)
	{
		m_pKeyBoard->Uninit(); //キーボードの終了処理
		delete m_pKeyBoard;
		m_pKeyBoard = nullptr;
	}


	//ジョイパットの情報がある時
	if (m_pJyoPad != nullptr)
	{
		m_pJyoPad->Uninit(); //ジョイパットの終了処理
		delete m_pJyoPad;
		m_pJyoPad = nullptr;
	}

	//音源の情報がある時
	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound(); //サウンドの終了処理
		delete m_pSound;
		m_pSound = nullptr;
	}


	//画面遷移の情報があるとき
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit(); //終了処理を呼ぶ
		delete m_pScene; //メモリの解放
		m_pScene = nullptr; //情報をなくす
	}

	//インスタンス情報があるとき
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit();
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	//textファイルの情報がある時
	if (m_pObjectSet != nullptr)
	{
		delete m_pObjectSet;
		m_pObjectSet = nullptr;
	}

	if (m_pEvent != nullptr)
	{
		delete m_pEvent;
		m_pEvent = nullptr;
	}

	if (m_pMain != nullptr)
	{
		delete m_pMain;
		m_pMain = nullptr;
	}
}

//==================
//更新処理
//==================
void CManager::Update()
{
	m_pKeyBoard->Update(); //キーボードの更新処理
	m_pJyoPad->Update();   //ジョイパットの更新処理
	m_pRenderer->Update(); //レンダラーの更新処理
	m_pScene->Update();    //更新処理を呼ぶ
	m_pScene->AnyUpdate();    //更新処理を呼ぶ
}


//==================
//描画処理
//==================
void CManager::Draw()
{
	m_pRenderer->Draw(); //レンダラーの描画処理
	m_pScene->Draw(); //描画処理を呼ぶ
}


//===============================
//画面遷移のモードの変更
//===============================
void CManager::SetMode(CScene::MODE mode)
{
	//sceneの情報がある時
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();  //破棄処理を呼ぶ
		delete m_pScene;     //情報を消す
		m_pScene = nullptr;  //情報を無くす
	}

	//インスタンス情報があるとき
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit();  //破棄処理を呼ぶ
		delete m_pInstance;     //情報を消す
		m_pInstance = nullptr;  //情報を無くす
	}

	//eventの情報がある時
	if (m_pEvent != nullptr)
	{
		delete m_pEvent;     //情報を消す
		m_pEvent = nullptr;  //情報を無くす
	}

	m_pSound->StopSound();           //音源を止める
	m_pInstance = new CInstance();   //インスタンスの生成
	m_pScene = CScene::Create(mode); //sceneの生成

	//タイトルとリザルト時以外の時textファイルの情報を読み込む
	if (mode != CScene::MODE_TITLE)
	{
		m_pObjectSet = CObjectSet::Create(); //textから読み取ったオブジェクトを配置する
		m_pEvent = new CEvent();             //動的確保する
	}

	//シーンがリザルトの時
	if (mode == CScene::MODE_RESULT)
	{
		//情報がある時
		if (m_pObjectSet != nullptr)
		{
			delete m_pObjectSet;     //情報を消す
			m_pObjectSet = nullptr;  //情報を無くす
		}
	}
}


//===============================
//レンダラーの情報を取得する
//===============================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}


//===============================
//キーボードの情報を取得する
//===============================
CInputKeyBoard* CManager::GetKeyBorad()
{
	return m_pKeyBoard;
}


//================================
//ジョイパットの情報を取得
//================================
CInputJoyPad* CManager::GetJyoPad()
{
	return m_pJyoPad;
}


//================================
//サウンドの情報を取得
//================================
CSound* CManager::GetSound()
{
	return m_pSound;
}
