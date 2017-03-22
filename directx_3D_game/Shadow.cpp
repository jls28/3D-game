//=============================================================================
//
// ステンシルを使った影の表示処理 [Shadow.cpp]
// Author : 稲澤俊和
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Shadow.h"
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Bullet.h"
#include "Manager.h"
#include "CMeshField.h"
#include "Player.h"
#include "Game.h"
#include "MotionModel.h"
#include "Magma.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// 地面の幅
#define FIELD_HIGHT		(100.0f)		// 地面の縦
#define MODEL_ROT_SPEED				(0.01f)		//モデルの回転速度
#define MODEL_SPEED_X				(1.7f)		//モデルの移動速度
#define MODEL_SPEED_Z				(1.7f)		//モデルの移動速度
#define MODEL_SPEED_Y				(0.1f)		//モデルの移動速度
#define MODEL_SPEED					(0.5f)		//モデルの移動速度

//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CShadow::m_pShadow=NULL;
CPlayer* CShadow::m_pPlayer=NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl =D3DXVECTOR3(0.0f,0.0f,0.0f);
	pDevice =NULL;
	m_nNumMat =NULL;
	m_D3DXBuffMat =NULL;
	m_pD3DXMesh =NULL;
	m_pD3DBuff=NULL;

}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CShadow* CShadow::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CShadow *pShadow;
	//インスタンスの作成
	pShadow = new CShadow(OBJTYPE_SHADOW);
	pShadow->SetFileName("data/MODEL/shadow000.x");
	//CEnemyのInitを呼び出す
	pShadow->Init(m_pRenderer);
	//座標の設定
	pShadow->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pShadow->SetPos(fPosX,fPosY,fPosZ);
	m_pShadow=m_pRenderer;
	return pShadow;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(CRenderer *pRenderer)
{
	pDevice=pRenderer->GetDevice();
	//影モデルの指定
	FileName="data/MODEL/shadow000.x";
	m_Scl=D3DXVECTOR3(0.5f,1.0f,0.5f);
	//Ｘファイルを読み込み
	if(FAILED(D3DXLoadMeshFromX("data/MODEL/shadow000.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_D3DXBuffMat,NULL,&m_nNumMat,&m_pD3DXMesh)))
	{
		MessageBox(NULL, "影のXファイルの読み込みに失敗しました。", "警告", MB_OK);
		return E_FAIL;
	}

	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pD3DBuff,NULL)))
	{
		return E_FAIL;
	}

	//画面いっぱいの黒ポリゴンを出す設定
	VERTEX_2D *g_aVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&g_aVtx,0);
	//頂点の設定
	g_aVtx[0].vtx = D3DXVECTOR3(0,0,0.0f);
	g_aVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	g_aVtx[2].vtx = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);
	g_aVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	g_aVtx[0].rhw=1.0f;
	g_aVtx[1].rhw=1.0f;
	g_aVtx[2].rhw=1.0f;
	g_aVtx[3].rhw=1.0f;

	//色
	g_aVtx[0].diffuse = D3DCOLOR_RGBA(0,0,0,180);
	g_aVtx[1].diffuse = D3DCOLOR_RGBA(0,0,0,180);
	g_aVtx[2].diffuse = D3DCOLOR_RGBA(0,0,0,180);
	g_aVtx[3].diffuse = D3DCOLOR_RGBA(0,0,0,180);

	//テクスチャ座標
	g_aVtx[0].tex=D3DXVECTOR2(0,0);
	g_aVtx[1].tex=D3DXVECTOR2(1,0);
	g_aVtx[2].tex=D3DXVECTOR2(0,1);
	g_aVtx[3].tex=D3DXVECTOR2(1,1);

	m_pD3DBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	//自身のリソースの解放
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CShadow::Update(void)
{
	// ベクトル計算
	float Vx = 0.0f;
	float Vz = 0.0f;
	float fDiffRotY = 0.0f;
	D3DXVECTOR3 Normal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	//ギミックの判定関連
	Vector2 VecLine,VecToTarget;
	D3DXVECTOR3 OffSet;
	D3DXVECTOR3 Target;
	float ModelHigh=10.0f;
	//前フレームのギミックの座標
	float GimmickUpPosOld;
	float GimmickUnderPosOld;

	CScene* pGimmick;

	CScene* pSceneLinkOld=m_pSceneLink;
	m_pSceneLink=NULL;

	pGimmick=GetScene(OBJTYPE_GIMMICK);


	GimmickUpPosOld=pGimmick->GetPositionOld().y+ pGimmick->GetVertexMax().y;		//前フレームの
	GimmickUnderPosOld=pGimmick->GetPositionOld().y+ pGimmick->GetVertexMin().y;

	//ギミックに対するプレイヤーのオフセットを求める
	OffSet=m_Pos-pGimmick->GetPos();
	Target.x=pGimmick->GetPos().x+(cos(-pGimmick->GetRot().y)*
				OffSet.x+sin(-pGimmick->GetRot().y)*OffSet.z);
	Target.z=pGimmick->GetPos().z+(cos(-pGimmick->GetRot().y)*
				OffSet.z+sin(-pGimmick->GetRot().y)*OffSet.x);

	GimmickPos[0].x=pGimmick->GetPos().x + pGimmick->GetVertexMin().x;
	GimmickPos[0].z=pGimmick->GetPos().z + pGimmick->GetVertexMax().z;
	GimmickPos[1].x=pGimmick->GetPos().x + pGimmick->GetVertexMax().x;
	GimmickPos[1].z=pGimmick->GetPos().z + pGimmick->GetVertexMax().z;
	GimmickPos[2].x=pGimmick->GetPos().x + pGimmick->GetVertexMax().x;
	GimmickPos[2].z=pGimmick->GetPos().z + pGimmick->GetVertexMin().z;
	GimmickPos[3].x=pGimmick->GetPos().x + pGimmick->GetVertexMin().x;
	GimmickPos[3].z=pGimmick->GetPos().z + pGimmick->GetVertexMin().z;


	VecLine.x=GimmickPos[1].x-GimmickPos[0].x;
	VecLine.y=GimmickPos[1].z-GimmickPos[0].z;

	VecToTarget.x=Target.x-GimmickPos[0].x;
	VecToTarget.y=Target.z-GimmickPos[0].z;
	//奥の判定
	if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
	{
		VecLine.x=GimmickPos[2].x-GimmickPos[1].x;
		VecLine.y=GimmickPos[2].z-GimmickPos[1].z;
		VecToTarget.x=Target.x-GimmickPos[1].x;
		VecToTarget.y=Target.z-GimmickPos[1].z;
		//右の判定
		if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
		{
			VecLine.x=GimmickPos[3].x-GimmickPos[2].x;
			VecLine.y=GimmickPos[3].z-GimmickPos[2].z;
			VecToTarget.x=Target.x-GimmickPos[2].x;
			VecToTarget.y=Target.z-GimmickPos[2].z;
			//手前の判定
			if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
			{
				VecLine.x=GimmickPos[0].x-GimmickPos[3].x;
				VecLine.y=GimmickPos[0].z-GimmickPos[3].z;
				VecToTarget.x=Target.x-GimmickPos[3].x;
				VecToTarget.y=Target.z-GimmickPos[3].z;

				//左の判定
				if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
				{
					//ギミックと範囲内にいた場合
					float GimmickUpPos=pGimmick->GetPos().y+pGimmick->GetVertexMax().y;			//ギミックの上面の高さ
					float GimmickUnderPos=pGimmick->GetPos().y+pGimmick->GetVertexMin().y;		//ギミックの下面の高さ

					if((GimmickUpPos>m_Pos.y && GimmickUpPosOld<=m_PosOld.y) || (GimmickUpPos<=m_PosOld.y && GimmickUpPos>m_Pos.y))
					{
						//上からめり込んだ
						//プレイヤーの今と昔の高さを再設定
						m_Pos.y=GimmickUpPos;
						m_PosOld.y=GimmickUpPos;
						m_pSceneLink=pGimmick;
					}
					else if(m_Pos.y>GimmickUnderPos && m_PosOld.y<=GimmickUnderPos)
					{
 						m_PosOld.y=GimmickUnderPos-ModelHigh;
						m_Pos.y=GimmickUnderPos-ModelHigh;
					}
				}
			}
		}
	}



	for(int i=0;i<4;i++)
	{
		VecLine.x=GimmickPos[(i+1)%4].x-GimmickPos[i].x;
		VecLine.y=GimmickPos[(i+1)%4].z-GimmickPos[i].z;
		VecToTarget.x=Target.x-GimmickPos[i].x;
		VecToTarget.y=Target.z-GimmickPos[i].z;

		if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y <0.0f)
		{
			//範囲外処理中断

		}
	}
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);

	CSceneX::Update();
	m_PosOld=m_Pos;


	//影とプレイヤーの座標を同期
	CPlayer* pPlayer=CGame::GetPlayer();
	//CMotionModel* pMotion=CGame::GetMotionModel();
	m_Pos.x=pPlayer->GetPos().x;
	m_Pos.z=pPlayer->GetPos().z;
	//m_Pos=pPlayer->GetPos();
	//m_Pos=pMotion->GetPos();
	//CDebugProc::Print("\n影の座標: (%f,%f,%f)\n" ,  m_Pos.x,m_Pos.y,m_Pos.z);
}

