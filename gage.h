//=====================================
//
//ゲージに関するクラス[gage.h]
//Auther:Haruki Chiba
//
//=====================================

#pragma once

//=====================================
//インクルード
#include "object2D.h"
#include "object3D.h"

//==================================================
//燃料ゲージ
class CFuelGage : public CObject3D
{
public:
	CFuelGage(int nPriority = DEFAULT_PRIORITY);          //コンストラクタ;
	~CFuelGage();                                         //コンストラクタ;
	HRESULT Init()override;                               //初期化処理
	void Uninit()override;                                //破棄処理
	void Update()override;                                //更新処理
	void Draw()override;                                  //描画処理
	void DrawNoml()override;                              //通常描画処理

	static CFuelGage* Create();                           //生成処理

	inline bool& GetUse() { return m_bUse; }              //使われているかどうかの判定を取得する
private:
	//マクロ定義
	constexpr static float MAX_SIZEY = 100.0f;            //ゲージの大きさ
	constexpr static float MAX_MAINAS_GAGESPEED = 0.5f;   //ゲージの減る速さ
	bool m_bUse;                                          //ゲージを減らすかどうか判定するための変数

};


//==================================================
//ゲージの管理クラス
//==================================================
class CManagerGage : public CObject2D
{
public:  //アクセス可能
	CManagerGage(int nPriority = DEFAULT_PRIORITY);           //コンストラクタ;
	~CManagerGage()override;                                  //デストラクタ
	HRESULT Init()override;                                   //初期化処理
	void Uninit()override;                                    //破棄処理
	void  Update()override;                                   //更新処理
	void Draw()override;                                      //描画処理
	void DrawNoml()override;                                  //通常描画処理
	static CManagerGage* Create(CObject2D::TYPE type);        //ゲージの生成
	static CManagerGage* CreateLeave(CObject2D::TYPE type);   //残すゲージの生成

	float& GetPlayerHPSizeX() { return m_fHPSizeX; }          //プレイヤーのHPゲージを取得
	float& GetBossHPSizeX() { return m_fBossHPSizeX; }        //ボスのHPゲージを取得
	float& GetSaveSizeX() { return m_fSaveSizeX; }            //ゲージの保管を取得

protected://継承クラスのみアクセス可能
	float m_fSaveSizeX;

	//マクロ定義
	constexpr static float MAX_PLAYERGAGE_SIZE_Y = 40.0f; //プレイヤーのゲージのY軸の大きさ
	constexpr static float MAX_PLAYERGAGE_SIZE_Z = 70.0f; //プレイヤーのゲージのZ軸の大きさ

private:  //アクセス不可能
	float m_fHPSizeX;      //プレイヤーのHPゲージの大きさを管理する用の変数
	float m_fBossHPSizeX;  //ボスのHPゲージの大きさを管理する用の変数
};


//==================================================
//プレイヤーのHPゲージ
class CPlayerHPGage : public CManagerGage
{
public:
	CPlayerHPGage(int nPriority = DEFAULT_PRIORITY);   //コンストラクタ
	~CPlayerHPGage()override;                          //デストラクタ
	HRESULT Init()override;                            //初期化処理
	void Update()override;                             //更新処理
};
	

//==================================================
//ボスのHPゲージ
class CBossHPGage : public CManagerGage
{
public:
	CBossHPGage(int nPriority = DEFAULT_PRIORITY);     //コンストラクタ
	~CBossHPGage()override;                            //デストラクタ
	HRESULT Init()override;                            //初期化処理
	void Update()override;                             //更新処理
};


//==================================================
//プレイヤーのHPゲージを残す
class CPlayerHPGageLeave : public CManagerGage
{
public:
	CPlayerHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CPlayerHPGageLeave()override;                         //デストラクタ
	HRESULT Init()override;                                //初期化処理
};


//==================================================
//ボスのHPゲージを残す
class CBossHPGageLeave : public CManagerGage
{
public:
	CBossHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CBossHPGageLeave()override;                         //デストラクタ
	HRESULT Init()override;                              //初期化処理
};

