
//====================================================
//
//Xファイル読み込みクラス管理[objectX.h]
//Auther:Chiba Haruki
//
//====================================================


#pragma once

#ifndef _OBJECTX_H_
#define _OBJECTX_H_


//====================================================
//インクルード
#include "objectmanagerX.h"
#include "input.h"
#include "collision.h"
#include "ui.h"


class CObjectX : public CObjectManagerX
{
public://外部からのアクセス可能
	CObjectX(int nPriority = CObjectManagerX::DEFAULT_PRIORITY1);            //コンストラクタ
	~CObjectX() override;                                   //デストラクタ
	HRESULT Init()override;                                 //初期化処理
	void Uninit() override;                                 //破棄処理
	void Update() override;                                 //更新処理
	void Draw() override;                                   //描画処理
	void Size();                                            //３Dモデルのサイズを取得するための関数
	void Gravity();                                         //重力処理
	void GravityTogether();                                 //重力を同期させる処理
	void Junp(TYPE type, float fJumpPwer);                                   //飛ぶ処理
	void TargetHeadingTowards(CObjectX* pObject, float MAX_SPEED);           //目標に向かう処理
	HRESULT Lood();                                                          //ｘファイルの読み込み関数（引数で読み込むファイルパスを渡す）
	void ObjectArrangement(CObjectX::TYPE type, CUI* pUI1);                  //配置ツール

	bool CollisionBossPrts();                                                   //プレイヤーとボスの当たり判定
	bool CollisionRightSelectPlayer(CObjectX* pObject);                         //プレイヤーと指定したobjの当たり判定（単体）右側
	bool CollisionLeftSelectPlayer(CObjectX* pObject);                          //プレイヤーと指定したobjの当たり判定（単体）左側
	bool CollisionPlayerSelect(CObjectX* pObject);                              //プレイヤー他のobjの当たり判定
	bool CollisionPlayerInEnemy(CObjectX* pObject, float fMagnification);       //プレイヤー他のobjの当たり判定+当たり判定の範囲

	//==================================================
	//それぞれの処理に必要な情報を取得する
	int& GetLife() { return m_nLife; }          //ライフを取得
	int& GetRandom() { return m_nRandom; }      //乱数を取得
	int& GetFrame() { return m_nFrame; }        //フレームを取得
	int& GetDieFrame() { return m_nDieFrame; }  //死亡時のフレームを観測する用の情報を取得
	float& GetGravity() { return m_fGravity; }  //重力の情報を収得
	bool& GetJumpFlag() { return m_bJumpFlag; }
	bool& GetOneFlag() { return m_bOneFlag; }
	const char* GetFileName() { return m_aFileName; }

	//==================================================
	//各情報の設定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }                                //位置を引数と同期させる
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }                                //向きを引数と同期させる
	void SetLife(int nLife) { m_nLife = nLife; }                                 //ライフを引数と同期させる
	void SetRandom(int nRandom) { m_nRandom = nRandom; }                         //乱数を引数と同期させる	
	void SetFrame(int nFrame) { m_nFrame = nFrame; }                             //フレームを引数と同期させる
	void SetDieFrame(int nDieFrame) { m_nDieFrame = nDieFrame; }                 //死亡時のフレームを引数と同期させる
	void SetGravity(float fGravity) { m_fGravity = fGravity; }                   //重力の値を引数と同期させる
	void SetGravityFlag(bool bGravityFlag) { m_bGravityFlag = bGravityFlag; }    //重力フラグを引数と同期させる
	void SetJumpFlag(bool bJumpFlag) { m_bJumpFlag = bJumpFlag; }
	void SetOneFlag(bool bOneFlag) { m_bOneFlag = bOneFlag; }
	void SetFileName(const char* aFileName) { m_aFileName = aFileName; }

	//==================================================
	//パーツ毎の位置の情報を取得する
	inline D3DXVECTOR3& GetPosPrts(int nNumber) { return m_posPrts[nNumber]; }                       //プレイヤーの各partsのposの情報を返す関数
	inline D3DXVECTOR3& GetPosPrtsBoss(int nNumber) { return m_posPrtsBoss[nNumber]; }               //ボスの各partsのposの情報を返す関数
	inline D3DXVECTOR3& GetPosPrtsEnemy(int nNumber) { return m_posPrtsEnemy[nNumber]; }             //敵の各partsのposの情報を返す関数

   //==================================================
   //パーツ毎のサイズを取得する
	inline D3DXVECTOR3& GetModelSizePrts(int nNumber) { return m_ModelSizePrts[nNumber]; }           //プレイヤーのモデルのサイズを取得する
	inline D3DXVECTOR3& GetModelSizePrtsBoss(int nNumber) { return m_ModelSizePrtsBoss[nNumber]; }   //ボスのモデルのサイズを取得する
	inline D3DXVECTOR3& GetModelSizePrtsEnemy(int nNumber) { return m_ModelSizePrtsEnemy[nNumber]; } //敵のモデルのサイズを取得する

   //==================================================
   //プレイヤーのモデルサイズの取得
	inline D3DXVECTOR3& GetModelSize() { return m_ModelSize; }                                       //モデルのサイズを取得する

   //==================================================
   //三大基本情報の取得
	inline D3DXVECTOR3& GetPos() { return m_pos; }                                                   //派生クラスのposの情報を返す関数
	inline D3DXVECTOR3& GetRot() { return m_rot; }                                                   //派生クラスのrotの情報を返す関数
	inline D3DXVECTOR3& GetMove() { return m_move; }                                                 //派生クラスmoveの情報を返す

   //==================================================
   //生成に必要な物の情報の取得
	inline LPD3DXMESH& GetMesh() { return m_pMesh; }                                                 //meshの情報を返す
	inline LPD3DXBUFFER& GetBuffMat() { return m_pBuffMat; }                                         //BuffMatの情報を返す
	inline DWORD& GetdwNumMat() { return m_dwNumMat; }                                               //dwNumMatの数の情報を返す
	inline D3DXMATERIAL* GetMat() { return m_pMat; }                                                 //Matの情報を返す
	inline D3DXMATRIX& GetmtxWorld() { return m_mtxWorld; }                                          //ワールドマトリックスの情報を返す関数

	CCollision* GetCollision() { return m_pCollision; }                                              //当たり判定の情報を返す関数

    //==================================================
    //パーツごとのサイズ取得
	inline D3DXVECTOR3& GetMinPrts(int nNumber) { return m_minPrts[nNumber]; }
	inline D3DXVECTOR3& GetMaxPrts(int nNumber) { return m_maxPrts[nNumber]; }


	//==================================================
	//情報の値を計して設定
	inline D3DXVECTOR3& SetAddjustPos() { return m_pos; }    //位置の値を変更したい時の設定
	inline D3DXVECTOR3& SetAddjustRot() { return m_rot; }    //向きの値を変更したい時の設定
	inline D3DXVECTOR3& SetAddjustMove() { return m_move; }  //移動量の値を変更したい時の設定

	inline int& SetAddjustLife() { return m_nLife; }         //ライフの値を変更したいときの設定
	inline int& SetAddjustDieFrame() { return m_nDieFrame; } //死亡時のフレームを観測する用の情報を取得
	inline int& SetAddjustRandom() { return m_nRandom; }     //乱数の値を変更したい時の設定
	inline int& SetAddjustFrame() { return m_nFrame; }       //フレームの値を変更したい時の設定


	//==================================================
	//マクロ定義
	constexpr static int MAX_PRTS = 19;          //プレイヤーのパーツ数
	constexpr static int MAX_BOSSPARTS = 18;     //ボスのパーツ数
	constexpr static int MAX_ENEMYPARTS = 20;    //敵の最大パーツ数
	constexpr static int NUM_MOTION_KEY = 5;     //キーの数
	constexpr static float MAX_GRAVITY_G = 0.5f; //重力の最大値
	constexpr static float D3DX_PI_ORI = 1.57f;  //半円の角度

