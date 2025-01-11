//===================================
//
//モデルの設定をする処理[player.cpp]
//Author:chiba haruki
//
//===================================

//===================================
//インクルード
#include "main.h"
#include "player.x.h"
#include "rendererh.h"
#include "manager.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"
#include <time.h>
#include "DxLib.h"


//===================
//コンストラクタ
//===================
CPlayerX::CPlayerX(int nPriority) : CCharacter(nPriority)
{
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0); //プレイヤーのHPゲージの生成
	SetJumpFlag(false); //飛んでいないに設定
	SetGravity(0.0f);

	//テキストファイルに登録する時の葉配列番号の初期化
	m_nFiledCount = -1;
	m_nTelephonCount = -1;

	//テキストファイルに登録するした全ての配列番号の初期化
	m_nAllTelephonPoleCount = -1;
	m_nAllFiledCount = -1;

	m_ObjectNumber = 0;
	m_pMenyu = nullptr;
	m_pLaserUI = nullptr;

	m_nFrame = 0;
	m_nPraticlesCount = 0;
	SetRandom(0);
	m_nRandomCol = 0;            //乱数を保管する為の変数
	SetDieFrame(0);

	m_pTalkText = nullptr;
	m_pBuyText = nullptr;
	m_nSelectShopCount = 0;     //SHOPで選んでいる物
	m_nBuyOrSendCount = 0;
	m_pSelectGage = nullptr;
	m_pSelectGage001 = nullptr;
	SpecialAttack = false;
	m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;
	m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;
	m_nAlpha = 255;

	m_nMotionFrame = 0;
	m_nMotionFrame001 = 0;
	m_bNextStage = false;

	//吹っ飛ぶ処理の初期化
	m_nFlayFrame = 0;
	m_bFly = false;

	m_nDieRandom = 0;
	m_nRotNumber = 0;
	m_nSpecialAttackCount = 0;
	m_bOneCreate = false;
}


//===================
//デストラクタ
//===================
CPlayerX::~CPlayerX()
{
	//mciSendStringA("close BGM", NULL, 0, NULL);
}


//====================
//初期化処理
//====================
HRESULT CPlayerX::Init()
{
	CCharacter::Init();                                                       //初期化処理を呼ぶ
	CCharacter::Lood();                                                       //テキストファイルを読み込む処理
	CCharacter::SetMotion(WALK);                                              //モーションの設定
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));                         //向きの調整（右向き）
	m_pModelPrts[18]->m_bCreateGun = false;                                   //パーツの銃部分を非表示に設定
	SetPos(D3DXVECTOR3(3000.0f,0.0f,0.0f));                                   //位置の調整
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BGM1);  //BDMを流す
	SetLife(1);                                                               //自身のライフ
	return S_OK;                                                              //成功を返す
}

//==================
//終了処理
//=================
void CPlayerX::Uninit()
{
	//instance情報を消す
	InstanceMakeNull();

	CCharacter::Uninit(); //パーツごとの破棄処理
}

//===============================================================================================================================================================================
//instanceをnullptrにする
//===============================================================================================================================================================================
void CPlayerX::InstanceMakeNull()
{
	m_pTalkText = nullptr;      //話すテキストの情報を無くす
						        
	m_pMenyu = nullptr;         //武器の選択メニューの情報を無くす
						        
	m_pBuyText = nullptr;       //買う売るテキストの情報を無くす
							    
	m_pSelectGage = nullptr;    //選択ゲージの情報を無くす

	m_pSelectGage001 = nullptr; //選択ゲージ001の情報をなくす
}

//
//
//
void CPlayerX::ShopInstanceMakeNullptr()
{
	if (m_pSelectGage != nullptr)
	{
		m_pSelectGage->Release();
		m_pSelectGage = nullptr;
	}

	if (m_pSelectGage001 != nullptr)
	{
		m_pSelectGage001->Release();
		m_pSelectGage001 = nullptr;
	}

	if (m_pBuyText != nullptr)
	{
		m_pBuyText->Release();
		m_pBuyText = nullptr;
	}

	if (m_pMenyu != nullptr)
	{
		m_pMenyu->Release();
		m_pMenyu = nullptr;
	}

	if (CManager::GetInstance()->GetShopScreen() != nullptr)
	{
		CManager::GetInstance()->GetShopScreen()->Release();
		CManager::GetInstance()->DesignationUninit2D(CObject2D::TYPE::SCREEN);
	}
}


