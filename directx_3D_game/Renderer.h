//=============================================================================
//
// メイン処理 [Renderer.h]
// Author : 稲澤俊和
//
//=============================================================================
#include "main.h"
#include "debugproc.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define SCENE_MAX (5)

//前方宣言
class CScene;
class CLight;
class CCamera;

//=============================================================================
//CRendererクラス
//=============================================================================
class CRenderer
{
	//公開メンバ
	public:
		CRenderer();		//コンストラクタ
		~CRenderer();		//デストラクタ

		HRESULT Init(HWND hWmd,BOOL bWindow);	//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画

		void AddScene(CScene* pScenes);			//Sceneの追加

		LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;};	// デバイスの取得

	//非公開メンバ
	private:
		void DrawFPS(void);
		LPDIRECT3D9 m_pD3D;
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		LPD3DXFONT m_pD3DFont;

		float m_rot;

		CScene* m_apScenes[SCENE_MAX];

		int m_nCountScene;		//Sceneのカウント
};
