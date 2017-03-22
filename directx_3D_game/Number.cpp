
//=============================================================================
//
// ナンバー処理 [Number.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Number.h"
#include "Renderer.h"
#include "Scene.h"

//=============================================================================
// グローバル変数
//=============================================================================
//CRenderer* CNumber::m_pNumber=NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pDevice=NULL;
	m_pD3DNumberVtxBuff=NULL;
	m_pD3DNumber=NULL;
	m_pNumber=NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber(void)
{
	
}
//=============================================================================
// スコアの初期化
//=============================================================================
HRESULT CNumber::Init(CRenderer *pRenderer)
{
	int i;
	m_pDevice = pRenderer->GetDevice();			// デバイスへのポインタ

	m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//頂点バッファ確保
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pD3DNumberVtxBuff,NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	//ロック
	m_pD3DNumberVtxBuff -> Lock(0,0,(void**)&pVtx,0);

	//座標
	pVtx[0].vtx = D3DXVECTOR3(m_Pos.x,m_Pos.y,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(m_Pos.x+20,m_Pos.y,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(m_Pos.x,m_Pos.y+50,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(m_Pos.x+20,m_Pos.y+50,0.0f);
	for(i=0;i<4;i++)
	{
		pVtx[i].rhw=1.0f;
		//透明度
		pVtx[i].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	}
	//テクスチャ座標
	pVtx[0].tex=D3DXVECTOR2(0,0);
	pVtx[1].tex=D3DXVECTOR2(0.1f,0);
	pVtx[2].tex=D3DXVECTOR2(0,1);
	pVtx[3].tex=D3DXVECTOR2(0.1f,1);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/number000.png",&m_pD3DNumber);
	//アンロック
	m_pD3DNumberVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// スコアの終了処理
//=============================================================================
void CNumber::Uninit(void)
{	
	if(m_pD3DNumber != NULL)
	{
		m_pD3DNumber ->Release();
		m_pD3DNumber = NULL;
	}
	if(m_pD3DNumberVtxBuff !=NULL)
	{
		m_pD3DNumberVtxBuff ->Release();
		m_pD3DNumberVtxBuff = NULL;
	}

}
//=============================================================================
// スコアの更新処理
//=============================================================================
void CNumber::UpdateNumber(int nNumber)
{
	VERTEX_2D *pVtx;
	m_pD3DNumberVtxBuff -> Lock(0,0,(void**)&pVtx,0);

	pVtx[0].tex=D3DXVECTOR2(0+(nNumber*0.1f),0);
	pVtx[1].tex=D3DXVECTOR2(0.1f+(nNumber*0.1f),0);
	pVtx[2].tex=D3DXVECTOR2(0+(nNumber*0.1f),1);
	pVtx[3].tex=D3DXVECTOR2(0.1f+(nNumber*0.1f),1);
	
	m_pD3DNumberVtxBuff->Unlock();
}
void CNumber::Update(void)
{

}

//=============================================================================
// スコアの描画処理
//=============================================================================
void CNumber::Draw(void)
{
	m_pDevice->SetStreamSource(0,m_pD3DNumberVtxBuff,0,sizeof(VERTEX_2D));
	m_pDevice->SetTexture(0,m_pD3DNumber);
	m_pDevice->SetFVF(FVF_VERTEX_2D);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