//===============================================================================================================================================================================
//更新処理
//===============================================================================================================================================================================
void CPlayerX::Update()
{
	//生きている時
	if (GetLife() == 1)
	{
		if (CManager::GetScene()->GetPlayerX()->GetPos().x >= 9000.0f)
		{
			if (m_bOneCreate == false)
			{
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(9500.0f, 4500.0f, 0.0f));    //モーション付きの敵の生成
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(12000.0f, 1500.0f, 0.0f));    //モーション付きの敵の生成
				m_bOneCreate = true;
			}
		}

		CCharacter::UpdatePlayer();  //モーションの更新
		HitAttack();                 //特定の攻撃を受けた時の処理関数を呼ぶ

		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			m_nSpecialAttackCount++;
		}

		//次のsceneに行くフラグがOnの時
		if (m_bNextStage == true)
		{
			SceneMode(1); //sceneの切り替え
			return;		  //処理を抜ける
		}

		//ゲージのmanagerが生成されていた時
		if (CManager::GetInstance()->GetPlayerHPGage() != nullptr)
		{
			//HPゲージが０以下の時
			if (CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() <= 0)
			{
				CManager::GetInstance()->GetPlayerHPGage()->GetSaveSizeX() = 0.0f;
				SetLife(0); //ライフを０に設定で死亡判定にする
			}
		}

		//何もしていない時
		if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
		{
			NormalStateSummarizeFunction(); //専用の処理を呼ぶ
		}

		//SHOPで買い物をしている時
		else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE || m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
		{
			ShopStateSummarizeFunction();   //専用の処理を呼ぶ
		}

		CObjectX::Update(); //基底クラスの基底クラスの更新処理を呼ぶ
	}

	//死んだ時
	else if (GetLife() == 0)
	{
		GetDieFrame()++;                //死亡フレームを増やす
		GetPos().y = -50.0f;             //位置を低くする
		srand((unsigned)time(NULL));  //乱数系列を初期化

		//乱数が入ってない時
		if (m_nDieRandom == 0)
		{
			m_nDieRandom = -1 + rand() % 3; //乱数を入れる
		}
		m_pModelPrts[0]->m_pos += D3DXVECTOR3(GetDieFrame() * 0.1f * m_nDieRandom, 0.0f, GetDieFrame() * 0.1f * m_nDieRandom);

		CCharacter::Update();  //基底クラスの更新処理を呼ぶ
		SetMotion(DIE);        //モーションを死亡に設定する

		//１秒*指定秒
		if (GetDieFrame() >= 60 * 3)
		{
			SceneMode(3); //シーンの設定
			return;       //処理を抜ける
		}
	}
	SceneMode(2);         //シーンを選択
}


//==================================================================================================================================================
//吹っ飛び処理
//==================================================================================================================================================
void CPlayerX::BlowAway()
{
	m_nFlayFrame++;
	CCharacter::SetMotion(BLOWAWAY);

	if (m_nFlayFrame <= 40)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += 20.0f;
		CManager::GetScene()->GetPlayerX()->GetPos().y += 30.0f;
	}
	else if (m_nFlayFrame <= 90)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().y += 10.0f;
		CManager::GetScene()->GetPlayerX()->GetPos().x += 20.0f;
	}
	else
	{
		
		m_bFly = false;
		m_nFlayFrame = 0;
	}
}


//==================================================================================================================================================
//特定の攻撃を受けた時の処理
//==================================================================================================================================================
void CPlayerX::HitAttack()
{
	//衝撃破エフェクトのインスタンス情報がある時
	if (CManager::GetInstance()->GetImpact() != nullptr)
	{
		//当たったフラグがONの時
		if (CManager::GetInstance()->GetImpact()->GetFly() == true)
		{
			m_bFly = true; //飛ぶ
		}
	}

	//飛ぶフラグがONの時
	if (m_bFly == true)
	{
		BlowAway();  //吹っ飛び処理を呼ぶ
	}
}


