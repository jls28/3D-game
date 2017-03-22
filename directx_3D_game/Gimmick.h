//=============================================================================
//
// ギミック表示処理 [Gimmick.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// マクロ定義
//=============================================================================

//前方宣言
class CRenderer;

//=============================================================================
//CSceneクラスを継承したCGimmickクラス
//=============================================================================
class CGimmick:public CSceneX
{
	//公開メンバ
	public:
		CGimmick(OBJTYPE nObjType,int nPriority=3);		//コンストラクタ
		~CGimmick();									//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);			//初期化
		void Uninit(void);								//終了
		void Update(void);								//更新
		void Draw(void);								//描画

		static CGimmick* Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//生成

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};	//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};										//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};	//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};										//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		void SetScl(float x,float y,float z){m_Scl.x=x;m_Scl.y=y;m_Scl.z=z;};

		
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得

	//非公開メンバ
	private:
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Rot;			//角度
		D3DXVECTOR3 m_Scl;
		D3DXVECTOR3 m_PosOld;		//前フレの座標
		D3DXVECTOR3 m_RotOld;		//前フレの角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		float Movex;
		float Movez;



};

#endif