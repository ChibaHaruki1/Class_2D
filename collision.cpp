//===========================================
//
//�����蔻�菈��[collision.cpp]
//Auther:Haruki Chiba
//
//===========================================

#include "collision.h"
#include "manager.h"
#include "player.x.h"

//static�ϐ��̏�����
//bool CCollision::CollisionFlag = false;

#define PLAYER_COLLISION (40.0f)
#define BALLOON_COLLISION (10.0f)

//============================
//�R���X�g���N�^
//============================
CCollision::CCollision()
{

}


//===========================
//�f�X�g���N�^
//===========================
CCollision::~CCollision()
{

}


//======================
//�e�����̔���
//======================
bool CCollision::ColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		move.x = move.x + MAX_MOVESPEED; //�E���ɉ���
		return true;
	}

	//���̓����蔻��
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		move.x = move.x - MAX_MOVESPEED; //�����ɉ���
		return true;
	}

	//��O����̔���
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z + Size.z / 2 <= pos1.z - (Size1.z / 2) + 10.0f)
	{
		move.z = move.z - MAX_MOVESPEED; //��O�ɉ���
		return true;
	}

	//��납��̔���
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2) + 10.0f
		&& pos.z - Size.z / 2 >= pos1.z + (Size1.z / 2))
	{
		move.z = move.z + MAX_MOVESPEED; //���ɉ���
		return true;
	}
	return false;
}

//======================
//�e�����̔���
//======================
bool CCollision::ColiisionBox1(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		////move.x = move.x - 5.0f; //�E���ɉ���
		return true;
	}

	//���̓����蔻��
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		//move.x = move.x + 5.0f; //�����ɉ���
		return true;
	}
	return false;
}


//======================
//�e�����̔���
//======================
bool CCollision::ColiisionBoxRoadBlock001(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//���̓����蔻��
	if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		move.x = move.x - MAX_MOVESPEED; //�E���ɉ���
		return true;
	}

	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		move.x = move.x + MAX_MOVESPEED; //�E���ɉ���
		return true;
	}

	return false;
}




//======================
//�e�����̔���
//======================
bool CCollision::AnyColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2) + 1.0f
		&& pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2)
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}

	//���̓����蔻��
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 1.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}

	//��O����̔���
	else  if (pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z + Size.z / 2 <= pos1.z - (Size1.z / 2) + 10.0f)
	{
		return true;
	}

	//��납��̔���
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 <= pos1.z + (Size1.z / 2) + 10.0f
		&& pos.z + Size.z / 2 >= pos1.z + (Size1.z / 2))
	{
		return true;
	}
	return false;
}


//======================
//�S���ʂ̔���
//======================
bool CCollision::ColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	if (pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2) + 10.0f
		&& pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2) - 10.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) - 10.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) + 10.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}
	return false;
}



//======================
//�S���ʂ̔���
//======================
bool CCollision::AnyColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 10.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2) + 10.0f
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) - 10.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) + 10.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}
	return false;
}

//==========================================================================================================
//�^�񒆂���E���̔���
//==========================================================================================================
bool CCollision::ColiisionBoxRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//�^�񒆂���E�����̓����蔻��i���������j
	if (pos.x <=pos1.x + (Size1.x / 2) 
		&& pos.x + (Size.x / 2)>=pos1.x + (Size1.x / 2))
		
	{
		return true;
	}
	return false;
}

//======================
//�������̔���
//======================
bool CCollision::ColiisionBoxLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//�^�񒆂���E�����̓����蔻��i���������j
	//�^�񒆂���E�����̓����蔻��i���������j
	if (pos.x >= pos1.x + (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2))

	{
		return true;
	}

	return false;
}


//==================
//�����̔���
//==================
bool CCollision::ColiisionBoxInside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�����̔���(��)
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 1.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 1.0f
		&& pos.y >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) + 5.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) - 5.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}
	return false;
}


//==================
//�����̔���
//==================
bool CCollision::ColiisionBoxOutside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�����̔���(��)
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 5.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 5.0f
		&& pos.y <= pos1.y
		&& pos.y >= pos1.y - (Size1.y*0.1f)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) + 5.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) - 5.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		move.y -= 6.0f;
		return true;
	}
	return false;
}


//====================
//�~�̓����蔻��
//====================
bool CCollision::CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthZ * lengthZ); //pos��pos1�̋������v�Z

	float radiuSum = ((Size.x + Size1.x) + (Size.z + Size1.z)) * 0.25f;

	if (CenterDistance <= radiuSum)
	{
		return true;
	}

	return false;
}

//====================
//�~�̓����蔻��
//====================
bool CCollision::CircleCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x; //pos��pos1�̂��̋�������ɔ�r
	float lengthY = pos.y - pos1.y; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//pos��pos1�̋������v�Z

	float radiuSum = (Size.x * 0.5f + Size.y * 0.5f + Size.z * 0.5f)*0.5f;
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f)*0.5f;

	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true;
	}

	return false;
}


//==============================================================================================================================
//�R���|���S���ƃ��f���̔���
//==============================================================================================================================

//======================
//�e�����̔���
//======================
bool CCollision::ColiisionBox3D(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x - (X / 2) <= pos1.x + (Size1.x / 2) + 5.0f
		&& pos.x + (X / 2) >= pos1.x - (Size1.x / 2) - 5.0f
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 5.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 5.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 5.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 5.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}
	return false;
}

//======================
//�E�����̔���
//======================
bool CCollision::ColiisionBox3DRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x + (X / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (X / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 1.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 1.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 1.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 1.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}
	return false;
}

//======================
//�������̔���
//======================
bool CCollision::ColiisionBox3DLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x - (X / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (X / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 1.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 1.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 1.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 1.0f)//[]�̒�nCntBullet�ɂ��钍�ӂ���
	{
		return true;
	}

	return false;
}


//====================
//�~�̓����蔻��
//====================
bool CCollision::Coliision3DcircleBoss(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX, int nNumber) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->m_pos.x; //pos��pos1�̂��̋�������ɔ�r
	float lengthY = pos.y - pos1.y + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->m_pos.y; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->m_pos.z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//pos��pos1�̋������v�Z

	float radiuSum = (X * 0.5f + m_fSizeX + Y * 0.5f + Z * 0.5f) * 0.5f;
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f) * 0.5f;

	//����
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true;
	}

	return false;
}

//====================
//�~�̓����蔻��
//====================
bool CCollision::Coliision3Dcircle(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX, int nNumber) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x; //pos��pos1�̂��̋�������ɔ�r
	float lengthY = pos.y - pos1.y; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//pos��pos1�̋������v�Z

	float radiuSumX = ((X + m_fSizeX) * 0.5f);
	float radiuSumY = ((Y) * 0.5f);
	float radiuSumZ = (Z * 0.5f);
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f) * 0.5f;

	//����
	if (CenterDistance <= radiuSumX + radiuSumY + radiuSumZ + radiuSum1)
	{
		return true;
	}

	return false;
}


//====================
//�~�̓����蔻��
//====================
bool CCollision::TenCricale(D3DXVECTOR3 & pos1, float A, float B, float C,float D) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//����
	if (A<=pos1.x&&B>=pos1.y&&C>=pos1.x&&D<=pos1.y)
	{
		return true;
	}

	return false;
}
