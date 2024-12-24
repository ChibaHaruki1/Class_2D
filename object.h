//========================================
//
//オブジェクトクラス管理[object.h]
//Auther:Chiba Haruki
//
//========================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

#define MAX_OBJECT (250) //オブジェクトの最大数
#define DEFAULT_PRIORITY (3) //描画順の最大数
#define MAX_PRIORITY_OBJ (4) //描画順の最大数

//#include "main.h"
//#include "input.h"

//全てを管理するので仮想関数（純粋仮想関数）
class CObject
{
public:

	//
	typedef enum
	{
		NONE = 0,           //無し
		ENEMY,              //敵
		PLAYER,             //プレイヤー
		BULLET,             //通常弾
		SPECIALBULLET,      //必殺弾
		BOSSBULLET,         //ボスの弾
		ENEMYBULLET,
		BLOCK,              //ブロック
		ITEM,               //アイテム
		SCORE,              //スコア
		FIELD,              //地面
		PRTICLES,           //パーティクル
		PRTICLES001,        //パーティクル１
		EFFECT,             //エフェクト
		EXPLOSION,          //爆発
		EXPLOSION001,       //爆発１
		THENDER,            //雷
		FIRE,               //炎
		PILLAROFFIRE,       //柱状の炎
		IMPACT,             //衝撃波
		DEBRIS,             //破片
		SPECIALATTACK,      //必殺技
		BOSSSPECIALATTACK,  //ボスの必殺技

		//UI
		SCREEN,         //背景
		BUYSENDTEXT,    //買うテキスト
		HP,             //HPゲージ
		MP,             //MPゲージ
		BOSSHP,         //ボスHPゲージ
		BOSSMP,         //ボスMPゲージ
		FUELGAGE,
		MAX,            //最大数
	}TYPE;

	typedef enum
	{
		NONEUI = 0,      //無し
		INUI,            //オブジェクトにつくUI
		TELEPHONPOLEUI,  //電柱のUI
		TELEPHONPOLEUI1, //電柱のUI
		BUYTEXT,         //買うtext
		TALKTEXTR,       //話すtext
		LASER,          //レーザー
	}TYPE_UI;

	CObject(); //コンストラクタ
	CObject(int nPriority= DEFAULT_PRIORITY);
	virtual ~CObject(); //デストラクタ
	virtual HRESULT Init()=0; //初期化
	virtual void Uninit() = 0; //終了処理
	virtual void Update() = 0; //更新処理
	virtual void Draw() = 0; //描画処理
	virtual void DrawNoml() = 0; //描画処理
	static void ReleaseAll(); //全オブジェクトの解放
	static void UpdateAll(); //全オブジェクトの更新
	static void DrawAll(); //全オブジェクトの描画
	static void DrawNomlAll(); //全オブジェクトの通常描画
	static CObject* GetObject1(int nPri,int nIndex); //オブジェクト取得
	TYPE GetType(); //タイプ取得
	void SetType(TYPE type); //タイプ設定
	void Release(); //自分自身の解放

protected:
	static int m_nNumAll; //オブジェクトの総数

	/*CInputKeyBoard* pInputKeyBoard;
	CInputJoyPad* pInputJyoPad;*/

private:
	static CObject* m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT]; //全オブジェクトの管理
	int m_nPriority;
	int m_nID; //自分自身のID
	TYPE m_type; //オブジェクトタイプ

};

#endif // !_OBJECT_H_

