//=======================================
//
//åıåπÉNÉâÉXä«óù[light.h]
//Auther:Haruki Chiba
//
//=======================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();

private:
	static const int MAX_LIGHT = 4;
	D3DLIGHT9 m_aLight[MAX_LIGHT];
};

#endif // !_LIGHT_H_

