//======================================
//
//�S�̂��Ǘ�����N���X[manager.h]
//Auther:Chiba Hruki
//
//======================================

#ifndef _MANAGER_H_  //���̃}�O����`������Ă��Ȃ���������
#define _MANAGER_H_  //��d�C���N���[�h�h�~�̃}�N����`

#include "rendererh.h"
#include "input.h"
#include "block.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "instance.h"
#include "scene.h"
#include "object_set.h"
#include "event.h"

class CManager
{
public:
	CManager();  //�R���X�g���N�^
	~CManager(); //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow); //����������
	void Uninit(); //�I������
	void Update(); //�X�V����
	void Draw(); //�`�揈��
	//void Uninit

	static CRenderer* GetRenderer(); //�����_���[�̏����擾
	static CInputKeyBoard* GetKeyBorad(); //�L�[�{�[�h�̏����擾
	static CInputJoyPad* GetJyoPad(); //�W���C�p�b�g�̏����擾
	static CSound* GetSound(); //�����̏����擾
	static CInstance* GetInstance() { return m_pInstance; }
	static CScene* GetScene() { return m_pScene; }
	static CObjectSet* GetObjectSet() { return m_pObjectSet; }
	static CEvent* GetEvent() { return m_pEvent; }
	static void SetMode(CScene::MODE mode);  //���[�h�̊m��

private:
	static CRenderer* m_pRenderer;       //�����_���[�̏��
	static CInputKeyBoard* m_pKeyBoard;  //�L�[�{�[�h�̏��
	static CInputJoyPad* m_pJyoPad;      //�W���C�p�b�g�̏��
	static CSound* m_pSound;             //�����̏��
	static CScene* m_pScene;             //���݂̃��[�h
	static CInstance* m_pInstance;       //�e�N���X�̏�������
	static CObjectSet* m_pObjectSet;     //�e�L�X�g�t�@�C������ǂݍ���
	static CEvent* m_pEvent;             //�X�e�[�W���̃C�x���g���
};

#endif
