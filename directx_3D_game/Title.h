//=============================================================================
//
// タイトル処理 [Title.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//前方宣言
class CRenderer;
class CCamera;
class CLight;
class CFade;
//=============================================================================
//CManagerクラス
//=============================================================================
class CTitle
{
	public:
		CTitle();
		~CTitle();
		HRESULT Init(CRenderer* pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);

	private:
		static CRenderer* m_pRenderer;
		CFade* m_pFade;
		VERTEX_2D m_aVtx[4];						//頂点情報格納ワーク	
		LPDIRECT3DTEXTURE9  m_pD3DTex;
		LPDIRECT3DDEVICE9 m_pDevice;

};

#endif