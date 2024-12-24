//===================================
//
//地面の設定をする処理[field.cpp]
//Author:chiba haruki
//
//===================================

#include "main.h"
#include "field.h"
#include "rendererh.h"
#include "manager.h"
#include <iostream>
#include <DxLib.h>
using namespace std; //c++の基礎の省略
std::string u8FieldText = u8"地面の情報設定"; //日本語対応

int CField::m_nCountField = 0;

//============================
//コンストラクタ
//============================
CField::CField(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 200.0f;
	m_aFileName = "data\\TEXTURE\\bg101.jpg";
	m_pFile = nullptr;
	PosX = 0.0f;
}


//============================
//デストラクタ
//============================
CField::~CField()
{

}


//============================
//ポリゴンの初期化処理
//============================
HRESULT CField::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================
//ポリゴンの終了処理
//==========================
void CField::Uninit()
{
	CObject3D::Uninit();
}

//========================
//ポリゴンの更新処理
//========================
void CField::Update()
{
	SetSize(m_fSizeX, 0.0f, m_fSizeX);

	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_1) == true)
	//{
	//	m_fSizeX += 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_2) == true)
	//{
	//	m_fSizeX -= 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_O) == true)
	//{
	//	//TextFileWrite();
	//}
}


//======================================
//テキストファイルに書き込む処理
//======================================
void CField::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ)
{
	m_pFile = fopen("data\\TEXT\\ResultScore.txt", "a"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (m_pFile == nullptr)
	{
		return; //処理を抜ける
	}
	m_nCountField++;
	fprintf(m_pFile, "%s", "\n\n"); //数字を書き込む
	fprintf(m_pFile, "%s", "#=====================================\n"); //数字を書き込む
	fprintf(m_pFile, "%s", "#"); //数字を書き込む
	fprintf(m_pFile, "%d", m_nCountField); //数字を書き込む
	fprintf(m_pFile, "%s", u8FieldText.data()); //文字を書き込む(全角文字)
	fprintf(m_pFile, "%s", "\n"); //改行を行う
	fprintf(m_pFile, "%s", "#=====================================\n"); //数字を書き込む
	fprintf(m_pFile, "%s", "FILED\n"); //数字を書き込む
	fprintf(m_pFile, "%s", "		POS = "); //「POS」の文字を書き込む
	fprintf(m_pFile, "%.1f ", m_fPosX); //「位置」の文字を書き込む(少数点第１まで)
	fprintf(m_pFile, "%.1f ", m_fPosY); //「位置」の文字を書き込む(少数点第１まで)
	fprintf(m_pFile, "%.1f ", m_fPosZ); //「位置」の文字を書き込む(少数点第１まで)
	fprintf(m_pFile, "%s", "\n"); //改行を行う
	fprintf(m_pFile, "%s", "END_FILED\n"); //文字を書き込む
	fclose(m_pFile); //ファイルを閉じる
}


//======================
//ポリゴンの描画処理
//======================
void CField::Draw()
{
	CObject3D::Draw(); //基底クラスの描画処理を呼ぶ
}


//======================
//ポリゴンの描画処理
//======================
void CField::DrawNoml()
{
	
}


//========================
//床を生成
//========================
CField* CField::Create(D3DXVECTOR3 pos)
{
	CField* pCField = new CField(2); //動的確保

	if (SUCCEEDED(pCField->Init()))
	{
		if (pCField != nullptr)
		{
			pCField->m_pos = pos;
			pCField->Lood();
			return pCField;
		}
	}

	return nullptr;
}