//==================================================================================================================================================
//次のscene処理
//==================================================================================================================================================
void CPlayerX::SceneMode(int nType)
{
	//次のステージに行く用（ゲームループ）
	if (nType == 1)
	{
		m_bNextStage = false;
		switch (CManager::GetScene()->GetMode())
		{
		case CScene::MODE_GAME01:
			CManager::SetMode(CScene::MODE_GAME02); //画面遷移
			return; //処理を抜ける

		case CScene::MODE_GAME02:
			CManager::SetMode(CScene::MODE_RESULT); //画面遷移
			return; //処理を抜ける
		}
	}

	//デバック用
	else if (nType == 2)
	{
		//Enterキーが押された時（デバック用）
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true)
		{
			m_bNextStage = false;
			switch (CManager::GetScene()->GetMode())
			{
			case CScene::MODE_GAME01:
				CManager::SetMode(CScene::MODE_GAME02); //画面遷移
				return; //処理を抜ける

			case CScene::MODE_GAME02:
				CManager::SetMode(CScene::MODE_RESULT); //画面遷移
				return; //処理を抜ける
			}
		}
	}

	//死亡した時用
	else if (nType == 3)
	{
		m_bNextStage = false;
		CManager::SetMode(CScene::MODE_GAMEOVER); //画面遷移
		return; //処理を抜ける
	}
}


//===============================================================================================================================================================================
//通常状態時の関数をまとめる関数処理
//===============================================================================================================================================================================
void CPlayerX::NormalStateSummarizeFunction()
{
	if (m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
	{
		Praticles();        //パーティクルの生成処理関数を呼ぶ

		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_CHAGE); //BDMを流す
		}
	}
	BlockJudgement();   //オブジェクトとの当たり判定処理関数を呼ぶ

	if (SpecialAttack == false)
	{
		KeySet();           //キーごとの処理関数を呼ぶ
	}
	else
	{
		if (m_nMotionFrame >= 0)
		{
			m_nMotionFrame--;
		}

		if (m_nMotionFrame001 >= 0)
		{
			m_nMotionFrame001--;
		}

		else if(m_nMotionFrame<=0&& m_nMotionFrame001<=0)
		{
			SpecialAttack = false;
		}
	}
	Junp(TYPE::PLAYER, 10.0f);             //ジャンプと重力処理関数を呼ぶ
}


//===============================================================================================================================================================================
//買い物時の関数をまとめる関数処理
//===============================================================================================================================================================================
void CPlayerX::ShopStateSummarizeFunction()
{
	BlockJudgement();
	ShopKeySet();            //キーごとの処理
}


//===============================================================================================================================================================================
//ランダム処理
//===============================================================================================================================================================================
void CPlayerX::Random()
{
	//最小値＋rand()%最小値から何個分増やすか　（５だったら％６だったら　５、６、７、８、９、１０の合計６個になる）
	SetRandom(-50 + rand() % 100); //４～６の数値を出す（範囲指定）
	m_nRandomCol = rand() % 255; //４～６の数値を出す（範囲指定）
}


//===============================================================================================================================================================================
//パーティクルを出す処理
//===============================================================================================================================================================================
void CPlayerX::Praticles()
{
	Random();            //ランダム処理を呼ぶ
	m_nFrame++;       //フレームを加算させていく

	//フレームが既定の数値まで行った時
	if (m_nFrame >= 4)
	{
		m_nFrame = 0; //フレームを初期化する

		//配列の最大数か最大数より下分回す
		if (m_nPraticlesCount >= 0 && m_nPraticlesCount <= CInstance::MAX_OBJECT_DATA - 1)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)GetPos().x + GetRandom(), GetPos().y+50.0f, 0.0f)); //パーティクルの生成処理
			CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, 0, 0, m_nAlpha);
			m_nPraticlesCount++; //配列を進める
		}

		//最大数に突入
		else
		{
			CManager::GetInstance()->DesignationUninit(8);
			m_nPraticlesCount = 0; //配列カウントを初期化する
		}
	}
}


