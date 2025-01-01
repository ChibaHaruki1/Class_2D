//================================================================
//
//ステージ毎のイベント処理クラス[event.h]
//Auther:Haruki Chiba
//
//================================================================

#pragma once

//=====================
//インクルード
#include <vector>
#include "instance.h"

//=====================================================================================================
//eventの基底クラス
//=====================================================================================================
class CEvent
{
public:
	CEvent();                  //デストラクタ
	~CEvent();                 //コンストラクタ
	void Update();             //更新処理
	void DropObj();            //objの落とす処理
	void BossDirection();      //ボスの演出処理	
	void DropMeteorite();      //隕石を落とす処理
	void CreateEnemy();        //敵の生成
	bool& GetBossDirection() { return m_bBossDirection; } //ボスの生成がされているかどうかの情報を取得

private:
	int m_nCreateWoodenBoradsCounter;            //生成する数
	int m_nRandomRotX;                           //向きのランダム数を保管する
	int m_nRandomRotY;                           //向きのランダム数を保管する
	float m_nPosY;                               //生成時のY軸のpos
	float m_fDropSpeed[CInstance::MAX_RUBBLE];   //落とす速度を決める変数
	float m_fDropPosY[CInstance::MAX_RUBBLE];    //落とす位置をあらかじめ決める変数
	bool m_bBossDirection;                       //ボスの演出を1回だけ出すための処理
	bool m_bOneflag;                             //一回だけ処理を通す用の変数
	bool m_bOneCreate;                           //一回だけ生成する用の変数
};
