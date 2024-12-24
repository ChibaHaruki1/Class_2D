
//====================================================
//
//Xファイル読み込みクラス管理[objectX.h]
//Auther:Chiba Haruki
//
//====================================================

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "objectmanagerX.h"
#include "input.h"
#include "collision.h"
#include "ui.h"

#define MAX_TEXTURE (64) //保管できる最大のテクスチャー数
#define MAX_OBJECTSPEED (2.0f)

class CObjectX : public CObjectManagerX
{
public://外部からのアクセス可能
	CObjectX(int nPriority = DEFAULT_PRIORITY1);            //コンストラクタ
	~CObjectX() override;                                   //デストラクタ
	HRESULT Init()override;                                 //初期化処理
	void Uninit() override;                                 //破棄処理
	void Update() override;                                 //更新処理
	void Draw() override;                                   //描画処理
	void Size();                                            //３Dモデルのサイズを取得するための関数
	void Gravity();                                         //重力処理
	void GravityTogether();                                 //重力を同期させる処理
	void Junp(TYPE type,float fJumpPwer);                                   //飛ぶ処理
	void TargetHeadingTowards(CObjectX*pObject,float MAX_SPEED);            //目標に向かう処理
	HRESULT Lood();                                         //ｘファイルの読み込み関数（引数で読み込むファイルパスを渡す）
	void ObjectArrangement(CObjectX::TYPE type, CUI* pUI1); //配置ツール
	void BindTexture(LPDIRECT3DTEXTURE9 pTex, LPD3DXMESH pMesh, LPD3DXBUFFER BuffMat, DWORD NumMat, D3DXMATERIAL* pMat); //派生クラスの情報をもらうための関数（３Dモデル関連）

	bool CollisionBossPrts();                                                   //プレイヤーとボスの当たり判定
	bool CollisionRightSelectPlayer(CObjectX* pObject);                         //プレイヤーと指定したobjの当たり判定（単体）右側
	bool CollisionLeftSelectPlayer(CObjectX* pObject);                          //プレイヤーと指定したobjの当たり判定（単体）左側
	bool CollisionPlayerSelect(CObjectX* pObject);                              //プレイヤー他のobjの当たり判定
	bool CollisionPlayerInEnemy(CObjectX* pObject,float fMagnification);        //プレイヤー他のobjの当たり判定+当たり判定の範囲

	int& GetLife() { return m_nLife; }      //ライフを取得
	int& GetRandom() { return m_nRandom; }  //乱数を取得
	float& GetAngle() { return m_fAngle; }  //対角線の角度を取得

	D3DXVECTOR3& GetModelSize() { return m_ModelSize; }                                       //モデルのサイズを取得する
	D3DXVECTOR3& GetModelSizePrts(int nNumber) { return m_ModelSizePrts[nNumber]; }           //プレイヤーのモデルのサイズを取得する
	D3DXVECTOR3& GetPosPrts(int nNumber) { return m_posPrts[nNumber]; }                       //プレイヤーの各partsのposの情報を返す関数
	D3DXVECTOR3& GetModelSizePrtsBoss(int nNumber) { return m_ModelSizePrtsBoss[nNumber]; }   //ボスのモデルのサイズを取得する
	D3DXVECTOR3& GetPosPrtsBoss(int nNumber) { return m_posPrtsBoss[nNumber]; }               //ボスの各partsのposの情報を返す関数
	D3DXVECTOR3& GetModelSizePrtsEnemy(int nNumber) { return m_ModelSizePrtsEnemy[nNumber]; } //敵のモデルのサイズを取得する
	D3DXVECTOR3& GetPosPrtsEnemy(int nNumber) { return m_posPrtsEnemy[nNumber]; }             //敵の各partsのposの情報を返す関数

	D3DXVECTOR3& GetPos() { return m_pos; }                                                   //派生クラスのposの情報を返す関数
	D3DXVECTOR3& GetRot() { return m_rot; }                                                   //派生クラスのrotの情報を返す関数
	D3DXVECTOR3& GetMove() { return m_move; }                                                 //派生クラスmoveの情報を返す
	CCollision* GetCollision() { return m_pCollision; }                                       //当たり判定の情報を返す関数
	D3DXMATRIX& GetmtxWorld() { return m_mtxWorld; }                                          //ワールドマトリックスの情報を返す関数

	//マクロ定義
	constexpr static int MAX_PRTS = 19;          //プレイヤーのパーツ数
	constexpr static int MAX_BOSSPARTS = 18;     //ボスのパーツ数
	constexpr static int MAX_ENEMYPARTS = 20;    //敵の最大パーツ数
	constexpr static float MAX_GRAVITY_G = 0.5f; //重力の最大値

protected://継承クラスのみアクセス可能

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE]; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         //頂点バッファのポインタ
	D3DXVECTOR3 m_pos;                          //位置
	D3DXVECTOR3 m_move;                         //移動量
	D3DXVECTOR3 m_rot;                          //向き
	D3DXVECTOR3 m_col;                          //色
	D3DXMATRIX m_mtxWorld;                      //マトリックス
	LPD3DXMESH m_pMesh;                         //メッシュのへのポインタ
	LPD3DXBUFFER m_pBuffMat;                    //バッファへのポインタ
	DWORD m_dwNumMat;                           //マテリアルの数
	D3DXMATERIAL* m_pMat;                       //マテリアルのポインタ
	CCollision* m_pCollision;                   //当たり判定関数のポインター

	//モデルサイズの取得
	D3DXVECTOR3 min; //頂点の最小値
	D3DXVECTOR3 max; //頂点の最大値
	D3DXVECTOR3 m_ModelSize; //モデルのサイズを格納

	//パーツごとのサイズ取得
	D3DXVECTOR3 m_minPrts[MAX_PRTS]; //頂点の最小値
	D3DXVECTOR3 m_maxPrts[MAX_PRTS]; //頂点の最大値

	D3DXVECTOR3 m_ModelSizePrts[MAX_PRTS];            //モデルのサイズを格納
	D3DXVECTOR3 m_posPrts[MAX_PRTS];                  //モデルの位置を格納
	D3DXVECTOR3 m_ModelSizePrtsBoss[MAX_BOSSPARTS];   //ボスモデルのサイズを格納
	D3DXVECTOR3 m_posPrtsBoss[MAX_BOSSPARTS];         //ボスモデルの位置を格納
	D3DXVECTOR3 m_ModelSizePrtsEnemy[MAX_ENEMYPARTS]; //敵モデルのサイズを格納
	D3DXVECTOR3 m_posPrtsEnemy[MAX_ENEMYPARTS];       //敵モデルの位置を格納

	int m_nLife;              //Lifeを格納する変数（HP）
	int m_nRandom;            //乱数を格納する変数
	int m_nFrame;
	int m_nDieFrame;           //死亡カウンター
	float m_Gravity;           //重力加速度をつける
	float m_fAngle;            //角度から長さを求める用の変数
	bool m_GravityFlag;        //重力をONにするかどうか
	bool m_JumpFlag;           //ジャンプをしているかどうか
	bool m_bOneFlag;           //一回だけ処理を通したい時用の変数
	const char* m_aFileName;   //xファイルのパス渡しようの変数

	//マクロ定義
	constexpr static float D3DX_PI_ORI = 1.57f; //目標に向かう時の速さ
	
private:
	CUI* pUI;
};

#endif // !_OBJECT3D_H_

