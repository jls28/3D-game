//=============================================================================
//
// ドーム表示処理 [Dome.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Renderer.h"
#include "Dome.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================


//=============================================================================
// コンストラクタ
//=============================================================================
CDome::CDome(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CDome::~CDome()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CDome::Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumWeight,int NumHigh)
{
	VERTEX_3D *pVtx;
	WORD *pIndex;		//インデックス用
	int Cnt=0;			//カウンタ
	m_pD3DDevice = pRenderer->GetDevice();	// デバイスへのポインタ

	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0,0,0);
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fSizeWeight=(float)SizeX;
	m_fSizeHigh=(float)SizeY;
	
	m_nNumWeight=NumWeight;
	m_nNumHigh=NumHigh;

	// 総頂点数
	m_nNumVertex = (m_nNumWeight+1)*(m_nNumHigh+1);
	// 総ポリゴン数
	m_nNum = m_nNumWeight*m_nNumHigh*2+(m_nNumHigh-1)*4;
	// 頂点の総インデックス数
	m_nNumIndex = (m_nNumWeight+1)*(m_nNumHigh+1)+(m_nNumHigh-1)*(3+m_nNumWeight);

	//頂点バッファの作成
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DVtx,NULL)))
	{
		return E_FAIL;
	}
	//ロック
	m_pD3DVtx->Lock(0,0,(void**)&pVtx,0);
	//頂点座標の設定
	for(int i=0;i<=m_nNumHigh;i++)
	{
		for(int j=0;j<=m_nNumWeight;j++)
		{
			m_Length=cosf(2.0f*D3DX_PI*i/4/m_nNumHigh)*SizeX;
			//頂点情報
			pVtx[i*(m_nNumHigh+1)+j].vtx=D3DXVECTOR3(cosf(2.0f*D3DX_PI*j/m_nNumWeight)*m_Length,
													sinf(2.0f*D3DX_PI*i/4/m_nNumHigh)*SizeX,
													sinf(2.0f*D3DX_PI*j/m_nNumWeight)*m_Length);

			//法線ベクトル
			pVtx[i*(m_nNumHigh+1)+j].nor=D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[i*(m_nNumHigh+1)+j].diffuse=D3DCOLOR_RGBA(0xff,0xff,0xff,255);
			//テクスチャ情報の設定
			float a=(float)j/(float)NumHigh;
			pVtx[i*(m_nNumHigh+1)+j].tex=D3DXVECTOR2((float)i/(float)m_nNumWeight,(float)j/(float)m_nNumHigh);
		}
	}
	//テクスチャの設定
	D3DXCreateTextureFromFile(m_pD3DDevice,"data/TEXTURE/sora2.jpg",&m_pD3DTex);
	//アンロック
	m_pD3DVtx->Unlock();

	
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

	//インデックスバッファの設定
	m_pD3DIndex->Lock(0,0,(void**)&pIndex,0);
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

	//アンロック
	m_pD3DIndex->Unlock();
	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void CDome::Uninit(void)
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
void CDome::Update(void)
{

	m_Rot.y+=0.001f;

	this->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);

}

//=============================================================================
// 描画処理
//=============================================================================
void CDome::Draw(void)
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
// オブジェクトの生成
//=============================================================================
CDome* CDome::Create(float SizeX,float SizeZ,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer)
{
	CDome *pDome;

	pDome=new CDome(OBJTYPE_DOME);
	//初期化関数呼び出し
	pDome->Init(pRenderer,(int)SizeX,(int)SizeZ,NumX,NumZ);
	//座標の設定
	pDome->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	//座標設定
	pDome->SetPos(fPosX,fPosY,fPosZ);
	return pDome;
}