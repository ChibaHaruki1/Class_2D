//==============================================================
//
//プレイヤーの位置をやゴールクラス管理[pos_object.h]
//Auther:Haruki Chiba
//
//==============================================================

#ifndef _POS_OBJECT_H_
#define _POS_OBJECT_H_

#include "objectX.h"

//マクロ定義
#define MAX_POSOBJECT_TEXTURE (10)

class CStart : public CObjectX
{
public:
	CStart(int nPriority = DEFAULT_PRIORITY1);
	~CStart()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;

	static CStart* Create();
};

//class CLadder : public CPosObject
//{
//	CLadder(int nPriority = DEFAULT_PRIORITY1);
//	~CLadder()override;
//	HRESULT Init(float fTexSizeX, float fTexSizeY)override;
//	void Uninit()override;
//	void Update() override;
//	void Draw()override;
//	void DrawNoml()override;
//	D3DXVECTOR3& GetPosStatrtSize() { return m_StartSize; }
//
//	static HRESULT Lood();
//	static void Unlood();
//	static CLadder* Create();
//
//private:
//	//static LPDIRECT3DTEXTURE9 m_pStartTexture[MAX_LADDER_TEXTURE];
//	static LPD3DXMESH m_pStartMesh; //メッシュのへのポインタ
//	static LPD3DXBUFFER m_pStartBuffMat; //マテリアルへのポインタ
//	static DWORD m_StartdwNumMat; //マテリアルの数
//	static D3DXMATERIAL* m_pMat;
//	D3DXVECTOR3 m_StartSize;
//};

#endif // !_POS_OBJECT_H_

