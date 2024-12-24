//===========================================
//
//当たり判定処理[collision.cpp]
//Auther:Haruki Chiba
//
//===========================================

#include "collision.h"
#include "manager.h"
#include "player.x.h"

//static変数の初期化
//bool CCollision::CollisionFlag = false;

#define PLAYER_COLLISION (40.0f)
#define BALLOON_COLLISION (10.0f)

//============================
//コンストラクタ
//============================
CCollision::CCollision()
{

}


//===========================
//デストラクタ
//===========================
CCollision::~CCollision()
{

}


//======================
//各方向の判定
//======================
bool CCollision::ColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//右の当たり判定
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		move.x = move.x + MAX_MOVESPEED; //右側に押す
		return true;
	}

	//左の当たり判定
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		move.x = move.x - MAX_MOVESPEED; //左側に押す
		return true;
	}

	//手前からの判定
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z + Size.z / 2 <= pos1.z - (Size1.z / 2) + 10.0f)
	{
		move.z = move.z - MAX_MOVESPEED; //手前に押す
		return true;
	}

	//後ろからの判定
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2) + 10.0f
		&& pos.z - Size.z / 2 >= pos1.z + (Size1.z / 2))
	{
		move.z = move.z + MAX_MOVESPEED; //奥に押す
		return true;
	}
	return false;
}

//======================
//各方向の判定
//======================
bool CCollision::ColiisionBox1(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//右の当たり判定
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		////move.x = move.x - 5.0f; //右側に押す
		return true;
	}

	//左の当たり判定
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		//move.x = move.x + 5.0f; //左側に押す
		return true;
	}
	return false;
}


//======================
//各方向の判定
//======================
bool CCollision::ColiisionBoxRoadBlock001(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//左の当たり判定
	if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		move.x = move.x - MAX_MOVESPEED; //右側に押す
		return true;
	}

	//右の当たり判定
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		move.x = move.x + MAX_MOVESPEED; //右側に押す
		return true;
	}

	return false;
}




//======================
//各方向の判定
//======================
bool CCollision::AnyColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//右の当たり判定
	if (pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2) + 1.0f
		&& pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2)
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		return true;
	}

	//左の当たり判定
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 1.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))//[]の中nCntBulletにする注意する
	{
		return true;
	}

	//手前からの判定
	else  if (pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z + Size.z / 2 <= pos1.z - (Size1.z / 2) + 10.0f)
	{
		return true;
	}

	//後ろからの判定
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
//全方位の判定
//======================
bool CCollision::ColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	if (pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2) + 10.0f
		&& pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2) - 10.0f
		&& pos.y + (POS_FACE + (Size.y)) >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) - 10.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) + 10.0f)//[]の中nCntBulletにする注意する
	{
		return true;
	}
	return false;
}



//======================
//全方位の判定
//======================
bool CCollision::AnyColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 10.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2) + 10.0f
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) - 10.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) + 10.0f)//[]の中nCntBulletにする注意する
	{
		return true;
	}
	return false;
}

//==========================================================================================================
//真ん中から右側の判定
//==========================================================================================================
bool CCollision::ColiisionBoxRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//真ん中から右半分の当たり判定（高さ無し）
	if (pos.x <=pos1.x + (Size1.x / 2) 
		&& pos.x + (Size.x / 2)>=pos1.x + (Size1.x / 2))
		
	{
		return true;
	}
	return false;
}

//======================
//左方向の判定
//======================
bool CCollision::ColiisionBoxLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//真ん中から右半分の当たり判定（高さ無し）
	//真ん中から右半分の当たり判定（高さ無し）
	if (pos.x >= pos1.x + (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2))

	{
		return true;
	}

	return false;
}


//==================
//内側の判定
//==================
bool CCollision::ColiisionBoxInside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//内側の判定(上)
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 1.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 1.0f
		&& pos.y >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) + 5.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) - 5.0f)//[]の中nCntBulletにする注意する
	{
		return true;
	}
	return false;
}


