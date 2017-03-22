//=============================================================================
//
// ギミック表示処理 [Gimmick.cpp]
// Author : 稲澤俊和
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Gimmick.h"
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Player.h"
#include "Manager.h"
#include "debugproc.h"
#include "Game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE_SPEED					(1.3f)		//ギミックの移動速度
#define ROT_SPEED					(0.01f)		//ギミックの回転速度

//=============================================================================
// グローバル変数
//=============================================================================


//=============================================================================
// コンストラクタ
//=============================================================================
CGimmick::CGimmick(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosOld=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosOld=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotOld=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMin=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMax=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Movex=MOVE_SPEED;
	Movez=MOVE_SPEED;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGimmick::~CGimmick(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CGimmick* CGimmick::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CGimmick *pGimmick;
	//インスタンスの作成
	pGimmick = new CGimmick(OBJTYPE_GIMMICK);
	//CEnemyのInitを呼び出す
	pGimmick->Init(m_pRenderer);
	//座標の設定
	pGimmick->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pGimmick->SetPos(fPosX,fPosY,fPosZ);

	return pGimmick;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGimmick::Init(CRenderer *pRenderer)
{
	//Xファイルの指定
	FileName="data/MODEL/b.x";

	CSceneX::Init(pRenderer);

	//m_VtxMin=D3DXVECTOR3(-80.0f,-2.0f,-80.0f);
	//m_VtxMax=D3DXVECTOR3(80.0f,2.0f,80.0f);
	
	m_VtxMin=D3DXVECTOR3(-30.0f,-2.0f,-37.0f);
	m_VtxMax=D3DXVECTOR3(30.0f,2.0f,37.0f);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGimmick::Uninit(void)
{
	//自身のリソースの解放
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGimmick::Update(void)
{
	//ギミックの自動移動
	m_Pos.z+=Movez;
	//m_Pos.x+=Movex;
	////範囲外に行ったら反転
	//if(m_Pos.z<=-1000.0f || m_Pos.z>=-50.0f)
	//{
	//	Movez=-Movez;
	//}
	////
	//if(m_Pos.x>=1000.0f || m_Pos.x<=20.0f)
	//{
	//	Movex=-Movex;
	//}

	//移動の制御
	if(m_Pos.z < -753 || m_Pos.z > -400)
	{
		Movez=-Movez;
	}

	//CDebugProc::Print("\nギミックの座標: (%f,%f,%f)\n" ,  m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	

	CPlayer* pPlayer=CGame::GetPlayer();
	if(pPlayer!=NULL)
	{
		if(pPlayer->GetSceneLink()==this)
		{
			//リンクしている
			D3DXVECTOR3 RotDest,Offset,PlayerPos,PlayerRot,OffsetRot,GimmickMove;
			PlayerPos=pPlayer->GetPos();
			PlayerRot=pPlayer->GetRot();
			//CDebugProc::Print("\n移動前プレイやーの座標: (%f,%f,%f)\n" ,  PlayerPos.x,PlayerPos.y,PlayerPos.z);
			//回転の差分を算出
			RotDest=m_Rot-m_RotOld;

			//正規化
			if(RotDest.y > D3DX_PI)
			{
				RotDest.y += -D3DX_PI * 2.0f;
			}
			else if(RotDest.y < -D3DX_PI)
			{
				RotDest.y += D3DX_PI * 2.0f;
			}

			//オフセットの算出
			Offset=PlayerPos-m_Pos;

			//オフセットの回転
			OffsetRot.x=cos(RotDest.y)*Offset.x+sin(RotDest.y)*Offset.z;
			OffsetRot.z=cos(RotDest.y)*Offset.z-sin(RotDest.y)*Offset.x;

			//新プレイヤー座標
			PlayerPos.x=m_Pos.x+OffsetRot.x;
			PlayerPos.z=m_Pos.z+OffsetRot.z;

			//ギミックの移動量
			GimmickMove=m_Pos-m_PosOld;

			//新プレイヤー座標
			PlayerPos.x+=GimmickMove.x;
			PlayerPos.y=m_Pos.y+m_VtxMax.y;
			PlayerPos.z+=GimmickMove.z;
			//CDebugProc::Print("\nぎっみく移動差分の座標: (%f,%f,%f)\n" ,  GimmickMove.x,GimmickMove.y,GimmickMove.z);
			//CDebugProc::Print("\n移動後プレイやーの座標: (%f,%f,%f)\n" ,  PlayerPos.x,PlayerPos.y,PlayerPos.z);

			//各情報を反映
			pPlayer->CPlayer::SetPosition(PlayerPos);
			pPlayer->SetPositionOld(PlayerPos.x,PlayerPos.y,PlayerPos.z);
			pPlayer->AddRot(0,RotDest.y,0);
		}
	}

	m_PosOld=m_Pos;
	m_RotOld=m_Rot;
	CSceneX::Update();

}

//=============================================================================
// 描画処理
//=============================================================================
void CGimmick::Draw(void)
{
	CSceneX::Draw();
}