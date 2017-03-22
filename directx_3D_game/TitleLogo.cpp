//=============================================================================
//
// メイン処理 [Scene2D.cpp]
// Author :稲澤俊和
//
//=============================================================================
#include"TitleLogo.h"
#include"Renderer.h"
#include "Input.h"

//=============================================================================
// グローバル変数
//=============================================================================
D3DXVECTOR3 TitleSpeed=D3DXVECTOR3(0.0f,0.0f,0.0f);
int Count=0;
float Speed=0.7f;
float work=3;
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleLogo::CTitleLogo(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pD3DTex=NULL;
	m_pDevice=NULL;
	m_pD3DBuff=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fLength=0.0f;
	m_fAngle=0.0f;	
	m_aAlpha=255;
	Count=0;
	Speed=0.7f;
	work=3;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitleLogo::~CTitleLogo()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitleLogo::Init(CRenderer* m_pRenderer)
{
	//デバイスの取得
	m_pDevice = m_pRenderer->GetDevice();
	//関数の初期設定
	/*m_rot.z = 0;
	m_pos.x = 0;
	m_pos.y = 0;*/


	//頂点バッファの設定
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pD3DBuff,NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *aVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&aVtx,0);
	//頂点の設定
	aVtx[0].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[1].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[2].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);
	aVtx[3].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);

	aVtx[0].rhw=1.0f;
	aVtx[1].rhw=1.0f;
	aVtx[2].rhw=1.0f;
	aVtx[3].rhw=1.0f;

	//色
	aVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	aVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	aVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	aVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);

	//テクスチャ座標
	aVtx[0].tex=D3DXVECTOR2(0,0);
	aVtx[1].tex=D3DXVECTOR2(1,0);
	aVtx[2].tex=D3DXVECTOR2(0,1);
	aVtx[3].tex=D3DXVECTOR2(1,1);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/TitleLogo.png",&m_pD3DTex);
	//ロック
	m_pD3DBuff->Unlock();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTitleLogo::Uninit(void)
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
void CTitleLogo::Update(void)
{
	Count++;
	//頂点の更新
	VERTEX_2D *aVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&aVtx,0);
	aVtx[0].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[1].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[2].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);
	aVtx[3].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);
		//色
	aVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	aVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	aVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	aVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	m_pD3DBuff->Unlock();

	m_Pos.y+=Speed;
	if(m_Pos.y >= 200)
	{
		Speed=0;
		m_aAlpha+=work;
		if(m_aAlpha <= 50)
		{
			work=-work;
			m_aAlpha=51;
		}
		if(m_aAlpha >= 255)
		{
			work=-work;
			m_aAlpha=250;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CTitleLogo::Draw(void)
{
	m_pDevice ->SetStreamSource(0,m_pD3DBuff,0,sizeof(VERTEX_2D));
	m_pDevice ->SetTexture(0,m_pD3DTex);
	m_pDevice ->SetFVF(FVF_VERTEX_2D);
	m_pDevice ->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// クリエイト
//=============================================================================
CTitleLogo *CTitleLogo::Create(float fPosX,float fPosY,float fSizeX,float fSizeY,char* pTextureName,CRenderer* m_pRenderer,int nPriority)
{
	CTitleLogo *pTitleLogo;
	//インスタンスの設定
	pTitleLogo = new CTitleLogo(OBJTYPE_2D,nPriority);
	//テクスチャの指定
	pTitleLogo->TextureName=pTextureName;
	//座標の設定
	pTitleLogo->SetPos(fPosX,fPosY,0);
	//大きさの設定
	pTitleLogo->SetSize(fSizeX,fSizeY,0);
	pTitleLogo->Init(m_pRenderer);

	return pTitleLogo;
}