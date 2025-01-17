//=====================================
//
//ボスの処理[boss.cpp]
//Auther:Haruki Chiba
//
//=====================================


//=====================================
//インクルード
#include "boss.h"
#include "manager.h"
#include <time.h>
#include <iostream>


//========================
//コンストラクタ
//========================
CBoss::CBoss(int nPriority) : CCharacter(nPriority)
{
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::BOSSHP, 0); //ボスのHPゲージの生成
	
	m_nCoolTime = 0;                              //クールタイムの初期化
	SetRandom(-1);                                //乱数の初期化
	m_nSize = 0;                                  //配列数の初期化
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;  //どちらにいるかの初期化

	m_nSaveData.clear();                          //保管用ベクターの初期化
	m_nDataX.clear();                             //ｘ軸の位置の初期化
	m_nDataY.clear();                             //ｙ軸の位置の初期化
							                      
	m_bOneCreateFlag = false;                     //生成フラグの初期化
}

//========================
//デストラクタ
//========================
CBoss::~CBoss()
{
	//保管用ベクターの破棄
	m_nSaveData.clear();         //情報を消す
	m_nSaveData.shrink_to_fit(); //情報を無くす

	//X軸用のベクターの破棄
	m_nDataX.clear();            //情報を消す
	m_nDataX.shrink_to_fit();    //情報を無くす

	//Y軸用のベクターの破棄
	m_nDataY.clear();            //情報を消す
	m_nDataY.shrink_to_fit();    //情報を無くす
}


//========================
//初期化処理
//========================
HRESULT CBoss::Init()
{
	//ベクターの最大数分回す
	for (int nCount = 0; nCount < MAX_VECTOR_SIZE; nCount++)
	{
		m_nSaveData.push_back((float)nCount); //nCountをfloat型にcastして代入する
	}

	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //X軸用の変数に代入
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //Y軸用の変数に代入

	CCharacter::Init();                       //初期化
	CCharacter::LoodBoss();                   //ｘファイルの読み込み
	CCharacter::SetMotionBoss(BOSSJUMP);      //モーションの初期設定
	return S_OK;                              //成功を返す
}


//========================
//破棄処理
//========================
void CBoss::Uninit()
{
	CCharacter::Uninit();  //破棄処理
}


//========================
//更新処理
//========================
void CBoss::Update()
{
	CCharacter::UpdateBoss();    //モーションの情報を更新する

	//ボスが生きている時
	if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() > 0)
	{
		Collision();             //左右どちらにいるか処理している関数を呼ぶ
		AttackPatternSelect();   //攻撃の種類を選択する関数を呼ぶ
	}

	//ボスが死んだ時
	else if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() <= 0)
	{
		SetAddjustDieFrame()++;                                                     //死亡カウントを増やす
		SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSDIE);                        //モーションの種類を設定
		CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::BOSS, 0);  //ボスの（自身）インスタンスの情報を無くす

		//frameが規定値以上の時
		if (GetDieFrame() >= DIE_FRAME)
		{
			CManager::SetMode(CScene::MODE::MODE_RESULT); //リザルトへ移行
		}
	}

	CObjectX::Update();      //基底クラスの基底クラスでm_moveを更新
}


//====================================================================
//当たり判定で左右のどちらにいるか判定する関数
//====================================================================
void CBoss::Collision()
{
	//右側にいる時
	if (CollisionRightSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//左右ナンバーがー１の時
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_RIGHT_NUMBER; //番号を設定
		}
	}

	//左側にいる時
	else if (CollisionLeftSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//左右ナンバーがー１の時
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_LEFT_NUMBER; //番号を設定
		}
	}

	//ボスに当たった時
	if (CollisionBossPrts() == true)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += 100.0f;
	}
}


