//============================================================
//
//ステージに置くオブジェクトのクラス管理[statge_obj.h]
//Auther:Chiba Haruki
//
//============================================================

#pragma once

//===========================
//インクルード
#include "objectX.h"
#include <cstdio>

//ステージに置くオブジェクトの基底クラス管理
class CStageObj : public  CObjectX
{
public:
	CStageObj(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CStageObj()override;                         //デストラクタ
	HRESULT Init()override;                       //初期化処理
	void Uninit()override;                        //破棄処理
	void Update() override;                       //更新処理
	void Draw()override;                          //描画処理

	void TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ);

	static CStageObj* Create(D3DXVECTOR3 pos,CObjectX::TYPE type); //継承クラスをタイプごとに生成
private:
	static int m_nTelephonPoleCount;
	FILE* m_pFile;
};


//電柱のクラス管理
class CTelephonPole : public CStageObj
{
public:
	CTelephonPole(int nPriority = DEFAULT_PRIORITY1);
	~CTelephonPole()override;
};


//監視カメラの上の部分
class CSurveillanceCameraUP : public CStageObj
{
public:
	CSurveillanceCameraUP(int nPriority = DEFAULT_PRIORITY1);
	~CSurveillanceCameraUP()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;
};

//監視カメラの下の部分
class CSurveillanceCameraDown : public CStageObj
{
public:
	CSurveillanceCameraDown(int nPriority = DEFAULT_PRIORITY1);
	~CSurveillanceCameraDown()override;
	
};

//監視カメラの下の部分
class CShop : public CStageObj
{
public:
	CShop(int nPriority = DEFAULT_PRIORITY1);
	~CShop()override;
};

//壊れた家
class CBreakHouse : public CStageObj
{
public:
	CBreakHouse(int nPriority = DEFAULT_PRIORITY1);
	~CBreakHouse()override;
	void Update()override;

private:
};
