//=============================================================================
//
// メイン処理 [Scene2D.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// インクルード
//=============================================================================
#include"Scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCENE_2D (5)

//前方宣言
class CRenderer;

//=============================================================================
//CSceneクラスを継承したCScene2Dクラス
//=============================================================================
class CScene2D:public CScene
{
	//公開メンバ
	public:
		CScene2D(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CScene2D();										//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);		//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画

		static CScene2D* Create(float fPosX,float fPosY,float fSizeX,float fSizeY,char* TextureName,CRenderer* m_pRenderer,int nPriority =3);

		void SetSize(float x,float y,float z){m_Size.x=x;m_Size.y=y;m_Size.z=z;};

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//座標の代入
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};	//回転角度の代入
		D3DXVECTOR3 GetRot(void){return m_Rot;};								//回転角度の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		char* TextureName;

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pDevice;				//デバイス
		LPDIRECT3DTEXTURE9  m_pD3DTex;			//テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;		//頂点バッファインターフェースへのポインタ
		D3DXVECTOR3 m_Pos;						//ポリゴンの座標
		D3DXVECTOR3 m_Size;						//ポリゴンのサイズ
		D3DXVECTOR3 m_Rot;						//ポリゴンの回転角度
		float m_fLength;						//中心座標と頂点への距離
		float m_fAngle;							//中心座標と頂点への角度
		D3DXVECTOR3 m_PosOld;					//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;					//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif