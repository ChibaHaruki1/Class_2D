//======================================
//
//フェード処理[fade.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

//======================================
//インクルード
#include "object2D.h"

class CFade : public CObject2D
{
public:

	//フェードの種類
	enum class FADE
	{
		FADE_NONE = 0,  //何もなし
		FADE_IN,        //フェードイン
		FADE_OUT,       //フェードアウト
		FADE_MAX        //最大数
	};

	CFade(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CFade()override;						  //デストラクタ
	HRESULT Init()override;					  //初期化処理
	void Uninit()override;					  //破棄処理
	void  Update()override;					  //更新処理
	void Draw()override;					  //描画処理

	int GetCountAlpha() { return nCountAlpha; }   //alpha値を収得

	void SetFade(FADE Fadetype);              //フェードの設定
	static CFade* Create();                   //生成処理

private:
	FADE m_Fade;     //FADEの情報を格納する変数
	int nCountAlpha; //alpha値を保管する用の変数

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static int MAX_FADE_SPEED = 3;  //フェードの処理の色の変化する速度調整
};
