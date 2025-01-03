//==========================================================
//
//モーションの各パーツごとのクラス管理[model_prts.h]
//Auther;Chiba Haruki
//
//==========================================================

#pragma once

//==========================================================
//インクルード
#include "main.h"

#define MAX_MODEL_TEXTURE (50)

class CModelPrts
{
public:
	CModelPrts();                    //コンストラクタ
	~CModelPrts();                   //デストラクタ
	HRESULT Init();                  //初期化処理
	void Uninit();                   //破棄処理
	void Update();                   //更新処理
	void Draw(D3DXMATRIX MtxWolrd);  //描画処理
	void Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat);  //テクスチャの読み込みObjectXと同期させるために引数                                  //Xファイルの読み込み
	void BindSize(D3DXVECTOR3&max, D3DXVECTOR3&min, D3DXVECTOR3&ModelSize); //各モデルのパーツの大きさを渡す処理関数（ObjectXと同期の為引数）
	void SetParent(CModelPrts* pParent);              //親パーツの設定
	void Size();                                      //各モデルのパーツの大きさを求める処理関数
	D3DXMATRIX& GetWorldMtx() { return m_mtxWorld; }  //マトリックスの取得
	static CModelPrts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat); //生成処理

	int m_nIndexPrts;      //何番目のパーツ
	int m_nIndexModelPrts; //親のパーツ
	
	D3DXVECTOR3 m_pos;        //位置
	D3DXVECTOR3 m_rot;        //向き
	D3DXMATRIX m_mtxWorld;    //マトリックス
	LPD3DXMESH m_pMesh;       //メッシュのへのポインタ
	LPD3DXBUFFER m_pBuffMat;  //バッファのポインタ
	DWORD m_nNumMat;          //マテリアル数

	//モデルサイズの取得
	D3DXVECTOR3 m_min;       //頂点の最小値
	D3DXVECTOR3 m_max;       //頂点の最大値
	D3DXVECTOR3 m_ModelSize; //モデルのサイズを格納

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEXTURE];  //テクスチャへのポインタ
	bool m_bCreateGun;                                 //銃が作られたかどうか判定用の変数

private:
	CModelPrts* m_pParentlPrts;  //自分のポインター
};
