//======================================================
//
//外部ファイルから配置するクラス管理[object_set.h]
//Auther:Haruki Chiba
//
//======================================================

#pragma once

#include "main.h"
#include "stage_obj.h"

#define MAX_DATAMOJI (200) //文字列の配列の最大数

class CObjectSet
{
public:
	CObjectSet();
	~CObjectSet();
	HRESULT Init();

	//ステージ毎の読み込む関数をまとめる関数
	void StageOneInformation(const char*pFileName);       //ステージ１番目のオブジェクトの位置などを読み込む
	void ResultScoreInformation(const char* pFileName);	  //リザルトのオブジェクトの位置などを読み込む
	
	//ファイルに書き込む関数
	void ResultScoreWrite(const char* pFileName); //リザルトスコアの情報を読み込む

	//それぞれのオブジェクトの読み込み処理＋生成する関数（txtファイルの中身の情報を読み込む）
	void LoodTelephonPole(FILE*pFile);         //電柱の情報に関するデータを読み込む関数
	void LoodBlock(FILE* pFile);               //ブロックの情報に関するデータを読み込む関数
	void LoodBreakHouse(FILE* pFile);
	void LoodResultScore(FILE* pFile);         //リザルトの情報読み込み生成
	void LoodEnemy();                          //敵の読み込み
	void LoodEnemy1();                         //敵の読み込み１

	static CObjectSet* Create(); //情報の生成

	//取得用の関数
	const char* GetStratBlockName(CObjectX::TYPE type);
	const char* GetEndBlockName(CObjectX::TYPE type);

	static int m_nClearScore;

private:

	//テキストファイルから読み込む時に使うメンバ変数
	char m_aData[MAX_DATAMOJI]; //文字列を読み取る　

	int m_nResultScore[10];
	int m_nResultScoreNumber;

	//テキストファイルの読み書きに使うメンバ変数
	const char* m_aFieldBlockStratName;  //地面用のブロックの読み込み用の名前変数
	const char* m_aGoUpBlockStratName;	 //上がる用のブロックの読み込み用の名前変数
	const char* m_aRoadBlockStratName;	 //道用のブロックの読み込み用の名前変数
	const char* m_aWallRoadBlockStratName;	 //壁兼道用のブロックの読み込み用の名前変数
	const char* m_aWallRoadBlock001StratName;	 //壁兼道用のブロックの読み込み用の名前変数
	const char* m_aSmallBlockStratName;	 //壁兼道用のブロックの読み込み用の名前変数
	const char* m_aSmallBlock001StratName;	 //壁兼道用のブロックの読み込み用の名前変数
	const char* m_aUpWallBlockStratName;	 //壁兼道用のブロックの読み込み用の名前変数
	const char* m_aBreakBlockStratName;	 //壁兼道用のブロックの読み込み用の名前変数

	const char* m_aFieldBlockEndName;    //地面用のブロックの読み込み用の名前変数
	const char* m_aGoUpBlockEndName;     //上がる用のブロックの終了用の名前変数
	const char* m_aRoadBlockEndName;     //道用のブロックの終了用の名前変数
	const char* m_aWallRoadBlockEndName;     //壁兼道用のブロックの終了用の名前変数
	const char* m_aWallRoadBlock001EndName;     //壁兼道用のブロックの終了用の名前変数
	const char* m_aSmallBlockEndName;     //壁兼道用のブロックの終了用の名前変数
	const char* m_aSmallBlock001EndName;     //壁兼道用のブロックの終了用の名前変数
	const char* m_aUpWallBlockEndName;     //壁兼道用のブロックの終了用の名前変数
	const char* m_aBreakBlockEndName;     //壁兼道用のブロックの終了用の名前変数
};
