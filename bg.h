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
	CManagerBg(int nPriority = DEFAULT_PRIORITY);
	~CManagerBg()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CManagerBg* Create(CScene::MODE mode);
};


//==================================================================
//タイトル背景
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);
	~CTitleBg()override;
private:
	
};

//==================================================================
//リザルト背景
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);
	~CResultBg()override;
};


//==================================================================
//ゲームオーバー背景
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);
	~CGameOverBg()override;
	void Update()override;
};


//==================================================================
//ショップ時の背景
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);
	~CShopScreen()override;
	HRESULT Init()override;
	void Update()override;

	static CShopScreen* Create();
};