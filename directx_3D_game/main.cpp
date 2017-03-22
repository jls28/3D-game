#define _CRTDBG_MAP_ALLOC		//メモリリークチェック
#include <stdlib.h>
#include <crtdbg.h>
//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "main.h"
#include "Renderer.h"
#include "Scene.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneX.h"
#include "SceneBillboard.h"
#include "Manager.h"
#include "resource.h"
#include "CreateFire.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"さそりぴょんぴょん"				// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
#ifdef _DEBUG
int						g_nCountFPS = 0;			// FPSカウンタ
#endif
CManager* pManager;


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);		//メモリリークチェック
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1)),	//exeのアイコン
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		//MAKEINTRESOURCE(IDR_MENU1),			//メニュー
		CLASS_NAME,
		NULL
	};
	
	HWND hWnd;
	MSG msg;

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW&~(WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_THICKFRAME),
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);
	
	pManager = new CManager;
	pManager->Init(hInstance,hWnd,TRUE);

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	

	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);		// FPSを測定
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				pManager->Update();

				// 描画処理
				pManager->Draw();
				pManager->PhaseExchange();
				dwFrameCount++;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	pManager->Uninit();
	delete pManager;

	timeEndPeriod(1);				// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	//PAINTSTRUCT ps;
	
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

		case VK_SPACE:

		//DWORD	dw;
		//g_pD3DDevice->GetRenderState( D3DRS_FOGENABLE, &dw );
		//if( dw == TRUE )
		//{
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //フォグ：ON→OFF
		//}
		//else
		//{
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); //フォグ：OFF→ON
		//}
		//break;



	case WM_COMMAND:
		{
			int ID = LOWORD(wParam);
			switch(ID)
			{
				case ID_dialogue:
				{
					//HWND hDlg=CreateDialog((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
					//						MAKEINTRESOURCE(IDD_DIALOG1),
					//						hWnd,
					//						DlgProc);
					//ShowWindow(hDlg,SW_SHOW);
				}
				break;
			}
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn={0};		//0で初期化

	int x=0,y=0,z=0;
	char DefDir[MAX_PATH];
	char OpenFileName[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,&DefDir[0]);		//カレントディレクトリを取得
	char DefDir2[MAX_PATH];
	char OpenFileName2[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,&DefDir2[0]);		//カレントディレクトリを取得

	//OPENFILENAMEの必要なやつに値を入れる
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hWnd;
	ofn.lpstrInitialDir=&DefDir[0];
	ofn.lpstrFile=OpenFileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFilter="モデルのファイル(*.x)\0*.x\0すべてのファイル(*.*)\0*.*\0";		//全てのファイルがオープン対象
	ofn.lpstrFileTitle="モデル召喚";					//ダイアログタイトル
	ofn.Flags=OFN_FILEMUSTEXIST;


	switch(uMsg)
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		case WM_COMMAND:
		{
			int ID = LOWORD(wParam);
			switch(ID)
			{
				case IDCLOSE:
					DestroyWindow(hWnd);
					break;

				case IDC_BUTTON1:
					char Buff[32];							//文字表示用
					//テキストボックスに入力した位置に出る
					GetDlgItemText(hWnd,IDC_X,Buff,30);		//整数
					float x=(float)atof(Buff);		//少数
					GetDlgItemText(hWnd,IDC_Y,Buff,30);		//整数
					float y=(float)atof(Buff);		//少数
					GetDlgItemText(hWnd,IDC_Z,Buff,30);		//整数
					float z=(float)atof(Buff);		//少数

					// モデルのファイルオープンダイアログ表示
					if(GetOpenFileName(&ofn))
					{
						SetCurrentDirectory(&DefDir[0]);		//カレントディレクトリを設定
						//モデルの作成
						//CSceneX::Create((float)x,(float)y,(float)z,/*(CRenderer*)ofn.lpstrFile,(CRenderer*)ofn.lpstrFile,*/CManager::GetRenderer());
					}
					break;
			}
		}
	}
	return FALSE;
}




#ifdef _DEBUG
//=============================================================================
// FPS表示処理
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aftr[256];
	wsprintf(&aftr[0],"FPS:%d\n",g_nCountFPS);
	m_pD3DFont->DrawText(NULL,&aftr[0],-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
}
#endif