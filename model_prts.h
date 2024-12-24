//
//
//
//
//
//

#pragma once
#include "main.h"

#define MAX_MODEL_TEXTURE (50)

class CModelPrts
{
public:
	CModelPrts();                 //コンストラクタ
	~CModelPrts();                                         //デストラクタ
	HRESULT Init();                                        //初期化処理
	void Uninit();                                         //破棄処理
	void Update();                                        //更新処理
	void Draw(D3DXMATRIX MtxWolrd);                                           //描画処理
	void Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat);                                          //Xファイルの読み込み
	void BindSize(D3DXVECTOR3&max, D3DXVECTOR3&min, D3DXVECTOR3&ModelSize);
	void BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat);
	void BindPos(D3DXVECTOR3&pos);
	void SetParent(CModelPrts* pParent);
	void Size();
	D3DXMATRIX& GetWorldMtx() { return m_mtxWorld; }
	static CModelPrts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat); //生成処理

	int m_nIndexPrts;      //何番目のパーツ
	int m_nIndexModelPrts; //親のパーツ
	
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld; //マトリックス
	LPD3DXMESH m_pMesh; //メッシュのへのポインタ
	LPD3DXBUFFER m_pBuffMat; //バッファのポインタ
	DWORD m_nNumMat;

	//モデルサイズの取得
	D3DXVECTOR3 m_min; //頂点の最小値
	D3DXVECTOR3 m_max; //頂点の最大値
	D3DXVECTOR3 m_ModelSize; //モデルのサイズを格納

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEXTURE]; //テクスチャへのポインタ
	//D3DXMATERIAL* m_pMat; //マテリアルのポインタ
	bool m_bCreateGun;
private:
	CModelPrts* m_pParentlPrts;  //自分のポインター
	int nNumTexture;
};
