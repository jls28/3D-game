//=============================================================================
//
// 地面処理 [Explosion.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//======================================================
//インクルード
//======================================================
#include"main.h"
#include"Scene.h"

//======================================================
//マクロ定義
//======================================================


//前方宣言
class CRenderer;

//======================================================
//CSceneクラスを継承したCExplosionクラス
//=======================================================
class CExplosion:public CScene
{
	//公開メンバ
	public:
		CExplosion(OBJTYPE nObjType,int nPriority=3);
		~CExplosion();
		HRESULT Init(CRenderer *m_pRenderer);				//爆発処理の初期化
		void Update(void);					//爆発処理の更新
		void Uninit(void);					//爆発処理の終了
		void Draw(void);					//爆発処理の描画

		void TextureUpdate(float x,float y);		//爆発処理のテクスチャの設定
		void DeleteExplosion(void);					//爆発処理の削除

		void SetExplosionPosition(float PosX,float PosY,float PosZ);		//

		static CExplosion* Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);		//生成

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//角度の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;};										//角度の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};	//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};										//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};	//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};										//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	//非公開メンバ
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		LPDIRECT3DTEXTURE9		m_pD3DTex;						// テクスチャへのポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;	// 頂点バッファインターフェースへのポインタ
		
		D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
		CRenderer* pRenderer;
		
		D3DXVECTOR3 m_Pos;			//座標
		D3DXVECTOR3 m_Rot;			//角度
		D3DXVECTOR3 m_Scl;			//大きさ

		int m_nCounterAnim;
		int m_nPatternAnim;

		
		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	



};
#endif
