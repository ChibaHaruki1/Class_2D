//===================================
//
//�G�t�F�N�g�̏���[efect.cpp]
//Auther:Chiba Haruki
//
//===================================

#include "main.h"
#include "rendererh.h"
#include "efect.h"
#include "manager.h"


//==================================================================================
//���o�p�G�t�F�N�g�̃X�g���e�W�[�N���X��ꏈ��
//==================================================================================
CEffectDirection::CEffectDirection()
{
	m_pEffectFileName = nullptr;
	m_nLife = 0;
	m_pVtxBuffMine = nullptr;
}
CEffectDirection::~CEffectDirection()
{
	
}

//==================================================================================
//�e�N�X�`���̐ݒ菈��
//==================================================================================
void CEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,float fTexSize)
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
void CEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,double dLifeCount,float fMaxTex)
{
	m_nLife++;  //�J�E���g����

	//���C�t������̐��l�ɂȂ�����
	if (m_nLife >= CManagerEffect::MAX_EXPLOSION_LIFE * dLifeCount)
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
CThunder::CThunder()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\thunder.png";
}
CThunder::~CThunder()
{

}


//==================================================================================
//�����G�t�F�N�g
//==================================================================================
CExplotion::CExplotion()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\explosion001.png";
}
CExplotion::~CExplotion()
{

}


//==================================================================================
//���̔����G�t�F�N�g
//==================================================================================
CExplotionPillar::CExplotionPillar()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\Fire000.png";
}
CExplotionPillar::~CExplotionPillar()
{

}


//==================================================================================
//����̉��G�t�F�N�g
//==================================================================================
CExplotionPillar001::CExplotionPillar001()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\PillarOfFireAll.png";
}
CExplotionPillar001::~CExplotionPillar001()
{

}


//==================================================================================
//�j�ЃG�t�F�N�g�̃X�g���e�W�[�N���X�̌p������
//==================================================================================
CFormerDebris::CFormerDebris()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\010.png";
}
CFormerDebris::~CFormerDebris()
{

}


//==================================================================================
//�K�E�Z
//==================================================================================
CSourceSpecialAttack::CSourceSpecialAttack()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\SpecialGage\\SpecialGageRE.png";
}
CSourceSpecialAttack::~CSourceSpecialAttack()
{

}


//=======================================================================================================================================================================
//�G�t�F�N�g�̊Ǘ��ҏ���
//=======================================================================================================================================================================
 
//===========================
//�R���X�g���N�^
//===========================
CManagerEffect::CManagerEffect(int nPriority) : CObject3D(nPriority)
{
	m_nLife = (int)(SET_BULLET_LIFE*0.7f);                          //���C�t��e�̐ݒ肳�ꂽ���C�t�Ɠ����ɂ���i�����ɏ������߁j
	m_pEffectDirection000 = nullptr;
	m_nEffectNumber = -1;
	m_dLifeCount = 0.0;
	m_fMaxTex = MAX_EXPLOSION_TEX;
}

//===========================
//�f�X�g���N�^
//===========================
CManagerEffect::~CManagerEffect()
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
HRESULT CManagerEffect::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}
	SetSize(40.0f, 40.0f, 0.0f);  //�傫���̐ݒ�
	//m_pEffectDirection = std::make_shared<CEffectDirection>(0);
	return S_OK;
}

//============================
//�j������
//============================
void CManagerEffect::Uninit()
{
	CObject3D::Uninit(); //���N���X�̔j���������Ă�
}