//=============================================================================
// 描画処理
//=============================================================================
void CShadow::Draw(void)
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

	//ステンシルの設定
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);					//ステンシルを有効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);					//Zバッファへの書き込みを無効
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0x00000000);			//カラーバッファへの書き込み無効

	//DrawSubsetの前に書く
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);			//全て合格
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);		//ステンシルテスト合格・Zテスト合格→0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);		//ステンシルテスト合格・Zテスト不合格→1
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);		//ステンシルテスト不合格→0
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);					//カリングを逆にする
	pD3DXMat = (D3DXMATERIAL*)m_D3DXBuffMat->GetBufferPointer();
	for(int nCntMat = 0;nCntMat<(signed)m_nNumMat;nCntMat++)
	{
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		pDevice->SetTexture(0,0);
		m_pD3DXMesh->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_STENCILREF,0x01);						//ステンシル参照値を1にする
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_GREATEREQUAL);		//ステンシル値が1以上で合格
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);		//ステンシルテスト合格・Zテスト合格→+=1
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);		//ステンシルテスト合格・Zテスト不合格→0
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);		//ステンシルテスト不合格→0
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//カリングをもとに戻す
	for(int nCntMat = 0;nCntMat<(signed)m_nNumMat;nCntMat++)
	{
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		pDevice->SetTexture(0,0);
		m_pD3DXMesh->DrawSubset(nCntMat);
	}
	
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_STENCILREF,0x02);						//ステンシル参照値を2にする
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);			//ステンシル値が2で合格
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);		//ステンシルテスト合格・Zテスト合格→そのまま
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);		//ステンシルテスト合格・Zテスト不合格→そのまま
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);		//ステンシルテスト不合格→そのまま
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//カリングをもとに戻す
	
	
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,(D3DCOLORWRITEENABLE_RED   |
													D3DCOLORWRITEENABLE_GREEN |
													D3DCOLORWRITEENABLE_BLUE  |
													D3DCOLORWRITEENABLE_ALPHA ));
	//画面いっぱいに2D半透明の黒ポリゴンを描画
	pDevice ->SetStreamSource(0,m_pD3DBuff,0,sizeof(VERTEX_2D));
	pDevice ->SetFVF(FVF_VERTEX_2D);
	pDevice ->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
	//後片付け
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);		//ステンシルを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);		//Zバッファへの書き込みを無効

}
