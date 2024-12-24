//=================================
//
//DirectX�Ăяo��[main.h]
//Auther:Chiba Haruki
//
//=================================

#ifndef _MAIN_H_ //���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_ //��d�C���N���[�h�h�~�̃}�N����`


#include <Windows.h>

#include "d3dx9.h"
#define DIRECTINPUT_VERSION   (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h" //���͏����ɕK�v
#include "Xinput.h" //�W���C�p�b�h�����ɕK�v
#include "xaudio2.h" //����ǉ�

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib") //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib") //�u���R���X�D���k�h�a�v�̊g�����C�u����
#pragma comment(lib,"dxguid.lib") //�c�h�q�d�b�s�w�R���|�[�l���g�i���i�j�ɕK�v
#pragma comment(lib,"winmm.lib") //�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v
#pragma comment(lib, "xinput.lib") //�W���C�p�b�h�����ɕK�v

//�}�N����`
#define SCREEN_WIDTH	(1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720) //�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//���_���̍\����
typedef struct
{
	D3DXVECTOR3 pos; //���_���
	float rhw; //���W�ϊ��p�W���i�P�D�O���ŌŒ�j
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos; //���_���
	D3DXVECTOR3 nor;
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;

int GetFPS();

#endif