//==============================
//攻撃の種類を選択する処理
//==============================
void CBoss::AttackPatternSelect()
{
	//攻撃のクールタイムが過ぎた時
	if (m_nCoolTime >= 120)
	{
		if (GetRandom() == 0)
		{
			AttackPattern();
		}
		else if (GetRandom() == 1)
		{
			AttackPattern001();
		}
		else if (GetRandom() == 2)
		{
			SpecialAttack();
		}
	}
	//クールタイム中
	else
	{
		//乱数の生成
		if (GetRandom() == -1)
		{
			//srand((unsigned)time(NULL));  // 乱数系列を初期化
			//SetRandom(rand() % 3);
			SetRandom(1);
		}
		m_nCoolTime++;
	}
}

//==============================
//行動にまつわる物の初期化
//==============================
void CBoss::StatusInit()
{
	CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSNEUTRAL); //モーションの種類を設定

	//vectorの初期化
	m_nDataX.clear();          //中身の全削除
	m_nDataX.shrink_to_fit();  //キャパシティの削除（初期化）

	m_nDataY.clear();          //中身の全削除
	m_nDataY.shrink_to_fit();  //キャパシティの削除（初期化）

	//vectorの値取得（コピー）
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //ｘ軸用の位置の初期化
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //ｙ軸用の位置の初期化

	//メンバ変数の初期化
	SetFrame(0);                                   //フレームの初期化
	m_nCoolTime = 0;                               //クールタイムの初期化
	SetRandom(-1);                                 //ランダム数の初期化
	m_nSize = 0;                                   //vectorの配列数を初期化
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;   //左右のどちらに居るかの初期化
	m_bOneCreateFlag = false;                      //衝撃波を出すフラグの初期化
}


//==============================
//降下攻撃
//==============================
void CBoss::AttackPattern()
{
	GetFrame()++; //フレーム加算

	//第一行動
	if (GetFrame() <= 30)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK); //モーションの種類を設定
		
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 12.0f);  //プレイヤーに向かうように設定
	}

	else if (GetFrame()<=140)
	{
		GetRot().y = 0.0f;                                                     //向きの初期化
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSIMPACT); //モーションの種類を設定
		GetPos().y += PopY() * MAX_MOVE_SPEED;                                 //上に移動
	}

	else if (GetFrame() <= 141)
	{
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));//Y軸用の位置の初期化
	}

	else if (GetFrame()<=170)
	{
		GetPos().y -= PopY() * MAX_MOVE_SPEED * 1.2f;                                      //下に移動
	}

	//衝撃波
	else  if (GetFrame() <=180)
	{
		//フラグがoffの時
		if (m_bOneCreateFlag == false)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::IMPACT, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //衝撃波を生成
			CManager::GetInstance()->GetImpact()->SetEffect(GetPos());                                                //衝撃波エフェクトを呼ぶ

			m_bOneCreateFlag = true; //フラグをOnにして通らなくする
		}
	}

	//向きを修正
	else if (GetFrame() <= 300)
	{
		GetRot().y = -1.57f; //向きを戻す
	}

	//終了
	else
	{
		GetRot().y = 0.0f; //位置を初期化
		GetPos().y = 0.0f; //位置を初期化
		StatusInit();   //初期化
	}
}

