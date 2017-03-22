
//=============================================================================
//
// メッシュ地面の処理 [MeshField.cpp]
// Author : 稲澤俊和
//=============================================================================
#include "MeshWall.h"
#include "Input.h"
#include "Renderer.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_SIZE_X		(10)			// テクスチャのサイズはポリゴン横
#define TEX_SIZE_Z		(10)			// テクスチャのサイズはポリゴン縦

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshWall::CMeshWall(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pDevice=NULL;
	m_pD3DTextureField=NULL;
	m_pD3DVtxBuffField=NULL;
	m_pD3DIndexBuffField=NULL;
	m_rot =D3DXVECTOR3(0,0,0);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshWall::~CMeshWall(void)
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshWall::Init(CRenderer *pRenderer)
{
	m_pDevice = pRenderer->GetDevice();	// デバイスへのポインタ

	//サイズと分割数の設定
	m_nNumBlockX = WALL_NUM_BLOCK_X;
	m_nNumBlockZ = WALL_NUM_BLOCK_Z;
	m_fSizeBlockX = WALL_SIZE_BLOCK_X;
	m_fSizeBlockZ = WALL_SIZE_BLOCK_Z;

	// 総頂点数
	m_nNumVertex = (m_nNumBlockX+1)*(m_nNumBlockZ+1);

	// 総ポリゴン数
	m_nNumPolygon = m_nNumBlockX*m_nNumBlockZ*2+(m_nNumBlockZ-1)*4;

	// 頂点の総インデックス数
	//				頂点数							  +	縮退ポリゴン発生数		+ ダブってる点
	// (nNumBlockX+1)*(nNumBlockZ+1) +  (nNumBlockZ-1)*4		+(nNumBlockX-1)*(nNumBlockZ-1)
	m_nNumVertexIndex = (m_nNumBlockX+1)*(m_nNumBlockZ+1)+(m_nNumBlockZ-1)*(3+m_nNumBlockX);

	// 頂点情報のセット
	if(FAILED(InitMeshFieldVerTex(m_nNumBlockX, m_nNumBlockZ, m_fSizeBlockX, m_fSizeBlockZ)))
	{
		MessageBox(NULL, "InitVerTex():頂点情報の初期化に失敗しました", "警告" ,MB_OK);
		return E_FAIL;
	}

	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshWall::Uninit(void)
{
	// テクスチャの開放
	if(m_pD3DTextureField != NULL)
	{
		m_pD3DTextureField -> Release();
		m_pD3DTextureField = NULL;
	}

	// 頂点バッファ解放
	if(m_pD3DVtxBuffField != NULL)
	{
		m_pD3DVtxBuffField -> Release();
		m_pD3DVtxBuffField = NULL;
	}

	// 頂点インデックスバッファ解放
	if(m_pD3DIndexBuffField != NULL)
	{
		m_pD3DIndexBuffField -> Release();
		m_pD3DIndexBuffField = NULL;
	}
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshWall::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshWall::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	

	//ワールドトランスフォーム
	D3DXMatrixIdentity(&m_mtxWorldField);
	D3DXMatrixScaling(&mtxScl,1.0f,1.0f,1.0f);					//スケールを反映
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxScl);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_Trans.x,m_Trans.y,m_Trans.z);
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxTranslate);
	//回転
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.x,m_rot.y,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxRot);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,-m_Trans.x,m_Trans.y,-m_Trans.z);
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxTranslate);
	// ワールド設定を適応する
	m_pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorldField);

	//データを渡す(バインド)
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuffField,0,sizeof(VERTEX_3D));
	// インデックスバッファをバインド
	m_pDevice->SetIndices(m_pD3DIndexBuffField); 

	//FVFの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pDevice->SetTexture(0,m_pD3DTextureField);

	// 後でこれに変える
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_nNumVertex,						//総頂点数
									0,
									m_nNumPolygon);						//描画するプリシテイブ数

}
	

