//=============================================================================
//
// 影表示処理 [Shadow.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ANGLE_LEFT	(D3DX_PI/2.0f)
#define ANGLE_RIGHT	(-D3DX_PI/2.0f)
#define ANGLE_FLONT	(D3DX_PI)
#define ANGLE_BACK	(0.0f)

class CRenderer;
class CPlayer;
//=============================================================================
//CEnemyクラス
//=============================================================================
class CShadow:public CSceneX
{
	public:
		CShadow(OBJTYPE nObjType,int nPriority=3);
		~CShadow();
		HRESULT Init(CRenderer* m_pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		static CShadow* CShadow::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//回転の取得




		
	private:
		D3DXVECTOR3 m_rotDestModel;				//目的の向き
		bool m_Moving;							//モデルが動いてるか
		float m_fDiffRotY;
		D3DXVECTOR3 m_Rot;						//モデルの向き
		D3DXVECTOR3 m_speedModel;				//モデルのスピード
		D3DXVECTOR3 m_Pos;						//モデルのスピード
		D3DXVECTOR3 m_Scl;
		D3DXVECTOR3 m_RotDest;					//目的の向き
		static CRenderer *m_pShadow;
		D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
		LPD3DXMESH m_pD3DXMesh;		//メッシュ情報のポインタ
		LPD3DXBUFFER m_D3DXBuffMat;	//マテリアル情報へのポインタ
		LPDIRECT3DDEVICE9 pDevice;
		DWORD m_nNumMat;				//マテリアル情報の数
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;		//頂点バッファインターフェースへのポインタ
		static CPlayer* m_pPlayer;
		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度

		CScene* m_pSceneLink;		//ギミックとのリンク

		D3DXVECTOR3 GimmickPos[4];	//ギミックの4頂点の座標







};

#endif