//================================================================
//
//�X�e�[�W���̃C�x���g�����N���X[event.h]
//Auther:Haruki Chiba
//
//================================================================

#pragma once

//=====================
//�C���N���[�h
#include <vector>
#include "instance.h"

//=====================================================================================================
//event�̊��N���X
//=====================================================================================================
class CEvent
{
public:
	CEvent();                  //�f�X�g���N�^
	~CEvent();                 //�R���X�g���N�^
	void Update();             //�X�V����
	void DropObj();            //obj�̗��Ƃ�����
	void BossDirection();      //�{�X�̉��o����	
	void DropMeteorite();      //覐΂𗎂Ƃ�����
	void CreateEnemy();        //�G�̐���
	bool& GetBossDirection() { return m_bBossDirection; } //�{�X�̐���������Ă��邩�ǂ����̏����擾

private:
	int m_nCreateWoodenBoradsCounter;            //�������鐔
	int m_nRandomRotX;                           //�����̃����_������ۊǂ���
	int m_nRandomRotY;                           //�����̃����_������ۊǂ���
	float m_nPosY;                               //��������Y����pos
	float m_fDropSpeed[CInstance::MAX_RUBBLE];   //���Ƃ����x�����߂�ϐ�
	float m_fDropPosY[CInstance::MAX_RUBBLE];    //���Ƃ��ʒu�����炩���ߌ��߂�ϐ�
	bool m_bBossDirection;                       //�{�X�̉��o��1�񂾂��o�����߂̏���
	bool m_bOneflag;                             //��񂾂�������ʂ��p�̕ϐ�
	bool m_bOneCreate;                           //��񂾂���������p�̕ϐ�
};
