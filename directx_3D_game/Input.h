//=============================================================================
//
// 入力処理 [input.h]
// Author : 稲澤俊和
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#define DIRECTINPUT_VERSION (0x0800)    // 警告対策用
#include "dinput.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTriger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif

