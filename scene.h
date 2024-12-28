//==============================================
//
//��ʑJ�ڂ̃N���X�Ǘ�[scene.h]
//Auther:Haruki Chiba
//
//==============================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "ui.h"
#include "player.x.h"
#include "object_set.h"
#include "block.h"
#include "fade.h"
#include "skydoom.h"

//���N���X
class CScene
{
public:

	//��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0, //�^�C�g��
		MODE_GAME01, //�X�e�[�W�P
		MODE_GAME02, //�X�e�[�W�Q
		MODE_RESULT, //���U���g
		MODE_GAMEOVER,
		MODE_MAX //�ő吔
	}MODE;

	CScene(); //�R���X�g���N�^
	virtual ~CScene(); //�f�X�g���N�^
	virtual HRESULT Init(); //����������
	virtual void Uninit(); //�I������
	virtual void Update(); //�p���N���X�X�V����
	void AnyUpdate();      //
	virtual void Draw(); //�`�揈��
	MODE& GetMode() { return m_Mode; } //���݃��[�h�̎擾
	//static CMPTargetReTime* GetMPTargetReTime(); //�ΏۃI�u�W�F�N�g�̎��߂��p��MP�����擾����

	static CScene* Create(MODE mode); //mode�ɍ��킹��create�Ǘ�������

	CCamera* GetCamera(); //�J�����̏����擾
	CLight* GetLight(); //�����̏����擾
	CPlayerX* GetPlayerX();
	
	CObjectSet* GetObjectSet();

protected:
	CCamera* m_pCamera; //�J�����̏��
	CLight* m_pLight; //�����̏��
	CPlayerX* m_pPlayerX;
	CObjectSet* m_pObjectSet;

	MODE m_Mode; //���݂̃��[�h�̊Ǘ��ϐ�

	bool m_bOneSound;

private:
};


//�X�e�[�W�P�̃N���X�Ǘ�
class CGame01 : public CScene
{
public: //�A�N�Z�X�\
	CGame01(); //�R���X�g���N�^
	~CGame01()override; //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override; //�j������
	void Update()override; //�X�V����
	void Draw()override; //�`�揈��
	void CompileLood(); //�e�N�X�`����Lood�֐����܂Ƃ߂�֐�
	void CompileCreate(); //create�֐����܂Ƃ߂�֐�
	void CompileUnlood(); //�e�N�X�`����Unlood�֐����܂Ƃ߂�֐�

private: //�A�N�Z�X�s�\
};


//�X�e�[�W�Q�̃N���X�Ǘ�
class CGame02 : public CScene
{
public: //�A�N�Z�X�\
	CGame02(); //�R���X�g���N�^
	~CGame02()override; //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override; //�j������
	void Update()override; //�X�V����
	void Draw()override; //�`�揈��
	void CompileLood(); //�e�N�X�`����Lood�֐����܂Ƃ߂�֐�
	void CompileCreate(); //create�֐����܂Ƃ߂�֐�
	void CompileUnlood(); //�e�N�X�`����Unlood�֐����܂Ƃ߂�֐�
};

//�^�C�g���̃N���X�Ǘ�
class CTitle : public CScene
{
public: //�A�N�Z�X�\
	CTitle(); //�R���X�g���N�^
	~CTitle()override; //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override; //�j������
	void Update()override; //�X�V����
	void Draw()override; //�`�揈��

private: //�A�N�Z�X�s�\
	bool Count; //mode�̈ڍs�̔���ϐ�
	CFade* pFade;
};


//���U���g�̃N���X�Ǘ�
class CResult : public CScene
{
public: //�A�N�Z�X�\
	CResult(); //�R���X�g���N�^
	~CResult()override; //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override; //�j������
	void Update()override; //�X�V����
	void Draw()override; //�`�揈��

private: //�A�N�Z�X�s�\
	bool Count; //mode�̈ڍs�̔���ϐ�
};


//���U���g�̃N���X�Ǘ�
class CGameOver : public CScene
{
public: //�A�N�Z�X�\
	CGameOver(); //�R���X�g���N�^
	~CGameOver()override; //�f�X�g���N�^
	HRESULT Init()override; //����������
	void Uninit()override; //�j������
	void Update()override; //�X�V����
	void Draw()override; //�`�揈��

private: //�A�N�Z�X�s�\
	bool Count; //mode�̈ڍs�̔���ϐ�
};

#endif // !_SCENE_H_
