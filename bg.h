//===================================
//
//背景のプロトタイプ宣言[bg.h]
//Author:chiba haruki
//
//===================================

#pragma once

//===================================
//インクルード
#include "object2D.h"
#include "scene.h"


//==================================================================
//背景の管理基底クラス
class CManagerBg : public CObject2D
{
public:
	CManagerBg(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManagerBg()override;						   //デストラクタ
	HRESULT Init()override;						   //初期化処理
	void Uninit()override;						   //破棄処理
	void  Update()override;						   //更新処理
	void Draw()override;						   //描画処理

	static CManagerBg* Create(CScene::MODE mode);  //生成処理

private:
	int nCountAlpha; //alpha値を保管する用の変数
};


//==================================================================
//タイトル背景
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);    //コンストラクタ
	~CTitleBg()override;                           //デストラクタ
};

//==================================================================
//リザルト背景
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);   //コンストラクタ
	~CResultBg()override;                          //デストラクタ
};


//==================================================================
//ゲームオーバー背景
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CGameOverBg()override;                         //デストラクタ
	void Update()override;                          //更新処理
};


//==================================================================
//ショップ時の背景
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CShopScreen()override;                         //デストラクタ
	HRESULT Init()override;                         //初期化処理
	void Update()override;                          //更新処理

	static CShopScreen* Create();                   //生成処理
};