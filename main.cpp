//============================
//
//メイン処理[main.cpp]
//Auther:Chiba Haruki
//
//============================

#include"main.h"
#include "rendererh.h"
#include "object2D.h"
#include "manager.h"
#include "DxLib.h"

//マクロ定義
#define CLASS_NAME	"WindowClass" //ウィンドウクラスの名前
#define WINDOWS_NAME	"狂戦士ケルベロス" //ウィンドウの名前

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HRESULT Init(HINSTANCE hInstace, HWND hWnd, BOOL bWindow);
void Uninit();

//グローバル宣言
CManager* g_pMnager = nullptr;
//FPS表示の変数
int g_nCountFPS = 0;
char g_nCountFPS1[256];

int m_nScren_Width = SCREEN_WIDTH;
int m_nScren_Heght = SCREEN_HEIGHT;
int m_nBit = 32;

//=========================
//メイン関数
//=========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstanceprev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//// ウインドウモードに変更
	//ChangeWindowMode(TRUE);

	//SetGraphMode(m_nScren_Width, m_nScren_Heght, m_nBit);			// 画面サイズ設定
	//GetDefaultState(&m_nScren_Width, &m_nScren_Heght, &m_nBit);		// デフォルトウィンドウ値を得る
	//SetWindowSize(m_nScren_Width ,m_nScren_Heght);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更

	//if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	//{
	//	return -1;    // エラーが起きたら直ちに終了
	//}

	//printfDx("Hello world\n"); // 表示される

	//WaitKey();

	//DxLib_End();


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEXのメモリサイズ
		CS_CLASSDC, //ウィンドウのスタイル
		WindowProc, //ウィンドウプロージャ
		0, //０にする（通常は使用しない）
		0, //０にする（通常は使用しない）
		hInstance, //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW), //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1), //クライアント領域の背景色
		NULL, //メニューバー
		CLASS_NAME, //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION) //ファイルのアイコン
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,  //拡張ウィンドウスタイル
		CLASS_NAME, //ウィンドウクラスの名前
		WINDOWS_NAME, //ウィンドウの名前
		WS_OVERLAPPEDWINDOW, //ウィンドウのスタイル
		CW_USEDEFAULT, //ウィンドウの左上X座標
		CW_USEDEFAULT, //ウィンドウの左上Y座標
		(rect.right - rect.left), //ウィンドウの幅
		(rect.bottom - rect.top), //ウィンドウの高さ
		NULL, //親ウィンドウのハンドル
		NULL, //メニューハンドルまたは子ウィンドウID
		hInstance, //インスタンスハンドル
		NULL); //ウィンドウ作成データ

	//生成＆初期化
	g_pMnager = new CManager(); //マネージャーの生成

	//初期化処理
	if (FAILED(g_pMnager->Init(hInstance, hWnd, TRUE)))
	{//初期化処理を失敗した場合
		return -1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow); //ウィンドウの表示状態を設定
	UpdateWindow(hWnd); //クライアント領域を更新

	//時間の取得
	DWORD dwCurrentTime; //現在時刻
	DWORD dwExecLastTime; //最後に処理した時刻
	DWORD dwFrameCount; //フレームカウント
	DWORD dwFPSLastTime; //最後にFPSを計測した時刻

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//メッセージルーぷ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowの処理
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
		{//DirectXの処理

			dwCurrentTime = timeGetTime(); //現在時刻

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを観測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //FPSを測定した時刻を保存
				dwFrameCount = 0; //フレイムカウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//６０分の１秒経過
				dwExecLastTime = dwCurrentTime; //処理開始の時刻（現在時刻）を保存

				//更新処理
				g_pMnager->Update();

				//描画処理
				g_pMnager->Draw();

				dwFrameCount++; //フレイムカウントを加速
			}
		}
	}

	//終了処理を呼ぶ
	Uninit();

	DxLib_End();        // ＤＸライブラリ使用の終了処理

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================
//ウィンドウプロシージャ
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
	case WM_DESTROY: //ウィンドウ破棄のメッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

		//ECS選択時の処理
	case WM_KEYDOWN: //キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE: //[ECS]キーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);
			if (nID == IDYES)
			{
				//	ウィンドウを破棄する（WM_DESTOROYメッセージを送る）
				DestroyWindow(hWnd);
			}
			break;
		}

	case VK_RIGHT:
		pos.x++;

		//無効領域の強制発生
		InvalidateRect(hWnd, &rect, FALSE);

		break;

		//×ボタン選択時の処理
	case WM_CLOSE:
		nID = MessageBox(hWnd, "ウィンドウを閉じますか？", "終了メッセージ", MB_YESNO | MB_ICONWARNING);
		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //ゼロを返さないと終了してしまう
		}
		break;


		//マウス左クリックの処理
	case WM_LBUTTONDOWN: //マウス左クリックのメッセージ

		//ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //既定の処理を返す
}

//======================
//終了処理
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