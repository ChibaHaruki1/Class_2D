//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//HRESULT InitSound(HWND hWnd);
//void UninitSound(void);
//HRESULT PlaySound(SOUND_LABEL label);
//void StopSound(SOUND_LABEL label);
//void StopSound(void);


typedef struct
{
	const char* pFilename;	// �t�@�C����
	float Volume;         //���ʒ���
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDINFO;

//�T�E���h�N���X
class CSound
{
public:

	typedef enum
	{
		SOUND_LABEL_ITEM_GET=0,		// SE1
		SOUND_LABEL_BGM,		// SE1
		SOUND_LABEL_BGM1,		// SE1
		SOUND_LABEL_SE_JUMP,	// �W�����v��
		SOUND_LABEL_SE_SHOT,
		SOUND_LABEL_SE_CHAGE,
		SOUND_LABEL_SE_WING,
		SOUND_LABEL_MAX,

	} SOUND_LABEL;

	CSound(); //�R���X�g���N�^
	~CSound(); //�f�X�g���N�^

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	HRESULT InitSound(HWND hWnd);
	void UninitSound();
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound();

private:
	IXAudio2* g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

};

#endif
