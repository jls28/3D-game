//=============================================================================
//
// üÍ [input.h]
// Author : îāVra
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#define DIRECTINPUT_VERSION (0x0800)    // xÎôp
#include "dinput.h"
//*****************************************************************************
// vg^Cvéū
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTriger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif

