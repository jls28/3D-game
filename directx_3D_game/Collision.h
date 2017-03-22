//-----------------------------------------------------------------------------
//
// 当たり判定処理 : collision.h
// Author : 稲澤俊和
//
//-----------------------------------------------------------------------------
#ifndef _COLLISION_H_
#define _COLLISION_H_

//------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 構造体
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// プロトタイプ宣言
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 前方参照
//------------------------------------------------------------------------
class CRenderer;
class CScene;
//------------------------------------------------------------------------
// クラス
//------------------------------------------------------------------------
class CCollision
{
public : 
	CCollision( void );		// コンストラクタ
	~CCollision();			// デストラクタ

	//--  球と球  --//
	bool SphereToSphere3D( const D3DXVECTOR3& pos0 , float radius0 , const D3DXVECTOR3& pos1 , float radius1 );
	bool SphereToSphere3D( CScene& object0 , CScene& object1 , float radius0 , float radius1 );
	bool SphereToSphereXZ( const D3DXVECTOR3& pos0 , const D3DXVECTOR3& pos1 , float radius0 , float radius1 );

	//--  球と矩形  --//
	bool CircleToRectangle2D( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth );
	bool CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth );
	bool CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , CScene& object , float fHeight , float fWidth );

	//--  矩形と矩形  --//
	bool RectangleToRectangle3D( const D3DXVECTOR3& pos0 , float fHeight0 , float fWidth0 , const D3DXVECTOR3& pos1 , float fHeight1 , float fWidth1 );

	//--  外積の当たり判定  --//
	bool LinetoLineXZ( D3DXVECTOR3 pos0st , 
					   D3DXVECTOR3 pos0ed ,
					   D3DXVECTOR3 pos1st ,
					   D3DXVECTOR3 pos1ed ,
					   D3DXVECTOR3 *pPosCross ,
					   float *pfRote ,
					   D3DXVECTOR3 *pVecReflect );


private : 

protected : 
};

#endif // _COLLISION_H_

// END