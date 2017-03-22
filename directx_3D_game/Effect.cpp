//=============================================================================
//
// 自機モデル表示処理 [Player.cpp]
// Author : 稲澤俊和
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

#include "Renderer.h"

#include "Manager.h"

#include "Camera.h"
#include "Game.h"
#include "Effect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// 地面の幅
#define FIELD_HIGHT		(100.0f)		// 地面の縦
#define MODEL_ROT_SPEED				(0.05f)		//モデルの回転速度
#define MODEL_SPEED_X				(1.7f)		//モデルの移動速度
#define MODEL_SPEED_Z				(1.7f)		//
#define MODEL_SPEED_Y				(0.1f)		//
#define MODEL_SPEED					(0.7f)		//

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_EffectFlag=0;
	m_EffectCnt=0;
	m_pD3DVtxBuffEffect=NULL;
	m_EffectShow=0;

	m_pD3DTextureEffect=NULL;


}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CEffect* CEffect::Create(int Red,int Green,int Blue,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CEffect *pEffect;
	//インスタンスの作成
	pEffect = new CEffect(OBJTYPE_EFFECT);

	//座標の設定
	pEffect->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pEffect->m_Color.R=Red;
	pEffect->m_Color.G=Green;
	pEffect->m_Color.B=Blue;
	pEffect->m_Color.A=255;	
	//CEnemyのInitを呼び出す
	pEffect->Init(m_pRenderer);
	pEffect->m_pEffect=m_pRenderer;
	return pEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(CRenderer *pRenderer)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	m_pDevice = CManager::GetRenderer() ->GetDevice();	// デバイスへのポインタ

	//頂点情報の設定
	//頂点バッフア生成
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DVtxBuffEffect,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;
	m_pD3DVtxBuffEffect -> Lock(0,0,(void**)&pVtx,0);

	pVtx[0].vtx = D3DXVECTOR3(-10.0f,10.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(10.0f,10.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-10.0f,-10.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(10.0f,-10.0f,0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	for(int j=0;j<4;j++)
	{
		pVtx[j].diffuse = D3DCOLOR_RGBA(m_Color.R,m_Color.G,m_Color.B,m_Color.A);
	}
	pVtx[0].tex=D3DXVECTOR2(0,0);
	pVtx[1].tex=D3DXVECTOR2(1,0);
	pVtx[2].tex=D3DXVECTOR2(0,1);
	pVtx[3].tex=D3DXVECTOR2(1,1);	
	m_pD3DVtxBuffEffect->Unlock();
	m_EffectFlag = ON;
	m_EffectCnt = 0;

	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/shadow000.jpg",&m_pD3DTextureEffect);
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	if(m_pD3DTextureEffect !=NULL)
	{
		m_pD3DTextureEffect ->Release();
		m_pD3DTextureEffect = NULL;
	}
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{

	//	VERTEX_3D *pVtx;
	//	m_pD3DVtxBuffEffect -> Lock(0,0,(void**)&pVtx,0);
	//
	//	m_pD3DVtxBuffEffect->Unlock();


	//エフェクトの消える早さ
	//どんどん小さくしていく
	m_Scl.x-=0.08f;
	m_Scl.y-=0.08f;
	m_Scl.z-=0.08f;

	//0.1より小さくなったらもしくは高さが30以下になったら消去
	if(m_Scl.x<= 0.1f || m_Pos.y<30)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ	
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;
	mtxView = CCamera::GetMtxView();

	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
	//プレイヤー

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldeffect);
	D3DXMatrixInverse(&m_mtxWorldeffect,NULL,&mtxView);
	m_mtxWorldeffect._41 = 0.0f;
	m_mtxWorldeffect._42 = 0.0f;
	m_mtxWorldeffect._43 = 0.0f;

	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);					//スケールを反映
	D3DXMatrixMultiply(&m_mtxWorldeffect,&m_mtxWorldeffect,&mtxScl);		
	
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.x,m_Rot.y,m_Rot.z);		//回転を反映
	D3DXMatrixMultiply(&m_mtxWorldeffect,&m_mtxWorldeffect,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//位置を反映
	D3DXMatrixMultiply(&m_mtxWorldeffect,&m_mtxWorldeffect,&mtxTranslate);
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorldeffect);										//ワールドマトリックスの設定

	//加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//ポリゴンの描画	
	pDevice->SetStreamSource(0,m_pD3DVtxBuffEffect,0,sizeof(VERTEX_3D));
	pDevice->SetTexture(0,m_pD3DTextureEffect);
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//影ポリゴンの描画
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
}

