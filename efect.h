//=========================================
//
//エフェクトのクラス管理[efect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once
	
//=========================================
//インクルード
#include "object3D.h"
#include<memory>


//========================================================================================================
//ストラテジークラス基底
class CEffectDirection
{
public:
	CEffectDirection();  //コンストラクタ
	~CEffectDirection(); //デストラクタ

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                //テクスチャ（座標）の情報
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,double dLifeCount,float fMaxTex);  //エフェクトの処理

	const char* m_pEffectFileName;          //テクスチャのファイルパス
	int m_nLife;                            //テクスチャのライフ（アニメーション用の）
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //自身のバッファー
};


//========================================================================================================
//ストラテジークラス継承　雷
class CThunder : public CEffectDirection
{
public:
	CThunder();   //コンストラクタ
	~CThunder();  //デストラクタ			
};


//========================================================================================================
//ストラテジークラス継承　爆発
class CExplotion : public CEffectDirection
{
public:
	CExplotion();   //コンストラクタ
	~CExplotion();  //デストラクタ						  
};


//========================================================================================================
//炎
class CExplotionPillar : public CEffectDirection
{
public:
	CExplotionPillar();   //コンストラクタ
	~CExplotionPillar();  //デストラクタ
};


//========================================================================================================
//柱状の炎
class CExplotionPillar001 : public CEffectDirection
{
public:
	CExplotionPillar001();   //コンストラクタ
	~CExplotionPillar001();	 //デストラクタ
};


//========================================================================================================
//ストラテジー継承　破片
class CFormerDebris : public CEffectDirection
{
public:
	CFormerDebris();   //コンストラクタ
	~CFormerDebris();  //デストラクタ
};


//========================================================================================================
//ストラテジー継承　必殺技
class CSourceSpecialAttack : public CEffectDirection
{
public:
	CSourceSpecialAttack();   //コンストラクタ
	~CSourceSpecialAttack();  //デストラクタ
};


//========================================================================================================
//エフェクト管理の基底クラス
//========================================================================================================
class CManagerEffect : public CObject3D
{
public:
	CManagerEffect(int nPriority=DEFAULT_PRIORITY);
	~CManagerEffect();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerEffect* Create(D3DXVECTOR3 pos, TYPE type);

	CEffectDirection* m_pEffectDirection000;

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static float m_fPillarOfFireSizeX = 200.0f; //柱状の炎のX軸の大きさ
	constexpr static float m_fPillarOfFireSizeY = 600.0f; //柱状の炎のY軸の大きさ
	constexpr static float m_fSepecialAttackX = 200.0f;   //必殺技のX軸の大きさ
	constexpr static float m_fSepecialAttackY = 200.0f;   //必殺技のY軸の大きさ
	constexpr static float MAX_EXPLOSION_TEX = 0.125f;    //アニメーションの分割数
	constexpr static float MAX_EXPLOSION_LIFE = 8;        //アニメーションの更新する時のライフ

protected://継承クラスのみアクセス可能
	double m_dLifeCount; //アニメーションの速度
	float m_fMaxTex;     //テクスチャの最大のサイズ

private:
	int m_nEffectNumber;  //最後にエフェクトを呼ぶかどうか

};


//========================================================================================================
//こわれたときのエフェクト処理
class CBreakEffect : public CManagerEffect
{
public:
	CBreakEffect();
	~CBreakEffect()override;
	
};


//========================================================================================================
//1つ目の爆発エフェクト
class CExplosion : public CManagerEffect
{
public:
	CExplosion();
	~CExplosion()override;
};


//========================================================================================================
//二つ目の爆発エフェクト
class CExplosion001 : public CManagerEffect
{
public:
	CExplosion001();
	~CExplosion001()override;
};


//========================================================================================================
//炎エフェクト
class CFire : public CManagerEffect
{
public:
	CFire();
	~CFire()override;
	void Draw()override;
};


//========================================================================================================
//柱状の炎
class CPillarOfFire : public CManagerEffect
{
public:
	CPillarOfFire();
	~CPillarOfFire();
	HRESULT Init()override;
	void Update()override;

private:
};


//========================================================================================================
//弾の軌道につくエフェクト
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = DEFAULT_PRIORITY);
	~CEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);

	static CEffect* Create(D3DXVECTOR3 pos);

private:
	int m_nLife;
};


//========================================================================================================
//破片エフェクトのクラス
class CDebris : public CManagerEffect
{
public:
	CDebris();
	~CDebris();
	void Update()override;

private:
	float m_fSiseX;
};


//========================================================================================================
//必殺技のクラス
class CSpecialAttack : public CManagerEffect
{
public:
	CSpecialAttack();
	~CSpecialAttack();
	void Update()override;
	int& GetRotNumber() { return m_nRotNumber; }

private:
	int m_nRotNumber; //向きで大きさを変えるための変数
};
