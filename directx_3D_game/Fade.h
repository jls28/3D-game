//=============================================================================
//
// Fade処理 [Fade.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "Scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
//フェードの種類
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_IN_FINISH,
	FADE_OUT,
	FADE_OUT_FINISH,
	FADE_INFINITY,
	FADE_MAX
}FADE;


//前方宣言
class CRenderer;


//必ずScene遷移の際に使うフェードは一番最後に更新すること
//守らないとキーボードが更新されなくなる可能性あり

//=============================================================================
// CScene2Dを継承したCFadeクラス
//=============================================================================
class CFade:public CScene2D
{
	//公開メンバ
	public:
		CFade(OBJTYPE nObjType,int nPriority =7);							// コンストラクタ
		~CFade();						// デストラクタ
		HRESULT Init(CRenderer *pRenderer);	// 初期化

		void SetPos(float x,float y,float z){}
		void Uninit(void);					// 終了
		void Update(void);					// 更新
		void Draw(void);					// 描画

		void SetFade(FADE fade){m_Mode = fade;};		//フェードの設定
		FADE GetFade(void){return m_Mode;};				//フェードの状態の取得
		static CFade* Create(CRenderer *pRenderer);		//オブジェクトの生成
		void FadeStart(FADE Mode,int Time,COLOR Color);				//フェードの開始

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;			// デバイス
		VERTEX_2D m_aFadeVtx[4];
		LPDIRECT3DTEXTURE9 m_pD3DFadeTex;
		FADE m_Mode;							//モード
		int m_aAlpha;							//アルファ値
		int m_Time;								//時間
		COLOR m_Color;							//色
		bool m_Flag;								//フェードフラグ
		int m_RateAdd;
};

#endif