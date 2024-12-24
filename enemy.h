//==================================
//
//敵のクラス管理[enemy.h]
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
	CManagerEnemy(int nPriority = DEFAULT_PRIORITY);   //引数付きコンストラクタ
	~CManagerEnemy()override;                          //デストラクタ
	HRESULT Init()override;                      //初期化処理
	void Uninit()override;                       //終了処理
	void Update() override;                      //更新処理
	void Draw()override;                         //描画処理
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type);
};

//3D(X)敵のクラス
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
	//マクロ定義
	constexpr static float MAX_DAMAGE = 0.005f;
};

#endif // !_ENEMY_H_

