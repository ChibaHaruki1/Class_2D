//============================================
//
//ビルボードクラス管理[billboard.h]
//Auther:Haruki Chiba
//
//============================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//============================================
//インクルード
#include "object3D.h"

//==================================================================
//ビルボード処理
class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority = DEFAULT_PRIORITY);
	~CBillboard()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	static CBillboard* Create();

private:
	
};

#endif // !_BILLBOARD_H_

