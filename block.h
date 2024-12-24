//======================================
//
//障害物のクラス管理[block.h]
//Auther:Chiba Haruki
//
//======================================

#ifndef _BLOCK_H_
#define _BLOCK_H_

//======================================
//インクルード
#include "objectX.h"


//==================================================================
//ストラテジー基底クラス
//==================================================================
class CBlockXStrategy
{
public:
	CBlockXStrategy();
	~CBlockXStrategy();
	virtual void Block() = 0;

	const char* m_aBlockFile;
};


//==================================================================
//ストラテジークラス継承
class CBlock000 : public CBlockXStrategy
{
public:
	CBlock000();
	~CBlock000();
	void Block();
};


//==================================================================
//ストラテジークラス継承
class CBlock001 : public CBlockXStrategy
{
public:
	CBlock001();
	~CBlock001();
	void Block();
};


//==================================================================
//ストラテジークラス継承
class CBlock002 : public CBlockXStrategy
{
public:
	CBlock002();
	~CBlock002();
	void Block();
};


//==================================================================
//ストラテジークラス継承
class CBlock003 : public CBlockXStrategy
{
public:
	CBlock003();
	~CBlock003();
	void Block();
};


//==================================================================
//ストラテジークラス継承
class CBlock004 : public CBlockXStrategy
{
public:
	CBlock004();
	~CBlock004();
	void Block();
};

//==================================================================

//ストラテジークラス継承
class CBlock005 : public CBlockXStrategy
{
public:
	CBlock005();
	~CBlock005();
	void Block();
};


//==================================================================
//ストラテジークラス継承
class CBlock006 : public CBlockXStrategy
{
public:
	CBlock006();
	~CBlock006();
	void Block();
};


//==================================================================
//次のステージへ行く用のobj
class CSpaceBattleShip : public CBlockXStrategy
{
public:
	CSpaceBattleShip();
	~CSpaceBattleShip();
	void Block();
};


//==================================================================
//ボス専用のブロック（ステージ）
class CFinalBlock : public CBlockXStrategy
{
public:
	CFinalBlock();
	~CFinalBlock();
	void Block();
};


//==================================================================
// ボス専用のブロック（ステージ）
class CFinalBlock1 : public CBlockXStrategy
{
public:
	CFinalBlock1() { m_aBlockFile = "data\\XFILE\\BLOCK\\FianlStageCeiling.x"; }
	~CFinalBlock1() {};
	void Block() {};
};


//==================================================================
//がれきに関するブロック
class CRubble : public CBlockXStrategy
{
public:
	CRubble() {};
	~CRubble() {};
	void Block() {};

};


//==================================================================
//ブロックの基底クラス
//==================================================================
class CManagerBlock : public  CObjectX
{
public:
	CManagerBlock(int nPriority = DEFAULT_PRIORITY1);
	~CManagerBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update() override;
	void Draw()override;
	void TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ,CObjectX::TYPE type);

	static CManagerBlock* Create(D3DXVECTOR3 pos, STRATEGYTYPE type);

	CBlockXStrategy* m_pBlockXStrategy;

private:
	static int m_nCreateCount; //作られた数を保管する
};


//==================================================================
//3D障害物のクラス管理
class CFiledBlock : public  CManagerBlock
{
public:
	CFiledBlock();
	~CFiledBlock()override;
private:
	
};


//==================================================================
//上に上がるためのブロック
class CGoUpBlock : public CManagerBlock
{
public:
	CGoUpBlock();
	~CGoUpBlock()override;
};


//==================================================================
//道用のブロック
class CRoadBlock : public CManagerBlock
{
public:
	CRoadBlock();
	~CRoadBlock()override;
};


//==================================================================
//壁兼道用ブロック
class CWallRoadBlock : public CManagerBlock
{
public:
	CWallRoadBlock();
	~CWallRoadBlock()override;
};


//==================================================================
//小さいブロック
class CSmallBlock : public CManagerBlock
{
public:
	CSmallBlock();
	~CSmallBlock()override;
};


//==================================================================
//上壁のブロック
class CUpWallBlock : public CManagerBlock
{
public:
	CUpWallBlock();
	~CUpWallBlock()override;
};


//==================================================================
//壊れるブロック
class CBreakBlock : public CManagerBlock
{
public:
	CBreakBlock();
	~CBreakBlock()override;
};


//==================================================================
//次のステージへ行く為のシップ
class CSpaceBattleShip000 : public CManagerBlock
{
public:
	CSpaceBattleShip000();
	~CSpaceBattleShip000()override;
};


//==================================================================
//足場
class CScaffold : public CManagerBlock
{
public:
	CScaffold();
	~CScaffold()override;
};


//==================================================================
//天井
class CCeiling : public CManagerBlock
{
public:
	CCeiling();
	~CCeiling()override;
};


//==================================================================
//木の板群
class CWoodenBorad : public CManagerBlock
{
public:
	CWoodenBorad() {};
	~CWoodenBorad()override {};
};

#endif // !_BLOCK_H_
