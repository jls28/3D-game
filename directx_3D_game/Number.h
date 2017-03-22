//=============================================================================
//
// 数字表示処理 [Number.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene2D.h"
//=============================================================================
// マクロ定義
//=============================================================================


// 前方宣言
class CRenderer;

//=============================================================================
//CNumberクラス
//=============================================================================
class CNumber
{
	//公開メンバ
	public:
		CNumber();		//コンストラクタ
		~CNumber();		//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);		//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画

		static CNumber* Create(float fPosX,float fPosY,CRenderer* m_pRenderer);		//生成

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//座標の代入
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};		//回転角度の代入
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//回転角度の取得

		void UpdateNumber(int nNumber);					//数字の更新
		void SetNumber(int Num){m_Number = Num;};

	//非公開メンバ
	private:
		D3DXVECTOR3 m_Pos;						//ポリゴンの座標
		D3DXVECTOR3 m_Rot;						//ポリゴンの回転角度

		CRenderer *m_pNumber;					//数字のポインタ
		LPDIRECT3DVERTEXBUFFER9 m_pD3DNumberVtxBuff;
		LPDIRECT3DTEXTURE9 m_pD3DNumber;
		LPDIRECT3DDEVICE9 m_pDevice;
		int m_Number;

};

#endif

