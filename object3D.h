//====================================================
//
//3Dオブジェクトクラス管理[object3D.h]
//Auther:Chiba Haruki
//
//====================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = DEFAULT_PRIORITY); //コンストラクタ
	~CObject3D() override;                                   //デストラクタ
	HRESULT Init() override;                                 //初期化処理
	HRESULT BillboardInit();                                 //ビルボード時の初期化設定
	void Uninit() override;                                  //破棄処理
	void Update()override;                                   //更新処理
	void Draw() override;                                    //描画処理
	void DrawNoml()override;                                 //ビルボードの描画処理
	void DrawEffect();                                       //エフェクト用の描画処理
	void DrawEffect1();                                       //エフェクト用の描画処理
	void SetPos(D3DXVECTOR3 pos);                            //位置の設定処理
	void SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z);  //polygonのサイズを調整する処理
	void SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z);  //エフェクト用polygonのサイズを調整する処理
	void SetSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z);  //エフェクト用polygonのサイズを調整する処理
	void SetCol(int Red, int Green,int Blue,int& Alpha);     //色に関する設定
	void SetTexture(float SizeX, float Size1X);              //テクスチャのサイズを設定する

	//当たり判定処理
	bool CollisionPrts1Right(float X, float Y, float Z);     //パーツ毎の当たり判定　右側
	bool CollisionPrts1Left(float X, float Y, float Z);      //パーツ毎の当たり判定　左側
	bool CollisionPrtsPlayer(float X, float Y, float Z);     //パーツ毎の当たり判定　全体

	HRESULT Lood();                                          //テクスチャファイルの読み込み

	//情報の取得
	D3DXVECTOR3& GetPos() { return m_pos; }                  //位置の取得
	int& GetLife() { return m_nLife; }                       //ライフの取得
	int& GetAlpha() { return m_nAlpha; }
	float& GetSizeY() { return m_fSizeY; }

protected:
	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファのポインタ
	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_move; //移動量
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_col; //色
	D3DXMATRIX m_mtxWorld; //マトリックス

	int m_nLife;
	int m_nAlpha;
	int m_nFrame;
	float m_fSizeX;  //ｘ軸のサイズの調整用変数
	float m_fSizeY;  //ｙ軸のサイズの調整用変数
	const char* m_aFileName;
};

#endif // !_OBJECT3D_H_

