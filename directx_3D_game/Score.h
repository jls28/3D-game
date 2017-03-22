//=============================================================================
//
// スコア処理 [Score.h]
// Author : 稲澤俊和
//
//=============================================================================
#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// インクルード
//=============================================================================
#include"Scene.h"
#include "Number.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SCORE_MAX	(99999)		//カンスト
#define DIGIT		(5)			//桁数
//前方宣言
class CRenderer;
class CNumber;
//=============================================================================
//CScoreクラス
//=============================================================================
class CScore:public CScene
{
	//公開メンバ
	public:
		CScore(OBJTYPE nObjType,int nPriority=3);		//コンストラクタ	
		~CScore();										//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);		//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画

		static CScore* Create(float fPosX,float fPosY,CRenderer* m_pRenderer);		//生成

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//座標の代入
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};		//回転角度の代入
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//回転角度の取得

		static void AddScore(int nValue);						//スコアの加算

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの座標の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		static int GetScore(void){return m_nScore;};		//スコアの取得

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXVECTOR3 m_Pos;						//ポリゴンの座標
		D3DXVECTOR3 m_Rot;						//ポリゴンの回転角度
		float m_fLength;						//中心座標と頂点への距離
		float m_fAngle;							//中心座標と頂点への角度
		LPDIRECT3DVERTEXBUFFER9 m_pD3DScoreVtxBuff;
		LPDIRECT3DTEXTURE9 m_pD3DScore;

		static int m_nScore;		//スコア

		static CRenderer* m_pScore;		//スコアのポインタ
		static CNumber* m_pNumber;		//ナンバーのポインタ
		
		D3DXVECTOR3 m_PosOld;						//前フレの座標
		D3DXVECTOR3 m_RotOld;						//前フレの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif
