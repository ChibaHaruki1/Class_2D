//================================
//
//敵の処理[enemy.cpp]
//Auther:Chiba Haruki
//
//================================


//================================
//インクルード
#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "player.x.h"


//=========================
//コンストラクタ
//=========================
CManagerEnemy::CManagerEnemy(int Priority) : CObjectX(Priority)
{

}


//=========================
//デストラクタ
//=========================
CManagerEnemy::~CManagerEnemy()
{

}


//=========================
//初期化処理
//=========================
HRESULT CManagerEnemy::Init()
{
	//初期化に成功した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}


//=========================
//終了処理
//=========================
void CManagerEnemy::Uninit()
{
	CObjectX::Uninit(); //破棄処理
}


//=========================
//更新処理
//=========================
void CManagerEnemy::Update()
{
	
}

//==========================
//描画処理
//==========================
void CManagerEnemy::Draw()
{
	CObjectX::Draw(); //描画処理
}

//==========================
//3Dモデルの敵の作成
//==========================
CManagerEnemy* CManagerEnemy::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemy* pManagerEnemy = nullptr; //基底クラスのポインター

	//タイプが敵の時
	if (type == TYPE::ENEMY)
	{
		pManagerEnemy = new CEnemyX(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy000.x"); //ファイルパスの設定
		}
	}

	//タイプが敵001の時
	else if (type == TYPE::ENEMY001)
	{
		pManagerEnemy = new CEnemy001X(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy001.x"); //ファイルパスの設定
		}
	}

	//情報がある時
	if (pManagerEnemy != nullptr)
	{
		pManagerEnemy->SetPos(pos); //位置を引数と同期させる
		pManagerEnemy->Lood();      //Xファイルの読み込み
		pManagerEnemy->Size();      //サイズの取得
		return pManagerEnemy;       //情報を返す
	}

	return nullptr;                 //無を返す
}


//=====================================================================================================================================
//敵の処理
//=====================================================================================================================================

//=========================
//コンストラクタ
//=========================
CEnemyX::CEnemyX(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//デストラクタ
//=========================
CEnemyX::~CEnemyX()
{

}

//=========================
//更新処理
//=========================
void CEnemyX::Update()
{
	TargetHeadingTowards(CManager::GetScene()->GetPlayerX(),2.0f);  //プレイヤーに向かう処理関数を呼ぶ

	//プレイヤーと当たった時
	if (CollisionPlayerSelect(this) == true)
	{
		//プレイヤーのHPを減らす
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * CManagerBossEffect::MAX_DAMAGE;
	}

	//ライフが尽きた時
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）
		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));            //爆発エフェクトの位置を設定
		CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));         //爆発エフェクトの位置を設定
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);                                                          //スコアを加算
		CObjectX::Release(); //自身の削除
		return;              //処理を抜ける
	}

	CObjectX::Update();      //更新処理
}


//=====================================================================================================================================
//敵001の処理
//=====================================================================================================================================

//=========================
//コンストラクタ
//=========================
CEnemy001X::CEnemy001X(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//デストラクタ
//=========================
CEnemy001X::~CEnemy001X()
{

}

//=========================
//更新処理
//=========================
void CEnemy001X::Update()
{
	SetAddjustRot().y += PLUS_ROTY; //Y軸の向きを加算

	//プレイヤーと当たった時
	if (CollisionPlayerSelect(this) == true)
	{
		//プレイヤーのHPを削る
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
	}

	//ライフが尽きた時
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //爆発エフェクトを呼ぶ（1つ目）

		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y+50.0f, GetPos().z));      //爆発エフェクトの位置を設定
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);                                                  //スコアを加算
		CObjectX::Release(); //自身の削除
		return;              //処理を抜ける
	}
}