//============================
//�X�V����
//============================
void CManagerEffect::Update()
{
	if (m_dLifeCount != 0.0)
	{
		m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, m_dLifeCount, m_fMaxTex); //strategy�̊��N���X�̏������Ă�
	}
	m_nLife--;                     //���C�t�����炷

	//���ȊO
	if (m_nEffectNumber != 1)
	{
		if (m_nAlpha > 0)
		{
			m_nAlpha -= 5;                 //�A���t�@�l�����炷
		}
	}
	SetCol(255, 255, 255, m_nAlpha);  //�F�̐ݒ�

	//���C�t���s������
	if (m_nLife <= 0)
	{
		//���G�t�F�N�g��
		if (m_nEffectNumber == 1)
		{
			this->SetEffect(m_pos);  //���M�̃G�t�F�N�g���Ă�
			m_nAlpha = 200;          //�A���t�@�l�̐ݒ�
			m_nLife = 60;            //���C�t�̐ݒ�
			m_nEffectNumber = -1;    //�G�t�F�N�g�i���o�[�̏������i���̌�������߁j
		}

		//���̑��̎�
		else
		{
			CObject3D::Release();
			return;
		}
	}

	CObject3D::Update();
}

//============================
//�`�揈��
//============================
void CManagerEffect::Draw()
{
	CObject3D::DrawEffect();
}

//============================
//�r���{�[�h�`�揈��
//============================
void CManagerEffect::DrawNoml()
{

}


//============================
//�G�t�F�N�g�̐ݒ�
//============================
void CManagerEffect::SetEffect(D3DXVECTOR3 pos)
{
	m_pos = pos;
	//m_move = move;
	//m_nLife = nLife;
}