//===============================================================================================================================================================================
//電柱の配置処理
//===============================================================================================================================================================================
void CPlayerX::ObjectArrangementTelephonPole()
{
	ObjectArrangement(CObjectX::TYPE::TELEPHONPOLE,m_pLaserUI);
}



//===============================================================================================================================================================================
//キーごとの処理をまとめる関数
//===============================================================================================================================================================================
void CPlayerX::KeySet()
{
	//必殺技の発動
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_K) == true|| CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_RB)==true)
	{
		//武器が買われた時
		if (m_pModelPrts[18]->m_bCreateGun == true&& m_nSpecialAttackCount>= MAX_SPECIALATTACKCOUNT)
		{
			SpecialAttack = true;      
			m_nSpecialAttackCount = 0;
			//右向きの時
			if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //必殺技のエフェクトの生成
				m_nMotionFrame = CManager::GetInstance()->GetSpecialAttack()->GetLife();                                       //モーションのライフを同期させる
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = 1;                                               //サイズの設定用の番号を渡す
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(GetPosPrts(17).x + 220.0f,                   //エフェクトの出す位置を設定
					GetPosPrts(17).y, GetPosPrts(17).z));
			}

			//左向きの時
			else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI / 2)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //必殺技のエフェクトの生成
				m_nMotionFrame001 = CManager::GetInstance()->GetSpecialAttack()->GetLife();                                    //モーションのライフを同期させる
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = 2;											   //サイズの設定用の番号を渡す
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(GetPosPrts(17).x - 50.0f, 				   //エフェクトの出す位置を設定
					GetPosPrts(17).y, GetPosPrts(17).z));
			}
		}
	}

	//Aキーが押された時（押され続けた時）
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_LEFT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI / 2; //カメラの向きに合わせて向く
		GetMove().x -= sinf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		GetMove().z -= cosf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		m_nRotNumber = 1;
		//撃ってない時
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //歩きモーション
		}
	}

	//Dキーが押された時（押され続けた時）
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_RIGHT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2; //カメラの向きに合わせて向く
		GetMove().x += sinf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		GetMove().z += cosf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		m_nRotNumber = 2;
		//撃ってない時
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //歩きモーション
		}
	}

	//その他
	else
	{
		//撃ってない時と吹っ飛んでない時
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0 && m_bFly == false)
		{
			SpecialAttack = false;
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::NEUTRAL); //待機モーション
		}
	}

	//spaceキーを押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_SPACE) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
	{
		CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_SHOT); //BDMを流す
		if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2)
		{
			m_nMotionFrame = 60;
			CManagerBullet::Create(D3DXVECTOR3(GetPosPrts(17).x + 240.0f, GetPosPrts(17).y, GetPosPrts(17).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, 0.0f), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //正面
		}

		else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI / 2)
		{
			m_nMotionFrame001 = 60;
			CManagerBullet::Create(D3DXVECTOR3(GetPosPrts(17).x - 50.0f, GetPosPrts(17).y, GetPosPrts(17).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, -cosf(GetRot().y) * MAX_BUULET_SPEED), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //正面
		}
	}

	//XキーかAボタンが押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_X) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetJumpFlag(true); //飛んでいるに設定
		CManager::GetInstance()->GetFuelGage()->GetUse()= true;
	}

	//キーが押されてなく、ジャンプをしている時
	else if (GetJumpFlag() == true)
	{
		if (CManager::GetInstance()->GetFuelGage() != nullptr)
		{
			if (CManager::GetInstance()->GetFuelGage()->GetSizeY() > 0.0f && CManager::GetInstance()->GetFuelGage()->GetUse() == true)
			{
				//Xキーが押された時
				if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_X) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
				{
					GetMove().y += 1.0f;
					SetGravityFlag(false);//重力OFF

					if (GetGravity() > 1.0f)
					{
						SetGravity(1.0f);
					}
				}
				else
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false;
					SetGravityFlag(true);//重力ON
				}
			}
			else if (CManager::GetInstance()->GetFuelGage()->GetSizeY() <= 0.0f)
			{
				SetGravityFlag(true);//重力ON
				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
				return;
			}
		}
	}


	//右側の銃に関するフレームの処理
	if (m_nMotionFrame >= 0)
	{
		m_nMotionFrame--;
		SetMotion(CCharacter::MOTIONSTATE::ACTION);
	}
	//左側の銃に関するフレーム処理
	if (m_nMotionFrame001 >= 0)
	{
		m_nMotionFrame001--;
		SetMotion(CCharacter::MOTIONSTATE::ACTION);
	}
}


