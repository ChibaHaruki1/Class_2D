//================================================
//
//�{�X�̃N���X�Ǘ�[boss.h]
//Auther:Haruki Chiba
//
//================================================

#pragma once

//================================================
//�C���N���[�h
#include "character.h"
#include "enemycharacter.h"
#include<vector>


//==================================================================
//�{�X�̏���
class CBoss : public CCharacter
{
public: //�A�N�Z�X�\

	CBoss(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CBoss()override;                           //�f�X�g���N�^
	HRESULT Init()override;                     //����������
	void Uninit()override;                      //�j������
	void ThisUnInit();
	void Update() override;                     //�X�V����
	void Draw()override;                        //�`�揈��
	void AttackPattern();                       //�U���̎�ނ��Ƃ̊֐�
	void AttackPattern001();                    //�U���̎�ނ��Ƃ̊֐�
	void StatusInit();                          //�����̕ϐ��̏����������֐�
	void AttackPatternSelect();                 //�U���̎�ނ�I������֐�
	void Collision();                           //�����蔻�菈���֐�
	void SpecialAttack();                       //�K�E�Z

	float PopX(); //�l���폜
	float PopY(); //�l���폜
	float PopZ(); //�l���폜

	//static CBoss* Create(D3DXVECTOR3 pos,bool bUse);
	static CBoss* Create(D3DXVECTOR3 pos);

private: //�A�N�Z�X�s��

	int m_nCoolTime; //�U���I���㎟�̍U���ɍs���܂ł̎���
	int m_nSize;     //vector�̔z�񐔂��擾���邽�߂̕ϐ�

	int m_nWhichSideNumber; //���E�̂ǂ���ɋ��邩�𐔎��œn�����߂̕ϐ�
	bool m_bOneCreateFlag;  //�Ռ��g���P��̂݌ĂԂ��߂�

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_VECTOR_SIZE = 50;                //vector�z��̍ő吔
	constexpr static float MAX_MOVE_SPEED = 0.25f;            //�{�X�̈ړ����x��ݒ�
	constexpr static float MAX_MOVE_SPEED_IN_PLAYER = 8.0f;   //�v���C���[�Ɍ���������

	//vector�Ɋւ���ϐ�
	std::vector<float> m_nSaveData; //�z������m�ۂ���ׂ̕ϐ�
	std::vector<float> m_nDataX;    //X���p�̃f�[�^��ۊǂ���p�̕ϐ�
	std::vector<float> m_nDataY;    //Y���p�̃f�[�^��ۊǂ���p�̕ϐ�
};
