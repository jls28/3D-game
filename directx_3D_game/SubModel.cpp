//=============================================================================
//
// メイン処理 [SceneX.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Renderer.h"
#include "SubModel.h"

//=============================================================================
// グローバル変数
//=============================================================================


//=============================================================================
// コンストラクタ
//=============================================================================
CSubModel::CSubModel(int nPriority)
{
	pDevice =NULL;
	m_nNumMatPlayer =NULL;
	m_D3DXBuffMatPlayer =NULL;
	m_pD3DXMeshPlayer =NULL;
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.5f,0.5f,0.5f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CSubModel::~CSubModel()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSubModel::Init(CRenderer* m_pRenderer)
{
	pDevice = m_pRenderer->GetDevice();

	//Ｘファイルを読み込み
	if(FAILED(D3DXLoadMeshFromX(m_FileName,D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_D3DXBuffMatPlayer,NULL,&m_nNumMatPlayer,&m_pD3DXMeshPlayer)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました。", "警告", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CSubModel::Uninit(void)
{
	//自身のリソースの解放
	if(m_pD3DXMeshPlayer!=NULL)
	{
		m_pD3DXMeshPlayer->Release();
		m_pD3DXMeshPlayer= NULL;
	}
	if(m_D3DXBuffMatPlayer!=NULL)
	{
		m_D3DXBuffMatPlayer->Release();
		m_D3DXBuffMatPlayer= NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CSubModel::Update(void)
{	
}
//=============================================================================
// 描画処理
//=============================================================================
void CSubModel::Draw(void)
{
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxParent;
	
	if(m_Parent!=NULL)
	{
		mtxParent=m_Parent->GetWorld();
	}
	else
	{
		D3DXMatrixIdentity(&mtxParent);
	}
	
	//ワールドマトリックス
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//スケールを反映
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	//親を合成
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxParent);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);
	//現在マテリアルを取得
	pDevice->GetMaterial(&matDef);
	
	pD3DXMat = (D3DXMATERIAL*)m_D3DXBuffMatPlayer->GetBufferPointer();
	for(int nCntMat = 0;nCntMat<(signed)m_nNumMatPlayer;nCntMat++)
	{
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		pDevice->SetTexture(0,0);
		m_pD3DXMeshPlayer->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);
}


//=============================================================================
// クリエイト
//=============================================================================
CSubModel *CSubModel::Create(float fPosX,float fPosY,float fPosZ,char* FilePath,CRenderer* m_pRenderer)
{
	CSubModel *pObje;
	//インスタンスの作成
	pObje = new CSubModel();
	pObje->m_FileName=FilePath;
	//SceneXの初期化
	pObje->Init(m_pRenderer);
	//座標の設定
	pObje->SetPos(fPosX,fPosY,fPosZ);
	return pObje;
}