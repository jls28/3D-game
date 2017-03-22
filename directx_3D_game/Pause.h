//=============================================================================
//
// ポーズ処理 [Pause.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
//ポーズメニュー
typedef enum
{
	RETURN_GAME=0,
	RETURN_TITLE,
	RETRY,
	NONE,
	PAUSE_MANU_MAX
}PAUSE_MENU;

// 前方宣言
class CRenderer;
class CScene2D;
class CFade;

//=============================================================================
//Pauseクラス
//=============================================================================
class CPause
{
	//公開メンバ
	public:
		CPause();		//コンストラクタ
		~CPause();		//デストラクタ

		HRESULT Init(CRenderer* pRenderer);		//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画

		PAUSE_MENU GetMenu(void){return m_CurrentMenu;};	//

	//非公開メンバ
	private:
		CScene2D* m_pReturnTitle;		//タイトルへ戻る
		CScene2D* m_pReturnGame;		//ゲームに戻る
		CScene2D* m_pRetry;				//リトライ
		CScene2D* m_pArrow;				//矢印
		int m_Num;						//何番目か
		CFade* m_pMask;
		PAUSE_MENU m_CurrentMenu;
};

#endif