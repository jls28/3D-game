//=============================================================================
//
// Dome表示処理 [Dome.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _DOME_H_
#define _DOME_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"

//前方宣言
class CRenderer;

//=============================================================================
//CSceneクラスを継承したCDomeクラス
//=============================================================================
class CDome:public CScene
{
	//公開メンバ
	public:
		CDome(OBJTYPE nObjType,int nPriority =3);			// コンストラクタ
		~CDome();											// デストラクタ
		HRESULT Init(CRenderer *pRenderer){return S_OK;};	// 初期化
		HRESULT Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumH,int NumW);	// 初期化

		void SetPos(float x,float y,float z){}
		void Uninit(void);					// 終了
		void Update(void);					// 更新
		void Draw(void);					// 描画
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};				//座標の取得
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;}				//回転の取得

		static CDome* Create(float SizeX,float SizeZ,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer);

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの回転の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの回転の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	private:	// 非公開
		// メンバ変数
		LPDIRECT3DDEVICE9 m_pD3DDevice;			// デバイス
		LPDIRECT3DTEXTURE9 m_pD3DTex;		// テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtx;	// 頂点バッファインターフェースへのポインタ
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndex;

		D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
		D3DXVECTOR3 m_Pos;						// 座標
		D3DXVECTOR3 m_Rot;						// 向き(回転)
		D3DXVECTOR3 m_Scl;						// 大きさ(スケール)

		int m_nNumIndex;			//頂点の総インデックス数
		int m_nNumWeight,m_nNumHigh;		//ブロック数
		int m_nNumVertex;			//総頂点数
		int m_nNum;					//総ポリゴン数
		float m_fSizeWeight,m_fSizeHigh;	//ブロックサイズ
		float m_Length;

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;



};

#endif