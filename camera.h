//========================================
//
//カメラクラス管理[camera.h]
//Auther:Haruki Chiba
//
//========================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//========================================
//インクルード
#include "main.h"
#include "input.h"

//==============================================================
//カメラのクラス
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();                                            //カメラの情報の設定	
	D3DXVECTOR3& GetPosV() { return m_posV; }
	D3DXVECTOR3& GetPosR() { return m_posR; }
	D3DXVECTOR3& GetRot() { return rot; }
	int& GetAdjustmentPosZ() { return m_fAdjustmentPosZ; }
	float& GetSaveF() { return CountCamera; }

private:

	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点
	D3DXVECTOR3 m_vecU; //上方向
	D3DXMATRIX m_mtxProjection; //プロジェクション
	D3DXMATRIX m_mtxView; //ビュー行列
	D3DXVECTOR3 rot; //向き
	CInputKeyBoard* pInputKeyBoard1;
	int  m_fDistance;
	float CountCamera;
	D3DXVECTOR3 m_fSavePosV;
	//int m_nDistance; //視点から注視点までの距離
	int m_fAdjustmentPosZ;
};

#endif // !_CAMERA_H_

