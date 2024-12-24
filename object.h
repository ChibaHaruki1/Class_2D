//========================================
//
//�I�u�W�F�N�g�N���X�Ǘ�[object.h]
//Auther:Chiba Haruki
//
//========================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

#define MAX_OBJECT (250) //�I�u�W�F�N�g�̍ő吔
#define DEFAULT_PRIORITY (3) //�`�揇�̍ő吔
#define MAX_PRIORITY_OBJ (4) //�`�揇�̍ő吔

//#include "main.h"
//#include "input.h"

//�S�Ă��Ǘ�����̂ŉ��z�֐��i�������z�֐��j
class CObject
{
public:

	//
	typedef enum
	{
		NONE = 0,           //����
		ENEMY,              //�G
		PLAYER,             //�v���C���[
		BULLET,             //�ʏ�e
		SPECIALBULLET,      //�K�E�e
		BOSSBULLET,         //�{�X�̒e
		ENEMYBULLET,
		BLOCK,              //�u���b�N
		ITEM,               //�A�C�e��
		SCORE,              //�X�R�A
		FIELD,              //�n��
		PRTICLES,           //�p�[�e�B�N��
		PRTICLES001,        //�p�[�e�B�N���P
		EFFECT,             //�G�t�F�N�g
		EXPLOSION,          //����
		EXPLOSION001,       //�����P
		THENDER,            //��
		FIRE,               //��
		PILLAROFFIRE,       //����̉�
		IMPACT,             //�Ռ��g
		DEBRIS,             //�j��
		SPECIALATTACK,      //�K�E�Z
		BOSSSPECIALATTACK,  //�{�X�̕K�E�Z

		//UI
		SCREEN,         //�w�i
		BUYSENDTEXT,    //�����e�L�X�g
		HP,             //HP�Q�[�W
		MP,             //MP�Q�[�W
		BOSSHP,         //�{�XHP�Q�[�W
		BOSSMP,         //�{�XMP�Q�[�W
		FUELGAGE,
		MAX,            //�ő吔
	}TYPE;

	typedef enum
	{
		NONEUI = 0,      //����
		INUI,            //�I�u�W�F�N�g�ɂ�UI
		TELEPHONPOLEUI,  //�d����UI
		TELEPHONPOLEUI1, //�d����UI
		BUYTEXT,         //����text
		TALKTEXTR,       //�b��text
		LASER,          //���[�U�[
	}TYPE_UI;

	CObject(); //�R���X�g���N�^
	CObject(int nPriority= DEFAULT_PRIORITY);
	virtual ~CObject(); //�f�X�g���N�^
	virtual HRESULT Init()=0; //������
	virtual void Uninit() = 0; //�I������
	virtual void Update() = 0; //�X�V����
	virtual void Draw() = 0; //�`�揈��
	virtual void DrawNoml() = 0; //�`�揈��
	static void ReleaseAll(); //�S�I�u�W�F�N�g�̉��
	static void UpdateAll(); //�S�I�u�W�F�N�g�̍X�V
	static void DrawAll(); //�S�I�u�W�F�N�g�̕`��
	static void DrawNomlAll(); //�S�I�u�W�F�N�g�̒ʏ�`��
	static CObject* GetObject1(int nPri,int nIndex); //�I�u�W�F�N�g�擾
	TYPE GetType(); //�^�C�v�擾
	void SetType(TYPE type); //�^�C�v�ݒ�
	void Release(); //�������g�̉��

protected:
	static int m_nNumAll; //�I�u�W�F�N�g�̑���

	/*CInputKeyBoard* pInputKeyBoard;
	CInputJoyPad* pInputJyoPad;*/

private:
	static CObject* m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT]; //�S�I�u�W�F�N�g�̊Ǘ�
	int m_nPriority;
	int m_nID; //�������g��ID
	TYPE m_type; //�I�u�W�F�N�g�^�C�v

};

#endif // !_OBJECT_H_

