//======================================
//
//��Q���̃N���X�Ǘ�[block.h]
//Auther:Chiba Haruki
//
//======================================

#ifndef _BLOCK_H_
#define _BLOCK_H_

//======================================
//�C���N���[�h
#include "objectX.h"


//==================================================================
//�X�g���e�W�[���N���X
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
//�X�g���e�W�[�N���X�p��
class CBlock000 : public CBlockXStrategy
{
public:
	CBlock000();
	~CBlock000();
	void Block();
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock001 : public CBlockXStrategy
{
public:
	CBlock001();
	~CBlock001();
	void Block();
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock002 : public CBlockXStrategy
{
public:
	CBlock002();
	~CBlock002();
	void Block();
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock003 : public CBlockXStrategy
{
public:
	CBlock003();
	~CBlock003();
	void Block();
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock004 : public CBlockXStrategy
{
public:
	CBlock004();
	~CBlock004();
	void Block();
};

//==================================================================

//�X�g���e�W�[�N���X�p��
class CBlock005 : public CBlockXStrategy
{
public:
	CBlock005();
	~CBlock005();
	void Block();
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock006 : public CBlockXStrategy
{
public:
	CBlock006();
	~CBlock006();
	void Block();
};


//==================================================================
//���̃X�e�[�W�֍s���p��obj
class CSpaceBattleShip : public CBlockXStrategy
{
public:
	CSpaceBattleShip();
	~CSpaceBattleShip();
	void Block();
};


//==================================================================
//�{�X��p�̃u���b�N�i�X�e�[�W�j
class CFinalBlock : public CBlockXStrategy
{
public:
	CFinalBlock();
	~CFinalBlock();
	void Block();
};


//==================================================================
// �{�X��p�̃u���b�N�i�X�e�[�W�j
class CFinalBlock1 : public CBlockXStrategy
{
public:
	CFinalBlock1() { m_aBlockFile = "data\\XFILE\\BLOCK\\FianlStageCeiling.x"; }
	~CFinalBlock1() {};
	void Block() {};
};


//==================================================================
//���ꂫ�Ɋւ���u���b�N
class CRubble : public CBlockXStrategy
{
public:
	CRubble() {};
	~CRubble() {};
	void Block() {};

};


//==================================================================
//�u���b�N�̊��N���X
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
	static int m_nCreateCount; //���ꂽ����ۊǂ���
};


//==================================================================
//3D��Q���̃N���X�Ǘ�
class CFiledBlock : public  CManagerBlock
{
public:
	CFiledBlock();
	~CFiledBlock()override;
private:
	
};


//==================================================================
//��ɏオ�邽�߂̃u���b�N
class CGoUpBlock : public CManagerBlock
{
public:
	CGoUpBlock();
	~CGoUpBlock()override;
};


//==================================================================
//���p�̃u���b�N
class CRoadBlock : public CManagerBlock
{
public:
	CRoadBlock();
	~CRoadBlock()override;
};


//==================================================================
//�ǌ����p�u���b�N
class CWallRoadBlock : public CManagerBlock
{
public:
	CWallRoadBlock();
	~CWallRoadBlock()override;
};


//==================================================================
//�������u���b�N
class CSmallBlock : public CManagerBlock
{
public:
	CSmallBlock();
	~CSmallBlock()override;
};


//==================================================================
//��ǂ̃u���b�N
class CUpWallBlock : public CManagerBlock
{
public:
	CUpWallBlock();
	~CUpWallBlock()override;
};


//==================================================================
//����u���b�N
class CBreakBlock : public CManagerBlock
{
public:
	CBreakBlock();
	~CBreakBlock()override;
};


//==================================================================
//���̃X�e�[�W�֍s���ׂ̃V�b�v
class CSpaceBattleShip000 : public CManagerBlock
{
public:
	CSpaceBattleShip000();
	~CSpaceBattleShip000()override;
};


//==================================================================
//����
class CScaffold : public CManagerBlock
{
public:
	CScaffold();
	~CScaffold()override;
};


//==================================================================
//�V��
class CCeiling : public CManagerBlock
{
public:
	CCeiling();
	~CCeiling()override;
};


//==================================================================
//�؂̔Q
class CWoodenBorad : public CManagerBlock
{
public:
	CWoodenBorad() {};
	~CWoodenBorad()override {};
};

#endif // !_BLOCK_H_
