//================================================
//
//ボスのクラス管理[boss.h]
//Auther:Haruki Chiba
//
//================================================

#pragma once

//================================================
//インクルード
#include "character.h"
#include "enemycharacter.h"
#include<vector>


//==================================================================
//ボスの処理
class CBoss : public CCharacter
{
public: //アクセス可能

	CBoss(int nPriority = DEFAULT_PRIORITY1);   //コンストラクタ
	~CBoss()override;                           //デストラクタ
	HRESULT Init()override;                     //初期化処理
	void Uninit()override;                      //破棄処理
	void ThisUnInit();
	void Update() override;                     //更新処理
	void Draw()override;                        //描画処理
	void AttackPattern();                       //攻撃の種類ごとの関数
	void AttackPattern001();                    //攻撃の種類ごとの関数
	void StatusInit();                          //内部の変数の初期化処理関数
	void AttackPatternSelect();                 //攻撃の種類を選択する関数
	void Collision();                           //当たり判定処理関数
	void SpecialAttack();                       //必殺技

	float PopX(); //値を削除
	float PopY(); //値を削除
	float PopZ(); //値を削除

	//static CBoss* Create(D3DXVECTOR3 pos,bool bUse);
	static CBoss* Create(D3DXVECTOR3 pos);

private: //アクセス不可

	int m_nCoolTime; //攻撃終了後次の攻撃に行くまでの時間
	int m_nSize;     //vectorの配列数を取得するための変数

	int m_nWhichSideNumber; //左右のどちらに居るかを数字で渡すための変数
	bool m_bOneCreateFlag;  //衝撃波を１回のみ呼ぶための

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static int MAX_VECTOR_SIZE = 50;                //vector配列の最大数
	constexpr static float MAX_MOVE_SPEED = 0.25f;            //ボスの移動速度を設定
	constexpr static float MAX_MOVE_SPEED_IN_PLAYER = 8.0f;   //プレイヤーに向かう速さ

	//vectorに関する変数
	std::vector<float> m_nSaveData; //配列情報を確保する為の変数
	std::vector<float> m_nDataX;    //X軸用のデータを保管する用の変数
	std::vector<float> m_nDataY;    //Y軸用のデータを保管する用の変数
};
