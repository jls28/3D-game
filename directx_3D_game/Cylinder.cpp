//=============================================================================
//
// シリンダー表示処理 [Cylinder.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Renderer.h"
#include "Cylinder.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
float CCylinder::m_Lengthin[1];
int CCylinder::m_nCylinderNum=0;


//=============================================================================
// コンストラクタ
//=============================================================================
CCylinder::CCylinder(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pD3DDevice=NULL;
	m_pD3DTex=NULL;
	m_pD3DVtx=NULL;
	m_pD3DIndex=NULL;
	m_nNumVertex=0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCylinder::~CCylinder()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCylinder::Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumWeight,int NumHigh)
{
	VERTEX_3D *pVtx;
	WORD *pIndex;		//インデックス用
	int Cnt=0;

	m_pD3DDevice = pRenderer->GetDevice();	// デバイスへのポインタ


	m_Rot=D3DXVECTOR3(0,0,0);
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fSizeWeight=(float)SizeX;
	m_fSizeHigh=(float)SizeY;
	m_nNumWeight=(int)NumWeight;
	m_nNumHigh=(int)NumHigh;

	// 総頂点数
	m_nNumVertex = (m_nNumWeight+1)*(m_nNumHigh+1);
	// 総ポリゴン数
	m_nNum = m_nNumWeight*m_nNumHigh*2+(m_nNumHigh-1)*4;
	// 頂点の総インデックス数
	m_nNumIndex = (m_nNumWeight+1)*(m_nNumHigh+1)+(m_nNumHigh-1)*(3+m_nNumWeight);

	m_Length=D3DXVECTOR2(m_fSizeWeight,m_fSizeHigh);

	//頂点バッファの作成
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&m_pD3DVtx,
												NULL)))
	{
		return E_FAIL;
	}

	m_pD3DVtx->Lock(0,0,(void**)&pVtx,0);

	//頂点座標の設定
	for(int i=0;i<=m_nNumHigh;i++)
	{
		for(int j=0;j<=m_nNumWeight;j++)
		{
			float Rot=2.0f*D3DX_PI*j/m_nNumWeight;
			pVtx[i*(m_nNumHigh+1)+j].vtx=D3DXVECTOR3(-cosf(Rot)*m_Length.x,m_Length.y*i,sinf(Rot)*m_Length.x);
			pVtx[i*(m_nNumHigh+1)+j].nor=D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[i*(m_nNumHigh+1)+j].diffuse=D3DCOLOR_RGBA(0xff,0xff,0xff,0xff);
			pVtx[i*(m_nNumHigh+1)+j].tex=D3DXVECTOR2((float)i/(float)m_nNumWeight,(float)j/(float)m_nNumHigh);
		}
	}
	m_pD3DVtx->Unlock();

	//画像ファイルの読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,"data/TEXTURE/wall003.jpg",&m_pD3DTex);

	//インデックス生成
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(sizeof(DWORD)*m_nNumIndex,
												D3DUSAGE_WRITEONLY,
												D3DFMT_INDEX16,
												D3DPOOL_MANAGED,
												&m_pD3DIndex,
												NULL)))
	{
		return E_FAIL;
	}

	m_pD3DIndex->Lock(0,0,(void**)&pIndex,0);
	// i行t列
	int t = 0;
	int i = 0;
	for(int j = 0; j < m_nNumIndex; ++j)
	{
		// 縮退ポリゴン
		if(j == 2*(m_nNumWeight+1)+t*(2*(m_nNumWeight+1)+2))
		{
			pIndex[j] =  (i -1) + t*(m_nNumWeight+1);
			pIndex[j+1] = i + (t+1)*(m_nNumWeight+1);
			// 段がかわる
			j += 2;
			t++;
			i = 0;
		}
		// 下
		if(j % 2 == 0)
		{
			pIndex[j] = i + (t+1)*(m_nNumWeight+1);
		}
		// 上
		else
		{
			pIndex[j] = i + t*(m_nNumWeight+1);
			++i;
		}
	}
	m_pD3DIndex->Unlock();
	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void CCylinder::Uninit(void)
{
	if(m_pD3DVtx!=NULL)
	{
		m_pD3DVtx->Release();
		m_pD3DVtx=NULL;
	}
	if(m_pD3DIndex!=NULL)
	{
		m_pD3DIndex->Release();
		m_pD3DIndex=NULL;
	}
	if(m_pD3DTex!=NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCylinder::Update(void)
{
	m_Rot.y+=0.002f;

}

//=============================================================================
// 描画処理
//=============================================================================
void CCylinder::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate,mtxWorld;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);
	//スケールを反映
	D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	//回転の反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//ワールドマトリックスの設定
	m_pD3DDevice -> SetTransform(D3DTS_WORLD, &mtxWorld);
	//頂点バッファをバインド
	m_pD3DDevice -> SetStreamSource(0, m_pD3DVtx, 0, sizeof(VERTEX_3D));
	//テクスチャの設定
	m_pD3DDevice -> SetTexture(0, m_pD3DTex);
	//インデックス情報をバインド
	m_pD3DDevice->SetIndices(m_pD3DIndex);
	//頂点フォーマットの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);
	//ポリゴンの設定
	m_pD3DDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNum);
}

//=============================================================================
//オブジェクト生成
//float SizeX	横サイズ
//float SizeY	縦サイズ
//int NumX		横の分割数
//int NumZ		縦の分割数
//float fPosX	X座標
//float fPosY	Y座標
//flaot fPosZ	Z座標
//=============================================================================
CCylinder* CCylinder::Create(float SizeX,float SizeY,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer)
{
	CCylinder *pCylinder;
	//インスタンスの生成
	pCylinder=new CCylinder(OBJTYPE_CYLINDER);
	//初期化
	pCylinder->Init(pRenderer,(int)SizeX,(int)SizeY,NumX,NumZ);
	pCylinder->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);

	pCylinder->SetPos(fPosX,fPosY,fPosZ);

	return pCylinder;
}