//==================================
//
//敵のクラス管理[enemy.h]
//Auther:Chiba Haruki
//
//==================================

#pragma once

//==================================
//インクルード
#include "objectX.h"
#include "enemycharacter.h"


//==========================================================
//敵のマネージャー管理クラス
class CManagerEnemy : public CObjectX
{
public:
	CManagerEnemy(int nPriority = DEFAULT_PRIORITY);   //引数付きコンストラクタ
	~CManagerEnemy()override;                          //デストラクタ
	HRESULT Init()override;                            //初期化処理
	void Uninit()override;                             //終了処理
	void Update() override;                            //更新処理
	void Draw()override;                               //描画処理
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type); //生成処理
};


//==========================================================
//敵のクラス
class CEnemyX : public CManagerEnemy
{
public:
	CEnemyX(int nPriority = DEFAULT_PRIORITY1);  //コンストラクタ
	~CEnemyX()override;                          //デストラクタ
	void Update()override;                       //更新処理

private:
	//マクロ定義
	const float m_fMAX_SPPED = 2.0f; //移動速度
};


//==========================================================
//敵001のクラス
class CEnemy001X : public CManagerEnemy
{
public:
	CEnemy001X(int nPriority = DEFAULT_PRIORITY1);  //コンストラクタ
	~CEnemy001X()override; 							//デストラクタ
	void Update()override;							//更新処理
	
private:
	//マクロ定義
	constexpr static float MAX_DAMAGE = 0.005f; //プレイヤーに与えるダメージ数
};