private:
	//マクロ定義
	constexpr static int MAX_TEXTURE = 32;             //保管できる最大のテクスチャー数
	constexpr static float OBJECT_SET_PLUS_X = 1.0f;   //オブジェクトの配置時のX軸の右の移動の速さ
	constexpr static float OBJECT_SET_MINUS_X = 1.0f;  //オブジェクトの配置時のX軸の左の移動の速さ
	constexpr static float OBJECT_SET_PLUS_Y = 1.0f;   //オブジェクトの配置時のY軸の上の移動の速さ
	constexpr static float OBJECT_SET_MINUS_Y = 1.0f;  //オブジェクトの配置時のY軸の下の移動の速さ


	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE]; //テクスチャへのポインタ
	D3DXMATRIX m_mtxWorld;                      //マトリックス

	D3DXMATERIAL* m_pMat;                       //マテリアルのポインタ
	LPD3DXMESH m_pMesh;                         //メッシュのへのポインタ
	LPD3DXBUFFER m_pBuffMat;                    //バッファへのポインタ
	DWORD m_dwNumMat;                           //マテリアルの数

	//モデルサイズの取得
	D3DXVECTOR3 min;                            //頂点の最小値
	D3DXVECTOR3 max;                            //頂点の最大値
	D3DXVECTOR3 m_ModelSize;                    //モデルのサイズを格納

	//パーツ毎の位置
	D3DXVECTOR3 m_posPrts[MAX_PRTS];            //モデルの位置を格納
	D3DXVECTOR3 m_posPrtsBoss[MAX_BOSSPARTS];   //ボスモデルの位置を格納
	D3DXVECTOR3 m_posPrtsEnemy[MAX_ENEMYPARTS]; //敵モデルの位置を格納

	//パーツごとのサイズ
	D3DXVECTOR3 m_minPrts[MAX_PRTS];                  //頂点の最小値
	D3DXVECTOR3 m_maxPrts[MAX_PRTS];                  //頂点の最大値
	D3DXVECTOR3 m_ModelSizePrts[MAX_PRTS];            //モデルのサイズを格納
	D3DXVECTOR3 m_ModelSizePrtsBoss[MAX_BOSSPARTS];   //ボスモデルのサイズを格納
	D3DXVECTOR3 m_ModelSizePrtsEnemy[MAX_ENEMYPARTS]; //敵モデルのサイズを格納

	CCollision* m_pCollision;                         //当たり判定関数のポインター
	D3DXVECTOR3 m_col;                                //色
	D3DXVECTOR3 m_pos;                                //位置
	D3DXVECTOR3 m_rot;                                //向き
	D3DXVECTOR3 m_move;                               //移動量
	CUI* pUI;

	int m_nLife;                //Lifeを格納する変数（HP）
	int m_nRandom;              //乱数を格納する変数
	int m_nFrame;               //フレームを格納する変数
	int m_nDieFrame;            //死亡カウンター
	float m_fGravity;           //重力加速度をつける
	float m_fAngle;             //角度から長さを求める用の変数
	bool m_bGravityFlag;        //重力をONにするかどうか
	bool m_bJumpFlag;           //ジャンプをしているかどうか
	bool m_bOneFlag;            //一回だけ処理を通したい時用の変数
	const char* m_aFileName;    //xファイルのパス渡しようの変数
};

#endif // !_OBJECT3D_H_