//=============================================================================
// 頂点情報の初期化処理
//=============================================================================
HRESULT CMeshWall::InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{

	// 配列番号
	int nNum = 0;

	// 頂点情報計算用
	float fPosX,fPosY, fPosZ;
	double dTexU, dTexV;

	// i行t列
	int t = 0;
	int i = 0;

	// 頂点情報セット
	VERTEX_3D *pVtx;

	// インデックス情報のセット
	WORD *pIndex;

	// 頂点バッファメモリ確保！（解放も忘れずに）
	if(FAILED(m_pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffField,
											NULL)))
	{
		return E_FAIL;
	}
	
	// indexバッファメモリ確保！（解放も忘れずに）
	if(FAILED(m_pDevice -> CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuffField,
											NULL)))
	{
		return E_FAIL;
	}

	//ロック
	m_pD3DVtxBuffField -> Lock(0, 0, (void**)&pVtx, 0);

	// i行t列に頂点設定
	for(i = 0; i <= nNumBlockZ; i++)
	{
		dTexU = 0;
		dTexV = (double)i/TEX_SIZE_Z;
		for(t = 0; t <= nNumBlockX; t++)
		{
			nNum = i * (nNumBlockX+1) + t;
			fPosX = m_pos.x + (fSizeBlockX * t);
//			fPosX = (float)fSizeBlockX * (-nNumBlockX/2 + t);
			fPosY = m_pos.y - (fSizeBlockZ * i);
//			fPosZ = (float) fSizeBlockZ * (nNumBlockZ/2 - i);
			fPosZ=m_pos.z;
			dTexU = (double)-t/TEX_SIZE_X;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);		// 少し下にすることで、影などがきれいに出る
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// 合計が1.0fになるようにしないとダメ
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(200, 200, 200, 255);
			//pVtx[nNum].tex = D3DXVECTOR2((float)dTexU, (float)dTexV);
			pVtx[nNum].tex = D3DXVECTOR2(t*1.0f,i*1.0f);
		}
	}
	
	// アンロック
	m_pD3DVtxBuffField -> Unlock();

	// ロック
	m_pD3DIndexBuffField -> Lock(0, 0, (void**)&pIndex, 0);

	// i行t列
	i=0;
	t=0;

	for(int j = 0; j < m_nNumVertexIndex; ++j)
	{

		// 縮退ポリゴン
//		if(j == 2*(nNumBlockX+1)+t*(2*(nNumBlockX+1)+2))
		if(j == 2*(nNumBlockX+1)+t*(2*(nNumBlockX+1)+2))
		{
			pIndex[j] =  (i -1) + t*(nNumBlockX+1);
//			pIndex[j+1] = nNumBlockX+1 + i + t*(nNumBlockX+1);
			pIndex[j+1] = i + (t+1)*(nNumBlockX+1);

			// 段がかわる
			j += 2;
			t++;
			i = 0;
		}

		// 下
		if(j % 2 == 0)
		{
			pIndex[j] = i + (t+1)*(nNumBlockX+1);

		}
		// 上
		else
		{
			pIndex[j] = i + t*(nNumBlockX+1);
			++i;
		}
	}
	
	// アンロック
	m_pD3DIndexBuffField -> Unlock();

	// テクスチャ読み込み
	if(FAILED(D3DXCreateTextureFromFile(m_pDevice, "./data/TEXTURE/a.jpg", &m_pD3DTextureField)))
	{
		// 読み込み失敗
		MessageBox(NULL,
				"InitField:テクスチャの読み込みに失敗しました",
				"警告",
				MB_OK);

		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// 中心からＸ端までの距離を返す
//=============================================================================
float CMeshWall::GetFieldLengthX(void)
{
	return (float)m_nNumBlockX*m_fSizeBlockX/2;
}

//=============================================================================
// 中心からZ端までの距離を返す
//=============================================================================
float CMeshWall::GetFieldLengthZ(void)
{
	return (float)m_nNumBlockZ*m_fSizeBlockZ/2;
}



//=============================================================================
// オブジェクトの生成
//Pos  座標
//Rot  角度
//Translate  
//
//=============================================================================
CMeshWall* CMeshWall::Create(CRenderer *pRenderer,float PosX,float PosY,float PosZ,float RotX,float RotY,float RotZ,float TranslateX,float TranslateY,float TranslateZ)
{
	//インスタンスの生成
	CMeshWall *pScene = new CMeshWall(OBJTYPE_MESHWALL);
	//座標の設定
	pScene->SetPos(PosX,PosY,PosZ);
	pScene->SetTrans(TranslateX,TranslateY,TranslateZ);
	//角度の設定
	pScene->SetRot(RotX,RotY,RotZ);
	//初期化
	pScene->Init(pRenderer);

	return pScene;
}

