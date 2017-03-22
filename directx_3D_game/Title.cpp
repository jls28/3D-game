//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Title.h"
#include "Input.h"
#include "Game.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene2D.h"
#include "Fade.h"
#include "sound.h"
#include "TitleLogo.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CTitle::m_pRenderer;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pD3DTex=NULL;
	m_pDevice=NULL;
	m_pRenderer = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
	 
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(CRenderer* pRenderer)
{
	//デバイスの取得
	m_pDevice = pRenderer->GetDevice();
	//インタンス作成
	m_pFade = new CFade(OBJTYPE_FADE);

	//フェードの初期化
	m_pFade->Init(pRenderer);
	COLOR Color;
	Color.R=255;
	Color.G=255;
	Color.B=255;
	Color.A=255;
	m_pFade->FadeStart(FADE_IN,60,Color);

	CScene2D::Create(400,300,800,600,"data/TEXTURE/sasori.jpg",pRenderer);
	CTitleLogo::Create(400,100,500,300,"data/TEXTURE/TitleLogo.png",pRenderer);

	PlaySound(SOUND_LABEL_TITLE);


	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	StopSound(SOUND_LABEL_TITLE);

	//テクスチャの解放
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex ->Release();
		m_pD3DTex = NULL;
	}
	CScene::ReleaseAll();
}
//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	if(GetKeyboardTriger(DIK_RETURN))
	{
		PlaySound(SOUND_LABEL_ENTER);
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);

	}
	if(m_pFade->GetFade()==FADE_OUT_FINISH)
	{
		CManager::SetNextPhase(MODE_GAME);
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
	m_pDevice->SetTexture(0,m_pD3DTex);
	m_pDevice->SetFVF(FVF_VERTEX_2D);		
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
									  2,
									  &m_aVtx[0],
									  sizeof(VERTEX_2D));

}