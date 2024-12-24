//============================================================================
//
//モーション付きの敵のクラス管理[enemyinmotion.h]
//Auther;Haruki Chiba
//
//============================================================================

#pragma once

#include "enemycharacter.h"

class CManagerEnemyInMotion : public CEnemyCharacter
{
public: //アクセス可能

	CManagerEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);   //コンストラクタ
	~CManagerEnemyInMotion()override;                           //デストラクタ
	HRESULT Init()override;                                     //初期化処理
	void Uninit()override;                                      //破棄処理
	void Update() override;                                     //更新処理
	void Draw()override;                                        //描画処理

	static CManagerEnemyInMotion* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);      //生成処理

	//マクロ定義
	constexpr static float MAX_SPEED = 2.0f; //追いかける速度

protected:
	int m_nJumpFrame;    //飛ぶまでの時間
	int JumpNumber;      //行きだけ飛ぶように番号をつける為の変数
	int JumpRecastTime;  //飛ぶ為のリキャストタイム（連続で触れている判定になる為その修正）
};

//モーション付きの敵（通常）
class CEnemyInMotion : public CManagerEnemyInMotion
{
public: //アクセス可能
	CEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);   //コンストラクタ
	~CEnemyInMotion()override;                           //デストラクタ
	void Update() override;                              //更新処理
	
private:
};

//モーション付きの敵（特殊）
class CEnemyInMotion001 : public CManagerEnemyInMotion
{
public: //アクセス可能
	CEnemyInMotion001(int nPriority = DEFAULT_PRIORITY1);   //コンストラクタ
	~CEnemyInMotion001()override;                           //デストラクタ
	void Update() override;                                 //更新処理
	void AdjustmentBulletAndRot();                          //プレイヤーに対する機体と弾の調整処理
	void WhenCollisionBlock();                              //地面用ブロックに触れている時の処理
	void Correctionrot();                                   //向きを修正する関数
	void PlayerBloWwaway();


private:
	int m_nHitFrame;
	bool m_bHit;
};
