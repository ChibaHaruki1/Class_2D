//==================================
//
//�G�̃N���X�Ǘ�[enemy.h]
//Auther:Chiba Haruki
//
//==================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "objectX.h"
#include "enemycharacter.h"

class CManagerEnemy : public CObjectX
{
public:
	CManagerEnemy(int nPriority = DEFAULT_PRIORITY);   //�����t���R���X�g���N�^
	~CManagerEnemy()override;                          //�f�X�g���N�^
	HRESULT Init()override;                      //����������
	void Uninit()override;                       //�I������
	void Update() override;                      //�X�V����
	void Draw()override;                         //�`�揈��
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type);
};

//3D(X)�G�̃N���X
class CEnemyX : public CManagerEnemy
{
public:
	CEnemyX() { m_fAngle = 0.0f; }
	~CEnemyX()override{};
	void Update()override;
private:
	const float m_fMAX_SPPED = 2.0f;
	float m_fAngle;
};

//001
class CEnemy001X : public CManagerEnemy
{
public:
	CEnemy001X() { m_fAngle = 0.0f; }
	~CEnemy001X()override {};
	void Update()override;
	
private:
	//�}�N����`
	constexpr static float MAX_DAMAGE = 0.005f;
};

#endif // !_ENEMY_H_

