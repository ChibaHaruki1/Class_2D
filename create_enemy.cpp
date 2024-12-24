//==================================
//
//“G‚ð¶¬‚·‚éˆ—[create_enenmy]
//Auther:Haruki Chiba
//
//==================================

#include "create_enemy.h"
#include "manager.h"
int CCreateEnemy::m_nRandom = 0;

CCreateEnemy::CCreateEnemy()
{

}
CCreateEnemy::~CCreateEnemy()
{

}
void CCreateEnemy::CreateEnemy()
{
	m_nRandom = -500+rand() % 1000;
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMY, 0, D3DXVECTOR3(CManager::GetScene()->GetPlayerX()->GetPos().x+ m_nRandom, 0.0f, 0.0f));
}