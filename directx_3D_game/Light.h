//=============================================================================
//
// ライト処理 [Light.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"


//=============================================================================
// マクロ定義
//=============================================================================


//前方宣言
class CRenderer;

//=============================================================================
//CLightクラス
//=============================================================================
class CLight
{
	//公開メンバ
	public:
		CLight();		//コンストラクタ
		~CLight();		//デストラクタ

		HRESULT InitLight(CRenderer* pRenderer);		//初期化

	//非公開メンバ
	private:
		D3DLIGHT9 m_aLight[3];			//ライトの数
		LPDIRECT3DDEVICE9 m_pDevice;


};

#endif