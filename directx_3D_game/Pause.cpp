//=============================================================================
//
// ポーズ処理 [Pause.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Game.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene2D.h"
#include "Pause.h"
#include "Input.h"
#include "Fade.h"
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

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause()
{
	m_CurrentMenu=NONE;
	m_pMask=NULL;
	m_pReturnTitle=NULL;
	m_pReturnGame=NULL;
	m_pRetry=NULL;
	m_pArrow=NULL;
	m_Num=0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(CRenderer* pRenderer)
{
	//インスタンスの作成
	m_pMask= new CFade(OBJTYPE_FADE,6);

	//フェードの初期化
	m_pMask->Init(pRenderer);

	COLOR Color;
	Color.R=0;
	Color.G=0;
	Color.B=0;
	Color.A=128;
	m_pMask->FadeStart(FADE_INFINITY,60,Color);

	//画像の生成
	m_pReturnTitle=CScene2D::Create(400,150,300,200,"data/TEXTURE/ReturnGame.png",pRenderer,6);
	m_pReturnGame=CScene2D::Create(400,300,300,200,"data/TEXTURE/ReturnTitle.png",pRenderer,6);
	m_pRetry=CScene2D::Create(400,450,300,200,"data/TEXTURE/Retry.png",pRenderer,6);
	m_pArrow=CScene2D::Create(200,150,100,100,"data/TEXTURE/Arrow2.png",pRenderer,6);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	m_pMask->Uninit();
	m_pReturnTitle->Uninit();
	m_pReturnGame->Uninit();
	m_pRetry->Uninit();
	m_pArrow->Uninit();

}
//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	D3DXVECTOR3 ArrowPos=m_pArrow->GetPos();

	//上移動
	if(GetKeyboardTriger(DIK_W))
	{
		//PlaySound(SOUND_LABEL_SELECT);
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y-150,ArrowPos.z);
		m_Num--;
	}
	//↓移動
	if(GetKeyboardTriger(DIK_S))
	{
		//PlaySound(SOUND_LABEL_SELECT);
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y+150,ArrowPos.z);
		m_Num++;
	}
	//繰り返し処理
	if(m_Num<0)
	{
		m_Num=2;
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y+300,ArrowPos.z);
	}
	if(m_Num>2)
	{
		m_Num=0;
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y-300,ArrowPos.z);
	}
	//決定
	if(GetKeyboardTriger(DIK_RETURN))
	{
		//PlaySound(SOUND_LABEL_ENTER);
		m_CurrentMenu=(PAUSE_MENU)m_Num;
	}
	//ポーズ終了
	if(GetKeyboardTriger(DIK_P))
	{
		m_CurrentMenu=RETURN_GAME;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}
