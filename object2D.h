//===============================================
//
//２Ｄオブジェクトのクラス管理[object.h]
//Auther:Chiba Haruki
//
//===============================================

#pragma once

//===============================================
//インクルード
#include "object.h"
#include "input.h"


class CObject2D : public CObject
{
public:
	CObject2D(int nPriority=DEFAULT_PRIORITY);  //コンストラクタ
	~CObject2D() override;                      //デストラクタ
	HRESULT Init() override;                    //初期化処理
	void Uninit() override;                     //破棄処理
	void Update() override;                     //更新処理
	void Draw() override;                       //描画処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSIze(float SIZE_X,float SIZE1_X, float SIZE_Y, float SIZE1_Y); //polygonのサイズを調整する処理
	void SetCol(int Alph,int Alph1);       //alpha値を設定
	HRESULT Lood();	                       //テクスチャファイルの読み込み

	//==================================================
	//それぞれの処理に必要な情報を取得する
	LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; } //バッファの取得
	D3DXVECTOR3& GetCol() {return m_col;}                       //色の取得
	int& GetAlph() { return m_nAlph; }                          //アルファ値を取得

	//==================================================
	//各情報の設定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; } //位置の設定	
	void SetAlph(int nAlph) { m_nAlph = nAlph; }  //アルファ値を設定

	//==================================================
	///三大基本情報の取得
	D3DXVECTOR3& GetPos() { return m_pos; }                       //位置の取得
	D3DXVECTOR3& GetMove() { return m_move; }                     //移動量の取得
	D3DXVECTOR3& GetRot() { return m_rot; }                       //向きの取得

protected:
	int m_nAlph;
	int m_nRandom;
	int m_nFrame;

	bool m_bUse;
	const char* m_aFileName;

private:
	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファのポインタ
	D3DXVECTOR3 m_pos;  //位置
	D3DXVECTOR3 m_move; //移動量
	D3DXVECTOR3 m_rot;  //向き
	D3DXVECTOR3 m_col;  //色
};
 