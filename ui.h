//===================================
//
//UIのクラス管理宣言をするファイル[ui.h]
//Author:chiba haruki
//
//===================================

#ifndef _UI_H_  //このマグロ定義がされていなかったから
#define _UI_H_  //二重インクルード防止のマクロ定義

#include "object3D.h"
#include <cstdio>

//現在配置しているオブジェクトにUIをつけるクラス
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);
	~CUI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;

	float& GetSIzeX() { return m_fSizeX; }
	bool& GetDraw() { return m_bDraw; }

	static CUI* Create(CObject3D::TYPE_UI typeui);

private:
	float m_fSizeX;
	bool m_bDraw;
};


//現在の配置したオブジェクトの場所にUIを出すクラス管理
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);
	~CCreateInObject()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
};


//今作ろうとしているオブジェクトのUIをだすクラス管理
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);
	~CTalkText()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
};

//監視カメラからでるレーザークラス
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);
	~CLaserCamare()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;

private:
	int m_nRandom;
};

#endif 