//===============================================================================================================================================================================
//ショップ時のキーごとの処理をまとめる関数
//===============================================================================================================================================================================
void CPlayerX::ShopKeySet()
{
	//=======================================================================================================================================================
	//通常状態の時
	//=======================================================================================================================================================
	if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
	{
		//
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			//選択ゲージ１つ目を生成する
			if (m_pSelectGage == nullptr)
			{
				m_pSelectGage = CSelectGage::Create();
			}

			//選択ゲージ二つ目を生成する
			if (m_pSelectGage001 == nullptr)
			{
				m_pSelectGage001 = CSelectGage001::Create();
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //一つ目のゲージの大きさに合わせる
			}

			//背景UIを生成する
			if (CManager::GetInstance()->GetShopScreen() == nullptr)
			{
				CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCREEN, 0);
			}

			//買うか売るかのUIを生成する
			if (m_pBuyText == nullptr)
			{
				m_pBuyText = CBuyText::Create();
			}

			m_PlayerState = CPlayerX::PLAYER_STATE::SHOP_MODE; //モードを変更する
		}
	}

	//=======================================================================================================================================================
	//SHOP状態の時
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE)
	{
		//フラグ状態が通常時の時
		if (m_FlagSate == CPlayerX::PLAYER_STATE::NORMAI_MODE)
		{
			SelectGageUISize(50.0f, 270.0f); //選択ゲージ1つ目の大きさを設定する
			m_FlagSate = CPlayerX::PLAYER_STATE::SHOP_MODE;          //フラグ状態を店の状態へ変化させる
		}

		//買うを選択したとき（０からスタートもしくは０に戻る）
		if (m_nBuyOrSendCount == 0)
		{
			//Enterキーを押したとき
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
			{
				SelectGageUISize(50.0,150.0f);
				m_PlayerState = CPlayerX::PLAYER_STATE::BUY_MODE;
			}
		}

		//キーが押された時
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			SelectGageUISizeCalculation("Plus", 400.0f, 400.0f); //サイズを調整する
			m_nBuyOrSendCount += 1; //カウントを進める

			//選択外の数値になった時
			if (m_nBuyOrSendCount == 2 )
			{
				SelectGageUISize(50.0, 270.0f);
				m_nBuyOrSendCount = 0; //カウントを初期化する

			}
		}
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			SelectGageUISizeCalculation("Minus", 400.0f, 400.0f); //サイズを調整する
			m_nBuyOrSendCount -= 1; //カウントを進める

			//選択外の数値になった時
			if (m_nBuyOrSendCount ==-1)
			{
				SelectGageUISize(450.0, 670.0f);
				m_nBuyOrSendCount = 1; //カウントを初期化する

			}
		}

		//キーが押された時
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;          //フラグ状態を通常の状態へ変化させる
		}
	}

	//=======================================================================================================================================================
	//買う状態の時
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
	{
		//買うか売るかのUIを破棄する
		if (m_pBuyText != nullptr)
		{
			m_pBuyText->Release();
			m_pBuyText = nullptr;
			return;
		}

		//メニューを生成する
		if (m_pMenyu == nullptr)
		{
			m_pMenyu = CShopMenu::Create();
		}


		//キーが押された時
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;          //フラグ状態を通常の状態へ変化させる
		}

		//Sキーを押したとき
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				m_pSelectGage->GetSizeY() += 160.0f;
				m_pSelectGage->GetSize1Y() += 160.0f;
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount += 1;

				if (m_nSelectShopCount == 4 || m_nSelectShopCount == 5)
				{
					m_pSelectGage->GetSizeY() = 50.0f;
					m_pSelectGage->GetSize1Y() = 150.0f;
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = 0;

				}
			}
		}

		//Wキーを押したとき
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				m_pSelectGage->GetSizeY() -= 160.0f;
				m_pSelectGage->GetSize1Y() -= 160.0f;
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount -= 1;

				if (m_nSelectShopCount == -1)
				{
					m_pSelectGage->GetSizeY() = 530.0f;
					m_pSelectGage->GetSize1Y() = 630.0f;
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = 3;

				}
			}
		}

		//Enterキーを押したとき
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
		{
			CreateGun();
		}
	}
}


