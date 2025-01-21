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
	SetRandom(1);                                 //乱数の初期化
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
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_TOUCH_DAMAGE; //プレイヤーのHPゲージを減らす
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
		//乱数が０の時
		if (GetRandom() == 0)
		{
			AttackPattern();    //落下攻撃を呼ぶ
		}

		//乱数が１の時
		else if (GetRandom() == 1)
		{
			AttackPattern001(); //炎攻撃を呼ぶ
		}

		//乱数が２の時
		else if (GetRandom() == 2)
		{
			SpecialAttack();    //必殺技を呼ぶ
		}
	}

	//クールタイム中
	else
	{
		//乱数が３の時（全ての攻撃パターンを実行）
		if (GetRandom() == 3)
		{
			//srand((unsigned)time(NULL));  // 乱数系列を初期化
			//SetRandom(rand() % 3);
			SetRandom(0); //乱数を初期化
		}
		m_nCoolTime++;    //クールタイムを増やす
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
	SetAddjustRandom() += 1;                       //乱数を増やす
	m_nCoolTime = 0;                               //クールタイムの初期化
	m_nSize = 0;                                   //vectorの配列数を初期化
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;   //左右のどちらに居るかの初期化
	m_bOneCreateFlag = false;                      //衝撃波を出すフラグの初期化
}

//==============================
//降下攻撃
//==============================
void CBoss::AttackPattern()
{
	SetAddjustFrame()++; //フレームを加算

	//第一行動
	if (GetFrame() <= ATTACKPATTEN1_FRAME_1)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK);                      //モーションの種類を設定
		
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_1);  //プレイヤーに向かうように設定
	}

	//第二行動
	else if (GetFrame()<= ATTACKPATTEN1_FRAME_2)
	{
		SetAddjustRot().y = 0.0f;                                                            //Y軸の向きの初期化
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSIMPACT);                  //モーションの種類を設定
		SetAddjustPos().y += PopY() * MAX_MOVE_SPEED;                                        //Y軸の位置を保管してある値分上に移動
	}

	//第三行動
	else if (GetFrame() <= ATTACKPATTEN1_FRAME_3)
	{
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));     //Y軸用の位置の初期化
	}

	//第四行動
	else if (GetFrame()<= ATTACKPATTEN1_FRAME_4)
	{
		SetAddjustPos().y -= PopY() * MAX_DROP_MOVE_Y_SPEED_1;                                 //Y軸の位置を保管してある値分下に移動
	}

	//衝撃波
	else  if (GetFrame() <= ATTACKPATTEN1_FRAME_5)
	{
		//フラグがoffの時
		if (m_bOneCreateFlag == false)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::IMPACT, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //衝撃波を生成
			CManager::GetInstance()->GetImpact()->SetEffect(GetPos());                                                   //衝撃波エフェクトを呼ぶ

			m_bOneCreateFlag = true; //フラグをOnにして通らなくする
		}
	}

	//終了
	else
	{
		SetAddjustPos().y = 0.0f; //Y軸の位置を初期化
		SetAddjustRot().y = 0.0f; //Y軸の向きを初期化
		StatusInit();             //初期化
	}
}

