//=============================================================================
//
// CScene3D [CScene3D.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"

//前方宣言
class CRenderer;

//=============================================================================
//CScene3Dクラス
//=============================================================================
class CScene3D:public CScene
{
	public:		// 公開

		CScene3D(OBJTYPE nObjType,int nPriority =3);			// コンストラクタ
		~CScene3D();											// デストラクタ

		HRESULT Init(CRenderer *pRenderer);		// 初期化
		void Uninit(void);						// 終了
		void Update(void);						// 更新
		void Draw(void);						// 描画

		static CScene3D* Create(float fPosX,float fPosY,float fPosZ,float fSizeX,float fSizeY,float fSizeZ,CRenderer* m_pRenderer);		//オブジェクトの生成

		void SetPos(float x,float y,float z){}
		void SetScl(float x,float y,float z){m_Scl.x = x;m_Scl.y = y;m_Scl.z = z;};								//大きさの設定

		void SetCamera(void);				// カメラの設定処理
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};				//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//回転の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;}											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	private:	// 非公開

		// メンバ変数
		LPDIRECT3DDEVICE9 m_pD3DDevice;			// デバイス
		LPDIRECT3DTEXTURE9 m_pD3DTexture;		// テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;	// 頂点バッファインターフェースへのポインタ

		D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
		D3DXVECTOR3 m_Pos;						// 位置
		D3DXVECTOR3 m_Rot;						// 向き(回転)
		D3DXVECTOR3 m_Scl;						// 大きさ(スケール)

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		static CRenderer *m_pScene3D;			//3Dのポインタ

};

#endif