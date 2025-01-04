//======================================
//
//弾のクラス管理[bullet.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

//======================================
//インクルード
#include "object3D.h"


//============================================================================
//弾の管理の基底クラス
//============================================================================
class CManagerBullet : public CObject3D
{
public: //外部からアクセス可能
	CManagerBullet(int nPriority = DEFAULT_PRIORITY);              //引数付きコンストラクタ
	~CManagerBullet()override;                                     //デストラクタ
	HRESULT Init()override;                                        //初期化処理
	void Uninit()override;                                         //終了処理
	void Update()override;                                         //更新処理
	void Draw()override;                                           //描画処理
	void SetPos(D3DXVECTOR3 m_pos, D3DXVECTOR3 m_move, int nLife); //弾の位置に関する設定処理

	//純粋仮想関数にすることで基底クラスの処理をそのまま処理する
	virtual void CallEffect(bool bUse) = 0;  //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	virtual void CollisionOnObject() = 0; ;  //オブジェクトとの当たり判定

	static CManagerBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject3D::TYPE type); //3D弾の生成処理

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static float MAX_BULLET3D_SIZE_X = 40.0f; //3D弾のX軸の大きさ
	constexpr static float MAX_BULLET3D_SIZE_Y = 40.0f; //3D弾のY軸の大きさ
	constexpr static float MAX_BULLET3D_SIZE_Z = 40.0f; //3D弾のZ軸の大きさ
	constexpr static int SET_BULLET_LIFE = 60;          //ライフの最大数

private: //アクセス不可能

};

//プレイヤー通常弾のクラス
class CBullet3D : public CManagerBullet
{
public: //外部からアクセス可能
	CBullet3D(int nPriority = DEFAULT_PRIORITY);   //引数付きコンストラクタ
	~CBullet3D()override;                          //デストラクタ
	//void Update()override;                        //更新処理
	void CallEffect(bool bUse);                    //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                      //オブジェクトとの当たり判定

private: //アクセス不可能
};

//プレイヤー必殺技のクラス
class CSpecialBullet : public CManagerBullet
{
public: //外部からアクセス可能
	CSpecialBullet(int nPriority = DEFAULT_PRIORITY);   //引数付きコンストラクタ
	~CSpecialBullet()override;                          //デストラクタ
	void Update()override;                              //更新処理
	void CallEffect(bool bUse);                         //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                           //オブジェクトとの当たり判定

private: //アクセス不可能

};

//敵の通常弾のクラス
class CEnemyBullet : public CManagerBullet
{
public: //外部からアクセス可能
	CEnemyBullet(int nPriority = DEFAULT_PRIORITY);  //引数付きコンストラクタ
	~CEnemyBullet()override;                         //デストラクタ
	void Update()override;                          //更新処理
	void CallEffect(bool bUse);                     //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                       //オブジェクトとの当たり判定

	static float m_fAdditionPosY;                   //rot.yに値を追加していくための変数

	//マクロ提議
	constexpr static float InitAddItion = 7.0f;

private: //外部からアクセス不可能

};

//ボスの通常弾のクラス
class CBossBullet : public CManagerBullet
{
public: //外部からアクセス可能
	CBossBullet(int nPriority = DEFAULT_PRIORITY);  //引数付きコンストラクタ
	~CBossBullet()override;                         //デストラクタ
	void Update()override;                          //更新処理
	void CallEffect(bool bUse);                     //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                       //オブジェクトとの当たり判定

private: //外部からアクセス不可能

};

