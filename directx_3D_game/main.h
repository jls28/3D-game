//=============================================================================
//
// メイン処理 [main.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include "xaudio2.h"

#define DIRECTINPUT_VERSION (0x0800)		// 警告対策用
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ON			(1)
#define OFF			(0)

// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(800)				// ウインドウの幅
#define SCREEN_HEIGHT	(600)				// ウインドウの高さ

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;

//	ポリゴンのカリング
typedef enum
{
	CULL_CW = 0, CULL_CCW, CULL_MAX
}CULLING;

typedef struct
{
	float x;
	float y;
}Vector2;

//カラー構造体
struct COLOR
{
	int R;		//Red
	int G;		//Green
	int B;		//Blue
	int A;		//Alpha
};

//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
//#define new _NEW
//#define DBG_NEW new
//#endif
//#endif		//_DEBUG

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif


/*
今後やること

さそりのモデルに動きを入れる
　足をわちゃわちゃさせる
　腕を動かす
　尻尾を動かす


ステージをもっと簡単にする


マグマをもっとマグマっぽく


影モデルとギミックの描画順を入れ替えると影がギミックの上にでるかも



操作方法を入れるとなぜか２週目のCMeshFieldのInitMeshFieldVerTexの中の
ベクトルを作ってNorMapに格納しているところで止まる

*/