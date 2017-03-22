//=============================================================================
//
// マネージャ処理 [CManager.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//ゲームのモード
typedef enum
{
	MODE_TITLE,		//タイトル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_GAMEOVER,	//ゲームオーバー画面
	MODE_RESET
}MODE;


//前方宣言
class CRenderer;
class CField;
class CCamera;
class CLight;
class CPlayer;
class CGimmick;
class CDebugProc;
class CFade;
class CGame;
class CTitle;
class CResult;

//=============================================================================
//CManagerクラス
//=============================================================================
class CManager
{
	//公開メンバ
	public:
		CManager();		//コンストラクタ
		~CManager();	//デストラクタ

		HRESULT Init(HINSTANCE hInstance,HWND hWnd,bool bWindow);		//初期化
		void Uninit(void);												//終了
		void Update(void);												//更新
		void Draw(void);												//描画

		static CRenderer* GetRenderer(void){return m_pRenderer;};		//Rendererのポインタの取得

		static void SetNextPhase(MODE mode){m_NextPhase=mode;};			//モードの設定
		static MODE GetNextPhase(void){return m_NextPhase;};			//モードの取得

		static MODE GetPhase(void){return m_Phase;};			//モードの取得

		static void SetPauseFlag(bool PauseFlag);						//ポーズの設定
		static bool GetPauseFlag(void){return m_PauseFlag;};			//ポーズの取得

		void PhaseExchange(void);										//フェーズの切り替え

		static void SetFadeFlag(bool FadeFlag){m_FadeFlag=FadeFlag;};	//フェードフラグの設定
		static bool GetFadeFlag(void){return m_FadeFlag;}				//フェードフラグの取得

		static CCamera* GetCamera(void){return m_pCamera;};

	//非公開メンバ
	private:
		static CRenderer* m_pRenderer;
		CFade* m_pFade;				//フェードのポインタ
		static CGame* m_pGame;		//ゲーム画面のポインタ
		static CTitle* m_pTitle;	//タイトル画面のポインタ
		static CResult* m_pResult;	//リザルト画面のポインタ

		CLight* m_pLight;			//ライトのポインタ
		//CCamera* m_pCamera;			//カメラのポインタ
		CDebugProc* m_pDebug;		//デバッグ表示のポインタ

		static MODE m_Phase;		//現在のフェーズ
		static MODE m_NextPhase;	//次のフェーズ
		static bool m_PauseFlag;	//ポーズフラグ
		static bool m_FadeFlag;		//フェードフラグ
		static CCamera* m_pCamera;

};

#endif