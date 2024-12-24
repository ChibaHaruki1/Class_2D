//===============================================
//
//２Ｄオブジェクトのクラス管理[object.h]
//Auther:Chiba Haruki
//
//===============================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"
#include "input.h"

//マクロ定義
#define MAX_LIFE (40) //弾と弾につくエフェクトのLife

class CObject2D : public CObject
{
public:
	CObject2D(int nPriority=DEFAULT_PRIORITY); //コンストラクタ
	~CObject2D() override; //デストラクタ
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void DrawNoml()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSIze(float SIZE_X,float SIZE1_X, float SIZE_Y, float SIZE1_Y); //polygonのサイズを調整する処理
	void SetCol(int Alph,int Alph1);

	D3DXVECTOR3& GetPos() {return g_pos;}
	HRESULT Lood(); //テクスチャファイルの読み込み
	static CObject2D* Create();
	//LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; }

protected:
	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファのポインタ
	D3DXVECTOR3 g_pos; //位置
	D3DXVECTOR3 g_move; //移動量
	D3DXVECTOR3 g_rot; //向き
	D3DXVECTOR3 m_col; //色
	float g_fLength; //対角線の長さ
	float g_fAngle; //対角線の角度

	int m_nLife;
	int m_fAlph;
	int m_fAlph1;
	int m_nRandom;
	int m_nFrame;

	bool m_bUse;
	const char* m_aFileName;

private:
	static CObject2D* m_apObject2D[DEFAULT_PRIORITY][MAX_OBJECT];
};

#endif // !_OBJECT2D_H_
