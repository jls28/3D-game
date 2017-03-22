//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "input.h"
#include "Manager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define KEY_ON (128)						// キーが押されている
#define START_REPEAT	(10)				// リピート開始まで

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8 g_pDInput = NULL;	// DIRECTINPUTオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;	// デバイスオブジェクトへのポインタ
BYTE g_aKeyState[256];				// キーボード押下状態を受け取るワーク
BYTE g_prevKeyState[256];			// 前回のキー情報
int g_nCountRepeatKey[256];			// リピート用カウンタ
//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// キー情報の初期化
	for(int i = 0; i<256; i++)
	{
		g_aKeyState[i] = 0;
		g_prevKeyState[i] = 0;
		g_nCountRepeatKey[i] = 0;
	}


	// DirectInputオブジェクトの作成
	if(g_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);

		if(FAILED(hr))
		{

			MessageBox(NULL, "DirectInputオブジェクトの作成に失敗しました", "警告" ,MB_OK);
			return hr;
		}
	}

	// デバイスオブジェクトを作成
	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);

	if(FAILED(hr))
	{
		MessageBox(NULL, "デバイスオブジェクトの作成に失敗しました", "警告" ,MB_OK);
		return hr;
	}


	// データフォーマットを設定
	hr = g_pDIDevKeyboard -> SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		MessageBox(NULL, "データフォーマットの設定に失敗しました", "警告" ,MB_OK);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevKeyboard -> SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(FAILED(hr))
	{
		MessageBox(NULL, "協調モードの設定に失敗しました", "警告" ,MB_OK);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard -> Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	// DirectInputオブジェクトの開放
	if(g_pDInput != NULL)
	{
		g_pDInput -> Release();
		g_pDInput = NULL;
	}


	// デバイスオブジェクトの開放
	if(g_pDIDevKeyboard != NULL)
	{
		g_pDIDevKeyboard -> Acquire();
		g_pDIDevKeyboard -> Release();
		g_pDIDevKeyboard = NULL;
	}

}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[256];

	// キー入力を取得
	if(SUCCEEDED(g_pDIDevKeyboard -> GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		// キーボード情報の作成、保存
		for(int nKey=0;nKey<256;nKey++)
		{
			// 前回のキー情報格納
			g_prevKeyState[nKey] =g_aKeyState[nKey];

			// 現在の状態を格納
			g_aKeyState[nKey] =aKeyState[nKey];


			// リピート情報の作成
			if(g_aKeyState[nKey] == KEY_ON)
			{
				// リピートカウンタ
				g_nCountRepeatKey[nKey]++;
			}
			else
			{
				// キーを押してなければカウンタ0に
				g_nCountRepeatKey[nKey] =0;
			}

		}
	}
	else
	{
		g_pDIDevKeyboard ->Acquire();
	}

	if(CManager::GetFadeFlag()==true)
	{
		// キー情報の初期化
		for(int i = 0; i<256; i++)
		{
			g_aKeyState[i] = 0;
			g_prevKeyState[i] = 0;
			g_nCountRepeatKey[i] = 0;
		}
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	bool result = false;

	if(g_aKeyState[nKey] ==KEY_ON)
	{
		result = true;
	}

	return result;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTriger(int nKey)
{
	bool result = false;

	if(((g_aKeyState[nKey] ^g_prevKeyState[nKey]) &g_aKeyState[nKey]) ==KEY_ON)
	{
		result =true;
	}

	return result;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	bool result =false;

	if(g_nCountRepeatKey[nKey] ==1 || g_nCountRepeatKey[nKey] >=START_REPEAT)
	{
		result = true;
	}

	return result;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	bool result =false;

	if(((g_prevKeyState[nKey] ^ g_aKeyState[nKey])&g_prevKeyState[nKey]) ==KEY_ON)
	{
		result =true;
	}

	return result;
}
