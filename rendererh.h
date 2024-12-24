//==========================================
//
//�����_���[�N���X�Ǘ�[renderer.h]
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
	CRenderer(); //�R���X�g���N�^
	~CRenderer(); //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS();
	LPDIRECT3DDEVICE9 GetDevice(); //�RD�f�o�C�X
	bool& GetPause() { return m_bPause; }
	bool& GetDrawShader() { return m_bDrawShader; }

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3D�f�o�C�X

	//CObject* pObject[MAX_OBJECT];
	//CObjectManagerX* m_pObjectManagerX[MAX_OBJECTMANAGERX];
	LPD3DXFONT m_pFont;
	bool m_bPause;
	bool m_bDrawShader; //�V�F�[�_�[��`�悷�邩�ǂ���
};

#endif // !_RENDERER_H_