//===============================================================================================================================================================================
//選択ゲージのUIのサイズを設定する処理
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISize(float fSIzeX,float fSIze1X)
{
	m_pSelectGage->GetSizeY() = fSIzeX;
	m_pSelectGage->GetSize1Y() = fSIze1X;

	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //選択ゲージ２つ目の大きさを同期させる
}

//===============================================================================================================================================================================
//選択ゲージのUIのサイズを設定する処理
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISizeCalculation(const char* aSelect,float fSIzeX, float fSIze1X)
{
	if (aSelect == "Plus")
	{
		m_pSelectGage->GetSizeY() += fSIzeX;
		m_pSelectGage->GetSize1Y() += fSIze1X;
	}
	else if (aSelect == "Minus")
	{
		m_pSelectGage->GetSizeY() -= fSIzeX;
		m_pSelectGage->GetSize1Y() -= fSIze1X;
	}

	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //選択ゲージ２つ目の大きさを同期させる
}


//===============================================================================================================================================================================
//武器生成処理
//===============================================================================================================================================================================
void CPlayerX::CreateGun()
{
	//一番目の武器が選ばれた時
	if (m_nSelectShopCount == 0)
	{
		if (m_pModelPrts[18]->m_bCreateGun == false)
		{
			m_pModelPrts[18]->m_bCreateGun = true;
		}
	}

	//二番目の武器が選ばれた時
	if (m_nSelectShopCount == 1)
	{
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::DEBRIS, 0, GetPos());
	}

	//三番目の武器が選ばれた時
	if (m_nSelectShopCount == 2)
	{
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::DEBRIS, 0, GetPos());
	}

	//四番目の武器が選ばれた時
	if (m_nSelectShopCount == 3)
	{
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::DEBRIS, 0, GetPos());
	}

}

//===============================================================================================================================================================================
//描画処理
//===============================================================================================================================================================================
void CPlayerX::Draw()
{
	CCharacter::DrawPlayer(MAX_PRTS);
}

