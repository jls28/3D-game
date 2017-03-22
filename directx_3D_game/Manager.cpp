//=============================================================================
//
// メイン処理 [Manager.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "Scene.h"
#include "Fade.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "Shadow.h"
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
CRenderer* CManager::m_pRenderer=NULL;
CGame* CManager::m_pGame=NULL;
CTitle* CManager::m_pTitle=NULL;
CResult* CManager::m_pResult=NULL;
MODE CManager::m_Phase;
MODE CManager::m_NextPhase;
bool CManager::m_PauseFlag=false;
bool CManager::m_FadeFlag=false;
CCamera* CManager::m_pCamera=NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pGame=NULL;
	m_pTitle=NULL;
	m_pResult=NULL;
	m_Phase=MODE_TITLE;
	m_NextPhase=MODE_TITLE;
	m_PauseFlag=false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd,bool bWindow)
{
	//インタンス作成
	m_pRenderer = new CRenderer;
	m_pLight = new CLight;
	m_pCamera = new CCamera;


	//サウンドの初期化
	InitSound(hWnd);

	//キーボードの初期化
	InitKeyboard(hInstance,hWnd);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	//現在のフェーズ管理
	switch(m_Phase)
	{
		//タイトル時
		case MODE_TITLE:
			m_pTitle= new CTitle;
			m_pTitle->Init(m_pRenderer);
			break;

		//ゲーム時
		case MODE_GAME:
			m_pGame= new CGame;
			m_pGame->Init(m_pRenderer);
			break;

		//リザルト時
		case MODE_RESULT:
			m_pResult= new CResult;
			m_pResult->Init(m_pRenderer);
			break;
	}

#ifdef _DEBUG
	m_pDebug = new CDebugProc;
	m_pDebug->Init();
#endif

	//カメラの初期化
	m_pCamera->InitCamera(m_pRenderer);
	//ライトの初期化
	m_pLight->InitLight(m_pRenderer);
	

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{	
	//キーボードの終了
	UninitKeyboard();
	// 終了処理
	m_pDebug->Uninit();

#ifdef _DEBUG
	delete m_pDebug;
#endif

	//消去
	delete m_pLight;
	delete m_pCamera;
	
	//現在のフェーズ管理
	switch(m_Phase)
	{
		//タイトル時
		case MODE_TITLE:
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle=NULL;
			break;

		//ゲーム時
		case MODE_GAME:
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame=NULL;
			break;

		//リザルト時
		case MODE_RESULT:
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult=NULL;
			break;
	}
	CScene::ReleaseAll();

	m_pRenderer->Uninit();

	//delete m_pRenderer;		//必ず最後


}
//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	//キーボードの更新
	UpdateKeyboard();

	//カメラの更新
	m_pCamera->UpdateCamera();

	//現在のフェーズ管理
	switch(m_Phase)
	{
		//タイトル時
		case MODE_TITLE:
			m_pTitle->Update();
			break;

		//ゲーム時
		case MODE_GAME:
			m_pGame->Update();
			break;

		//リザルト時
		case MODE_RESULT:
			m_pResult->Update();
			break;
	}

	m_pRenderer->Update();		//こいつは必ず最後
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// カメラの設置
	m_pCamera->SetCamera();

	m_pRenderer->Draw();
}

//=============================================================================
// フェーズの切り替え処理
//=============================================================================
void CManager::PhaseExchange(void)
{
	//次のフェーズと現在のフェーズが違ったら
	if(m_NextPhase!=m_Phase)
	{
		//現在のフェーズの破棄
		switch(m_Phase)
		{
			case MODE_TITLE:
				m_pTitle->Uninit();
				delete m_pTitle;
				m_pTitle=NULL;
				break;

			case MODE_GAME:
				m_pGame->Uninit();
				delete m_pGame;
				m_pGame=NULL;
				break;

			case MODE_RESULT:
				m_pResult->Uninit();
				delete m_pResult;
				m_pResult=NULL;
				break;
		}

	//次のフェーズを生成・Init
	switch(m_NextPhase)
	{
		case MODE_TITLE:
			m_pTitle= new CTitle;
			m_pTitle->Init(m_pRenderer);
			break;

		case MODE_GAME:
			m_pGame= new CGame;
			m_pGame->Init(m_pRenderer);
			break;

		case MODE_RESULT:
			m_pResult= new CResult;
			m_pResult->Init(m_pRenderer);
			break;

		case MODE_RESET:
			switch(m_Phase)
			{
				case MODE_TITLE:
					m_pTitle= new CTitle;
					m_pTitle->Init(m_pRenderer);
					m_NextPhase=m_Phase;
					break;

				case MODE_GAME:
					m_pGame= new CGame;
					m_pGame->Init(m_pRenderer);
					m_NextPhase=m_Phase;
					break;

				case MODE_RESULT:
					m_pResult= new CResult;
					m_pResult->Init(m_pRenderer);
					m_NextPhase=m_Phase;
					break;
			}
		}
	}
	m_Phase=m_NextPhase;
}

//=============================================================================
// ポーズフラグの設定
//=============================================================================
void CManager::SetPauseFlag(bool PauseFlag)
{
	m_PauseFlag=PauseFlag;
	CScene::SetPauseFlag(m_PauseFlag);
	CCamera::SetPauseFlag(m_PauseFlag);
}