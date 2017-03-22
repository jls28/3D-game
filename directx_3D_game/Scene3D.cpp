//=============================================================================
//
// CScene3D [CScene3D.cpp]
// Author : 稲澤俊和
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene3D.h"
#include "Renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// 地面の幅
#define FIELD_HIGHT		(100.0f)		// 地面の縦

CRenderer* CScene3D::m_pScene3D=NULL;			//3Dのポインタ


//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	// メンバ変数の初期化
	m_pD3DDevice = NULL;
	m_pD3DTexture = NULL;
	m_pD3DVtxBuff = NULL;
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D(void)
{
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CScene3D* CScene3D::Create(float fPosX,float fPosY,float fPosZ,float fSizeX,float fSizeY,float fSizeZ,CRenderer* m_pRenderer)
{
	/*CScene3D *pScene = new CScene3D(OBJTYPE_3D);

	pScene->Init(pRenderer);

	return pScene;
	*/

	//インスタンスの生成
	CScene3D *pScene= new CScene3D(OBJTYPE_3D);
	//CEnemyのInitを呼び出す
	pScene->Init(m_pRenderer);
	//座標の設定
	pScene->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pScene->SetPos(fPosX,fPosY,fPosZ);
	//大きさの指定
	pScene->m_Scl = D3DXVECTOR3(fSizeX,fSizeY,fSizeZ);
	pScene->SetPos(fSizeX,fSizeY,fSizeZ);

	m_pScene3D=m_pRenderer;
	return pScene;

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(CRenderer *pRenderer)
{
	VERTEX_3D *pVtx;
	m_pD3DDevice = pRenderer->GetDevice();	// デバイスへのポインタ

	// 頂点バッファの生成
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	// ステータスの初期化
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポリゴンの設定
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	//頂点の設定
	pVtx[0].vtx = D3DXVECTOR3(-FIELD_WIDTH/2, 0, FIELD_HIGHT/2);
	pVtx[1].vtx = D3DXVECTOR3(FIELD_WIDTH/2,  0, FIELD_HIGHT/2);
	pVtx[2].vtx = D3DXVECTOR3(-FIELD_WIDTH/2, 0, -FIELD_HIGHT/2);
	pVtx[3].vtx = D3DXVECTOR3(FIELD_WIDTH/2,  0, -FIELD_HIGHT/2);

	// 法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	// 色の設定
	pVtx[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	// 頂点の画像の設定
	pVtx[0].tex = D3DXVECTOR2(0,0);
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);
	m_pD3DVtxBuff->Unlock();

	//テクスチャ(画像ファイル)の読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,
							  "data/TEXTURE/magmas.jpg",
							  &m_pD3DTexture);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	// m_pD3DDeviceの解放
	if(m_pD3DDevice != NULL)
	{
		m_pD3DDevice = NULL;
	}

	// m_pD3DTextureの解放
	if(m_pD3DTexture!= NULL)
	{
		m_pD3DTexture->Release();
		m_pD3DTexture = NULL;
	}

	// m_pD3DVtxBuffの解放
	if(m_pD3DVtxBuff != NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	//// 右回転
	//if(CInputKeyboad::GetKeyboardRepeat(DIK_D))
	//{
		//m_Rot.y += 0.01f;
	//}
	//// 左回転
	//if(CInputKeyboad::GetKeyboardRepeat(DIK_A))
	//{
	//	m_Rot.y -= 0.01f;
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//スケールの反映
	D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	//回転の反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	//ワールドマトリックスの設定
	m_pD3DDevice -> SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pD3DDevice -> SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	m_pD3DDevice -> SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	m_pD3DDevice -> SetTexture(0, m_pD3DTexture);
	m_pD3DDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
