//=============================================================================
//
// 弾処理 [Bullet.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Bullet.h"
#include "main.h"
#include "Explosion.h"

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(OBJTYPE nObjType,int nPriority):CSceneBillboard(nObjType,nPriority)
{
	
	m_Rot = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	
}
//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(CRenderer* m_pRenderer)
{
	CSceneBillboard::Init(m_pRenderer);
	pRenderer=m_pRenderer;

	/*WallPos[0]=D3DXVECTOR3(0,500,sqrtf(500*500+500*500));

	WallPos[1]=D3DXVECTOR3(sqrtf(500*500+500*500),500,0);

	WallPos[2]=D3DXVECTOR3(0,500,-sqrtf(500*500+500*500));

	WallPos[3]=D3DXVECTOR3(-sqrtf(500*500+500*500),500,0);*/
	WallPos[0]=D3DXVECTOR3(100,0,-100);

	WallPos[1]=D3DXVECTOR3(900,0,-100);

	WallPos[2]=D3DXVECTOR3(900,0,-900);

	WallPos[3]=D3DXVECTOR3(100,0,-900);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{

	CSceneBillboard::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	//変数宣言
	Vector2 VecLine,VecToTarget;

	for(int i=0;i<4;i++)
	{
		if(i!=3)
		{
			VecLine.x=WallPos[i+1].x-WallPos[i].x;
			VecLine.y=WallPos[i+1].z-WallPos[i].z;
		}
		else
		{
			VecLine.x=WallPos[0].x-WallPos[i].x;
			VecLine.y=WallPos[0].z-WallPos[i].z;
		}

		VecToTarget.x=this->m_Pos.x-WallPos[i].x;
		VecToTarget.y=this->m_Pos.z-WallPos[i].z;
		
		//外積判定
		if(VecToTarget.x * VecLine.y - VecToTarget.y * VecLine.x > 0)
		{
			m_Pos.x -= sinf(m_Rot.y) * 0.5f;
			m_Pos.z -= cosf(m_Rot.y) * 0.5f;
		}
		else
		{
			CExplosion::Create(m_Pos.x,m_Pos.y,m_Pos.z,pRenderer);
			CBullet::Uninit();
		}
	}


	this->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	CSceneBillboard::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CSceneBillboard::Draw();
}

//===========================================================================
// オブジェクト作成
//=============================================================================
CBullet *CBullet::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer,float dir)
{
	CBullet *pBullet;
	//インスタンスの生成
	pBullet = new CBullet(OBJTYPE_BULLET);
	//初期化
	pBullet->Init(m_pRenderer);
	//座標の設定
	pBullet->SetPos(fPosX,fPosY,fPosZ);
	pBullet->m_Pos=D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pBullet->m_Rot.y=dir;
	return pBullet;
}
