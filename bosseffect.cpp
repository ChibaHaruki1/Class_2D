//===================================
//
//�G�t�F�N�g�̏���[efect.cpp]
//Auther:Chiba Haruki
//
//===================================

//�C���N���[�h
#include "main.h"
#include "rendererh.h"
#include "bosseffect.h"
#include "manager.h"

//==================================================================================
//���o�p�G�t�F�N�g�̃X�g���e�W�[�N���X��ꏈ��
//==================================================================================

//==========================================
//�R���X�g���N�^
//==========================================
CBossEffectDirection::CBossEffectDirection()
{
	m_pEffectFileName = nullptr;
	m_nLife = 0;
	m_pVtxBuffMine = nullptr;
}

//==========================================
//�f�X�g���N�^
//==========================================
CBossEffectDirection::~CBossEffectDirection()
{

}

//==================================================================================
//�e�N�X�`���̐ݒ菈��
//==================================================================================
void CBossEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize)
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(fTexSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexSize, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================
//�e�N�X�`���̍X�V����
//==================================================================================
void CBossEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount ,float fMaxTex)
{
	m_nLife++;  //�J�E���g����

	//���C�t������̐��l�ɂȂ�����
	if (m_nLife >= CManagerBossEffect::MAX_BOSSANIMATION_LIFE * dLifeCount)
	{
		VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex.x = pVtx[0].tex.x + fMaxTex;
		pVtx[1].tex.x = pVtx[1].tex.x + fMaxTex;
		pVtx[2].tex.x = pVtx[2].tex.x + fMaxTex;
		pVtx[3].tex.x = pVtx[3].tex.x + fMaxTex;

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

		m_nLife = 0; //���C�t������������
	}
}


//==================================================================================
//���o�p�G�t�F�N�g�̃X�g���e�W�[�N���X�̌p������
//==================================================================================

//==========================================
//�R���X�g���N�^
//==========================================
CAttackEffect::CAttackEffect()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Impact.png";
}

//==========================================
//�f�X�g���N�^
//==========================================
CAttackEffect::~CAttackEffect()
{

}


//==================================================================================
//�K�E�Z�̃X�g���e�W�[�N���X�̌p������
//==================================================================================

//==========================================
//�R���X�g���N�^
//==========================================
CSourceSpecialAttackBoss::CSourceSpecialAttackBoss()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\SpecialGage\\BossSpecialAllGage002.png";
}

//==========================================
//�f�X�g���N�^
//==========================================
CSourceSpecialAttackBoss::~CSourceSpecialAttackBoss()
{

}


//=======================================================================================================================================================================
//�G�t�F�N�g�̊Ǘ��ҏ���
//=======================================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CManagerBossEffect::CManagerBossEffect(int nPriority) : CObject3D(nPriority)
{
	m_nLife = 100;                         //���C�t��e�̐ݒ肳�ꂽ���C�t�Ɠ����ɂ���i�����ɏ������߁j
	m_pEffectDirection000 = nullptr;
	m_nEffectNumber = -1;
	m_nFrame = 0;
	m_nBossRotNumber = 0;
	m_dLifeCount = 0.0;
	m_bFly = false;
}


//===========================
//�f�X�g���N�^
//===========================
CManagerBossEffect::~CManagerBossEffect()
{
	if (m_pEffectDirection000 != nullptr)
	{
		delete m_pEffectDirection000;
		m_pEffectDirection000 = nullptr;
	}
}


//============================
//����������
//============================
HRESULT CManagerBossEffect::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}
	m_fSizeX = 40.0f;
	m_fSizeY = 40.0f;
	SetSize(m_fSizeX, m_fSizeY, 40.0f);  //�傫���̐ݒ�
	//m_pEffectDirection = std::make_shared<CEffectDirection>(0);
	return S_OK;
}


//============================
//����������
//============================
void CManagerBossEffect::Uninit()
{
	//m_pEffectDirection = std::make_shared<CEffectDirection>(1);
	CObject3D::Uninit(); //���N���X�̔j���������Ă�
}


//============================
//����������
//============================
void CManagerBossEffect::Update()
{
	//m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, m_dLifeCount, fMaxTex);
	//m_nLife--;                           //���C�t�����炷

	//SetCol(255, 255, 255, m_nAlpha);     //�F�̐ݒ�

	////���C�t���s������
	//if (m_nLife <= 0)
	//{
	//	CManager::GetInstance()->DesignationUninit3D(IMPACT);
	//	CObject3D::Release();
	//	return;
	//}

	//CObject3D::Update();
}

//============================
//����������
//============================
void CManagerBossEffect::Draw()
{
	CObject3D::DrawEffect();
}


//============================
//�G�t�F�N�g�̐ݒ�
//============================
void CManagerBossEffect::SetEffect(D3DXVECTOR3 pos)
{
	m_pos = pos;
	//m_move = move;
	//m_nLife = nLife;
}


