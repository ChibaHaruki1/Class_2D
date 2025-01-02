//======================================
//
//�t�F�[�h����[fade.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

//======================================
//�C���N���[�h
#include "object2D.h"

class CFade : public CObject2D
{
public:

	//�t�F�[�h�̎��
	enum class FADE
	{
		FADE_NONE = 0,  //�����Ȃ�
		FADE_IN,        //�t�F�[�h�C��
		FADE_OUT,       //�t�F�[�h�A�E�g
		FADE_MAX        //�ő吔
	};

	CFade(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CFade()override;						  //�f�X�g���N�^
	HRESULT Init()override;					  //����������
	void Uninit()override;					  //�j������
	void  Update()override;					  //�X�V����
	void Draw()override;					  //�`�揈��

	int GetCountAlpha() { return nCountAlpha; }   //alpha�l������

	void SetFade(FADE Fadetype);              //�t�F�[�h�̐ݒ�
	static CFade* Create();                   //��������

private:
	FADE m_Fade;     //FADE�̏����i�[����ϐ�
	int nCountAlpha; //alpha�l��ۊǂ���p�̕ϐ�

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_FADE_SPEED = 3;  //�t�F�[�h�̏����̐F�̕ω����鑬�x����
};
