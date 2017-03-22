//=============================================================================
//
// メイン処理 [SceneBillboard.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include"SceneBillboard.h"
#include"Renderer.h"
#include "Camera.h"


//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneBillboard::CSceneBillboard(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pD3DTex=NULL;
	m_pD3DBuff=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fLength=0.0f;
	m_fAngle=0.0f;
	SpeedX=0.0f;	
	SpeedZ=0.0f;	
	m_pBillboard=NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CSceneBillboard::~CSceneBillboard()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneBillboard::Init(CRenderer* m_pRenderer)
{
	pDevice = m_pRenderer->GetDevice();
	pRenderer = m_pRenderer;

	//プレイヤーの座標を取る
	m_Pos = D3DXVECTOR3(0.0f,10.0f,0.0f);
	m_Rot = D3DXVECTOR3(0,0,0);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//頂点情報の設定
	//頂点バッフア生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DBuff,NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;
	//ロック
	m_pD3DBuff -> Lock(0,0,(void**)&pVtx,0);
	//座標
	pVtx[0].vtx = D3DXVECTOR3(-5.0f,5.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(5.0f,5.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-5.0f,-5.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(5.0f,-5.0f,0.0f);
	//法線
	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	for(int j=0;j<4;j++)
	{
		//色
		pVtx[j].diffuse = D3DCOLOR_RGBA(255,50,0,255);
	}
	//テクスチャ座標
	pVtx[0].tex=D3DXVECTOR2(0,0);
	pVtx[1].tex=D3DXVECTOR2(1,0);
	pVtx[2].tex=D3DXVECTOR2(0,1);
	pVtx[3].tex=D3DXVECTOR2(1,1);
	//アンロック
	m_pD3DBuff->Unlock();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,"data/TEXTURE/bullet000.png",&m_pD3DTex);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CSceneBillboard::Uninit(void)
{	
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex ->Release();
		m_pD3DTex = NULL;
	}
	
	if(m_pD3DBuff != NULL)
	{
		m_pD3DBuff ->Release();
		m_pD3DBuff = NULL;
	}
	CScene::Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneBillboard::Update(void)
{
	/*for(int i=0;i<BULLET_MAX;i++)
	{
		if(BulletFlag == true)
		{
			g_posBullet[i].x  += sinf(g_rotBullet[i].x)*SpeedX[i];
			g_posBullet[i].z  += cosf(g_rotBullet[i].x)*SpeedZ[i];
			g_posBulletL[i].x += sinf(g_rotBullet[i].x)*SpeedX[i];
			g_posBulletL[i].z += cosf(g_rotBullet[i].x)*SpeedZ[i];
			g_posBulletR[i].x += sinf(g_rotBullet[i].x)*SpeedX[i];
			g_posBulletR[i].z += cosf(g_rotBullet[i].x)*SpeedZ[i];
		}
		g_posBullet[i] = D3DXVECTOR3(g_posBullet[i].x,g_posBullet[i].y,g_posBullet[i].z);			
	}*/
}
//=============================================================================
// 描画処理
//=============================================================================
void CSceneBillboard::Draw(void)
{
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	mtxView = CCamera::GetMtxView();
	//アルフャテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);


	//ワールドマトリックス
	D3DXMatrixIdentity(&m_mtxWorldBullet);													//ワールドマトリックスの初期化
	D3DXMatrixInverse(&m_mtxWorldBullet,NULL,&mtxView);
	m_mtxWorldBullet._41 = 0.0f;
	m_mtxWorldBullet._42 = 0.0f;
	m_mtxWorldBullet._43 = 0.0f;

	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);				//スケールを反映
	D3DXMatrixMultiply(&m_mtxWorldBullet,&m_mtxWorldBullet,&mtxScl);		
	D3DXMatrixRotationYawPitchRoll(&mtxRot,0.0f,m_Rot.y,m_Rot.z);	//回転を反映
	D3DXMatrixMultiply(&m_mtxWorldBullet,&m_mtxWorldBullet,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);	//位置を反映
	D3DXMatrixMultiply(&m_mtxWorldBullet,&m_mtxWorldBullet,&mtxTranslate);
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorldBullet);									//ワールドマトリックスの設定
	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	//描画
	
	pDevice->SetStreamSource(0,m_pD3DBuff,0,sizeof(VERTEX_3D));
	pDevice->SetTexture(0,m_pD3DTex);
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);			
	//	
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	//アルフャテストＯＦＦ
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}