//===========================
//�G�t�F�N�g�̐���
//===========================
CManagerEffect* CManagerEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CManagerEffect* pEffect = nullptr; //���N���X�̃|�C���^�[

	//��
	if (type == CObject3D::TYPE::THENDER)
	{
		pEffect = new CBreakEffect(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;                                        //�G�t�F�N�g�i���o�[�̐ݒ�
			pEffect->m_pEffectDirection000 = new CThunder();                     //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff,1.0f);   //�ꕪ��
			pEffect->m_dLifeCount = 0.0;
			pEffect->m_fMaxTex = 1.0;
		}
	}

	//����
	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		pEffect = new CExplosion(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);  //������
			pEffect->SetSize(70.0f, 70.0f, 0.0f);                                             //�傫����ݒ�
			pEffect->m_dLifeCount = 0.6;
		}
	}

	//�����O�O�P
	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		pEffect = new CExplosion001(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                                     //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\explosion004.png";  //�e�N�X�`���̃t�@�C���p�X��ݒ�
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);                       //������
			pEffect->SetSize(70.0f, 70.0f, 0.0f);                                                                  //�傫����ݒ�
			pEffect->m_dLifeCount = 0.6;                                                                           //�A�j���[�V�����̐i�߂鑬����ݒ�
		}
	}

	//��
	else if (type == CObject3D::TYPE::FIRE)
	{
		pEffect = new CFire(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar();                          //�p���N���X
			pEffect->m_nEffectNumber = 1;                                                     //�G�t�F�N�g�i���o�[�̐ݒ�
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);  //������                                          
			pEffect->SetSize(92.0f, 190.0f, 0.0f);                                            //�傫���̐ݒ�
			pEffect->m_dLifeCount = 0.5;                                                      //�A�j���[�V�����̐i�߂鑬����ݒ�
		}
	}

	//����̉�
	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		pEffect = new CPillarOfFire(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar001();                           //�X�g���e�W�[�̌p���N���X
			pEffect->m_nEffectNumber = 2;                                                         //�G�t�F�N�g�i���o�[�̐ݒ�
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);      //������
			pEffect->SetSize(pEffect->m_fPillarOfFireSizeX, pEffect->m_fPillarOfFireSizeY, 0.0f); //�傫���̐ݒ�
			pEffect->m_dLifeCount = 0.5;                                                          //�A�j���[�V�����̐i�߂鑬����ݒ�
		}
	}

	//�j��
	else if (type == CObject3D::TYPE::DEBRIS)
	{
		pEffect = new CDebris(); //�p���N���X

		//�������ɐ���������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CFormerDebris();                                 //�X�g���e�W�[�p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, 1.0f);                   //�ꕪ��
		}
	}

	//�K�E�Z
	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		pEffect = new CSpecialAttack(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttack();                        //�X�g���e�W�[�p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);    //������
			pEffect->SetSize(pEffect->m_fSepecialAttackX, pEffect->m_fSepecialAttackY, 0.0f);   //�傫���̐ݒ�
		}
	}

	//�e�N�X�`���[��ʒu�̓���
	if (pEffect != nullptr)
	{
		pEffect->m_aFileName = pEffect->m_pEffectDirection000->m_pEffectFileName;  //�e�N�X�`���̃t�@�C���p�X�̓���
		pEffect->m_pos = pos;                                                      //�ʒu�̓���
		pEffect->Lood();                                                           //�e�N�X�`���̓ǂݍ��݊֐�
		return pEffect;                                                            //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//=======================================================================================================================================================
//��ꂽ�Ƃ��̃G�t�F�N�g����
//=======================================================================================================================================================
CBreakEffect::CBreakEffect()
{
	
}
CBreakEffect::~CBreakEffect()
{

}


//==============================================================================================================================================================
//�����G�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CExplosion::CExplosion()
{
	
}

//===========================
//�R���X�g���N�^
//===========================
CExplosion::~CExplosion()
{

}


//==============================================================================================================================================================
//���G�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
CFire::CFire()
{
	m_nLife = 120;
}

//===========================
//�R���X�g���N�^
CFire::~CFire()
{

}

//===========================
//�`�揈��
//===========================
void CFire::Draw()
{
	CObject3D::DrawEffect1();
}


//==============================================================================================================================================================
//����̉�
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
CPillarOfFire::CPillarOfFire()
{
	m_nLife = 180;
	m_nAlpha = 255;
	m_nFrame = 0;
}

//===========================
//�R���X�g���N�^
CPillarOfFire::~CPillarOfFire()
{

}

//============================
//����������
//============================
HRESULT CPillarOfFire::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//============================
//�X�V����
//============================
void CPillarOfFire::Update()
{
	this->m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff,0.5, MAX_EXPLOSION_TEX); //���g�̃X�g���e�W�[�p���N���X�̏������Ă�
	SetCol(255, 255, 255, m_nAlpha);  //�F�̐ݒ�

	//�t���[�����K��l�ɍs������
	if (m_nFrame >= 60)
	{
		if (CObject3D::CollisionPrtsPlayer(m_fPillarOfFireSizeX, m_fPillarOfFireSizeY, 40.0f) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.01f; //HP�Q�[�W�����炷
			CManager::GetInstance()->GetPlayerHPGage()->SetSIze(0.0f, CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX(), 40.0f, 70.0f);  //�傫�������炩���ߌ��߂Ȃ���
			m_nFrame = 0;
			m_nLife = 0;
		}
	}
	else
	{
		m_nFrame++;
	}

	//���C�t���O�ȉ��̎�
	if (m_nLife <= 0)
	{
		m_nAlpha -= 5;  //alpha�l�����炷
		
		//alpha�l���O�ȉ��̎�
		if (m_nAlpha <= 0)
		{
			CObject::Release(); //���g���폜
			return;             //�����𔲂���
		}
	}
	else
	{
		m_nLife--;
	}
}


//==============================================================================================================================================================
//�e�ɂ��G�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CEffect::CEffect(int nPriority) : CObject3D(nPriority)
{
	m_nLife = SET_BULLET_LIFE/2;                          //���C�t��e�̐ݒ肳�ꂽ���C�t�Ɠ����ɂ���i�����ɏ������߁j
	m_aFileName = "data\\TEXTURE\\UI\\effect000.jpg"; //�e�N�X�`���̃t�@�C���p�X��ݒ�
}


//===========================
//�f�X�g���N�^
//===========================
CEffect::~CEffect()
{
	
}


//============================
//����������
//============================
HRESULT CEffect::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}
	SetSize(40.0f, 40.0f, 0.0f);
	return S_OK;
}


//============================
//�j������
//============================
void CEffect::Uninit()
{
	CObject3D::Uninit(); //���N���X�̔j���������Ă�
}


