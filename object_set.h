//======================================================
//
//�O���t�@�C������z�u����N���X�Ǘ�[object_set.h]
//Auther:Haruki Chiba
//
//======================================================

#pragma once

#include "main.h"
#include "stage_obj.h"

#define MAX_DATAMOJI (200) //������̔z��̍ő吔

class CObjectSet
{
public:
	CObjectSet();
	~CObjectSet();
	HRESULT Init();

	//�X�e�[�W���̓ǂݍ��ފ֐����܂Ƃ߂�֐�
	void StageOneInformation(const char*pFileName);       //�X�e�[�W�P�Ԗڂ̃I�u�W�F�N�g�̈ʒu�Ȃǂ�ǂݍ���
	void ResultScoreInformation(const char* pFileName);	  //���U���g�̃I�u�W�F�N�g�̈ʒu�Ȃǂ�ǂݍ���
	
	//�t�@�C���ɏ������ފ֐�
	void ResultScoreWrite(const char* pFileName); //���U���g�X�R�A�̏���ǂݍ���

	//���ꂼ��̃I�u�W�F�N�g�̓ǂݍ��ݏ����{��������֐��itxt�t�@�C���̒��g�̏���ǂݍ��ށj
	void LoodTelephonPole(FILE*pFile);         //�d���̏��Ɋւ���f�[�^��ǂݍ��ފ֐�
	void LoodBlock(FILE* pFile);               //�u���b�N�̏��Ɋւ���f�[�^��ǂݍ��ފ֐�
	void LoodBreakHouse(FILE* pFile);
	void LoodResultScore(FILE* pFile);         //���U���g�̏��ǂݍ��ݐ���
	void LoodEnemy();                          //�G�̓ǂݍ���
	void LoodEnemy1();                         //�G�̓ǂݍ��݂P

	static CObjectSet* Create(); //���̐���

	//�擾�p�̊֐�
	const char* GetStratBlockName(CObjectX::TYPE type);
	const char* GetEndBlockName(CObjectX::TYPE type);

	static int m_nClearScore;

private:

	//�e�L�X�g�t�@�C������ǂݍ��ގ��Ɏg�������o�ϐ�
	char m_aData[MAX_DATAMOJI]; //�������ǂݎ��@

	int m_nResultScore[10];
	int m_nResultScoreNumber;

	//�e�L�X�g�t�@�C���̓ǂݏ����Ɏg�������o�ϐ�
	const char* m_aFieldBlockStratName;  //�n�ʗp�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aGoUpBlockStratName;	 //�オ��p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aRoadBlockStratName;	 //���p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aWallRoadBlockStratName;	 //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aWallRoadBlock001StratName;	 //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aSmallBlockStratName;	 //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aSmallBlock001StratName;	 //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aUpWallBlockStratName;	 //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aBreakBlockStratName;	 //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�

	const char* m_aFieldBlockEndName;    //�n�ʗp�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aGoUpBlockEndName;     //�オ��p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aRoadBlockEndName;     //���p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aWallRoadBlockEndName;     //�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aWallRoadBlock001EndName;     //�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aSmallBlockEndName;     //�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aSmallBlock001EndName;     //�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aUpWallBlockEndName;     //�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aBreakBlockEndName;     //�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
};
