//========================================
//
//オブジェクトクラス管理[object.h]
//Auther:Chiba Haruki
//
//========================================

#ifndef _OBJECTMANAGERX_H_
#define _OBJECTMANAGERX_H_

#include "main.h"

#define MAX_OBJECTMANAGERX (250) //オブジェクトの最大数
#define DEFAULT_PRIORITY1 (3) //デフォルトの描画順
#define MAX_PRIORITY_MANAGER_OBJ (4) //描画順の最大数

//#include "main.h"
//#include "input.h"

//全てを管理するので仮想関数（純粋仮想関数）
class CObjectManagerX
{
public:

	typedef enum
	{
		NONE = 0,                    //無し
		ENEMY,                       //敵
		ENEMY001,                    //敵001
		ENEMYINMOTION,               //モーション付きの敵
		ENEMYINMOTION001,               //モーション付きの敵
		
		BOSS,                       //ボス
		PLAYER,                     //プレイヤー
		FIELDBLOCK,
		GOUPBLOCK,
		ROADBLOCK,
		WALLROADBLOCK,
		WALLROADBLOCK_001,
		SMALLBLOCK,
		SMALLBLOCK_001,
		UPWALLBLOCK,
		BREAKBLOCK,

		START,
		INITGUN,
		INITGUN001,
		TELEPHONPOLE,                //電柱
		SURVEILLANCECAMERAUP,        //監視カメラの上部分
		SURVEILLANCECAMERADOWN,      //監視カメラの下部分
		SHOP,                        //店
		DEBRIS,                      //破片
		BREAKHOUSE,                  //壊れた家
		MAX
	}TYPE;

	typedef enum
	{
		NONEITEM = 0,
		TARGET_RECOVERY_MP,
		TARGET_RECOVERY_MP1,
		TRAGET_FARME_INIT,
		GEAR,
		ITEMBLOCK,
		MAXITEM
	}ITEMTYPE;

	typedef enum
	{
		NONEGIMMICK = 0,
		RED_RIGHTDOOR,
		RED_LEFTDOOR,
		MAXGIMMICK

	}GIMMICKTYPE;

	typedef enum
	{
		NONESTRATEGY=0,
		BLOCK000,
		BLOCK001,
		BLOCK002,
		BLOCK003,
		BLOCK003_001,
		BLOCK004,
		BLOCK004_001,
		BLOCK005,
		BLOCK006,
		SPECEBATTLESHIP000,
		FINALBLOCK,
		FINALCEILLING,
		WODDENBORAD,
	}STRATEGYTYPE;

	CObjectManagerX(int nPriority = DEFAULT_PRIORITY1);
	virtual ~CObjectManagerX(); //デストラクタ
	virtual HRESULT Init() = 0; //初期化
	virtual void Uninit() = 0; //終了処理
	virtual void Update() = 0; //更新処理
	virtual void Draw() = 0; //描画処理
	static void ReleaseAll(); //全オブジェクトの解放
	static void UpdateAll(); //全オブジェクトの更新
	static void DrawAll(); //全オブジェクトの描画
	static CObjectManagerX* GetObjectManagerX(int nPri, int nIndex); //オブジェクト取得
	TYPE GetType(); //タイプ取得
	ITEMTYPE GetItemType(); //タイプ取得
	GIMMICKTYPE GetGimmickType(); //タイプ取得
	void SetType(TYPE type); //タイプ設定
	void SetItemType(ITEMTYPE ItemType);
	void SetGimmickType(GIMMICKTYPE GimmickType);
	void Release(); //自分自身の解放


protected:

	/*CInputKeyBoard* pInputKeyBoard;
	CInputJoyPad* pInputJyoPad;*/

private:
	static CObjectManagerX* m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX]; //全オブジェクトの管理
	static int m_nNumAll; //オブジェクトの総数
	int m_nPriority;
	int m_nID; //自分自身のID
	TYPE m_type; //オブジェクトタイプ
	ITEMTYPE m_ItemType;
	GIMMICKTYPE m_GimmickType;

};

#endif // !_OBJECTMANAGERX_H_