//==================
//下側の判定
//==================
bool CCollision::ColiisionBoxOutside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//内側の判定(下)
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 5.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 5.0f
		&& pos.y <= pos1.y
		&& pos.y >= pos1.y - (Size1.y*0.1f)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) + 5.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) - 5.0f)//[]の中nCntBulletにする注意する
	{
		move.y -= 6.0f;
		return true;
	}
	return false;
}


//====================
//円の当たり判定
//====================
bool CCollision::CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x; //posとpos1のｘの距離を常に比較
	float lengthZ = pos.z - pos1.z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthZ * lengthZ); //posとpos1の距離を計算

	float radiuSum = ((Size.x + Size1.x) + (Size.z + Size1.z)) * 0.25f;

	if (CenterDistance <= radiuSum)
	{
		return true;
	}

	return false;
}

//====================
//円の当たり判定
//====================
bool CCollision::CircleCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x; //posとpos1のｘの距離を常に比較
	float lengthY = pos.y - pos1.y; //posとpos1のｙの距離を常に比較
	float lengthZ = pos.z - pos1.z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//posとpos1の距離を計算

	float radiuSum = (Size.x * 0.5f + Size.y * 0.5f + Size.z * 0.5f)*0.5f;
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f)*0.5f;

	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true;
	}

	return false;
}


//==============================================================================================================================
//３ｄポリゴンとモデルの判定
//==============================================================================================================================

//======================
//各方向の判定
//======================
bool CCollision::ColiisionBox3D(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x - (X / 2) <= pos1.x + (Size1.x / 2) + 5.0f
		&& pos.x + (X / 2) >= pos1.x - (Size1.x / 2) - 5.0f
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 5.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 5.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 5.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 5.0f)//[]の中nCntBulletにする注意する
	{
		return true;
	}
	return false;
}

//======================
//右方向の判定
//======================
bool CCollision::ColiisionBox3DRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x + (X / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (X / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 1.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 1.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 1.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 1.0f)//[]の中nCntBulletにする注意する
	{
		return true;
	}
	return false;
}

//======================
//左方向の判定
//======================
bool CCollision::ColiisionBox3DLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x - (X / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (X / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 1.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 1.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 1.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 1.0f)//[]の中nCntBulletにする注意する
	{
		return true;
	}

	return false;
}


//====================
//円の当たり判定
//====================
bool CCollision::Coliision3DcircleBoss(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX, int nNumber) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->m_pos.x; //posとpos1のｘの距離を常に比較
	float lengthY = pos.y - pos1.y + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->m_pos.y; //posとpos1のｙの距離を常に比較
	float lengthZ = pos.z - pos1.z + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->m_pos.z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//posとpos1の距離を計算

	float radiuSum = (X * 0.5f + m_fSizeX + Y * 0.5f + Z * 0.5f) * 0.5f;
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f) * 0.5f;

	//判定
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true;
	}

	return false;
}

//====================
//円の当たり判定
//====================
bool CCollision::Coliision3Dcircle(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX, int nNumber) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x; //posとpos1のｘの距離を常に比較
	float lengthY = pos.y - pos1.y; //posとpos1のｙの距離を常に比較
	float lengthZ = pos.z - pos1.z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//posとpos1の距離を計算

	float radiuSumX = ((X + m_fSizeX) * 0.5f);
	float radiuSumY = ((Y) * 0.5f);
	float radiuSumZ = (Z * 0.5f);
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f) * 0.5f;

	//判定
	if (CenterDistance <= radiuSumX + radiuSumY + radiuSumZ + radiuSum1)
	{
		return true;
	}

	return false;
}


//====================
//円の当たり判定
//====================
bool CCollision::TenCricale(D3DXVECTOR3 & pos1, float A, float B, float C,float D) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//判定
	if (A<=pos1.x&&B>=pos1.y&&C>=pos1.x&&D<=pos1.y)
	{
		return true;
	}

	return false;
}
