//==============================================
//
//画面遷移のクラス管理[scene.h]
//Auther:Haruki Chiba
//
//==============================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "ui.h"
#include "player.x.h"
#include "object_set.h"
#include "block.h"
#include "fade.h"
#include "skydoom.h"

//基底クラス
class CScene
{
public:

	//画面の種類
	typedef enum
	{
		MODE_TITLE = 0, //タイトル
		MODE_GAME01, //ステージ１
		MODE_GAME02, //ステージ２
		MODE_RESULT, //リザルト
		MODE_GAMEOVER,
		MODE_MAX //最大数
	}MODE;

	CScene(); //コンストラクタ
	virtual ~CScene(); //デストラクタ
	virtual HRESULT Init(); //初期化処理
	virtual void Uninit(); //終了処理
	virtual void Update(); //継承クラス更新処理
	void AnyUpdate();      //
	virtual void Draw(); //描画処理
	MODE& GetMode() { return m_Mode; } //現在モードの取得
	//static CMPTargetReTime* GetMPTargetReTime(); //対象オブジェクトの時戻し用のMP情報を取得する

	static CScene* Create(MODE mode); //modeに合わせてcreate管理をする

	CCamera* GetCamera(); //カメラの情報を取得
	CLight* GetLight(); //光源の情報を取得
	CPlayerX* GetPlayerX();
	
	CObjectSet* GetObjectSet();

protected:
	CCamera* m_pCamera; //カメラの情報
	CLight* m_pLight; //光源の情報
	CPlayerX* m_pPlayerX;
	CObjectSet* m_pObjectSet;

	MODE m_Mode; //現在のモードの管理変数

	bool m_bOneSound;

private:
};


//ステージ１のクラス管理
class CGame01 : public CScene
{
public: //アクセス可能
	CGame01(); //コンストラクタ
	~CGame01()override; //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override; //破棄処理
	void Update()override; //更新処理
	void Draw()override; //描画処理
	void CompileLood(); //テクスチャのLood関数をまとめる関数
	void CompileCreate(); //create関数をまとめる関数
	void CompileUnlood(); //テクスチャのUnlood関数をまとめる関数

private: //アクセス不可能
};


//ステージ２のクラス管理
class CGame02 : public CScene
{
public: //アクセス可能
	CGame02(); //コンストラクタ
	~CGame02()override; //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override; //破棄処理
	void Update()override; //更新処理
	void Draw()override; //描画処理
	void CompileLood(); //テクスチャのLood関数をまとめる関数
	void CompileCreate(); //create関数をまとめる関数
	void CompileUnlood(); //テクスチャのUnlood関数をまとめる関数
};

//タイトルのクラス管理
class CTitle : public CScene
{
public: //アクセス可能
	CTitle(); //コンストラクタ
	~CTitle()override; //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override; //破棄処理
	void Update()override; //更新処理
	void Draw()override; //描画処理

private: //アクセス不可能
	bool Count; //modeの移行の判定変数
	CFade* pFade;
};


//リザルトのクラス管理
class CResult : public CScene
{
public: //アクセス可能
	CResult(); //コンストラクタ
	~CResult()override; //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override; //破棄処理
	void Update()override; //更新処理
	void Draw()override; //描画処理

private: //アクセス不可能
	bool Count; //modeの移行の判定変数
};


//リザルトのクラス管理
class CGameOver : public CScene
{
public: //アクセス可能
	CGameOver(); //コンストラクタ
	~CGameOver()override; //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override; //破棄処理
	void Update()override; //更新処理
	void Draw()override; //描画処理

private: //アクセス不可能
	bool Count; //modeの移行の判定変数
};

#endif // !_SCENE_H_
