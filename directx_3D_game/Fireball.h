//=============================================================================
//
// メイン処理 [SceneBillboard.h]
// Author : 稲澤俊和
//
//=============================================================================
#pragma once
#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include "SceneBillboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//前方宣言
class CRenderer;
class CEffect;

//=============================================================================
//CSceneクラスを継承したCSceneBillboardクラス
//=============================================================================
class CFireball:public CSceneBillboard
{
	//公開メンバ
	public:
		CFireball(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CFireball();										//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);		//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画

		static CFireball* CFireball::Create(int Pattern,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//角度の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;};										//角度の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	//非公開メンバ
	private:
		CRenderer* pRenderer;
		LPDIRECT3DDEVICE9 pDevice;
		LPDIRECT3DTEXTURE9  m_pD3DTex;
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;		//頂点バッファインターフェースへのポインタ
		D3DXMATRIX m_mtxWorldBullet;			//ワールドマトリックス

		D3DXVECTOR3 m_Pos;		//座標
		D3DXVECTOR3 m_Rot;		//角度
		D3DXVECTOR3 m_Scl;		//大きさ

		D3DXVECTOR3 m_Angle;


		float m_fLength;
		float m_fAngle;

		CFireball *m_pFireball;

		float SpeedX;							//X軸速度
		float SpeedZ;							//Z軸速度
		bool BulletFlag;						//使用フラグ

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		int m_Pattern;

};

#endif