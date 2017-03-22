//=============================================================================

// 弾の処理 [Bullet.h]
// Author : 稲澤俊和

//=============================================================================
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "SceneBillboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX (50)

//前方宣言
class CRenderer;

//=============================================================================
//CSceneBillboardクラスを継承したBulletクラス
//=============================================================================
class CBullet:public CSceneBillboard
{
	//公開メンバ
	public:
		CBullet(OBJTYPE nObjType,int nPriority =3);
		~CBullet();
		HRESULT Init(CRenderer* m_pRenderer);		//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画
		static CBullet *CBullet::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer,float dir);		//生成

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		CRenderer* pRenderer;
		D3DXVECTOR3 m_Pos;			//座標
		D3DXVECTOR3 m_Rot;			//角度
		D3DXVECTOR3 m_Scl;			//大きさ
		float SpeedX;				//X軸速度
		float SpeedZ;				//Z軸速度
		float Direction;
		D3DXVECTOR3 WallPos[4];
	

};

#endif