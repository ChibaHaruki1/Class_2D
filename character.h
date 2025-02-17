//============================================
//
//characterクラス管理[character.h]
//Ajther: Chiba haruki
//
//============================================

#pragma once

//============================================
//インクルード
#include "objectX.h"
#include "model_prts.h"


//======================================================
//キャラクターの各パーツクラス
class CCharacter : public CObjectX
{
public://外部からのアクセス可能
	////共通化でもいいかも
	//typedef enum
	//{
	//	NEUTRAL = 0, //待機
	//	WALK,        //歩き
	//	ACTION,      //
	//	JUMP,
	//}COMMON;

	//typedef enum
	//{
	//	BOSSJUMP1=4,
	//}BOSSMOTIONSTATE;

	//typedef enum
	//{
	//	BLOWAWAY=4,
	//}MOTIONSTATE;

	//ボスのモーションの種類
	typedef enum
	{
		BOSSNEUTRAL = 0, //待機
		BOSSWALK,        //歩く
		BOSSACTION,      //撃つ
		BOSSJUMP,        //飛ぶ
		BOSSIMPACT,      //飛ぶ001
		BOSSATTACK,      //攻撃
		BOSSDIE,         //死亡
	}BOSSMOTIONSTATE;

	//プレイヤーのモーションの種類
	typedef enum
	{
		NEUTRAL = 0, //待機
		WALK,        //歩き
		ACTION,      //撃つ
		JUMP,        //飛ぶ
		BLOWAWAY,    //吹っ飛ぶ
		DIE,         //死亡
		SLOWSHOT,    //ゆっくり撃つ
		TITLE_JUMP,  //タイトル時の飛ぶ
		LANDING,     //着地
		LOKING ,     //探す(タイトル時)
	}MOTIONSTATE;

	CCharacter(int nPriority = DEFAULT_PRIORITY1);         //コンストラクタ
	~CCharacter();                                         //デストラクタ
	HRESULT Init();                                        //初期化処理
	void Uninit();                                         //破棄処理

	//プレイヤー
    void Lood();
	void UpdatePlayer();                                   //プレイヤーの更新処理
	void DrawPlayer(int NumPrts);                          //プレイヤーの描画処理
	void MotionInfo();                                     //モーションの情報を扱う処理
	void SetMotion(MOTIONSTATE motiontype);                //モーションごとの処理
	
	//ボス
	void LoodBoss();
	void UpdateBoss();                                     //ボスの更新処理
	void DrawBoss(int NumPrts);                            //描画処理
	void MotionInfoBoss();                                 //ボスモーションの情報を扱う処理
	void SetMotionBoss(BOSSMOTIONSTATE motiontype);        //ボスモーションごとの処理

	MOTIONSTATE m_MotionState;                   //プレイヤーのモーションの種類の情報を持つ
	BOSSMOTIONSTATE m_MotionStateBoss;           //ボスのモーションの種類の情報を持つ
	CModelPrts* m_pModelPrts[MAX_PRTS];          //モデルパーツの情報のポインター
	CModelPrts* m_pModelPrtsBoss[MAX_BOSSPARTS]; //モデルパーツの情報のポインター


	//=====================================
	//情報の取得
	CModelPrts* GetModelPrtasBoss(int nNumber) { return m_pModelPrtsBoss[nNumber]; } //ボスのパーツの情報の取得
	//bool& GetMotionType() { return m_bMotionType; }                                  //プレイヤーのモーションタイプの取得


	//=====================================
	//情報の設定
	void SetMotionType(bool bMotionType) { m_bMotionType = bMotionType; }            //プレイヤーのモーションタイプの設定


	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static int MAX_KEYSET = 8;        //モーションに使うキーの数
	constexpr static int NUM_MOTION = 11;       //プレイヤーモーションの総数
	constexpr static int NUM_RIGHTLEFTPRTS = 4; //プレイヤーの側のパーツ数
	constexpr static int NUM_MOTIONBOSS = 10;   //ボスのモーションの総数
	constexpr static int NUM_RIGHTPRTSBOSS = 8; //ボスの側のパーツ数

private://外部からのアクセス不可能

	//キーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //向き
	}Key;

	//キーセットの構造体
	typedef struct
	{
		int Frame;                 //フレーム数
		Key aKey[MAX_PRTS];        //キー数(パーツ分確保)
	}KeySet;

	//モーションの構造体
	typedef struct
	{
		bool Loop;                  //モーションがループするかどうか判定用
		int NumKey;                 //キーの総数
		KeySet KeySet[MAX_KEYSET];  //モーションのキーセット（モーション時のキーセットの数）
	}MotionSet;

	//モーション情報を確保する構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //向き
	}SAVEMODELINFO;

	//キャラクターの情報を保管する変数
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_PRTS], m_pSaveModelPrtInfoBoss[MAX_BOSSPARTS];   //モデルパーツの情報のポインター
	D3DXVECTOR3 SaveMotionPos[MAX_PRTS], SaveMotionPosBoss[MAX_BOSSPARTS];                 //各パーツの位置情報を確保する変数
	D3DXVECTOR3 SaveMotionRot[MAX_PRTS], SaveMotionRotBoss[MAX_BOSSPARTS];                 //各パーツの向き情報を獲得する変数
	MotionSet MotionSetPlayer[NUM_MOTION], MotionSetBoss[NUM_MOTIONBOSS];                  //各モーションの種類を格納する変数

	int m_nMotionFrameBoss;            //モーション時のフレームをカウントするための変数
	int MotionCount, MotionCountBoss;  //現在のモーションをカウントするための変数(Keyカウント)

	bool m_bMotionType, m_bMotionBossType;       //特殊なモーションかどうかを判定する為の変数
};