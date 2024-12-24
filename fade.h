//===========================================
//
//フェード処理[fade.h]
//Auther:Chiba Haruki
//
//===========================================

#ifndef _FADE_H_
#define _FADE_H_

#include "object2D.h"

//マクロ定義
#define MAX_FADE_SPEED (2) //フェードの処理の色の変化する速度調整

class CFade : public CObject2D
{
public:
	typedef enum
	{
		FADE_NONE=0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade(int nPriority = DEFAULT_PRIORITY);
	~CFade()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	//static HRESULT Lood();
	//static void Unlood();
	//static Bind();

	 int GetCountCol();

	void SetFade(FADE Fadetype);
	static CFade* Create();

private:
	 int nCountCol;
	FADE m_Fade;
	//static LPDIRECT3DTEXTURE9 m_pFadetexture; //テクスチャの情報格納
};


#endif
