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
#include "SceneX.h"
#include "Input.h"
#include "Manager.h"
#include "CMeshField.h"
#include "Gimmick.h"
#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "Leg.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_ROT_SPEED				(0.05f)		//モデルの回転速度
#define MODEL_SPEED_X				(1.7f)		//モデルの移動速度
#define MODEL_SPEED_Z				(4.0f)		//
#define MODEL_SPEED_Y				(0.1f)		//
#define MODEL_SPEED					(0.7f)		//

//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CLeg::m_pLeg=NULL;
int CLeg::m_LegNum=0; 
//=============================================================================
// コンストラクタ
//=============================================================================
CLeg::CLeg(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_pPlayer=NULL;
	m_Ratio=0.0f;
	m_State=0;
	m_Rotate=0.1f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLeg::~CLeg(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CLeg* CLeg::Create(float Ratio,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CLeg *pLeg;
	//インスタンスの作成
	pLeg = new CLeg(OBJTYPE_LEG);

	//座標の設定
	pLeg->SetRatio(Ratio);
	pLeg->m_State=m_LegNum;
	m_LegNum++;
	pLeg->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pLeg->SetPos(fPosX,fPosY,fPosZ);
		//CEnemyのInitを呼び出す
	pLeg->Init(m_pRenderer);
	m_pLeg=m_pRenderer;
	return pLeg;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLeg::Init(CRenderer *pRenderer)
{
	//自機モデルの指定
	FileName="data/MODEL/player/sasori_leg.x";

	switch(m_State)
	{
		case 0:
			FileName="data/MODEL/player/sasori_leg_l.x";
			m_Rot.z=D3DX_PI/4;
			break;
		case 1:
			FileName="data/MODEL/player/sasori_leg_l.x";
			m_Rot.z=0.0f;
			break;
		case 2:
			FileName="data/MODEL/player/sasori_leg_l.x";
			m_Rot.z=-D3DX_PI/4;
			break;
		case 3:
			FileName="data/MODEL/player/sasori_leg.x";
			m_Rot.z=D3DX_PI/4;
			break;
		case 4:
			FileName="data/MODEL/player/sasori_leg.x";
			m_Rot.z=0.0f;
			break;
		case 5:
			FileName="data/MODEL/player/sasori_leg.x";
			m_Rot.z=-D3DX_PI/4;
			break;


	}


	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLeg::Uninit(void)
{
	//自身のリソースの解放
	m_LegNum=0;
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLeg::Update(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	
	

	m_Rot.y=pPlayer->GetRot().y;

	switch(m_State)
	{
		case 0:	//左の１本目
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y+D3DX_PI*5/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y+D3DX_PI*5/8)*MODEL_SPEED_Z;
			break;
		case 1:	//左の２本目
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y+D3DX_PI/2)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y+D3DX_PI/2)*MODEL_SPEED_Z;
			break;
		case 2:	//左の3本目
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y+D3DX_PI*3/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y+D3DX_PI*3/8)*MODEL_SPEED_Z;
			break;
		case 3:	//右の１本目
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y-D3DX_PI*5/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y-D3DX_PI*5/8)*MODEL_SPEED_Z;
			break;
		case 4:	//右の２本目
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y-D3DX_PI/2)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y-D3DX_PI/2)*MODEL_SPEED_Z;
			break;
		case 5:	//右の3本目
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y-D3DX_PI*3/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y-D3DX_PI*3/8)*MODEL_SPEED_Z;
			break;
	}
	if(pPlayer->GetMoveFlag() == true)
	{
			m_Rot.z += m_Rotate;
			
			if(m_Rot.z>D3DX_PI/4)
			{
				m_Rotate = -m_Rotate;
			}
			if(m_Rot.z<-D3DX_PI/4)
			{
				m_Rotate = -m_Rotate;
			}
	}

	m_Pos.y =pPlayer->GetPos().y;
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	CSceneX::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CLeg::Draw(void)
{
	CSceneX::Draw();
}

