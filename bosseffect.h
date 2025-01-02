//=========================================
//
//ボス用エフェクトのクラス管理[efect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once

//=========================
//インクルード
#include "object3D.h"


//========================================================================================================
//ストラテジークラス基底
class CBossEffectDirection
{
public:
	CBossEffectDirection();   //コンストラクタ
	~CBossEffectDirection();  //デストラクタ

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                 //テクスチャの設定
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex); //テクスチャの更新

	const char* m_pEffectFileName; //ファイルパス

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //自身のバッファ
	int m_nLife; //アニメーションのライフ用の変数
};


//========================================================================================================
//ストラテジークラス継承　衝撃破
class CAttackEffect : public CBossEffectDirection
{
public:
	CAttackEffect();   //コンストラクタ
	~CAttackEffect();  //デストラクタ
};

//========================================================================================================
//必殺技
class CSourceSpecialAttackBoss : public CBossEffectDirection
{
public:
	CSourceSpecialAttackBoss();   //コンストラクタ
	~CSourceSpecialAttackBoss();  //デストラクタ
};


//========================================================================================================
//ボスエフェクト管理の基底クラス
class CManagerBossEffect : public CObject3D
{
public: //外部からアクセス可能
	CManagerBossEffect(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManagerBossEffect();								   //デストラクタ
	HRESULT Init()override;								   //初期化処理
	void Uninit()override;								   //破棄処理
	void Update()override;								   //更新処理
	void Draw()override;								   //描画処理
	void SetEffect(D3DXVECTOR3 pos);                       //エフェクトの位置の設定

	static CManagerBossEffect* Create(D3DXVECTOR3 pos, TYPE type);  //生成処理（継承クラスをTYPEで生成する）

	bool& GetFly() { return m_bFly; }                 //衝撃波に当たったかどうか判定用の変数の取得
	int& GetRotNumber() { return m_nBossRotNumber; }  //左右どちらの向きになっているか数字で判定する情報を取得

	CBossEffectDirection* m_pEffectDirection000;      //ストラテジー基底クラスのポインター

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static float MAX_BOSSANIMETION_TEX = 0.125f;     //アニメーションの分割数
	constexpr static float MAX_BOSSANIMATION_LIFE = 8;         //アニメーションの更新する時のライフ
	constexpr static float MAX_BOSSSPECIALATTACK_X = 200.0f;   //ボスの必殺技のY軸の大きさ
	constexpr static float MAX_BOSSSPECIALATTACK_Y = 200.0f;   //ボスの必殺技のY軸の大きさ
	constexpr static float PLUS_POS_Y = 100.0f;                //必殺技のY軸の位置を足し合わせる為のマクロ
	constexpr static float MAX_DAMAGE = 0.01f;                 //ボスの必殺技のY軸の大きさ

protected://継承クラスのみアクセス可能
	double m_dLifeCount;  //アニメーションの速度
	bool m_bFly;          //吹っ飛ぶかどうか

private://外部からのアクセス不可能
	int m_nEffectNumber;  //最後にエフェクトを呼ぶかどうか
	int m_nBossRotNumber; //向きで大きさを変えるための変数
};


//========================================================================================================
//衝撃波のエフェクト処理
class CImpact : public CManagerBossEffect
{
public:
	CImpact();              //コンストラクタ
	~CImpact()override;     //デストラクタ
	void Update()override;  //更新処理
};


//========================================================================================================
//必殺技のエフェクト処理
class CBossSpecialAttack : public CManagerBossEffect
{
public:
	CBossSpecialAttack();           //コンストラクタ
	~CBossSpecialAttack()override;  //デストラクタ
	void Update()override;          //更新処理

};