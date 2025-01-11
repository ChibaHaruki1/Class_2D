//================================
//
//カメラ処理[camera.cpp]
//Auther:Haruki Chiba
//
//================================

//インクルード
#include "camera.h"
#include "object.h"
#include "rendererh.h"
#include "manager.h"
#include "player.x.h"

//マクロ定義
#define MAX_ROTSPEED (0.01f) //カメラの回転の速さを調整する
#define MAX_CAMERASPEED (1.0f) //カメラの移動の速さを調整

//========================
//コンストラクタ
//========================
CCamera::CCamera()
{
	m_fDistance = 300;
	CountCamera = 10.0f;
	pInputKeyBoard1 = nullptr;

	m_fAdjustmentPosZ = 1000;
}


//========================
//デストラクタ
//========================
CCamera::~CCamera()
{

}


//========================
//初期化処理
//========================
HRESULT CCamera::Init()
{
	pInputKeyBoard1 = CManager::GetKeyBorad(); //キーボードの情報を獲得する

	/*switch (CManager::GetScene()->GetMode())
	{
	case CScene::MODE_GAME01:
		m_fAdjustmentPosZ = 600;
		break;
	case CScene::MODE_GAME02:
		m_fAdjustmentPosZ = 1000;
		break;
	}*/

	m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f); //視点を調整
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);////注視点をモデルに設定
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSavePosV = m_posV;

	return S_OK;
}


//========================
//終了処理
//========================
void CCamera::Uninit()
{

}


//========================
//更新処理
//========================
void CCamera::Update()
{
	if (pInputKeyBoard1->GetKeyboardPress(DIK_Y) == true)
	{//視点が下（小さく）になる
		m_posV.y += MAX_CAMERASPEED;
		CountCamera += MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_N) == true)
	{//視点が上（大きく）なる
		m_posV.y -= MAX_CAMERASPEED;
		CountCamera -= MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_Z) == true)
	{//視点が左に動く
		rot.y += MAX_ROTSPEED;
		m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) * m_fDistance;
		m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) * m_fDistance;

	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_C) == true)
	{//視点が右に動く
		rot.y -= MAX_ROTSPEED;
		m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) * m_fDistance;
		m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) * m_fDistance;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_T) == true)
	{//注視点が下（小さく）になる
		m_posR.y += MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_B) == true)
	{//注視点が上（大きく）なる
		m_posR.y -= MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_Q) == true)
	{//注視点が左に向く
		rot.y -= MAX_ROTSPEED;
		m_posR.x = m_posV.x + sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(rot.y) * m_fDistance;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_E) == true)
	{//注視点が右に向く
		rot.y += MAX_ROTSPEED;
		m_posR.x = m_posV.x + sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(rot.y) * m_fDistance;
	}

	if (pInputKeyBoard1->GetKeyboardPress(DIK_V) == true)
	{
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//カメラがプレイヤーにつく処理
	m_posR.x = CManager::GetScene()->GetPlayerX()->GetPos().x;
	m_posR.y = CManager::GetScene()->GetPlayerX()->GetPos().y;
	m_posR.z = CManager::GetScene()->GetPlayerX()->GetPos().z;

	m_posV.x = CManager::GetScene()->GetPlayerX()->GetPos().x;
	m_posV.y = CManager::GetScene()->GetPlayerX()->GetPos().y + m_fSavePosV.y + CountCamera;
	m_posV.z = CManager::GetScene()->GetPlayerX()->GetPos().z;

	//カメラ自体もプレイヤーに合わせて動く(直接モデルの値を代入するとカメラ回転時強制的に正面に戻されるため）
	m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) * m_fAdjustmentPosZ;
	m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) * m_fAdjustmentPosZ;
}


//========================
//カメラの設定（描画）
//========================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice= pRenderer->GetDevice(); //デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)CMain::SCREEN_WIDTH / (float)CMain::SCREEN_HEIGHT, 10.0f, 4000.0f);

	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)CMain::SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 10.0f, 2000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}