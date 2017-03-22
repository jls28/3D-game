//-----------------------------------------------------------------------------
//
// 当たり判定処理 : collision.cpp
// Author : 稲澤俊和
//
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------
#include "main.h"
#include "Renderer.h"
#include "Collision.h"

#include <math.h>
#include "scene.h"

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
// 静的メンバ変数
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------

//-------------------------------------------------------------------
// 関数名 : コンストラクタ
//
// 引数   : なし
//-------------------------------------------------------------------
CCollision::CCollision(void)
{
}

//-------------------------------------------------------------------
// 関数名 : デストラクタ
//
// 引数   : なし 
//-------------------------------------------------------------------
CCollision::~CCollision(void)
{
}

//-------------------------------------------------------------------
// 関数名 : 球と球の当たり判定
//
// 引数   : CSCENE& object0 : オブジェクト0
// 引数   : CSCENE& object1 : オブジェクト1
// 引数   : float radius0 : 半径
// 引数   : float radius1 : 半径
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::SphereToSphere3D(CScene& object0,CScene& object1,float radius0,float radius1)
{
	//--  計算用  --//
	D3DXVECTOR3 pos0 = object0.GetPos();
	D3DXVECTOR3 pos1 = object1.GetPos();

	//--  円の判定用  --//
	D3DXVECTOR3 pos = pos0 - pos1 ;

	float r = radius0 + radius1 ;

	if( ( ( pos.x * pos.x ) + ( pos.y * pos.y ) + ( pos.z * pos.z ) < ( r * r ) == true ) )
	{
		return true ;		// HIT
	}

	return false ;
}

//-------------------------------------------------------------------
// 関数名 : 球と球の当たり判定
//
// 引数   : VECTOR3& pos0 : 座標0
// 引数   : VECTOR3& pos1 : 座標1
// 引数   : float radius0 : 半径
// 引数   : float radius1 : 半径
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::SphereToSphere3D( const D3DXVECTOR3& pos0 , float radius0 , const D3DXVECTOR3& pos1 , float radius1 )
{
	//--  円の判定用  --//
	D3DXVECTOR3 pos ;
	pos.x = pos0.x - pos1.x ;
	pos.y = pos0.y - pos1.y ;
	pos.z = pos0.z - pos1.z ;

	float r = radius0 + radius1 ;

	if( ( ( pos.x * pos.x ) + ( pos.y * pos.y ) + ( pos.z * pos.z ) < ( r * r ) == true ) )
	{
		return true ;		// HIT
	}

	return false ;
}

//-------------------------------------------------------------------
// 関数名 : 球と球の当たり判定
//
// 引数   : VECTOR3& pos0 : 座標0
// 引数   : VECTOR3& pos1 : 座標1
// 引数   : float radius0 : 半径
// 引数   : float radius1 : 半径
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::SphereToSphereXZ( const D3DXVECTOR3& pos0 , const D3DXVECTOR3& pos1 , float radius0 , float radius1 )
{
	//--  円の判定用  --//
	D3DXVECTOR3 pos ;
	pos.x = pos0.x - pos1.x ;
	pos.y = pos0.y - pos1.y ;
	pos.z = pos0.z - pos1.z ;

	float r = radius0 + radius1 ;

	if( ( ( pos.x * pos.x ) + ( pos.z * pos.z ) < ( r * r ) == true ) )
	{
		return true ;		// HIT
	}

	return false ;
}

//-------------------------------------------------------------------
// 関数名 : 円と矩形
//
// 引数   : VECTOR3& pos0 : オブジェクト0
// 引数   : float radius : 半径
// 引数   : VECTOR3& pos1 : オブジェクト1
// 引数   : float fHeight : 縦幅
// 引数   : float fWidth : 横幅
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::CircleToRectangle2D( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth )
{
	D3DXVECTOR3 pos[ 4 ];

	pos[ 0 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 0 ].y = pos1.y + fHeight * 0.5f ;

	pos[ 1 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 1 ].y = pos1.y + fHeight * 0.5f ;

	pos[ 2 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 2 ].y = pos1.y - fHeight * 0.5f ;

	pos[ 3 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 3 ].y = pos1.y - fHeight * 0.5f ;

	for( int i = 0 ; i < 4 ; i ++ )
	{
		if( SphereToSphere3D( pos0 , radius , pos[ i ] , 0.1f ) )
		{
			return true ;
		}
	}

	return false ;
}

