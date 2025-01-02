//===================================
//
//背景のプロトタイプ宣言[bg.h]
//Author:chiba haruki
//
//===================================

#pragma once

//======================================
//インクルード
#include "main.h"
#include "object2D.h"


//==================================================================
//今作ろうとしているオブジェクトのUIクラス
class CNowCreateUI : public CObject2D
{
public:
	CNowCreateUI(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CNowCreateUI()override;                         //デストラクタ
	HRESULT Init()override;                          //初期化処理
	void Uninit()override;                           //破棄処理
	void Update()override;                           //更新処理
	void Draw()override;                             //描画処理
};

//==================================================================
//店のメニュー一覧UIクラス
class CShopMenu : public CObject2D
{
public:
	CShopMenu(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CShopMenu()override;						  //デストラクタ
	HRESULT Init()override;						  //初期化処理
	void Uninit()override;						  //破棄処理
	void  Update()override;						  //更新処理
	void Draw()override;						  //描画処理

	static CShopMenu* Create();                   //生成処理
};

//==================================================================
//BuyText表示UIクラス
class CBuyText : public CObject2D
{
public:
	CBuyText(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CBuyText()override;						 //デストラクタ
	HRESULT Init()override;						 //初期化処理
	void Uninit()override;						 //破棄処理
	void  Update()override;						 //更新処理
	void Draw()override;						 //描画処理

	static CBuyText* Create();                   //生成処理

};

//==================================================================
//選ぶ時のUIクラス
class CSelectGage : public CObject2D
{
public:
	CSelectGage(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CSelectGage()override;							//デストラクタ
	HRESULT Init()override;							//初期化処理
	void Uninit()override;							//破棄処理
	void  Update()override;							//更新処理
	void Draw()override;							//描画処理

	float& GetSizeX() { return m_fSizeX; }          //選択ゲージのX軸の大きさの取得
	float& GetSizeY() { return m_fSizeY; }          //選択ゲージのy軸の大きさを取得
	float& GetSize1X() { return m_fSize1X; }        //選択ゲージ001のx軸の大きさの取得
	float& GetSize1Y() { return m_fSize1Y; }        //選択ゲージ001のy軸の大きさの取得

	static CSelectGage* Create();                   //生成処理

private:
	float m_fSizeX;    //選択ゲージのX軸の大きさ
	float m_fSizeY;    //選択ゲージのy軸の大きさ
	float m_fSize1X;   //選択ゲージ001のx軸の大きさ
	float m_fSize1Y;   //選択ゲージ001のy軸の大きさ
};

//==================================================================
//選ぶ時のUIクラス
class CSelectGage001 : public CSelectGage
{
public:
	CSelectGage001(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CSelectGage001()override;						   //デストラクタ
	HRESULT Init()override;							   //初期化処理
	void Uninit()override;							   //破棄処理
	void  Update()override;							   //更新処理
	void Draw()override;							   //描画処理

	static CSelectGage001* Create();                   //生成処理
};