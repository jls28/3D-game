//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Fade.h"
#include "Renderer.h"
#include "Manager.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade(OBJTYPE nObjType,int nPriority):CScene2D(nObjType,nPriority)
{
	m_pD3DFadeTex = NULL;
	m_pD3DDevice=NULL;
	m_Mode = FADE_IN;
	m_aAlpha = 0;
	m_Time=0;
	m_Color.R=0;
	m_Color.G=0;
	m_Color.B=0;
	m_Color.A=0;
	m_Flag=false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{

}
//=============================================================================
// フェードの初期化
//=============================================================================
HRESULT CFade::Init(CRenderer *pRenderer)
{
	int i;
	m_pD3DDevice = pRenderer->GetDevice();	// デバイスへのポインタ

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);


	m_aFadeVtx[0].vtx = D3DXVECTOR3(0,0,0.0f);
	m_aFadeVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	m_aFadeVtx[2].vtx = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);
	m_aFadeVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	for(i=0;i<4;i++)
	{
		m_aFadeVtx[i].rhw=1.0f;
		m_aFadeVtx[i].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	}

	m_aFadeVtx[0].tex=D3DXVECTOR2(0,0);
	m_aFadeVtx[1].tex=D3DXVECTOR2(1,0);
	m_aFadeVtx[2].tex=D3DXVECTOR2(0,1);
	m_aFadeVtx[3].tex=D3DXVECTOR2(1,1);

	return S_OK;
}
//=============================================================================
// フェードの終了処理
//=============================================================================
void CFade::Uninit(void)
{
	if(m_pD3DFadeTex!=NULL)
	{
		m_pD3DFadeTex->Release();
		m_pD3DFadeTex= NULL;
	}
	CScene::Release();
}
//=============================================================================
// フェードの更新処理
//=============================================================================
void CFade::Update(void)
{
	switch(m_Mode)
	{
		//フェードをしていないとき
		case FADE_NONE:
			m_Flag=false;
			break;

		//フェードアウト時の処理
		case FADE_OUT:
			m_aAlpha+=m_RateAdd;		//アルファ値を加算
			if(m_aAlpha >= 255)
			{
				m_Mode=FADE_OUT_FINISH;
				m_aAlpha=255;
			}
			break;

		//フェードインが終わったら
		case FADE_IN_FINISH:
			m_Flag=false;
			break;

		//フェードイン時の処理
		case FADE_IN:
			m_aAlpha-=m_RateAdd;		//アルファ値を減算
			if(m_aAlpha <= 0)
			{
				m_Mode=FADE_NONE;
				m_aAlpha=0;
			}
			break;

		//フェードアウトが終わったら
		case FADE_OUT_FINISH:
			
			break;

		case FADE_INFINITY:
			break;
	}

	for(int i=0;i<4;i++)
	{
		m_aFadeVtx[i].diffuse = D3DCOLOR_RGBA((int)m_Color.R,(int)m_Color.G,(int)m_Color.B,m_aAlpha);
	}

	CManager::SetFadeFlag(m_Flag);
}

//=============================================================================
// フェードの描画処理
//=============================================================================
void CFade::Draw(void)
{
	m_pD3DDevice->SetTexture(0,m_pD3DFadeTex);
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,&m_aFadeVtx[0],sizeof(VERTEX_2D));
}

//=============================================================================
// フェードの開始
//=============================================================================
void CFade::FadeStart(FADE Mode,int Time,COLOR Color)
{
	m_Time=Time;
	m_Mode=Mode;
	m_Color=Color;

	if(Mode==FADE_IN)
	{
		m_aAlpha=255;
		m_Flag=true;
	}

	if(Mode==FADE_OUT)
	{
		m_aAlpha=0;
		m_Flag=true;
	}
	if(Mode==FADE_INFINITY)
	{
		m_aAlpha=(int)m_Color.A;
		m_Flag=true;
	}
	if(Mode==FADE_NONE)
	{
		m_Flag=false;
	}

	m_RateAdd=255/m_Time;
	m_Color.A=m_aAlpha;
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CFade* CFade::Create(CRenderer *pRenderer)
{
	CFade *pFade = new CFade(OBJTYPE_FADE);

	pFade->Init(pRenderer);

	return pFade;
}