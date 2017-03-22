//=============================================================================
//
// シリンダー表示処理 [Cylinder.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "Scene.h"

//=============================================================================
//CSceneを継承したCCylinderクラス
//=============================================================================
class CCylinder :public CScene
{
	//公開メンバ
	public:
		CCylinder(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CCylinder();										//デストラクタ
		HRESULT Init(CRenderer *pRenderer){return S_OK;};	// 初期化
		HRESULT Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumW,int NumH);
		void Uninit(void);									//終了
		void Update(void);									//更新
		void Draw(void);									//描画

		static CCylinder* Create(float SizeX,float SizeZ,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer);

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//座標の代入
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};		//回転角度の代入
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//回転角度の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};


	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		LPDIRECT3DTEXTURE9 m_pD3DTex;
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtx;
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndex;

		D3DXVECTOR3 m_Pos;		//座標
		D3DXVECTOR3 m_Rot;		//回転
		D3DXVECTOR3 m_Scl;		//大きさ

		int m_nNumIndex;
		int m_nNumWeight,m_nNumHigh;		//横幅と高さ
		int m_nNumVertex;
		int m_nNum;
		float m_fSizeWeight,m_fSizeHigh;	//横サイズと縦サイズ
		D3DXVECTOR2 m_Length;
		static float m_Lengthin[1];
		static int m_nCylinderNum;

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;





		
};








#endif