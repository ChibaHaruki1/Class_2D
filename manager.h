//======================================
//
//全体を管理するクラス[manager.h]
//Auther:Chiba Hruki
//
//======================================

#ifndef _MANAGER_H_  //このマグロ定義がされていなかったから
#define _MANAGER_H_  //二重インクルード防止のマクロ定義

#include "rendererh.h"
#include "input.h"
#include "block.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "instance.h"
#include "scene.h"
#include "object_set.h"
#include "event.h"

class CManager
{
public:
	CManager();  //コンストラクタ
	~CManager(); //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow); //初期化処理
	void Uninit(); //終了処理
	void Update(); //更新処理
	void Draw(); //描画処理
	//void Uninit

	static CRenderer* GetRenderer(); //レンダラーの情報を取得
	static CInputKeyBoard* GetKeyBorad(); //キーボードの情報を取得
	static CInputJoyPad* GetJyoPad(); //ジョイパットの情報を取得
	static CSound* GetSound(); //音源の情報を取得
	static CInstance* GetInstance() { return m_pInstance; }
	static CScene* GetScene() { return m_pScene; }
	static CObjectSet* GetObjectSet() { return m_pObjectSet; }
	static CEvent* GetEvent() { return m_pEvent; }
	static void SetMode(CScene::MODE mode);  //モードの確定

private:
	static CRenderer* m_pRenderer;       //レンダラーの情報
	static CInputKeyBoard* m_pKeyBoard;  //キーボードの情報
	static CInputJoyPad* m_pJyoPad;      //ジョイパットの情報
	static CSound* m_pSound;             //音源の情報
	static CScene* m_pScene;             //現在のモード
	static CInstance* m_pInstance;       //各クラスの情報を持つ
	static CObjectSet* m_pObjectSet;     //テキストファイルから読み込む
	static CEvent* m_pEvent;             //ステージ毎のイベント情報
};

#endif
