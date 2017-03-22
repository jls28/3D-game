//=============================================================================
//
// 自機モデル表示処理 [Player.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define EFFECT_MAX (100)

//前方宣言
class CRenderer;



//=============================================================================
//CSceneXクラスを継承したCEnemyクラス
//=============================================================================
class CEffect:public CScene
{
	//公開メンバ
	public:
		CEffect(OBJTYPE nObjType,int nPriority=3);		//コンストラクタ
		~CEffect();										//デストラクタ

		HRESULT Init(CRenderer *pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		static CEffect* Create(int Red,int Green,int Blue,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);

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
		LPDIRECT3DTEXTURE9		m_pD3DTextureEffect;		// テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffEffect;	// 頂点バッファインターフェースへのポインタ
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXMATRIX m_mtxWorldeffect;				//ワールドマトリックス
		
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Rot;
		D3DXVECTOR3 m_Scl;

		
		int m_EffectFlag;
		int m_EffectCnt;
		int m_EffectShow;

		CRenderer* m_pEffect;

		COLOR m_Color;

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;



};

#endif