//-------------------------------------------------------------------
// 関数名 : 円と矩形
//
// 引数   : VECTOR3& pos0 : オブジェクト0
// 引数   : float radius : 半径
// 引数   : VECTOR3& pos1 : オブジェクト1
// 引数   : float fHeight : 縦幅
// 引数   : float fWidth : 横幅
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , const D3DXVECTOR3& pos1 , float fHeight , float fWidth )
{
	//VECTOR3 pos0 = object0.GetPos();
	//VECTOR3 pos1 = object1.GetPos();

	D3DXVECTOR3 pos[ 4 ];		// 頂点
	D3DXVECTOR3 VecLine ;		// ベクトル
	D3DXVECTOR3 VecToTarget ;	// ターゲット

	for( int i = 0 ; i < 4 ; i++ )
	{
		pos[ i ] = D3DXVECTOR3( 0 , 0 , 0 );
	}

	pos[ 0 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 0 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 1 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 1 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 2 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 2 ].z = pos1.z - fHeight * 0.5f ;

	pos[ 3 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 3 ].z = pos1.z - fHeight * 0.5f ;

	//VECTOR3 offset = pos0 - pos1 ;	// オフセット
	//pos0.x = pos1.x + ( cosf( -pos1->GetRot().y ) * offset.x ) + sinf( -pos1->GetRot().y ) * offset.z ;
	//pos0.z = pos1.z + ( cosf( -pos1->GetRot().y ) * offset.z ) + sinf( -pos1->GetRot().y ) * offset.x ;

	for( int i = 0 ; i < 4 ; i ++ )
	{
		VecLine = pos[ ( 1 + i ) %4 ] - pos[ i ];

		VecToTarget.x = pos0.x - pos[ i ].x ;
		VecToTarget.y = pos0.y - pos[ i ].y ;
		VecToTarget.z = pos0.z - pos[ i ].z ;

		//--  範囲外に行ったら  --//
		if( VecToTarget.x * VecLine.z - VecToTarget.z * VecLine.x < 0.001f )
		{
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------
// 関数名 : 円と矩形
//
// 引数   : VECTOR3& pos0 : 座標
// 引数   : float radius : 半径
// 引数   : CSCENE& object : オブジェクト
// 引数   : float fHeight : 縦幅
// 引数   : float fWidth : 横幅
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::CircleToRectangleXZ( const D3DXVECTOR3& pos0 , float radius , CScene& object , float fHeight , float fWidth )
{
	//VECTOR3 pos0 = object0.GetPos();
	D3DXVECTOR3 pos1 = object.GetPos();
	D3DXVECTOR3 rot =  object.GetRot();

	D3DXVECTOR3 pos[ 4 ];		// 頂点
	D3DXVECTOR3 VecLine ;		// ベクトル
	D3DXVECTOR3 VecToTarget ;	// ターゲットベクトル
	D3DXVECTOR3 target ;		// ターゲット

	pos[ 0 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 0 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 1 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 1 ].z = pos1.z + fHeight * 0.5f ;

	pos[ 2 ].x = pos1.x + fWidth * 0.5f ;
	pos[ 2 ].z = pos1.z - fHeight * 0.5f ;

	pos[ 3 ].x = pos1.x - fWidth * 0.5f ;
	pos[ 3 ].z = pos1.z - fHeight * 0.5f ;

	D3DXVECTOR3 offset ; // = pos0 - pos1 ;	// オフセット
	offset.x = pos0.x - pos1.x ;
	offset.y = pos0.y - pos1.y ;
	offset.z = pos0.z - pos1.z ;

	target.x = pos1.x + cosf( rot.y ) * offset.x + sinf( rot.y ) * offset.z ;
	target.z = pos1.z + cosf( rot.y ) * offset.z + sinf( rot.y ) * offset.x ;

	for( int i = 0 ; i < 4 ; i ++ )
	{
		VecLine = pos[ ( 1 + i ) % 4 ] - pos[ i ];
		VecToTarget = target - pos[ i ];

		//--  範囲外に行ったら  --//
		if( VecToTarget.x * VecLine.z - VecToTarget.z * VecLine.x < 0.0f )
		{
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------
// 関数名 : 矩形と矩形
//
// 引数   : CSCENE& pos0 : オブジェクト0
// 引数   : float fHeight : 縦幅
// 引数   : float fWidth : 横幅
// 引数   : CSCENE& pos1 : オブジェクト1
// 引数   : float fHeight : 縦幅
// 引数   : float fWidth : 横幅
// 返り値 : 真偽
//-------------------------------------------------------------------
bool RectangleToRectangle3D( CScene& pos0 , float fHeight0 , float fWidth0 , CScene& pos1 , float fHeight1 , float fWidth1 )
{
	//VECTOR3 p0 = object0.GetPos();
	//VECTOR3 p1 = object1.GetPos();

	//VECTOR3 pos0[ 4 ];
	//VECTOR3 pos1[ 4 ];

	//pos0[ 0 ].x = p0.x - fWidth0 * 0.5f ;
	//pos0[ 0 ].y = p0.y + fHeight0 * 0.5f ;
	//			 
	//pos0[ 1 ].x = p0.x + fWidth0 * 0.5f ;
	//pos0[ 1 ].y = p0.y + fHeight0 * 0.5f ;
	//			 
	//pos0[ 2 ].x = p0.x - fWidth0 * 0.5f ;
	//pos0[ 2 ].y = p0.y - fHeight0 * 0.5f ;
	//			
	//pos0[ 3 ].x = p0.x + fWidth0 * 0.5f ;
	//pos0[ 3 ].y = p0.y - fHeight0 * 0.5f ;

	//pos1[ 0 ].x = p1.x - fWidth0 * 0.5f ;
	//pos1[ 0 ].y = p1.y + fHeight0 * 0.5f ;
	//		
	//pos1[ 1 ].x = p1.x + fWidth0 * 0.5f ;
	//pos1[ 1 ].y = p1.y + fHeight0 * 0.5f ;
	//
	//pos1[ 2 ].x = p1.x - fWidth0 * 0.5f ;
	//pos1[ 2 ].y = p1.y - fHeight0 * 0.5f ;

	//pos1[ 3 ].x = p1.x + fWidth0 * 0.5f ;
	//pos1[ 3 ].y = p1.y - fHeight0 * 0.5f ;

	////--  Zの判定  --//
	//if( g_Bullet[ nBulletNum ].object.pos.z - HITBULLETLENGEZ < pEnemyBox[ nEnemyNum ].object.pos.z + HITBULLETLENGEZ && 
	//	g_Bullet[ nBulletNum ].object.pos.z + HITBULLETLENGEZ > pEnemyBox[ nEnemyNum ].object.pos.z - HITBULLETLENGEZ )
	//{
	//	//--  Xの判定  --//
	//	if( g_Bullet[ nBulletNum ].object.pos.x - HITBULLETLENGEX < pEnemyBox[ nEnemyNum ].object.pos.x + HITBULLETLENGEX && 
	//		g_Bullet[ nBulletNum ].object.pos.x + HITBULLETLENGEX > pEnemyBox[ nEnemyNum ].object.pos.x - HITBULLETLENGEX )
	//	{
	//		//--  Yの判定  --//
	//		if( g_Bullet[ nBulletNum ].object.pos.y - HITBULLETLENGEY < pEnemyBox[ nEnemyNum ].object.pos.y + HITBULLETLENGEY && 
	//			g_Bullet[ nBulletNum ].object.pos.y + HITBULLETLENGEY > pEnemyBox[ nEnemyNum ].object.pos.y - HITBULLETLENGEY )
	//		{
	//			//--  削除  --//
	//			DeleteEnemyBox( nEnemyNum );
	//			DeleteBullet( nBulletNum );

	//			//--  爆発  --//
	//			SetExplosion( g_Bullet[ nBulletNum ].object.pos );

	//			//--  サウンド  --//
	//			PlaySound( SOUND_LABEL_SE_EXPLOSION01 );

	//			AddScore( 1000 );
	//		}
	//	}
	//}

	return false ;
}

//-------------------------------------------------------------------
// 関数名 : 外積の当たり判定
//
// 引数   : VECTOR3 pos0st		: 一方の線分の始点
// 引数   : VECTOR3 pos0ed		: 一方の線分の終点
// 引数   : VECTOR3 pos1st		: もう一方の線分の始点
// 引数   : VECTOR3 pos1ed		: もう一方の線分の終点
// 引数   : VECTOR3 *pPosCross	: out : 二点の交点
// 引数   : float *pRote			: out : 始点から交点までの長さの線分の長さ
// 引数   : VECTOR3 *pVecReflect: out : 反射ベクトル
// 返り値 : 真偽
//-------------------------------------------------------------------
bool CCollision::LinetoLineXZ( D3DXVECTOR3 pos0st , 
							   D3DXVECTOR3 pos0ed ,
							   D3DXVECTOR3 pos1st ,
							   D3DXVECTOR3 pos1ed ,
							   D3DXVECTOR3 *pPosCross ,
							   float *pfRote ,
							   D3DXVECTOR3 *pVecReflect )
{
	D3DXVECTOR3 vec0 , vec1 , vec2 ;

	vec0 = pos0ed - pos0st ;
	vec1 = pos1ed - pos1st ;
	vec2 = pos0st - pos1st ;

	//--  vec0 - vec1の線分の外積( vec0がvec1より右( マイナス )なら )  --//
	float fCrossProduct_0_1 = vec0.z * vec1.x - vec0.x * vec1.z ;

	if( fCrossProduct_0_1 == 0.0f )
	{
		return false ;
	}

	//--  vec1 - vec0の線分の外積( vec1がvec0より右( マイナス )なら )  --//
	float fCrossProduct_1_2 = vec1.z * vec1.x - vec1.x * vec2.z ;
	
	float fRate_1_2 = fCrossProduct_1_2 / fCrossProduct_0_1 ;

	//--  線分がクロス内にいるか  --//
	if( fRate_1_2 >= 0.0f && fRate_1_2 <= 1.0f )
	{
		//--  vec0 - vec1の線分の外積に対するvec2 - vec0の線分の外積の内分化を算出  --//
		//--  vec1がvec0の右側 : 1.0より上  --//
		//--  vec1がvec0の左側 : 0より下  --//

		if( pPosCross != NULL )
		{
			//--  交点  --//
			*pPosCross = pos0st + vec0 * fRate_1_2 ;
			//*pPosCross = pos1st + vec1 * fRate_0_2 ;

			if( pfRote != NULL )
			{
				//--  内積　線分同士の交差までの内分比  --//
				*pfRote = fRate_1_2 ;
			}

			//--  反射  --//
			if( pVecReflect != NULL )
			{
				D3DXVECTOR3 vecMove , vecLine ;

				vecMove = pos1ed - pos1st ;
				vecLine = pos0ed - pos0st ;

				//--  交差する線分同士の内積算出  --//
				float fDotProduct = vecLine.x * vecMove.x + vecLine.z * vecMove.z ;

				//--  交差する線分のなす角( a*b = |->a||->b|cosθ )  --//
				float fValueLine = sqrt( vecLine.x * vecLine.x + vecLine.z * vecLine.x );
				float fValueMove = sqrt( vecMove.x * vecMove.x + vecMove.z * vecMove.x );

				float fAngle = acosf( fDotProduct / ( fValueMove * fValueLine ) );

				//--  反射ベクトル  --//
				D3DXVECTOR3 vecMoveNew( cosf( fAngle ) * vecLine.z + sinf( fAngle ) * vecLine.x ,
										0.0f , 
										cosf( fAngle ) * vecLine.z + sinf( fAngle ) * vecLine.x );

				D3DXVec3Normalize( &vecMoveNew , &vecMoveNew );

				*pVecReflect = vecMoveNew ;
			}

			return true ;
		}
	}
	return false ;
}

//-------------------------------------------------------------------
// 関数名 : 
//
// 引数   : 
// 返り値 : 
//-------------------------------------------------------------------


// END
