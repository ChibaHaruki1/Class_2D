//============================
//
//���C������[main.cpp]
//Auther:Chiba Haruki
//
//============================

#include"main.h"
#include "rendererh.h"
#include "object2D.h"
#include "manager.h"
#include "DxLib.h"

//�}�N����`
#define CLASS_NAME	"WindowClass" //�E�B���h�E�N���X�̖��O
#define WINDOWS_NAME	"����m�P���x���X" //�E�B���h�E�̖��O

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HRESULT Init(HINSTANCE hInstace, HWND hWnd, BOOL bWindow);
void Uninit();

//�O���[�o���錾
CManager* g_pMnager = nullptr;
//FPS�\���̕ϐ�
int g_nCountFPS = 0;
char g_nCountFPS1[256];

int m_nScren_Width = SCREEN_WIDTH;
int m_nScren_Heght = SCREEN_HEIGHT;
int m_nBit = 32;

//=========================
//���C���֐�
//=========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstanceprev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//// �E�C���h�E���[�h�ɕύX
	//ChangeWindowMode(TRUE);

	//SetGraphMode(m_nScren_Width, m_nScren_Heght, m_nBit);			// ��ʃT�C�Y�ݒ�
	//GetDefaultState(&m_nScren_Width, &m_nScren_Heght, &m_nBit);		// �f�t�H���g�E�B���h�E�l�𓾂�
	//SetWindowSize(m_nScren_Width ,m_nScren_Heght);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX

	//if (DxLib_Init() == -1)    // �c�w���C�u��������������
	//{
	//	return -1;    // �G���[���N�����璼���ɏI��
	//}

	//printfDx("Hello world\n"); // �\�������

	//WaitKey();

	//DxLib_End();


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC, //�E�B���h�E�̃X�^�C��
		WindowProc, //�E�B���h�E�v���[�W��
		0, //�O�ɂ���i�ʏ�͎g�p���Ȃ��j
		0, //�O�ɂ���i�ʏ�͎g�p���Ȃ��j
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW), //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1), //�N���C�A���g�̈�̔w�i�F
		NULL, //���j���[�o�[
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION) //�t�@�C���̃A�C�R��
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,  //�g���E�B���h�E�X�^�C��
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		WINDOWS_NAME, //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT, //�E�B���h�E�̍���X���W
		CW_USEDEFAULT, //�E�B���h�E�̍���Y���W
		(rect.right - rect.left), //�E�B���h�E�̕�
		(rect.bottom - rect.top), //�E�B���h�E�̍���
		NULL, //�e�E�B���h�E�̃n���h��
		NULL, //���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance, //�C���X�^���X�n���h��
		NULL); //�E�B���h�E�쐬�f�[�^

	//������������
	g_pMnager = new CManager(); //�}�l�[�W���[�̐���

	//����������
	if (FAILED(g_pMnager->Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow); //�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd); //�N���C�A���g�̈���X�V

	//���Ԃ̎擾
	DWORD dwCurrentTime; //���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ�����������
	DWORD dwFrameCount; //�t���[���J�E���g
	DWORD dwFPSLastTime; //�Ō��FPS���v����������

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//���b�Z�[�W���[��
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Window�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime(); //���ݎ���

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���ϑ�
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //FPS�𑪒肵��������ۑ�
				dwFrameCount = 0; //�t���C���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//�U�O���̂P�b�o��
				dwExecLastTime = dwCurrentTime; //�����J�n�̎����i���ݎ����j��ۑ�

				//�X�V����
				g_pMnager->Update();

				//�`�揈��
				g_pMnager->Draw();

				dwFrameCount++; //�t���C���J�E���g������
			}
		}
	}

	//�I���������Ă�
	Uninit();

	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================
//�E�B���h�E�v���V�[�W��
//=============================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	//PAINTSTRUCT ps;
	//HPEN hPen, hPenold;
	static POINT pos = { 100.100 };
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

		//ECS�I�����̏���
	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE: //[ECS]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);
			if (nID == IDYES)
			{
				//	�E�B���h�E��j������iWM_DESTOROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			break;
		}

	case VK_RIGHT:
		pos.x++;

		//�����̈�̋�������
		InvalidateRect(hWnd, &rect, FALSE);

		break;

		//�~�{�^���I�����̏���
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�E�B���h�E����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONWARNING);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //�[����Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;


		//�}�E�X���N���b�N�̏���
	case WM_LBUTTONDOWN: //�}�E�X���N���b�N�̃��b�Z�[�W

		//�E�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //����̏�����Ԃ�
}

//======================
//�I������
//======================
void Uninit()
{
	g_pMnager->Uninit();
	delete g_pMnager;
}

int GetFPS()
{
	return g_nCountFPS;
}