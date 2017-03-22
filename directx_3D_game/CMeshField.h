//=============================================================================

// メッシュフィールド処理 [MeshField.h]
// Author : 稲澤俊和

//=============================================================================


#ifndef _CFIELD_H_
#define _CFIELD_H_
//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene3D.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CScene3D;

//=============================================================================
// CSceneを継承したMeshFieldクラス
//=============================================================================
class CField : public CScene
{
	// 公開メンバ
	public:
		CField(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CField();										//デストラクタ
		HRESULT Init(CRenderer* pRenderer);				//初期化
		void Uninit();									//解放
		void Update();									//更新
		void Draw();									//描画
		void SetPosition(D3DXVECTOR3 pos){m_Pos = pos;};//accerer
		void SetPosition(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};//accerer
		void SetRot(D3DXVECTOR3 angle){m_Rot = angle;};	//accerer
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//座標の代入
		D3DXVECTOR3 GetPos(void){return m_Pos;};		//座標の取得
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};	//回転角度の代入
	
		D3DXVECTOR3 GetRot(void){return m_Rot;};		//accerer
		D3DXVECTOR3 GetPosition(void){return m_Pos;};	//accerer
	
		static CField* Create(CRenderer* pRenderer,float fPosX,float fPosY,float fPosZ);	//生成
	
		float GetHeight(D3DXVECTOR3 Pos,D3DXVECTOR3* pNormal);
		float GetHeightPolygon(const D3DXVECTOR3& P0,const D3DXVECTOR3& P1,const D3DXVECTOR3& P2,const D3DXVECTOR3& Pos,D3DXVECTOR3* pNormal);
		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};
		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};
		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};
	
	//=============================================================================
	// 非公開メンバ
	//=============================================================================
	private:
		void SetVertexPolygon();				//座標設定
		HRESULT InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	
		VERTEX_3D *m_pVtx;						//座標構造体変数
		LPDIRECT3DDEVICE9 m_pD3DDevice;			//Deviceオブジェクト(描画に必要)
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtexBuff;	//Textureオブジェクト(描画に必要)
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndexBuff;	//インデックスバッファへのポインタ
		LPDIRECT3DTEXTURE9 m_pD3DTex;			//テクスチャ用変数
	
		//座標関係
		D3DXVECTOR3 m_Pos;				//座標
		D3DXVECTOR3 m_Rot;				//角度
		D3DXVECTOR3 m_Scl;				//大きさ
	
		int m_nNumVertexIndex;			//頂点の総インデックス数
	
		int m_nNumBlockX; 				//横のブロック数
		int m_nNumBlockZ;				//縦のブロック数
		float m_fSizeBlockX;			//横のブロックサイズ
		float m_fSizeBlockZ;			//縦のブロックサイズ
	
		int m_nNumVertex;				// 総頂点数
		int m_nNumPolygon;				// 総ポリゴン数
	
		//int m_nNumVertexIndex;			// 頂点の総インデックス数
	
		//回転用変数
		float n_fLength;						//回転用変数
		float n_fAngle;							//回転用変数
		// 頂点情報セット
		VERTEX_3D *pVtx;
	
		D3DXVECTOR3 m_PosOld;					//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;					//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	
};// class CWall
#endif

// EOF