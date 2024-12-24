//==========================================
//
//レンダラークラス管理[renderer.h]
//Auther:Chiba Haruki
//
//==========================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "object.h"
#include "input.h"
#include "objectmanagerX.h"
#include "objectX.h"
//#include "tutorial.h"

class CRenderer
{
public:
	CRenderer(); //コンストラクタ
	~CRenderer(); //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS();
	LPDIRECT3DDEVICE9 GetDevice(); //３Dデバイス
	bool& GetPause() { return m_bPause; }
	bool& GetDrawShader() { return m_bDrawShader; }

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3Dデバイス

	//CObject* pObject[MAX_OBJECT];
	//CObjectManagerX* m_pObjectManagerX[MAX_OBJECTMANAGERX];
	LPD3DXFONT m_pFont;
	bool m_bPause;
	bool m_bDrawShader; //シェーダーを描画するかどうか
};

#endif // !_RENDERER_H_

