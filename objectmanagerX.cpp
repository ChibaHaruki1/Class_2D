//=========================================
//
//全オブジェクトの処理[object.cpp] 
//Auther:Chiba Haruki
//
//=========================================

#include "main.h"
#include "manager.h"
#include "objectmanagerX.h"

//静的メンバーの初期化
int CObjectManagerX::m_nNumAll = 0;
CObjectManagerX* CObjectManagerX::m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX] = {};


//==========================
//引数付きコンストラクタ
//==========================
CObjectManagerX::CObjectManagerX(int nPriority)
{
	m_nPriority = nPriority; //引数と同期する
	m_type = NONE; //初期化する
	m_ItemType = NONEITEM;
	m_GimmickType = NONEGIMMICK;
	m_nID = 0; //初期化する

	//オブジェクト分回す
	for (int nCnt = 0; nCnt < MAX_OBJECTMANAGERX; nCnt++)
	{
		//情報がない場合
		if (m_apObjectManagerX[m_nPriority][nCnt] == nullptr)
		{//空いている場所に自信を追加

			m_apObjectManagerX[m_nPriority][nCnt] = this; //自分自身を代入
			m_nID = nCnt; //自分自身のIDを代入
			m_nNumAll++; //総数カウント
			break; //抜ける
		}
	}
}


//====================
//デストラクタ
//====================
CObjectManagerX::~CObjectManagerX()
{

}


//====================
//初期化処理
//====================
HRESULT CObjectManagerX::Init()
{
	return S_OK; //成功
}


//====================
//終了処理
//====================
void CObjectManagerX::Uninit()
{
	m_nID = 0;
}


//====================
//更新処理
//====================
void CObjectManagerX::Update()
{

}


//====================
//描画処理
//====================
void CObjectManagerX::Draw()
{

}


//====================
//全オブジェクトの解放
//====================
void CObjectManagerX::ReleaseAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//情報がある場合
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Release(); //削除処理を呼ぶ
			}
		}
	}
}


//====================
//全オブジェクトの更新
//====================
void CObjectManagerX::UpdateAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//情報がある場合
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Update(); //更新処理を呼ぶ
			}
		}
	}

}


//====================
//全オブジェクトの描画
//====================
void CObjectManagerX::DrawAll()
{
	//puriority分回す
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//情報がある場合
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Draw(); //描画処理を呼ぶ
			}
		}
	}
}


//=====================
//自分自身の解放
//=====================
void CObjectManagerX::Release()
{
	int nID = m_nID; //自身のIDを代入
	int nPriority = m_nPriority; //自身のpriorityを代入

	//情報がある場合
	if (m_apObjectManagerX[nPriority][nID] != nullptr)
	{
		m_apObjectManagerX[nPriority][nID]->Uninit(); //終了処理（破棄）を呼ぶ
		delete m_apObjectManagerX[nPriority][nID]; //削除する
		m_apObjectManagerX[nPriority][nID] = nullptr; //情報を無くす
		m_nNumAll--; //デクリメント
	}
}


//=====================
//オブジェクトの収得
//=====================
CObjectManagerX* CObjectManagerX::GetObjectManagerX(int nPri, int nIndex)
{
	return m_apObjectManagerX[nPri][nIndex];
}


//=====================
//タイプ取得
//=====================
CObjectManagerX::TYPE CObjectManagerX::GetType()
{
	return m_type; //タイプを返す
}

//=====================
//アイテムタイプ取得
//=====================
CObjectManagerX::ITEMTYPE CObjectManagerX::GetItemType()
{
	return m_ItemType; //タイプを返す
}


//===============================
//ギミックタイプを取得
//===============================
CObjectManagerX::GIMMICKTYPE CObjectManagerX::GetGimmickType()
{
	return m_GimmickType;
}


//=====================
//設定処理
//=====================
void CObjectManagerX::SetType(TYPE type)
{
	m_type = type; //引数と同期する
}


//==================================
//アイテムのタイプ設定処理
//==================================
void CObjectManagerX::SetItemType(ITEMTYPE Itemtype)
{
	m_ItemType = Itemtype; //引数と同期する
}


//==================================
//ギミックのタイプ設定処理
//==================================
void CObjectManagerX::SetGimmickType(GIMMICKTYPE GimmickType)
{
	m_GimmickType = GimmickType; //引数と同期する
}