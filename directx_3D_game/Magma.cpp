//=============================================================================
//
// フィールド処理 [MeshField.cpp]
// Author : 稲澤俊和
//
//============================================================================
#include "Magma.h"
#include "Input.h"
#include "Manager.h"
#include "main.h"
#include "Renderer.h"

#define NUM_VTX_INDEX	(14)
#define TEX_SIZE_X		(90)			// テクスチャのサイズはポリゴン横
#define TEX_SIZE_Z		(90)			// テクスチャのサイズはポリゴン縦
#define NUM_BLOCK_X		(50)			//フィールドの横の数
#define NUM_BLOCK_Z		(50)			//フィールドの縦の数


static D3DXVECTOR3 NORMAL_MAP[100*100];



//=============================================================================
// コンストラクタ
//=============================================================================
CMagma::CMagma(OBJTYPE nObjType,int nPriority):CScene3D(nObjType,nPriority)
{
	n_pVtx=NULL;
	n_pD3DDevice=NULL;
	n_pD3DVtexBuff=NULL;
	n_pD3DIndexBuff=NULL;
	n_pD3DTex=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rotate=0.00004f;

}

//=============================================================================
// デストラクタ
//=============================================================================
CMagma::~CMagma()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMagma::Init(LPDIRECT3DDEVICE9 device)
{
	m_Rot = D3DXVECTOR3(0,0,0);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	float n=0;
	m_fWaterTime = 0.f;
	m_Color = 255;
	m_ColorAdd = 1;

	for(int i=0;i<50*50;i++)
	{
		n=(float)(rand()%50);
		n /= 3;
	}

	//角度正規か
	if(CMagma::m_Rot.y < -D3DX_PI)
	{
		CMagma::m_Rot.y = D3DX_PI;
	}
	else if(CMagma::m_Rot.y > D3DX_PI)
	{
		CMagma::m_Rot.y = -D3DX_PI;
	}

	n_nNumVertexIndex = NUM_VTX_INDEX;
	n_pD3DDevice = device;

	//m_nNumBlockX * m_nNumBlockZのメッシュ作成
	m_nNumBlockX = NUM_BLOCK_X;
	m_nNumBlockZ = NUM_BLOCK_Z;
	//ポリゴン一枚のサイズ
	m_fSizeBlockX = TEX_SIZE_X;
	m_fSizeBlockZ = TEX_SIZE_Z;

	// 総頂点数
	m_nNumVertex = (m_nNumBlockX+1)*(m_nNumBlockZ+1);
	// 総ポリゴン数
	m_nNumPolygon = m_nNumBlockX*m_nNumBlockZ*2+(m_nNumBlockZ-1)*4;

	// 頂点の総インデックス数
	m_nNumVertexIndex = (m_nNumBlockX+1)*(m_nNumBlockZ+1)+(m_nNumBlockZ-1)*(3+m_nNumBlockX);

	// 頂点情報のセット
	if(FAILED(InitMeshFieldVerTex(m_nNumBlockX, m_nNumBlockZ, m_fSizeBlockX, m_fSizeBlockZ)))
	{
		MessageBox(NULL, "InitVerTex():頂点情報の初期化に失敗しました", "警告" ,MB_OK);
		return E_FAIL;
	}

	//ポリゴンの設定
	D3DXCreateTextureFromFile(device,"data/TEXTURE/magmas2.jpg",&n_pD3DTex);

	return S_OK;
}

