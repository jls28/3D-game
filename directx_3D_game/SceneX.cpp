//=============================================================================
//
// メイン処理 [SceneX.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "SceneX.h"
#include "Renderer.h"
#include "Input.h"
#include "Enemy.h"
//=============================================================================
// グローバル変数
//=============================================================================


//=============================================================================
// コンストラクタ
//=============================================================================
CSceneX::CSceneX(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	pDevice =NULL;
	m_nNumMatPlayer =NULL;
	m_D3DXBuffMatPlayer =NULL;
	m_pD3DXMeshPlayer =NULL;
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosDest =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PlayerMove =false;
	m_ShootCnt =0;

}
//=============================================================================
// デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneX::Init(CRenderer* m_pRenderer)
{
	pDevice = m_pRenderer->GetDevice();

	//プレイヤーステータス初期化
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl =D3DXVECTOR3(0.2f,0.2f,0.2f);
	
	m_PosDest = D3DXVECTOR3(m_Pos.x,m_Pos.y,m_Pos.z);

	//Ｘファイルを読み込み
	if(FAILED(D3DXLoadMeshFromX(FileName,D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_D3DXBuffMatPlayer,NULL,&m_nNumMatPlayer,&m_pD3DXMeshPlayer)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました。", "警告", MB_OK);
		return E_FAIL;
	}
	m_PlayerMove = false;
	m_ShootCnt = 0;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CSceneX::Uninit(void)
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
	CScene::Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneX::Update(void)
{	
	////BackSpaceキーが押されたら
	//if(GetKeyboardPress(DIK_BACK))
	//{
	//	//CSceneXのUninitを呼ぶ
	//	CSceneX::Uninit();
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void CSceneX::Draw(void)
{

	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
		
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
CSceneX *CSceneX::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CSceneX *pSceneX;
	//インスタンスの作成
	pSceneX = new CSceneX(OBJTYPE_X);
	//SceneXの初期化
	pSceneX->Init(m_pRenderer);
	//座標の設定
	pSceneX->SetPos(fPosX,fPosY,fPosZ);
	return pSceneX;
}