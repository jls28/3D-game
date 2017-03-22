//=============================================================================
//
// スコア処理 [Score.h]
// Author : 稲澤俊和
//
//=============================================================================
#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

//=============================================================================
// インクルード
//=============================================================================
#include"Scene.h"
#include "Number.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TIMER_MAX	(999)		//カンスト
#define TIMER_DIGIT	  (3)			//桁数
//前方宣言
class CRenderer;
class CNumber;
//=============================================================================
//CScene2Dクラス
//=============================================================================
class CTimer:public CScene
{
	public:
		CTimer(OBJTYPE nObjType,int nPriority=3);
		~CTimer();
		HRESULT Init(CRenderer* m_pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};
		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};
		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};
		static int GetTime(void){return m_nTimer;};
		static CTimer* Create(float fPosX,float fPosY,CRenderer* m_pRenderer);
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//座標の代入
		D3DXVECTOR3 GetPos(void){return m_Pos;};		//座標の取得
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};	//回転角度の代入
		D3DXVECTOR3 GetRot(void){return m_Rot;};		//回転角度の取得
		static void AddTimer(int nValue);						//スコアの加算




	private:
		D3DXVECTOR3 m_Pos;						//ポリゴンの座標
		D3DXVECTOR3 m_Rot;						//ポリゴンの回転角度
		static int m_nTimer;
		static CRenderer *m_pTimer;
		static CNumber* m_pNumber;
		
		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif