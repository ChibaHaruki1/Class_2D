//========================================
//
//�I�u�W�F�N�g�N���X�Ǘ�[object.h]
//Auther:Chiba Haruki
//
//========================================

#pragma once

//========================================
//�C���N���[�h
#include "main.h"

#define MAX_OBJECTMANAGERX (250) //�I�u�W�F�N�g�̍ő吔
#define DEFAULT_PRIORITY1 (3) //�f�t�H���g�̕`�揇
#define MAX_PRIORITY_MANAGER_OBJ (4) //�`�揇�̍ő吔

//�S�Ă��Ǘ�����̂ŉ��z�֐��i�������z�֐��j
class CObjectManagerX
{
public:

	enum class TYPE
	{
		NONE = 0,                    //����
		ENEMY,                       //�G
		ENEMY001,                    //�G001
		ENEMYINMOTION,               //���[�V�����t���̓G
		ENEMYINMOTION001,            //���[�V�����t���̓G001

		BOSS,                       //�{�X
		PLAYER,                     //�v���C���[
		FIELDBLOCK,                 //�n�ʗp�u���b�N
		GOUPBLOCK,                  //��ɏオ��p�̃u���b�N
		ROADBLOCK,                  //���p�u���b�N
		WALLROADBLOCK,              //�ǌ����p�u���b�N
		WALLROADBLOCK_001,          //�ǌ����p�u���b�N001
		SMALLBLOCK,                 //�������u���b�N
		SMALLBLOCK_001,             //�������u���b�N001
		UPWALLBLOCK,                //��ǂ̃u���b�N
           
		INITGUN,
		INITGUN001,
		TELEPHONPOLE,                //�d��
		SURVEILLANCECAMERAUP,        //�Ď��J�����̏㕔��
		SURVEILLANCECAMERADOWN,      //�Ď��J�����̉�����
		SHOP,                        //�X
		DEBRIS,                      //�j��
		BREAKHOUSE,                  //��ꂽ��
		MAX
	};

	typedef enum
	{
		NONEITEM = 0,
		TARGET_RECOVERY_MP,
		TARGET_RECOVERY_MP1,
		TRAGET_FARME_INIT,
		GEAR,
		ITEMBLOCK,
		MAXITEM
	}ITEMTYPE;

	typedef enum
	{
		NONEGIMMICK = 0,
		RED_RIGHTDOOR,
		RED_LEFTDOOR,
		MAXGIMMICK

	}GIMMICKTYPE;

	typedef enum
	{
		NONESTRATEGY = 0,
		BLOCK000,
		BLOCK001,
		BLOCK002,
		BLOCK003,
		BLOCK003_001,
		BLOCK004,
		BLOCK004_001,
		BLOCK005,
		BLOCK006,
		SPECEBATTLESHIP000,
		FINALBLOCK,
		FINALCEILLING,
		WODDENBORAD,
	}STRATEGYTYPE;

	CObjectManagerX(int nPriority = DEFAULT_PRIORITY1);
	virtual ~CObjectManagerX(); //�f�X�g���N�^
	virtual HRESULT Init() = 0; //������
	virtual void Uninit() = 0; //�I������
	virtual void Update() = 0; //�X�V����
	virtual void Draw() = 0; //�`�揈��
	static void ReleaseAll(); //�S�I�u�W�F�N�g�̉��
	static void UpdateAll(); //�S�I�u�W�F�N�g�̍X�V
	static void DrawAll(); //�S�I�u�W�F�N�g�̕`��
	static CObjectManagerX* GetObjectManagerX(int nPri, int nIndex); //�I�u�W�F�N�g�擾
	TYPE GetType(); //�^�C�v�擾
	ITEMTYPE GetItemType(); //�^�C�v�擾
	GIMMICKTYPE GetGimmickType(); //�^�C�v�擾
	void SetType(TYPE type); //�^�C�v�ݒ�
	void SetItemType(ITEMTYPE ItemType);
	void SetGimmickType(GIMMICKTYPE GimmickType);
	void Release(); //�������g�̉��


protected:

	/*CInputKeyBoard* pInputKeyBoard;
	CInputJoyPad* pInputJyoPad;*/

private:
	static CObjectManagerX* m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX]; //�S�I�u�W�F�N�g�̊Ǘ�
	static int m_nNumAll; //�I�u�W�F�N�g�̑���
	int m_nPriority;
	int m_nID; //�������g��ID
	TYPE m_type; //�I�u�W�F�N�g�^�C�v
	ITEMTYPE m_ItemType;
	GIMMICKTYPE m_GimmickType;

};


