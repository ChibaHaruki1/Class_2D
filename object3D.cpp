//=========================================
//
//3Dオブジェクトの処理[object3D.cpp]
//Auther:Chiba Haruki
//
//=========================================

#include "object3D.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//引数付きコンストラクタ
//=============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する
	m_col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nAlpha = 255;
	m_nFrame = 0;
	m_nRandom = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_aFileName = nullptr;
	//g_pBuffMatGun = {};
}


//=====================
//デストラクタ
//=====================
CObject3D::~CObject3D()
{

}


//=====================
//初期化処理
//=====================
HRESULT CObject3D::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	//初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}


//=====================================
//ビルボード時の初期化設定
//=====================================
HRESULT CObject3D::BillboardInit()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	//初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}


//==================
//終了処理
//==================
void CObject3D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}


//==================
//更新処理
//==================
void CObject3D::Update()
{
	//位置を更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//移動量を更新（減衰させる）
	m_pos.x += (0.0f - m_move.x) * 0.5f; //少ないほうが早く、ぬるぬる動く
	m_pos.y += (0.0f - m_move.y) * 0.5f; //少ないほうが早く、ぬるぬる動く
	m_pos.z += (0.0f - m_move.z) * 0.5f; //少ないほうが早く、ぬるぬる動く
}


//==================
//サイズの設定
//==================
void CObject3D::SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X - SIZE_X*0.5f, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X - SIZE_X*0.5f, -SIZE_Y, SIZE_Z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================
//サイズの設定
//==================
void CObject3D::SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(0.0f, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, -SIZE_Y, SIZE_Z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================
//サイズの設定
//==================
void CObject3D::SetSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, 0.0f, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, 0.0f, SIZE_Z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//===================================================
//色の設定処理
//===================================================
void CObject3D::SetCol(int Red, int Green, int Blue,int& Alpha)
{
	VERTEX_3D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//===================================================
//テクスチャの大きさを設定させる
//===================================================
void CObject3D::SetTexture(float SizeX, float Size1X)
{
	VERTEX_3D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(SizeX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Size1X, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//================================
//各パーツ毎の当たり判定処理（選択）
//================================
bool CObject3D::CollisionPrtsPlayer(float X, float Y, float Z)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < CObjectX::MAX_PRTS - 1; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)*1.2f) == true)
		{
			return true; //成功
		}
	}
	return false; //失敗
}

//================================
//各パーツ毎の当たり判定処理
//================================
bool CObject3D::CollisionPrts1Left(float X, float Y, float Z)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < CCharacter::NUM_RIGHTPRTS; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 2), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 2)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 10), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 10)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
	}

	//胴体
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(0), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0)) == true)
	{
		return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}
	return false;
}

//================================
//各パーツ毎の当たり判定処理
//================================
bool CObject3D::CollisionPrts1Right(float X, float Y, float Z)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < CCharacter::NUM_RIGHTPRTS; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 2), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 2)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 10), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 10)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
	}

	//胴体
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(0), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0)) == true)
	{
		return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}
	return false;
}


//==================
//描画処理
//==================
void CObject3D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===========================
//ビルボード描画処理
//===========================
void CObject3D::DrawNoml()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView; //ビューマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得取得用;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//===========================
//エフェクト時の描画処理
//===========================
void CObject3D::DrawEffect()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView; //ビューマトリックス


	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得取得用;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//aブレンディを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================
//エフェクト時の描画処理
//===========================
void CObject3D::DrawEffect1()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView; //ビューマトリックス

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//aブレンディを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=====================
//位置の設定処理
//=====================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//===================================
//テクスチャファイルの読み込み
//===================================
HRESULT CObject3D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL;
	}
	return S_OK;
}