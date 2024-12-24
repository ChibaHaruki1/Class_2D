//===================================
//
//�v���C���[�̃v���g�^�C�v�錾������t�@�C��[player.h]
//Author:chiba haruki
//
//===================================

#ifndef _PLAYERX_H_  //���̃}�O����`������Ă��Ȃ���������
#define _PLAYERX_H_  //��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "input.h"
#include "camera.h"
#include "collision.h"
#include "field.h"
#include "ui.h"
#include "2d_ui.h"
#include "character.h"

//�}�N����`
#define POS_FACE (70.0f)      //��̈ʒu
#define MAX_MOVESPEED (3.0f)  //���������炵�����̈ړ��ʂ̑���
#define MAX_TEXT_OBJECT (9)   //���z�u�c�[���ɐݒ肳��Ă�I�u�W�F�N�g�̐��[�P���i�O�X�^�[�g������j
#define MAX_BUULET_SPEED (30) //�e�̑���


class CPlayerX : public CCharacter
{
public: //�A�N�Z�X�\

	CPlayerX(int nPriority = DEFAULT_PRIORITY1);                 //�R���X�g���N�^
	~CPlayerX()override;                                         //�f�X�g���N�^
	HRESULT Init()override;                                      //����������
	void Uninit()override;                                       //�j������
	void Update()override;                                      //�X�V����
	void Draw()override;                                         //�`�揈��
	//void ObjectArrangement();                                   //�I�u�W�F�N�g�̔z�u�����i�����������t�@�C���ɏ������ށj
	void ObjectArrangementTelephonPole();                        //�d���̔z�u�����i�����������t�@�C���ɏ�������
	void KeySet();                                               //�L�[���Ƃ̏������܂Ƃ߂�֐�
	void ShopKeySet();                                           //���[�h��SHOP���̃L�[���Ƃ̏������܂Ƃ߂�֐�
	void BlockJudgement();                                       //�u���b�N�Ƃ̔���
	void Random();                                               //�����_������
	void Praticles();                                            //�p�[�e�B�N�����o������
	void NormalStateSummarizeFunction();                         //�ʏ펞�̊֐����܂Ƃ߂�֐�
	void ShopStateSummarizeFunction();                           //�X�ɖK�⎞�̊֐����܂Ƃ߂�֐�
	void CreateGun();                                            //�e�̐����C���X�^���X���Ă�
	void InstanceMakeNull();                                     //instance��nullptr�ɂ��鏈��
	void ShopInstanceMakeNullptr();                              //�V���b�v�Ŏg�p����C���X�^���X��nullptr�ɂ���
	void SelectGageUISize(float SIzeX,float SIze1X);             //�I���Q�[�W�̑傫����ݒ肷��֐�
	void SelectGageUISizeCalculation(const char*aSelect,float SIzeX,float SIze1X);  //�I���Q�[�W�̑傫�����v�Z�i���Z�⌸�Z�Ȃǁj����֐�
	void BlowAway();
	void HitAttack();          //����̍U�����󂯂��Ƃ��̏���
	void SceneMode(int nType); //scene�̕���

	//CObjectX�Ŏg�p����p�̎擾
	int& GetTelephonPoleCount() { return m_nTelephonCount; }   //�d���̔z���i�߂�
	int& GetAllTelephonPoleCount() { return m_nAllTelephonPoleCount; }   //�d���̔z���i�߂�
	int& GetMuki() { return m_nMuki; }

	static CPlayerX* Create();                   //��������

private: //�A�N�Z�X�s�\
	//�v���C���[�̏��
	typedef enum
	{
		NORMAI_MODE,
		SHOP_MODE,
		BUY_MODE,
		SEND_MODE,
	}PLAYER_STATE;

	//�C���X�^���X
	CUI* m_pTalkText;                    //�u�b���vtextUI
	CUI* m_pLaserUI;
	CShopMenu* m_pMenyu;                 //���j���[UI
	CBuyText* m_pBuyText;                //[�����A����]textUI
	CSelectGage* m_pSelectGage;          //�I�����̃Q�[�WUI
	CSelectGage001* m_pSelectGage001;    //�I�����̃Q�[�WUI

	//�\���̂̃C���X�^���X
	PLAYER_STATE m_PlayerState;
	PLAYER_STATE m_FlagSate;

	int m_nAlpha;                //�p�[�e�B�N���̓����x�������_���Ō��߂�ϐ�

	//�e�L�X�g�t�@�C���ɓo�^���鎞�̔z��ԍ�
	int m_nFiledCount;           //�t�B�[���h�̔z���i�߂�ׂ̃J�E���g
	int m_nTelephonCount;        //�d���̔z���i�߂�ׂ̃J�E���g�{text����ĂԂƂ��ɃC���X�^���X���̔z���o�^����������n��

	//�e�L�X�g�t�@�C���ɓo�^���邵���S�Ă̔z��ԍ�
	int m_nAllTelephonPoleCount; //�d���̍��̍��ꂽ����ۊǂ���
	int m_nAllFiledCount;        //�t�B�[���h�̍��̍��ꂽ����ۊǂ���

	//�p�[�e�B�N���Ɋւ���ϐ�
	int m_nFrame;                //���t���[�����ϑ�����ׂ̕ϐ�
	int m_nPraticlesCount;       //�p�[�e�B�N���̔z����J�E���g����ׂ̕ϐ�
	int m_nRandomCol;            //������ۊǂ���ׂ̕ϐ�

	//�v���C���[�Ɋւ���ϐ�
	int m_nMotionFrame;          //�e��łۂ̃J�E���g
	int m_nMotionFrame001;       //�e�����ۂ̃J�E���g
	int m_ObjectNumber;          //���݂̃I�u�W�F�N�g�̎�ނ̔ԍ���ۊǂ���ϐ�
	bool m_bNextStage;           //���̃X�e�[�W�֍s���ׂ̔�������p�̕ϐ�
	bool SpecialAttack;          //�K�E�Z���g���Ă���Ƃ��͓����Ȃ�

	//SHOP�Ɋւ���ϐ�
	int m_nSelectShopCount;      //���𔃂����J�E���g����ׂ̕ϐ�
	int m_nBuyOrSendCount;       //���������邩��I������Ƃ��ɔ��ʂ���悤�̕ϐ�

	//������я����ɕK�v�ȕϐ�
	int m_nFlayFrame;  //������Ԏ��Ԃ��ϑ�
	bool m_bFly;       //���@���������ł��邩�ǂ����̔���ׂ̈̕ϐ��i���[�V�����̍��G������邽�߁j

	int m_nDieRandom;  //���S���̃t���[����ۊǂ���ϐ�

	int m_nMuki;
	int m_nSpecialAttackCount;
	bool m_bOneCreate;

	//�}�N����`
	constexpr static float MAX_JUMPPAWER = 10.0f;          //��ԗ�
	constexpr static float MAX_SPECIALATTACKCOUNT = 60*60;  //�K�E�Z�̌��Ă鎞��
};

#endif 