//===========================
//�G�t�F�N�g�̐���
//===========================
CManagerBossEffect* CManagerBossEffect::Create(D3DXVECTOR3 pos, CObject3D::TYPE type)
{
	CManagerBossEffect* pEffect = nullptr;

	if (type == CObject3D::TYPE::IMPACT)
	{
		pEffect = new CImpact();

		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;
			pEffect->m_pEffectDirection000 = new CAttackEffect();
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff,1.0f);
		}
	}
	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		pEffect = new CBossSpecialAttack();

		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttackBoss();
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_BOSSANIMETION_TEX);
			pEffect->SetSize(200.0f, 200.0f, 0.0f);   //�傫���̐ݒ�
		}
	}
	
	if (pEffect != nullptr)
	{
		pEffect->m_aFileName = pEffect->m_pEffectDirection000->m_pEffectFileName;
		pEffect->m_pos = pos;
		pEffect->Lood();
		return pEffect;
	}

	return nullptr;
}


//=======================================================================================================================================================
//�Ռ��g�̃G�t�F�N�g�̏���
//=======================================================================================================================================================

//============================
//�R���X�g���N�^
//============================
CImpact::CImpact()
{

}

//============================
//�f�X�g���N�^
//============================
CImpact::~CImpact()
{

}

//============================
//�X�V����
//============================
void CImpact::Update()
{
	//m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, 0.0f,1.0f);
	m_nLife--;                           //���C�t�����炷
	m_fSizeX += 4.0f;                    //�����̃T�C�Y��傫������
	m_fSizeY += 1.0f;                    //�����̃T�C�Y��傫������

	SetCol(255, 255, 255, m_nAlpha);     //�F�̐ݒ�
	SetSize(m_fSizeX, m_fSizeY, 40.0f);  //�傫���̍X�V

	//�E���ɓ���������
	if (CObject3D::CollisionPrts1Right(m_fSizeX * 1.5f, m_fSizeY * 1.1f, 40.0f) == true)
	{
		m_bFly = true;
	}
	//�����ɓ���������
	else if (CObject3D::CollisionPrts1Left(m_fSizeX * 1.5f, m_fSizeY * 1.1f, 40.0f) == true)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x -= 100.0f;
		CManager::GetScene()->GetPlayerX()->GetPos().y += 100.0f;
	}

	//���C�t���s������
	if (m_nLife <= 0)
	{
		CManager::GetInstance()->DesignationUninit3D(IMPACT);
		CObject3D::Release();
		return;
	}

	CObject3D::Update();
}


//=======================================================================================================================================================
//�K�E�Z�̃G�t�F�N�g�̏���
//=======================================================================================================================================================

//============================
//�R���X�g���N�^
//============================
CBossSpecialAttack::CBossSpecialAttack()
{

}

//============================
//�f�X�g���N�^
//============================
CBossSpecialAttack::~CBossSpecialAttack()
{

}

//============================
//�X�V����
//============================
void CBossSpecialAttack::Update()
{
	this->m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, 0.3, MAX_BOSSANIMETION_TEX); //���g�̃X�g���e�W�[�p���N���X�̏������Ă�

	SetCol(255, 255, 255, m_nAlpha);          //�F�̐ݒ�

	//�T�C�Y���K��l���傫���Ȃ�����
	if (m_fSizeX <= 2000.0f)
	{
		m_fSizeX += 30.0f;                    //�T�C�Y��傫������
	}

	float a = m_pos.y - CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(17).y * 1.5f;
	float b = CManager::GetScene()->GetPlayerX()->GetPos().x;

	//�����ԍ����P�̎�
	if (GetRotNumber() == 1)
	{
		SetEffectSize(m_fSizeX, MAX_BOSSSPECIALATTACK_Y, 0.0f);    //�T�C�Y�̐ݒ�

		//�_C�͎��@���E�ɋ��鎞�_�Ŋm��ŏ��������ߌ��݂�pos.x�𑫂�����Ōv�Z����
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), m_pos.x, m_pos.y + PLUS_POS_Y,
			m_fSizeX+m_pos.x, a)==true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
		}
	}	

	//�����ԍ����Q�̎�
	else if (GetRotNumber() == 2)
	{
		SetEffectSize(-m_fSizeX, MAX_BOSSSPECIALATTACK_Y, 0.0f);   //�T�C�Y�̐ݒ�

		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), -m_fSizeX+m_pos.x, m_pos.y + PLUS_POS_Y,
			m_pos.x, a)==true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
		}
	}

	//���C�t���O�ȉ��̎�
	if (m_nLife <= 0)
	{
		m_nAlpha -= 5;          //alpha�l�����炷

		//alpha�l���O�ȉ��̎�
		if (m_nAlpha <= 0)
		{
			CObject::Release(); //���g���폜
			return;             //�����𔲂���
		}
	}
	else
	{
		m_nLife--; //���C�t�����炷
	}
}