//==============================
//炎攻撃
//==============================
void CBoss::AttackPattern001()
{
	SetAddjustFrame()++; //フレーム加算

	//第一行動
	if (GetFrame() <= ATTACKPATTEN2_FRAME)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK);                       //モーションの種類を設定
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_2);   //プレイヤーに向かうように設定
	}

	//第二行動
	else if (GetFrame() <= ATTACKPATTEN2_FRAME*3)
	{
		SetAddjustRot().y = 0.0f;                                           //Y軸の向きを初期化
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSATTACK); //モーションの種類を設定
		SetAddjustPos().y += PopY() * MAX_DROP_MOVE_Y_SPEED_2;              //Y軸の位置を保管してある値分上に移動     
	}

	//第三行動
	else if (GetFrame() <= ATTACKPATTEN2_FRAME*3+1)
	{
		//弾の生成(弾にエフェクトを呼ぶ処理がついているためエフェクトを変更したい時は弾の処理をいじる)
		CManagerBullet::Create(D3DXVECTOR3(GetPosPrtsBoss(17).x+100.0f, GetPosPrtsBoss(17).y-150.0f, GetPosPrtsBoss(17).z), D3DXVECTOR3(-sinf(GetRot().y) * 0, 0.0f, -cosf(GetRot().y) * 0), CManagerBullet::SET_BULLET_LIFE,CObject3D::TYPE::BOSSBULLET);
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));      //ｘ軸用の位置の初期化
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX));      //ｘ軸用の位置の初期化
	}

	//第四行動
	else if (GetFrame() <= ATTACKPATTEN2_FRAME*4)
	{
		SetAddjustPos().y -= PopY() * MAX_DROP_MOVE_Y_SPEED_2; //Y軸の位置を保管してある値分下に移動 

		//左にいる時
		if (m_nWhichSideNumber == WICHI_SIDE_LEFT_NUMBER)
		{
			SetAddjustRot().y = D3DX_PI_ORI;                     //Y軸の向きを設定
			SetAddjustMove().x -= PopX() * MAX_MOVE_SPEED_SIDE;  //Y軸の移動量を減算設定
		}

		//右にいる時
		else if (m_nWhichSideNumber == WICHI_SIDE_RIGHT_NUMBER)
		{
			SetAddjustRot().y = -D3DX_PI_ORI;                    //Y軸の向きを設定
			SetAddjustMove().x += PopX() * MAX_MOVE_SPEED_SIDE;  //Y軸の移動量を加算設定
		}
	}

    //終了
	else
	{
		SetAddjustPos().y = 0.0f; //Y軸の位置を初期化
		SetAddjustRot().y = 0.0f; //Y軸の向きを初期化
		StatusInit();             //初期化
	}
}

//=======================================================================================================================================================
//必殺技の処理
//=======================================================================================================================================================
void CBoss::SpecialAttack()
{
	SetAddjustFrame()++; //フレーム加算

	//第一行動
	if (GetFrame() <= ATTACKPATTEN3_FRAME_1)
	{
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 10.0f);    //プレイヤーに向かうように設定
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSACTION); //モーションの種類を設定
	}

	//第二行動
	else if (GetFrame() <= ATTACKPATTEN3_FRAME_2)
	{

	}

	//第三行動
	else if (GetFrame() <= ATTACKPATTEN3_FRAME_3)
	{
		//生成フラグがOffの時
		if (m_bOneCreateFlag == false)
		{
			//必殺技のエフェクトの生成
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::BOSSSPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); 

			//向きの条件式
			if (GetRot().y >= D3DX_PI_ORI)
			{
				//サイズの設定用の番号を渡す
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(2);

				//位置を銃に設定
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3
				(
					GetPosPrtsBoss(17).x,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));

			}

			//向きの条件式
			else if (GetRot().y <= -D3DX_PI_ORI)
			{
				//サイズの設定用の番号を渡す
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(1);                                        

				//位置を銃に設定
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPrtsBoss(17).x +300.0f ,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));
			}

			m_bOneCreateFlag = true; //生成フラグOnにする
		}
	}

	//終了
	else if(CManager::GetInstance()->GetBossSpecialAttack()->GetAlpha()<=0)
	{
		SetAddjustPos().y = 0.0f; //Y軸の位置を初期化
		SetAddjustRot().y = 0.0f; //Y軸の向きを初期化
		StatusInit();             //初期化
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
	int nSize = m_nDataX.size() - 1;        //サイズの設定

	//大きさが０以上の時
	if (nSize > 0)
	{
		nSize--;                            //大きさを減らす
		m_nDataX.erase(m_nDataX.end() - 1); //それぞれの配列のX軸の値を返す
		return m_nDataX[nSize];             //情報を返す
	}

	return 0;                               //０を返す
}

//============================
//スタックのY値を削除
//============================
float CBoss::PopY()
{
	int nSize = m_nDataY.size() - 1;        //サイズの設定

	//サイズが０以上の時
	if (nSize > 0)
	{
		nSize--;                            //サイズを減らす
		m_nDataY.erase(m_nDataY.end() - 1); //それぞれの配列のX軸の値を返す
		return m_nDataY[nSize];             //情報を返す
	}

	return 0;                               //０を返す
}

//========================
//描画処理
//========================
void CBoss::Draw()
{
	CCharacter::DrawBoss(MAX_BOSSPARTS); //パーツごとの描画処理
}

//========================
//生成処理
//========================
CBoss* CBoss::Create(D3DXVECTOR3 pos)
{
	CBoss* pBoss = new CBoss(3); //動的確保

	//初期化が成功した時
	if (SUCCEEDED(pBoss->Init()))
	{
		pBoss->SetPos(pos); //位置を引数と同期させる
		return pBoss;       //プレイヤーの情報を返す
	}

	return nullptr;             //無を返す
}