//===============================================================================================================================================================================
//様々な物の当たり判定
//===============================================================================================================================================================================
void CPlayerX::BlockJudgement()
{
	//地面用のブロックの生成数分回す
	for (int nCount = 0; nCount <CManager::GetInstance()->GetFieldBlockCount()+1; nCount++)
	{
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.05f, GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y + CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//上がる用のブロックの生成数分回す
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetGoUpBlockCount() + 1; nCount1++)
	{
		if (CManager::GetInstance()->GetGoUpBlock(nCount1) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize(), GetMove()) == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false;
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize().y + CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//道用ブロック分回す
	for (int nCount2 = 0; nCount2 < CManager::GetInstance()->GetRoadBlockCount() + 1; nCount2++)
	{
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//壁兼道用ブロック分回す
	for (int nCount3 = 0; nCount3 < CManager::GetInstance()->GetWallRoadBlockCount() + 1; nCount3++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			if (GetCollision() ->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//壁兼道001用ブロック分回す
	for (int nCount4 = 0; nCount4 < CManager::GetInstance()->GetWallRoadBlock001Count() + 1; nCount4++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				GravityTogether();
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;//y軸の位置を設定
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //飛んでいないに設定
				}
			}
		}
	}

	//小さいブロック分回す
	for (int nCount5 = 0; nCount5 < CManager::GetInstance()->GetSmallBlockCount() + 1; nCount5++)
	{
		if (CManager::GetInstance()->GetSmallBlock(nCount5) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize() * 1.3f, GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), GetMove()) == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false;
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
				else if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), GetMove()) == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false;
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//上壁ブロック分回す
	for (int nCount6 = 0; nCount6 < CManager::GetInstance()->GetUpWallBlockCount() + 1; nCount6++)
	{
		if (CManager::GetInstance()->GetUpBlock(nCount6) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize() * 1.05f, GetMove()) == true)
			{
				//GetPos().x = 100.0f;
			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false;
					GravityTogether();
					GetPos().y = CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize().y + CManager::GetInstance()->GetUpBlock(nCount6)->GetPos().y;//y軸の位置を設定
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
				else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false;
					GravityTogether();
					SetJumpFlag(false); //飛んでいないに設定
				}
			}
		}
	}

	//小さいブロック001分回す
	for (int nCount7 = 0; nCount7 < CManager::GetInstance()->GetSmallBlock001Count() + 1; nCount7++)
	{
		if (CManager::GetInstance()->GetSmallBlock001(nCount7) != nullptr)
		{
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
				GravityTogether();
				GetPos().y = CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos().y;//y軸の位置を設定
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //飛んでいないに設定
				}
			}
			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				SetJumpFlag(false); //飛んでいないに設定
			}
		}
	}
	
	//ボス戦の足場
	if (CManager::GetInstance()->GetFinalBlock() != nullptr)
	{
		if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFinalBlock()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalBlock()->GetModelSize(), GetMove()) == true)
		{
			GravityTogether();
			GetPos().y = CManager::GetInstance()->GetFinalBlock()->GetModelSize().y + CManager::GetInstance()->GetFinalBlock()->GetPos().y;//y軸の位置を設定
			if (GetJumpFlag() == true)
			{
				SetJumpFlag(false); //飛んでいないに設定
			}
		}
	}
	//ボス戦の天井
	if (CManager::GetInstance()->GetFinalCeiling() != nullptr)
	{
		if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize(), GetMove()) == true)
		{
			//m_JumpFlag = false; //フラグをflaseにする
			SetGravityFlag(true);//重力ON
		}
		//その他
		else
		{
			SetGravityFlag(true);//重力ON
		}
	}



	//バトルシップとの当たり判定
	if (CManager::GetInstance()->GetSpeceBattleShip() != nullptr)
	{
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetSpeceBattleShip()->GetPos(), GetModelSize(), CManager::GetInstance()->GetSpeceBattleShip()->GetModelSize() * 1.1f) == true)
		{
			m_bNextStage = true; //次のsceneへ行くフラフをONにする
		}
	}

	//SHOPとの当たり判定
	if (CManager::GetInstance()->GetShop() != nullptr)
	{
		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize(), GetMove()) == true)
		{

		}

		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize() * 1.5f) == true)
		{
			//話すtextの情報がない時
			if (m_pTalkText == nullptr)
			{
				m_pTalkText = CUI::Create(CObject3D::TYPE_UI::TALKTEXTR);
				m_pTalkText->GetPos() = D3DXVECTOR3(CManager::GetInstance()->GetShop()->GetPos().x, CManager::GetInstance()->GetShop()->GetPos().y + 150.0f, CManager::GetInstance()->GetShop()->GetPos().z); //位置の初期化
				m_pTalkText->GetDraw() = true;
			}

			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				ShopKeySet();
			}
		}
		else
		{
			//話すtextの情報がある時
			if (m_pTalkText != nullptr)
			{
				m_pTalkText->Release();
				m_pTalkText = nullptr;
			}
		}
	}
}

//===============================================================================================================================================================================
//モデルの取得
//===============================================================================================================================================================================
CPlayerX* CPlayerX::Create()
{
	CPlayerX* pPlayerX = new CPlayerX(3); //動的確保

	if (SUCCEEDED(pPlayerX->Init()))
	{
		if (pPlayerX != nullptr)
		{
			//pPlayerX->Size(); //Playerのサイズの計算をする
			pPlayerX->SetType(TYPE::PLAYER); //タイプをPLAYERに設定
			return pPlayerX; //プレイヤーの情報を返す
		}
	}

	return nullptr; //情報なし
}