//============================
//�X�V����
//============================
void CEffect::Update()
{
	m_nLife--;
	if (m_nLife <= 0)
	{
		CObject3D::Release();
		return;
	}

	CObject3D::Update();
}


//============================
//�`�揈��
//============================
void CEffect::Draw()
{
	CObject3D::DrawEffect();
}


//============================
//�r���{�[�h�`�揈��
//============================
void CEffect::DrawNoml()
{
	
}


//============================
//�G�t�F�N�g�̐ݒ�
//============================
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	m_pos = pos;
	m_move = move;
	m_nLife = nLife;
}


//===========================
//�G�t�F�N�g�̐���
//===========================
CEffect* CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect* pEffect = new CEffect();

	if (SUCCEEDED(pEffect->Init()))
	{
		if (pEffect != nullptr)
		{
			pEffect->m_pos = pos;
			pEffect->Lood();
			return pEffect;
		}
	}

	return nullptr;
}


//==============================================================================================================================================================
//�����G�t�F�N�g001
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CExplosion001::CExplosion001()
{
	
}


//===========================
//�R���X�g���N�^
//===========================
CExplosion001::~CExplosion001()
{

}

//==============================================================================================================================================================
//�j�ЃG�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CDebris::CDebris()
{
	m_nLife = 10;
	m_fSiseX = 50.0f;
}


//===========================
//�R���X�g���N�^
//===========================
CDebris::~CDebris()
{

}

//===========================
//�X�V����
//===========================
void CDebris::Update()
{
	m_nLife--;                            //���C�t�����炷
	m_fSiseX+=4.0f;                       //�T�C�Y��傫������
	SetSize(m_fSiseX,m_fSiseX,0.0f);      //�T�C�Y�̐ݒ�

	//���C�t���O�ȉ��̎�
	if (m_nLife <= 0)
	{
		CObject3D::Release(); //���g������
	}
}


//==============================================================================================================================================================
//�K�E�Z
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
CSpecialAttack::CSpecialAttack()
{
	m_nLife = 180;
	m_nAlpha = 255;
	m_nFrame = 0;
	m_fSizeX = m_fSepecialAttackX;
	m_nRotNumber = 0;
}

//===========================
//�R���X�g���N�^
CSpecialAttack::~CSpecialAttack()
{

}

//============================
//�X�V����
//============================
void CSpecialAttack::Update()
{
	this->m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff,0.3, MAX_EXPLOSION_TEX); //���g�̃X�g���e�W�[�p���N���X�̏������Ă�

	SetCol(255, 255, 255, m_nAlpha);         //�F�̐ݒ�

	if (m_fSizeX <= 2000.0f)
	{
		m_fSizeX += 30.0f;                    //�T�C�Y��傫������
	}

	if (m_nRotNumber == 1)
	{
		SetEffectSize(m_fSizeX, m_fSepecialAttackY, 0.0f);    //�T�C�Y�̐ݒ�
	}
	else if(m_nRotNumber == 2)
	{
		SetEffectSize(-m_fSizeX, m_fSepecialAttackY, 0.0f);   //�T�C�Y�̐ݒ�
	}

	if (CManager::GetScene()->GetPlayerX()->GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2)
	{
		//m_rot.y = CManager::GetScene()->GetCamera()->GetRot().y -D3DX_PI;
	}

	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		for (int nCount2 = 0; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
				m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
				CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), m_fSizeX, nCount2))
			{
				//CManager::GetInstance()->GetPlayerHPGage()->SetSIze(0.0f, CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX(), 40.0f, 70.0f); //�傫�������炩���ߌ��߂Ȃ���
				CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.00005f; //�{�X��HP�Q�[�W�����炷
			}
		}
	}

	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count() + 1; nMotionInEnemy001++)
	{
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			for (int nCount1 = 0; nCount1 < CObjectX::MAX_ENEMYPARTS; nCount1++)
			{
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(nCount1),
					m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePrtsEnemy(nCount1), m_fSizeX, nCount1))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() -= 1;

					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //�|�C���^�[��nullptr�ɂ���
						return;
					}
				}
			}
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