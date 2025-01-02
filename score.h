//=======================================
//
//スコアのプロトタイプ宣言[score.h]
//Author:chiba haruki
//
//=======================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "object2D.h"
#include "scene.h"

class CManagerScore : public CObject2D
{
public://外部からのアクセス可能

	//弾構造体の定義
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		bool bUse; //使用しているかどうか
	}Score;

	CManagerScore(int nPriority = DEFAULT_PRIORITY);               //コンストラクタ
	~CManagerScore()override;                                      //デストラクタ
	 HRESULT Init()override;                                       //初期化
	 void Uninit()override;                                        //終了処理
	 void Update() override;                                       //更新処理
	 void Draw()override;                                          //描画処理
	 void DrawNoml()override;                                      //描画処理
	 void SetScorepos(D3DXVECTOR3 pos);                            //スコアの位置設定処理
	 void SetScore(int nScore);                                    //スコアの設定処理
	 void AddScore(int nValue);                                    //スコアのカウント増減処理
	 void InitAddScore(int nValue);                                //スコアのカウント増減処理
	 void PosScore(void);                                          //スコアの設定処理
	 static  CManagerScore* Create(CScene::MODE mode, int Number); //スコアの生成処理

	 //マクロ定義 （constexprでコンパイル時に初期化）
	 constexpr static int MAX_SCORE = 10;  //スコアの最大数
	 constexpr static int MAX_SIZE_X = 20; //スコアのX軸の大きさ
	 constexpr static int MAX_SIZE_Y = 40; //スコアのY軸の大きさ

private://外部からのアクセス不可能
	Score m_aScore[MAX_SCORE]; //スコアの情報
	int m_nSocre;              //スコアの値を保管する用
	float m_fPosX;             //スコアの初期化位置(x)の更新
	float m_fPosY;             //スコアの初期化位置(x)の更新
};

//ゲームスコア
class CGameScore : public CManagerScore
{
public:
	CGameScore(int nPriority = DEFAULT_PRIORITY);
	~CGameScore()override;
};

//リザルトスコアクラス
class CResultScore : public CManagerScore
{
public:
	CResultScore(int nPriority = DEFAULT_PRIORITY);
	~CResultScore()override;
};

#endif
