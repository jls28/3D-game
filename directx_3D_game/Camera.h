//=============================================================================
//
// カメラ処理 [Camera.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_SPEED		(1.5f)//カメラの速さ
#define CAMERA_SPEED2		(1.5f)//カメラの速さ
#define CIRCLE_CAMERA		(3.0f)


class CScene2D;
//=============================================================================
//Cameraクラス
//=============================================================================
class CCamera
{
	//公開メンバ
	public:
		typedef enum 
		{
			MODE_FIRSTPERSON,
			MODE_THIRDPERSON
		}MODE;

		CCamera();			//コンストラクタ
		~CCamera();			//デストラクタ
		HRESULT InitCamera(CRenderer* pRenderer);					//初期化
		void UpdateCamera(void);									//更新
		void SetCamera(void);										//カメラのセット
		D3DXVECTOR3 GetRotCamera(void){return m_rotCamera;};		//カメラの向きの取得
		static D3DXMATRIX GetMtxView(void){return m_mtxView;};		//MtxViewの取得
		void DrawRot(void);
		static D3DXVECTOR3 GetRot(void){return m_rotCamera;};		//カメラの向きの取得
		D3DXVECTOR3 GetRotDest(void){return m_posCameraPDest;};		//
		static CCamera* GetCamera(void){return m_pCamera;};			//
		static void SetPauseFlag(bool PauseFlag){m_PauseFlag=PauseFlag;};	//ポーズの設定
		static bool GetPauseFlag(void){return m_PauseFlag;};		//ポーズフラグの取得
		void FirstPersonCamera(void);
		void ThirdPersonCamera(void);

		void SetCameraMode(MODE Mode){m_Mode=Mode;};		//前フレの角度の設定
		MODE GetCameraMode(void){return m_Mode;};

		void SetVecCamera(D3DXVECTOR3 Vector){m_VecCamera=Vector;};		//前フレの角度の設定
		D3DXVECTOR3 GetVecCamera(void){return m_VecCamera;};


		// 

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXVECTOR3 m_posCameraP;		//カメラの視点
		D3DXVECTOR3 m_posCameraR;		//カメラの注意点
		D3DXVECTOR3 m_vecCameraV;		//カメラの上方向ベクトル
		static D3DXVECTOR3 m_rotCamera;	//カメラの向き（回転方向）
		D3DXVECTOR3 m_rotCameraDest;	//カメラの向き（回転方向）
		D3DXVECTOR3 m_posCameraPDest;	//目的の視点
		D3DXVECTOR3 m_posCameraRDest;	//目的の注視点
		static D3DXMATRIX m_mtxView;			//ビューマトリックス
		D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
		D3DXVECTOR3 m_zoom;				//ズーム用
		D3DVIEWPORT9 m_viewport;		//画面分割
		LPD3DXFONT m_pFont;
		float m_fAngle;
		float m_fLength;
		float m_angle;
		float m_angleDest;
		float fDiffRotY;
		static CCamera* m_pCamera;
		static bool m_PauseFlag;		//ポーズフラグ
		D3DXVECTOR3 m_Vec;
		MODE m_Mode;
		bool m_FirstPersonFlag;
		D3DXVECTOR3 m_VecCamera;		//カメラのベクトル
		CScene2D* m_pScene2D;


};

#endif 