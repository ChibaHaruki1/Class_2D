//================================================================
//
//characterクラス管理[character.h]
//Ajther: Chiba haruki
//
//================================================================

#pragma once

#include "objectX.h"
#include "model_prts.h"

//敵
#define MAX_ENEMYKEYSET (5)   //キー数
#define NUM_ENEMYMOTION (10)  //モーション数

//キャラクターの各パーツクラス
class CEnemyCharacter : public CObjectX
{
public:

	//敵のモーションの種類
	typedef enum
	{
		ENEMYWALK = 0,
		ENEMYJUMP,
		ENEMYATTACK,
		ENEMYDIE,

	}ENEMYMOTIONSTATE;

	CEnemyCharacter(int nPriority = DEFAULT_PRIORITY1);      //コンストラクタ
	~CEnemyCharacter();                                      //デストラクタ
	HRESULT Init();                                          //初期化処理
	void Uninit();                                           //破棄処理
	void SelectUninitPrtas(TYPE type, int nNumber);          //何を破棄するか選択する破棄処理
	void UpdateEnemy001();                                   //敵001の更新処理
	void DrawEnemy(int NumPrts ,int nNumber);                //描画処理
	void LoodEnemy(const char* aSelect);                     //モデルを読み込む処理＋情報を取得する処理
	void MotionInfoEnemy();                                  //ボスモーションの情報を扱う処理
	void SetMotionEnemy(ENEMYMOTIONSTATE motiontype);        //ボスモーションごとの処理

	CModelPrts* GetModelPrtasEnemy(int nNumber) { return m_pModelPrtsEnemy[nNumber]; }

	bool m_bMotionType, m_bMotionBossType;         //特殊なモーションかどうか
	ENEMYMOTIONSTATE m_MotionStateBoss;            //ボスのモーションの種類の情報を持つ
	CModelPrts* m_pModelPrtsEnemy[MAX_ENEMYPARTS]; //モデルパーツの情報のポインター

	static int m_nMaxCreate;                       //現在のプレイヤーのparts数

private:
	//キーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}Key;

	//キーセットの構造体
	typedef struct
	{
		int Frame;
		Key aKey[MAX_ENEMYPARTS];
	}KeySet;

	//モーションの構造体
	typedef struct
	{
		bool Loop;
		int NumKey;
		KeySet KeySet[MAX_ENEMYKEYSET];
	}MotionSet;

	//モーション情報を確保する構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}SAVEMODELINFO;

	//キャラクターの情報を保管する変数
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_ENEMYPARTS],m_pSaveModelPrtUpdateInfo[MAX_ENEMYPARTS];         //モデルパーツの情報のポインター
	D3DXVECTOR3 SaveMotionPos[MAX_ENEMYPARTS];                 //各パーツの位置情報を確保する変数
	D3DXVECTOR3 SaveMotionRot[MAX_ENEMYPARTS];                 //各パーツの向き情報を獲得する変数
	MotionSet MotionSetEnemy[NUM_ENEMYMOTION];                 //各モーションの種類を格納する変数

	int m_nMotionFrameBoss;        //モーション時のフレームをカウントするための変数
	int MotionCount, MotionCountBoss;  //現在のモーションをカウントするための変数(Keyカウント)
};