//==============================
//炎攻撃
//==============================
void CBoss::AttackPattern001()
{
	GetFrame()++; //フレーム加算

	//第一行動
	if (GetFrame() <= 40)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK); //モーションの種類を設定
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 8.0f);  //プレイヤーに向かうように設定
	}

	//第二行動
	else if (GetFrame() <= 120)
	{
		if (GetRot().y >= 0.0f)
		{
			GetRot().y -= 0.1f;
		}
	}

	//第三行動
	else if (GetFrame() <= 200)
	{
		GetRot().y = 0.0f;
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSATTACK); //モーションの種類を設定
		GetPos().y += PopY() * 0.25f;
	}

	else if (GetFrame() <= 201)
	{
		CManagerBullet::Create(D3DXVECTOR3(GetPosPrtsBoss(17).x+100.0f, GetPosPrtsBoss(17).y-150.0f, GetPosPrtsBoss(17).z), D3DXVECTOR3(-sinf(GetRot().y) * 0, 0.0f, -cosf(GetRot().y) * 0), CManagerBullet::SET_BULLET_LIFE,CObject3D::TYPE::BOSSBULLET); //正面
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));      //ｘ軸用の位置の初期化
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX));      //ｘ軸用の位置の初期化
	}

	//第四行動
	else if (GetFrame() <= 240)
	{
		GetPos().y -= PopY() * 0.25f;

		if (m_nWhichSideNumber == WICHI_SIDE_LEFT_NUMBER)
		{
			GetRot().y = 1.57f;
			GetMove().x -= PopX() *0.1f;
		}
		else if (m_nWhichSideNumber == WICHI_SIDE_RIGHT_NUMBER)
		{
			GetRot().y = -1.57f;
			GetMove().x += PopX() * 0.1f;
		}
	}

    //終了
	else
	{
		GetRot().y = 0.0f;
		GetPos().y = 0.0f;
		StatusInit(); //初期化
	}
}


//=======================================================================================================================================================
//必殺技の処理
//=======================================================================================================================================================
void CBoss::SpecialAttack()
{
	GetFrame()++; //フレーム加算

	if (GetFrame() <= 10)
	{
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 10.0f);  //プレイヤーに向かうように設定
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSACTION); //モーションの種類を設定
	}

	else if (GetFrame() <= 60)
	{

	}

	else if (GetFrame() <= 61)
	{
		if (m_bOneCreateFlag == false)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::BOSSSPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //必殺技のエフェクトの生成

			if (GetRot().y >= D3DX_PI_ORI)
			{
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(2);                                           //サイズの設定用の番号を渡す
				//位置を銃に設定
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPrtsBoss(17).x,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));

			}
			else if (GetRot().y <= -D3DX_PI_ORI)
			{
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(1);                                           //サイズの設定用の番号を渡す

				//位置を銃に設定
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPrtsBoss(17).x +300.0f ,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));
			}
			m_bOneCreateFlag = true;
		}
	}
	else if (GetFrame() <= 220)
	{

	}
	//終了
	else
	{
		GetRot().y = 0.0f;
		GetPos().y = 0.0f;
		StatusInit(); //初期化
	}
}


//=======================================================================================================================================================
//  スタック構造の処理
//=======================================================================================================================================================

//============================
//スタックのX値を削除
//============================
float CBoss::PopX()
{
	if (m_nSize == 0)
	{
		m_nSize = m_nDataX.size() - 1;
	}

	else if (m_nSize > 0)
	{
		m_nSize--;
		m_nDataX.erase(m_nDataX.end() - 1); //それぞれの配列のX軸の値を返す
		return m_nDataX[m_nSize];
	}
	return 0;
}


//============================
//スタックのY値を削除
//============================
float CBoss::PopY()
{
	int Number = m_nDataY.size() - 1;

	if (Number > 0)
	{
		Number--;
		m_nDataY.erase(m_nDataY.end() - 1); //それぞれの配列のX軸の値を返す
		return m_nDataY[Number];
	}
	return 0;
}


//========================
//描画処理
//========================
void CBoss::Draw()
{
	CCharacter::DrawBoss(MAX_BOSSPARTS);
}


//========================
//生成処理
//========================
CBoss* CBoss::Create(D3DXVECTOR3 pos )
{
	CBoss* pBoss = new CBoss(3); //動的確保
	//pBoss->m_bUse = bUse;
	if (SUCCEEDED(pBoss->Init()))
	{
		if (pBoss != nullptr)
		{
			pBoss->GetPos() = pos;
			//pBoss->SetType(BOSS); //タイプをPLAYERに設定
			return pBoss; //プレイヤーの情報を返す
		}
	}

	return nullptr; //情報なし
}