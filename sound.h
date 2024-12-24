//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//HRESULT InitSound(HWND hWnd);
//void UninitSound(void);
//HRESULT PlaySound(SOUND_LABEL label);
//void StopSound(SOUND_LABEL label);
//void StopSound(void);


typedef struct
{
	const char* pFilename;	// ファイル名
	float Volume;         //音量調整
	int nCntLoop;		// ループカウント
} SOUNDINFO;

//サウンドクラス
class CSound
{
public:

	typedef enum
	{
		SOUND_LABEL_ITEM_GET=0,		// SE1
		SOUND_LABEL_BGM,		// SE1
		SOUND_LABEL_BGM1,		// SE1
		SOUND_LABEL_SE_JUMP,	// ジャンプ音
		SOUND_LABEL_SE_SHOT,
		SOUND_LABEL_SE_CHAGE,
		SOUND_LABEL_SE_WING,
		SOUND_LABEL_MAX,

	} SOUND_LABEL;

	CSound(); //コンストラクタ
	~CSound(); //デストラクタ

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	HRESULT InitSound(HWND hWnd);
	void UninitSound();
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound();

private:
	IXAudio2* g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* g_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

};

#endif