//=============================================================================
// 頂点情報の初期化処理
//=============================================================================
HRESULT CMagma::InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	// 配列番号
	int nNum = 0;
	int nNum2 = 0;
	// 頂点情報計算用
	float fPosX, fPosZ;
	double dTexU, dTexV;
	// i行t列
	int t = 0;
	int i = 0;

	// インデックス情報のセット
	WORD *pIndex;

	D3DXVECTOR3 line1;
	D3DXVECTOR3 line2;
	D3DXVECTOR3 Vec1;
	D3DXVECTOR3 Vec2;


	// 頂点バッファメモリ確保！（解放も忘れずに）
	if(FAILED(n_pD3DDevice -> CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&n_pD3DVtexBuff,
											NULL)))
	{
		return E_FAIL;
	}

	// indexバッファメモリ確保！（解放も忘れずに）
	if(FAILED(n_pD3DDevice -> CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&n_pD3DIndexBuff,
											NULL)))
	{
		return E_FAIL;
	}

	//ロック
	n_pD3DVtexBuff -> Lock(0, 0, (void**)&pVtx, 0);

	// i行t列に頂点設定
	for(i = 0; i <= nNumBlockZ; i++)
	{
		dTexU = 0;
		dTexV = (double)i/TEX_SIZE_Z;
		for(t = 0; t <= nNumBlockX; t++)
		{
			nNum = i * (nNumBlockX+1) + t;

			fPosX = m_Pos.x + (fSizeBlockX * t);
			fPosZ = m_Pos.z + (-fSizeBlockZ * i);
			//fPosX = m_fSizeBlockX * (m_nNumBlockX/2) - (fSizeBlockX * t);
			//fPosZ = m_fSizeBlockZ * (m_nNumBlockZ/2) - (fSizeBlockZ * i);
			dTexU = (double)-t/TEX_SIZE_X;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, 0.f, fPosZ);		// 少し下にすることで、影などがきれいに出る
			//pVtx[nNum].vtx = D3DXVECTOR3(fPosX,0.0, fPosZ);					// 少し下にすることで、影などがきれいに出る
			//pVtx[nNum].nor = D3DXVECTOR3(0,1,0);
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(m_Color, m_Color, m_Color, 255);
			pVtx[nNum].tex = D3DXVECTOR2(t*1.0f,i*1.0f);
		}
	}
	//	// ベクトルを作ってNorMapに格納
	//for(i = 0; i <= nNumBlockZ; i++)
	//{
	//	for(t = 0; t <= nNumBlockX; t++)
	//	{
	//		if(t == nNumBlockX)
	//		{
	//			continue;
	//		}
	//		nNum = i * (nNumBlockX) + t;
	//		nNum2 = i * (nNumBlockX + 1) + t;
	//		line1 = pVtx[nNum2 + 1].vtx - pVtx[nNum2].vtx; 
	//		line2 = pVtx[nNum2 + nNumBlockZ + 1].vtx - pVtx[nNum2].vtx; 

	//		D3DXVec3Cross(&Vec1,&line1,&line2);

	//		line1 = pVtx[nNum2 + nNumBlockZ + 1].vtx - pVtx[nNum2 + nNumBlockZ + 2].vtx; 
	//		line2 = pVtx[nNum2 + 1].vtx - pVtx[nNum2 + nNumBlockZ + 2].vtx; 

	//		D3DXVec3Cross(&Vec2,&line1,&line2);

	//		Vec1 = (Vec1 + Vec2) / 2;

	//		D3DXVec3Normalize(&Vec1,&Vec1);

	//		NORMAL_MAP[nNum] = Vec1;
	//	}
	//}


	// 法線ベクトル算出
	for(i = 0; i <= nNumBlockZ; i++)
	{
		for(t = 0; t <= nNumBlockX; t++)
		{
			nNum = i * (nNumBlockX) + t;
			nNum2 = i * (nNumBlockX+1) + t;

			//左上
			if( i == 0 && t == 0)
			{
				Vec1 = NORMAL_MAP[nNum];
			}else
			//左下
			if( i == nNumBlockZ && t == 0)
			{
				Vec1 = NORMAL_MAP[nNum - nNumBlockX + nNumBlockZ];
			}else
			//右上
			if( i == 0 && t == nNumBlockX)
			{
				Vec1 = NORMAL_MAP[nNum - 1];
			}else
			//右下
			if( i == nNumBlockZ && t == nNumBlockX)
			{
				Vec1 = NORMAL_MAP[nNum2 - i - 1];
			}else
			//左端
			if( i < nNumBlockZ && i > 0 && t == 0)
			{
				Vec1 = (NORMAL_MAP[nNum - i] + NORMAL_MAP[nNum - nNumBlockX - i]) / 2;
			}else
			//右端
			if( i < nNumBlockZ && i > 0 && t == nNumBlockX)
			{
				Vec1 = (NORMAL_MAP[nNum - i - 1] + NORMAL_MAP[nNum - nNumBlockX - i - 1]) / 2;
			}else
			//上端
			if( i == 0 && t < nNumBlockX && t > 0)
			{
				Vec1 = (NORMAL_MAP[0] + NORMAL_MAP[1]) / 2;
			}else
			//下端
			if( i == nNumBlockZ && t < nNumBlockX && t > 0)
			{
				Vec1 = (NORMAL_MAP[0] + NORMAL_MAP[1]) / 2;
			}else
			//真ん中
			if( i < nNumBlockZ && i > 0 && t < nNumBlockX && t > 0)
			{
				Vec1 = NORMAL_MAP[nNum -  i] + NORMAL_MAP[nNum - i - 1] + NORMAL_MAP[nNum - i - nNumBlockX] + NORMAL_MAP[nNum - i - nNumBlockX - 1] / 4;
			}

			D3DXVec3Normalize(&Vec1,&Vec1);
			pVtx[nNum].nor = Vec1;
		}
	}
	// アンロック
	n_pD3DVtexBuff -> Unlock();

	// ロック
	n_pD3DIndexBuff -> Lock(0, 0, (void**)&pIndex, 0);

	// i行t列
	i=0;
	t=0;

	for(int j = 0; j < m_nNumVertexIndex; ++j)
	{
		// 縮退ポリゴン
		if(j == 2*(nNumBlockX+1)+t*(2*(nNumBlockX+1)+2))
		{
			pIndex[j] =  (i -1) + t*(nNumBlockX+1);
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
	n_pD3DIndexBuff -> Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMagma::Uninit()
{
	// テクスチャの開放
	if(n_pD3DTex != NULL)
	{
		n_pD3DTex -> Release();
		n_pD3DTex = NULL;
	}

	// 頂点バッファ解放
	if(n_pD3DVtexBuff != NULL)
	{
		n_pD3DVtexBuff -> Release();
		n_pD3DVtexBuff = NULL;
	}

	// 頂点インデックスバッファ解放
	if(n_pD3DIndexBuff != NULL)
	{
		n_pD3DIndexBuff -> Release();
		n_pD3DIndexBuff = NULL;
	}

	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMagma::Update()
{
	// 経過時間速度
	const float dt = 0.01f;

	// 振幅
	const float amplitube = 4.f;

	// 色変更
	if (m_Color > 254 || m_Color < 140)
	{
		m_ColorAdd *= -1;
	}

	// 色加算
	m_Color+=m_ColorAdd;

	//ロック
	n_pD3DVtexBuff->Lock(0, 0, (void**)&pVtx, 0);

	// i行t列に頂点設定
	for (int i = 0; i <= m_nNumBlockZ; i++)
	{
		for (int t = 0; t <= m_nNumBlockX; t++)
		{
			// 
			int nNum = i * (m_nNumBlockX + 1) + t;

			// 中心のインデックス
			int centerIndex = (m_nNumBlockZ / 2) * (m_nNumBlockX + 1) + (m_nNumBlockX / 2);

			// 波紋発生点からの距離
			float length = sqrtf(
				(pVtx[nNum].vtx.x - pVtx[centerIndex].vtx.x) * (pVtx[nNum].vtx.x - pVtx[centerIndex].vtx.x) + 
				(pVtx[nNum].vtx.z - pVtx[centerIndex].vtx.z) * (pVtx[nNum].vtx.z - pVtx[centerIndex].vtx.z)	);

			// 波の高さ
			float fPosY = sinf(-m_fWaterTime * 3.f + length * 0.02f) *
				amplitube * (1000 - length) * 0.0015f ;

			pVtx[nNum].vtx.y = fPosY;		// 少し下にすることで、影などがきれいに出る

			// 色を上下させることでマグマ感を演出
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(m_Color, m_Color, m_Color, 255);
		}
	}

	// アンロック
	n_pD3DVtexBuff->Unlock();

	// 経過時間
	m_fWaterTime += dt;

	m_Rot.y+=m_Rotate;


	if(m_Rot.y > 0.38f)
	{
		m_Rotate=-m_Rotate;
	}
	if(m_Rot.y < 0)
	{
		m_Rotate=-m_Rotate;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void CMagma::Draw()
{
	D3DXMATRIX mtxWorld,mtxScl,mtxRot,mtxTranslate;

	// ライト無効
	n_pD3DDevice->SetRenderState(D3DRS_LIGHTING , FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);
	//スケールを反映
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxScl);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTranslate,-1000,m_Pos.y,1000);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);

	//ワールドマトリックスの設定
	n_pD3DDevice->SetTransform(D3DTS_WORLD,&mtxWorld);
	n_pD3DDevice->SetIndices(n_pD3DIndexBuff);

	//頂点フォーマットの設定
	n_pD3DDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	n_pD3DDevice->SetTexture(0,n_pD3DTex);
	n_pD3DDevice->SetStreamSource(0,n_pD3DVtexBuff,0,sizeof(VERTEX_3D));

	//ポリゴン
	n_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);

	// ライト戻す
	n_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// オブジェクト生成
//=============================================================================
CMagma* CMagma::Create(LPDIRECT3DDEVICE9 device,float fPosX,float fPosY,float fPosZ)
{
	CMagma* pMagma;
	pMagma = new CMagma(OBJTYPE_MESHMAGMA);
	
	pMagma ->m_Pos=D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pMagma->SetPos(fPosX,fPosY,fPosZ);
	pMagma ->Init(device);
	return pMagma;
}


float CMagma::GetHeight(D3DXVECTOR3 Pos,D3DXVECTOR3* pNormal)
{
	D3DXVECTOR3 Vec0,Vec1;
	int nNum=0;
	// 法線ベクトルつっこむ
	for(int i = 0; i <= m_nNumBlockZ; i++)
	{
		for(int t = 0; t <= m_nNumBlockX; t++)
		{
			nNum = i * (m_nNumBlockX) + t;
			Vec0=pVtx[nNum].vtx-pVtx[nNum+m_nNumBlockX+1].vtx;
			Vec1=Pos-pVtx[nNum+m_nNumBlockX+1].vtx;

			//2Dの外積
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >=0)
			{
				Vec0=pVtx[nNum+m_nNumBlockX+2].vtx-pVtx[nNum].vtx;
				Vec1=Pos-pVtx[nNum].vtx;

				if(Vec0.z*Vec1.x-Vec0.x*Vec1.z >=0)
				{
					Vec0=pVtx[nNum+m_nNumBlockX+1].vtx-pVtx[nNum+m_nNumBlockX+2].vtx;
					Vec1=Pos-pVtx[nNum+m_nNumBlockX+2].vtx;

					if(Vec0.z*Vec1.x-Vec0.x*Vec1.z >=0)
					{
						//乗っている
						return GetHeightPolygon(pVtx[nNum+m_nNumBlockX+1].vtx,
										pVtx[nNum+m_nNumBlockX+2].vtx,
										pVtx[nNum].vtx,
										Pos,
										pNormal);
					}
				}
			}


			Vec0=pVtx[nNum+1].vtx-pVtx[nNum].vtx;
			Vec1=Pos-pVtx[nNum].vtx;

			//2Dの外積
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >=0)
			{
				Vec0=pVtx[nNum+m_nNumBlockX+2].vtx-pVtx[nNum+1].vtx;
				Vec1=Pos-pVtx[nNum+1].vtx;

				if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >=0)
				{
					Vec0=pVtx[nNum].vtx-pVtx[nNum+m_nNumBlockX+2].vtx;
					Vec1=Pos-pVtx[nNum+m_nNumBlockX+2].vtx;

					if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >=0)
					{
						//乗っている
						return GetHeightPolygon(pVtx[nNum+1].vtx,
										pVtx[nNum+m_nNumBlockX].vtx,
										pVtx[nNum+m_nNumBlockX+2].vtx,
										Pos,
										pNormal);
					}
				}
			}
		}
	}
	return 0.0f;
}


float CMagma::GetHeightPolygon(const D3DXVECTOR3& P0,const D3DXVECTOR3& P1,const D3DXVECTOR3& P2,const D3DXVECTOR3& Pos,D3DXVECTOR3* pNormal)
{
	D3DXVECTOR3 Normal,Vec0,Vec1;
	float Height;

	Vec0=P1-P0;
	Vec1=P2-P0;
	D3DXVec3Cross(&Normal,&Vec0,&Vec1);
	D3DXVec3Normalize(&Normal,&Normal);
	pNormal=&Normal;

	if(Normal.y==0.0)
	{
		return 0.0f;
	}

	//内積
	Height=P0.y-(Normal.x*(Pos.x-P0.x)+Normal.z*(Pos.z-P0.z))/Normal.y;

	return Height;
}