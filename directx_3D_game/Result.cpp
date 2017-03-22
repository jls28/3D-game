//=============================================================================
//
// リザルト処理 [Result.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Result.h"
#include "Renderer.h"
#include "Manager.h"
#include "Input.h"
#include "Scene.h"
#include "Fade.h"
#include "Manager.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CResult::m_pRenderer;

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pDevice=NULL;
	m_pD3DTex=NULL;
	m_pRenderer = NULL;
	m_pFade=NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(CRenderer* pRenderer)
{
	//デバイスの取得
	m_pDevice = pRenderer->GetDevice();

	//インタンス作成
	m_pFade = new CFade(OBJTYPE_FADE);

	PlaySound(SOUND_LABEL_RESULT);

	//フェードの初期化
	m_pFade->Init(pRenderer);
	COLOR Color;
	Color.R=255;
	Color.G=255;
	Color.B=255;
	Color.A=255;
	m_pFade->FadeStart(FADE_IN,60,Color);

	//リザルト画面のテクスチャ
	CScene2D::Create(400,300,800,600,"data/TEXTURE/result.png",pRenderer);




	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{	
	StopSound(SOUND_LABEL_RESULT);

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
void CResult::Update(void)
{
	//えんたーキーでタイトルへ
	if(GetKeyboardTriger(DIK_RETURN))
	{
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);
	}
	if(m_pFade->GetFade()==FADE_OUT_FINISH)
	{
		CManager::SetNextPhase(MODE_TITLE);
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
	m_pDevice->SetTexture(0,m_pD3DTex);
	m_pDevice->SetFVF(FVF_VERTEX_2D);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
									  2,
									  &m_aVtx[0],
									  sizeof(VERTEX_2D));

}