//===================================
//
//プレイヤーのプロトタイプ宣言をするファイル[player.h]
//Author:chiba haruki
//
//===================================

#ifndef _PLAYERX_H_  //このマグロ定義がされていなかったから
#define _PLAYERX_H_  //二重インクルード防止のマクロ定義

#include "main.h"
#include "input.h"
#include "camera.h"
#include "collision.h"
#include "field.h"
#include "ui.h"
#include "2d_ui.h"
#include "character.h"

//マクロ定義
#define POS_FACE (70.0f)      //顔の位置
#define MAX_MOVESPEED (3.0f)  //感性を減らした分の移動量の増加
#define MAX_TEXT_OBJECT (9)   //今配置ツールに設定されてるオブジェクトの数ー１分（０スタートだから）
#define MAX_BUULET_SPEED (30) //弾の速さ


class CPlayerX : public CCharacter
{
public: //アクセス可能

	CPlayerX(int nPriority = DEFAULT_PRIORITY1);                 //コンストラクタ
	~CPlayerX()override;                                         //デストラクタ
	HRESULT Init()override;                                      //初期化処理
	void Uninit()override;                                       //破棄処理
	void Update()override;                                      //更新処理
	void Draw()override;                                         //描画処理
	//void ObjectArrangement();                                   //オブジェクトの配置処理（生成＆情報をファイルに書き込む）
	void ObjectArrangementTelephonPole();                        //電柱の配置処理（生成＆情報をファイルに書き込む
	void KeySet();                                               //キーごとの処理をまとめる関数
	void ShopKeySet();                                           //モードがSHOP時のキーごとの処理をまとめる関数
	void BlockJudgement();                                       //ブロックとの判定
	void Random();                                               //ランダム処理
	void Praticles();                                            //パーティクルを出す処理
	void NormalStateSummarizeFunction();                         //通常時の関数をまとめる関数
	void ShopStateSummarizeFunction();                           //店に訪問時の関数をまとめる関数
	void CreateGun();                                            //銃の生成インスタンスを呼ぶ
	void InstanceMakeNull();                                     //instanceをnullptrにする処理
	void ShopInstanceMakeNullptr();                              //ショップで使用するインスタンスをnullptrにする
	void SelectGageUISize(float SIzeX,float SIze1X);             //選択ゲージの大きさを設定する関数
	void SelectGageUISizeCalculation(const char*aSelect,float SIzeX,float SIze1X);  //選択ゲージの大きさを計算（加算や減算など）する関数
	void BlowAway();
	void HitAttack();          //特定の攻撃を受けたときの処理
	void SceneMode(int nType); //sceneの分岐

	//CObjectXで使用する用の取得
	int& GetTelephonPoleCount() { return m_nTelephonCount; }   //電柱の配列を進める
	int& GetAllTelephonPoleCount() { return m_nAllTelephonPoleCount; }   //電柱の配列を進める
	int& GetMuki() { return m_nMuki; }

	static CPlayerX* Create();                   //生成する

private: //アクセス不可能
	//プレイヤーの状態
	typedef enum
	{
		NORMAI_MODE,
		SHOP_MODE,
		BUY_MODE,
		SEND_MODE,
	}PLAYER_STATE;

	//インスタンス
	CUI* m_pTalkText;                    //「話す」textUI
	CUI* m_pLaserUI;
	CShopMenu* m_pMenyu;                 //メニューUI
	CBuyText* m_pBuyText;                //[買う、売る]textUI
	CSelectGage* m_pSelectGage;          //選択時のゲージUI
	CSelectGage001* m_pSelectGage001;    //選択時のゲージUI

	//構造体のインスタンス
	PLAYER_STATE m_PlayerState;
	PLAYER_STATE m_FlagSate;

	int m_nAlpha;                //パーティクルの透明度をランダムで決める変数

	//テキストファイルに登録する時の配列番号
	int m_nFiledCount;           //フィールドの配列を進める為のカウント
	int m_nTelephonCount;        //電柱の配列を進める為のカウント＋textから呼ぶときにインスタンス情報の配列を登録したいから渡す

	//テキストファイルに登録するした全ての配列番号
	int m_nAllTelephonPoleCount; //電柱の今の作られた数を保管する
	int m_nAllFiledCount;        //フィールドの今の作られた数を保管する

	//パーティクルに関する変数
	int m_nFrame;                //毎フレームを観測する為の変数
	int m_nPraticlesCount;       //パーティクルの配列をカウントする為の変数
	int m_nRandomCol;            //乱数を保管する為の変数

	//プレイヤーに関する変数
	int m_nMotionFrame;          //銃を打つ際のカウント
	int m_nMotionFrame001;       //銃を撃つ際のカウント
	int m_ObjectNumber;          //現在のオブジェクトの種類の番号を保管する変数
	bool m_bNextStage;           //次のステージへ行く為の判定を取る用の変数
	bool SpecialAttack;          //必殺技を使っているときは動けない

	//SHOPに関する変数
	int m_nSelectShopCount;      //何を買うかカウントする為の変数
	int m_nBuyOrSendCount;       //買うか売るかを選択するときに判別するようの変数

	//吹っ飛び処理に必要な変数
	int m_nFlayFrame;  //吹っ飛ぶ時間を観測
	bool m_bFly;       //自機が吹っ飛んでいるかどうかの判定の為の変数（モーションの混雑を避けるため）

	int m_nDieRandom;  //死亡時のフレームを保管する変数

	int m_nMuki;
	int m_nSpecialAttackCount;
	bool m_bOneCreate;

	//マクロ定義
	constexpr static float MAX_JUMPPAWER = 10.0f;          //飛ぶ力
	constexpr static float MAX_SPECIALATTACKCOUNT = 60*60;  //必殺技の撃てる時間
};

#endif 

