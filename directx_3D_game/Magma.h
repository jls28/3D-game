//
//めっしフィールド
//

#ifndef _MAGMA_H_
#define _MAGMA_H_
//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "Scene3D.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CScene3D;

//=============================================================================
// クラス定義
//=============================================================================
class CMagma : public CScene3D
{
//=============================================================================
// 公開メンバ
//=============================================================================
public:
	CMagma(OBJTYPE nObjType,int nPriority =3);										//コンストラクタ
	~CMagma();										//デストラクタ
	HRESULT Init(LPDIRECT3DDEVICE9 device);			//初期化
	void Uninit();									//解放
	void Update();									//更新
	void Draw();									//描画
	void SetPosition(D3DXVECTOR3 pos){m_Pos = pos;};//accerer
	void SetPosition(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};//accerer
	void SetRot(D3DXVECTOR3 angle){m_Rot = angle;};	//accerer

	D3DXVECTOR3 GetRot(void){return m_Rot;};		//accerer
	D3DXVECTOR3 GetPosition(void){return m_Pos;};	//accerer

	static CMagma* Create(LPDIRECT3DDEVICE9 device,float fPosX,float fPosY,float fPosZ);	

	float GetHeight(D3DXVECTOR3 Pos,D3DXVECTOR3* pNormal);
	float GetHeightPolygon(const D3DXVECTOR3& P0,const D3DXVECTOR3& P1,const D3DXVECTOR3& P2,const D3DXVECTOR3& Pos,D3DXVECTOR3* pNormal);


//=============================================================================
// 非公開メンバ
//=============================================================================
private:
	void SetVertexPolygon();				//座標設定
	HRESULT InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	VERTEX_3D *n_pVtx;						//座標構造体変数
	LPDIRECT3DDEVICE9 n_pD3DDevice;			//Deviceオブジェクト(描画に必要)
	LPDIRECT3DVERTEXBUFFER9 n_pD3DVtexBuff;	//Textureオブジェクト(描画に必要)
	LPDIRECT3DINDEXBUFFER9 n_pD3DIndexBuff;	//インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9 n_pD3DTex;			//テクスチャ用変数

	//座標関係
	D3DXVECTOR3 m_Pos;						//座標変数
	D3DXVECTOR3 m_Rot;						//角度変数
	D3DXVECTOR3 m_Scl;

	int n_nNumVertexIndex;					//頂点の総インデックス数

	int m_nNumBlockX; 			// ブロック数
	int m_nNumBlockZ;
	float m_fSizeBlockX;		// ブロックサイズ
	float m_fSizeBlockZ;

	int m_nNumVertex;						// 総頂点数
	int m_nNumPolygon;						// 総ポリゴン数

	int m_nNumVertexIndex;							// 頂点の総インデックス数

	//回転用変数
	float n_fLength;						//回転用変数
	float n_fAngle;							//回転用変数
	// 頂点情報セット
	VERTEX_3D *pVtx;

	// 時間
	float m_fWaterTime;

	float m_Rotate;

	// 色
	unsigned char m_Color;
	unsigned char m_ColorAdd;

};// class CWall
#endif

// EOF