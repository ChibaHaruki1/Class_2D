//====================================================
//
//ステージ毎のevent処理をする[enent.cpp]
//Auther:Haruki Chiba
//
//====================================================

//インクルード
#include "event.h"
#include "manager.h"
#include <time.h>


//============================
//コンストラクタ
//============================
CEvent::CEvent()
{
	//生成できる最大数分回す
	for (int nCount = 0; nCount < CInstance::MAX_RUBBLE; nCount++)
	{
		m_fDropSpeed[nCount] = 0.0f;                //落とすスピードの初期化
		m_fDropPosY[nCount] = (float)(nCount * 15); //落とす位置をどんどん高くする（積みあがらせる為）
	}

	m_nCreateWoodenBoradsCounter = 0;       //生成した数の初期化
	m_nRandomRotX = 0;                      //ｘ軸の向きの乱数の初期化
	m_nRandomRotY = 0;                      //ｙ軸の向きの乱数の初期化
	m_nPosY = 300.0f;                       //生成するY軸のposの初期化
	m_bOneflag = false;                     //一回だけ通すフラグの初期化（使われてない）
	m_bBossDirection = false;               //ボス演出を一回だけするフラグの初期化（使われてない）
	m_bOneCreate = false;

	mciSendStringA("open data\\BGM\\Bossbgm-Short.wav alias BGM", NULL, 0, NULL); //設定した音源を開く（再生は別）
}


//============================
//デストラクタ
//============================
CEvent::~CEvent()
{
	mciSendStringA("close BGM", NULL, 0, NULL); //設定した音源を閉じる
}


//============================
//更新処理
//============================
void CEvent::Update()
{
	//現在の生成数が最大数よりすくない時
	if (m_nCreateWoodenBoradsCounter < CInstance::MAX_RUBBLE)
	{
		BossDirection();  //ボス線の演出処理を呼ぶ
	}

	//木の板群が生成された時
	if (CManager::GetInstance()->GetWoodenBoardCount() > 0)
	{
		//まだ全て落ち切ってない時
		if (m_bOneflag == false)
		{
			DropObj();  //木の板群を落とす処理を呼ぶ
		}

		//木の板群を生成した数分回す
		for (int a = 0; a < m_nCreateWoodenBoradsCounter; a++)
		{
			//プレイヤーと木の板の当たり判定
			if (CManager::GetScene()->GetPlayerX()->CollisionPlayerSelect(CManager::GetInstance()->GetWoodenBoard(a)))
			{
				//Aキーが押された時
				if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
				{
					CManager::GetScene()->GetPlayerX()->GetMove().x += CPlayerX::MAX_MOVESPEED; //プレイヤーを逆側へ押し出す
				}
			}
		}
	}
	//CreateEnemy();

}


//============================
//プレイヤーの必殺技
//============================
void CEvent::BossDirection()
{
	//プレイヤーが生成されていた時
	if (CManager::GetScene()->GetPlayerX() != nullptr)
	{
		//プレイヤーのposが既定の場所へ行った時
		if (CManager::GetScene()->GetPlayerX()->GetPos().x >= 3450)
		{
			//ボスの演出がまだの時
			if (m_bBossDirection == false)
			{
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BOSS, 0, D3DXVECTOR3(4500.0f, 0.0f, 0.0f)); //ボスを生成
				CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);                                //指定の音源を止める
				mciSendStringA("play BGM", NULL, 0, NULL);                                                              //開かれた音源を再生する（開かれてないと生成しない）         
				m_bBossDirection = true;                                                                                //演出フラグをtrueにし、通らなくする
			}

			//カメラの位置を変更
			CManager::GetScene()->GetCamera()->GetAdjustmentPosZ() = 1400; //カメラのＺ軸の値を設定
			CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = 400.0f;        //カメラのＹ軸の値を設定

			m_nPosY += 10.0f;             //落とす位置を増やす
			m_nRandomRotY = rand() % 31;  //Ｙ軸の向きを乱数で調整
			m_nRandomRotX = rand() % 15;  //Ｘ軸の向きを乱数で調整

			CManager::GetInstance()->CreateRubble(CObjectX::STRATEGYTYPE::WODDENBORAD, D3DXVECTOR3(3250.0f, m_nPosY, 0.0f));   //木の板群を出す
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().y = (float)m_nRandomRotY * 0.1f;               //Ｙ軸の向きを設定
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().x = (float)m_nRandomRotX * 0.1f;               //Ｘ軸の向きを設定
			m_nCreateWoodenBoradsCounter++; //配列カウントを進める
		}
	}
}


//============================
//落とす処理
//============================
void CEvent::DropObj()
{
	//木の板群が生成された数分回す
	for (int nCount = 0; nCount < m_nCreateWoodenBoradsCounter; nCount++)
	{
		//生成した木の板群の位置が設定した位置より大きい（同じ）時
		if (CManager::GetInstance()->GetWoodenBoard(nCount)->GetPos().y >= m_fDropPosY[nCount])
		{
			m_fDropSpeed[nCount] += 0.07f;                                                         //落とす速度を増やす
			CManager::GetInstance()->GetWoodenBoard(nCount)->GetMove().y -= m_fDropSpeed[nCount];  //木の板群を落とす
		}

		//生成した木の板群の位置が設定した位置より小さい時
		else
		{
			//for分のカウントが最大数分行った時
			if (nCount == CInstance::MAX_RUBBLE - 1)
			{
				m_bOneflag = true; //フラグをONにする
			}
		}
	}
}


//============================
//隕石を落とす処理
//============================
void CEvent::DropMeteorite()
{

}


//================================
//モーション付きの敵の生成処理
//================================
void CEvent::CreateEnemy()
{
	if (CManager::GetScene()->GetPlayerX()->GetPos().x >= 9500.0f)
	{
		if (m_bOneCreate == false)
		{
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(9500.0f, 5000.0f, 0.0f));     //モーション付きの敵の生成
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(10000.0f, 5000.0f, 0.0f));    //モーション付きの敵の生成
			m_bOneCreate = true;
		}
	}
}