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

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                  //テクスチャ（座標）の情報
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex);  //エフェクトの処理

	const char* GetEffectFileNamePass() { return m_aEffectFileName; }                               //ファイルパスを取得
	void SetEffectFileNamePass(const char* aEffectFieName) { m_aEffectFileName = aEffectFieName; }  //ファイルパスを設定

private:
	//マクロ定義
	constexpr static float MAX_EXPLOSION_LIFE = 8;        //アニメーションの更新する時のライフ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //自身のバッファー
	int m_nLife;                            //テクスチャのライフ（アニメーション用の）
	const char* m_aEffectFileName;          //テクスチャのファイルパス

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
	CManagerEffect(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManagerEffect();								   //デストラクタ
	HRESULT Init()override;							   //初期化処理
	void Uninit()override;							   //破棄処理
	void Update()override;							   //更新処理
	void Draw()override;							   //描画処理
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerEffect* Create(D3DXVECTOR3 pos, TYPE type); //生成処理

	CEffectDirection* GetEffectDirection() { return m_pEffectDirection000; } //ストラテジー基底クラスのポインターを取得

protected://継承クラスのみアクセス可能

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static int SET_BULLET_LIFE = 42;          //ライフの最大数
	constexpr static float m_fPillarOfFireSizeX = 200.0f; //柱状の炎のX軸の大きさ
	constexpr static float m_fPillarOfFireSizeY = 600.0f; //柱状の炎のY軸の大きさ
	constexpr static float m_fSepecialAttackX = 200.0f;   //必殺技のX軸の大きさ
	constexpr static float m_fSepecialAttackY = 200.0f;   //必殺技のY軸の大きさ
	constexpr static float MAX_EXPLOSION_TEX = 0.125f;    //アニメーションの分割数

private:
	int m_nEffectNumber;  //最後にエフェクトを呼ぶかどうか
	double m_dLifeCount; //アニメーションの速度
	float m_fMaxTex;     //テクスチャの最大のサイズ
	CEffectDirection* m_pEffectDirection000;  //ストラテジー基底クラスのポインター
};


//========================================================================================================
//こわれたときのエフェクト処理
class CBreakEffect : public CManagerEffect
{
public:
	CBreakEffect();            //コンストラクタ
	~CBreakEffect()override;   //デストラクタ

};


//========================================================================================================
//1つ目の爆発エフェクト
class CExplosion : public CManagerEffect
{
public:
	CExplosion();          //コンストラクタ
	~CExplosion()override; //デストラクタ
};


//========================================================================================================
//二つ目の爆発エフェクト
class CExplosion001 : public CManagerEffect
{
public:
	CExplosion001();           //コンストラクタ
	~CExplosion001()override;  //デストラクタ
};


//========================================================================================================
//炎エフェクト
class CFire : public CManagerEffect
{
public:
	CFire();              //コンストラクタ
	~CFire()override;	  //デストラクタ
	void Draw()override;  //描画処理

private:
	//マクロ定義
	constexpr static int FIRELIFE = 120; //ファイアのライフ
};


//========================================================================================================
//柱状の炎
class CPillarOfFire : public CManagerEffect
{
public:
	CPillarOfFire();           //コンストラクタ
	~CPillarOfFire()override;  //デストラクタ
	HRESULT Init()override;    //初期化処理
	void Update()override;     //更新処理

private:
	//マクロ定義
	constexpr static int PILLARFIRELIFE = 180; //ファイアのライフ
};


//========================================================================================================
//弾の軌道につくエフェクト
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CEffect()override;							//デストラクタ
	HRESULT Init()override;						//初期化処理
	void Uninit()override;						//破棄処理
	void Update()override;						//更新処理
	void Draw()override;						//描画処理
	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);

	static CEffect* Create(D3DXVECTOR3 pos);    //生成処理

private:
	//マクロ定義
	constexpr static int SET_EFFECT_LIFE = 30; //ライフの最大数
};


//========================================================================================================
//破片エフェクトのクラス
class CDebris : public CManagerEffect
{
public:
	CDebris();              //コンストラクタ
	~CDebris()override;     //デストラクタ
	void Update()override;  //更新処理

private:
	//マクロ定義
	constexpr static int DEBRISLIFE = 10;
};


//========================================================================================================
//必殺技のクラス
class CSpecialAttack : public CManagerEffect
{
public:
	CSpecialAttack();                               //コンストラクタ
	~CSpecialAttack()override;                      //デストラクタ
	void Update()override;                          //更新処理
	int& GetRotNumber() { return m_nRotNumber; }    //現在の向きを番号で取得する

private:
	//マクロ定義
	constexpr static int SPECIALATTACKLIFE = 180;

	int m_nRotNumber; //向きで大きさを変えるための変数
};
