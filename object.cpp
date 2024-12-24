//=========================================
//
//全オブジェクトの処理[object.cpp] 
//Auther:Chiba Haruki
//
//=========================================

#include "main.h"
#include "object.h"
#include "object3D.h"
#include "manager.h"

//静的メンバーの初期化
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT] = {};

//====================
//コンストラクタ
//====================
CObject::CObject()
{
	m_nPriority = 0;
	m_nID = 0;
	m_type = NONE;
}


//==========================
//引数付きコンストラクタ
//==========================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority; //引数と同期する
	m_type = NONE; //初期化する
	m_nID = 0; //初期化する

	//オブジェクト分回す
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//情報がない場合
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{//空いている場所に自信を追加

			m_apObject[m_nPriority][nCnt] = this; //自分自身を代入
			m_nID = nCnt; //自分自身のIDを代入
			m_nNumAll++; //総数カウント
			break; //抜ける
		}
	}
}


//====================
//デストラクタ
//====================
CObject::~CObject()
{

}


//====================
//初期化処理
//====================
HRESULT CObject::Init()
{
	return S_OK; //成功
}


//====================
//終了処理
//====================
void CObject::Uninit()
{

}


//====================
//更新処理
//====================
void CObject::Update()
{

}


//====================
//描画処理
//====================
void CObject::Draw()
{

}


//====================
//描画処理
//====================
void CObject::DrawNoml()
{

}


//====================
//全オブジェクトの解放
//====================
void CObject::ReleaseAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Release(); //削除処理を呼ぶ
			}
		}
	}
}


//====================
//全オブジェクトの更新
//====================
void CObject::UpdateAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Update(); //更新処理を呼ぶ
			}
		}
	}

}


//====================
//全オブジェクトの描画
//====================
void CObject::DrawAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Draw(); //描画処理を呼ぶ
			}
		}
	}
}


//====================
//全オブジェクトの描画
//====================
void CObject::DrawNomlAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->DrawNoml(); //描画処理を呼ぶ
			}
		}
	}
}


//=====================
//自分自身の解放
//=====================
void CObject::Release()
{
	int nID = m_nID; //自身のIDを代入
	int nPriority = m_nPriority; //自身のpriorityを代入

	//情報がある場合
	if (m_apObject[nPriority][nID] != nullptr)
	{
		m_apObject[nPriority][nID]->Uninit(); //終了処理（破棄）を呼ぶ
		delete m_apObject[nPriority][nID]; //削除する
		m_apObject[nPriority][nID] = nullptr; //情報を無くす
		m_nNumAll--; //デクリメント
	}
}


//=====================
//オブジェクトの収得
//=====================
CObject*CObject::GetObject1(int nPri,int nIndex)
{
	return m_apObject[nPri][nIndex];
}


//=====================
//タイプ取得
//=====================
CObject::TYPE CObject::GetType()
{
	return m_type; //タイプを返す
}


//=====================
//設定処理
//=====================
void CObject::SetType(TYPE type)
{
	m_type = type; //引数と同期する
}