//=============================================================================
//
// メイン処理 [SCENEX.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include"Scene.h"

//前方宣言
class CRenderer;

//=============================================================================
//CSceneXクラス
//=============================================================================
class CSceneX:public CScene
{
	//公開メンバ
	public:
		CSceneX(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CSceneX();										//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);		//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画

		static CSceneX *CSceneX::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);		//生成

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//角度の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//角度の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		void SetFileName(char* FileName){m_FileName=FileName;};

		char *FileName;

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 pDevice;
		//LPDIRECT3DTEXTURE9  g_pD3DTex;
		//LPDIRECT3DVERTEXBUFFER9 g_pD3DBuff;
		/*float g_fLength;
		float g_fAngle;*/
		
		LPD3DXMESH m_pD3DXMeshPlayer;		//メッシュ情報のポインタ
		LPD3DXBUFFER m_D3DXBuffMatPlayer;	//マテリアル情報へのポインタ
		DWORD m_nNumMatPlayer;				//マテリアル情報の数

		D3DXMATRIX m_mtxWorld;				//ワールドマトリックス


		D3DXVECTOR3 m_PosDest;		//目的の視点
		D3DXVECTOR3 m_RotDest;		//目的の向き
		//フラグ
		bool m_PlayerMove;
		int m_ShootCnt;

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		char* m_FileName;

protected:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;			//モデルの向き
	D3DXVECTOR3 m_Scl;			//モデルの大きさ


};

#endif