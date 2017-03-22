//=============================================================================

// メッシュウォールの処理 [MeshWall.h]
// Author : 稲澤俊和

//=============================================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define WALL_NUM_BLOCK_X		(100)		//横のブロック数
#define WALL_NUM_BLOCK_Z		(3)		//縦のブロック数
#define WALL_SIZE_BLOCK_X		(10)			//横のブロックサイズ
#define WALL_SIZE_BLOCK_Z		(10)			//縦のブロックサイズ


//=============================================================================
// CSceneクラスを継承したMeshWallクラス
//=============================================================================
class CMeshWall:public CScene
{
	//公開メンバ
	public:
		CMeshWall(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CMeshWall();										//デストラクタ

		HRESULT Init(CRenderer *pRenderer);		//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画

		static CMeshWall* CMeshWall::Create(CRenderer *pRenderer,float PosX,float PosY,float PosZ,float RotX,float RotY,float RotZ,float TranslateX,float TranslateY,float TranslateZ);

		void SetPos(float x,float y,float z){m_pos.x=x;m_pos.y=y;m_pos.z=z;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_pos;};									//座標の取得

		void SetRot(float x,float y,float z){m_rot.x=x;m_rot.y=y;m_rot.z=z;};		//角度の設定
		D3DXVECTOR3 GetRot(void){return m_rot;};									//角度の取得

		void SetTrans(float x,float y,float z){m_Trans.x=x;m_Trans.y=y;m_Trans.z=z;};		//平行移動

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		HRESULT InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
		float GetFieldLengthX(void);			// 中心からＸ端まで
		float GetFieldLengthZ(void);			// 中心からZ端まで

	//非公開メンバ
	private:
		LPDIRECT3DTEXTURE9 m_pD3DTextureField;			// テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffField;		// 頂点バッファへのポインタ
		
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndexBuffField;	// インデックスバッファへのポインタ
		int m_nNumVertexIndex;							// 頂点の総インデックス数
		D3DXMATRIX m_mtxWorldField;			// ワールドマトリックス
		D3DXVECTOR3 m_pos;					// 位置
		D3DXVECTOR3 m_rot;					// 向き
		D3DXVECTOR3 m_Trans;					//

		int m_nNumBlockX, m_nNumBlockZ;			// ブロック数
		int m_nNumVertex;						// 総頂点数
		int m_nNumPolygon;						// 総ポリゴン数
		float m_fSizeBlockX, m_fSizeBlockZ;		// ブロックサイズ
		LPDIRECT3DDEVICE9 m_pDevice;

		
		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		
};


#endif
