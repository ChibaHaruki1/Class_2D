//==========================================
//
//UIのクラス管理宣言をするファイル[ui.h]
//Author:chiba haruki
//
//==========================================

#pragma once

//==========================================
//インクルード
#include "object3D.h"
#include <cstdio>


//======================================================
//UIのマネージャー管理クラス
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CUI()override;							//デストラクタ
	HRESULT Init()override;					//初期化処理
	void Uninit()override;					//破棄処理
	void Update()override;					//更新処理
	void Draw()override;					//描画処理

	bool& GetDraw() { return m_bDraw; }     //使われているかどうかを判定する情報を取得

	static CUI* Create(CObject3D::TYPE_UI typeui); //生成処理

private:
	bool m_bDraw; //使われているかどうかを判定する変数
};


//======================================================
//現在の配置したオブジェクトの場所にUIを出すクラス管理
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CCreateInObject()override;                         //デストラクタ
};


//======================================================
//今作ろうとしているオブジェクトのUIをだすクラス管理
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CTalkText()override;                         //デストラクタ
	HRESULT Init()override;                       //初期化処理
	void Draw()override;                          //描画処理
};


//======================================================
//監視カメラからでるレーザークラス
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CLaserCamare()override;                         //デストラクタ
	HRESULT Init()override;                          //初期化処理
	void Update()override;                           //更新処理
	void Draw()override;                             //描画処理
};
