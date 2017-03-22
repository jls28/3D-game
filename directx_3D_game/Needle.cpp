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
#include "TailBall.h"
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Bullet.h"
#include "Manager.h"
#include "CMeshField.h"
#include "Gimmick.h"
#include "Camera.h"
#include "Game.h"
#include "Fade.h"
#include "Score.h"
#include "sound.h"
#include "Needle.h"
#include "Collision.h"
#include "Target.h"
#include "Player.h"
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
CRenderer* CNeedle::m_pNeedle=NULL;
bool CNeedle::m_RotFlag;
CFade* CNeedle::m_pFade=NULL;
CNeedle* CNeedle::m_pFlag;
//=============================================================================
// コンストラクタ
//=============================================================================
CNeedle::CNeedle(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_pNeedle=NULL;
	m_pSceneLink=NULL;
	m_pFlag=NULL;
	m_pFade=NULL;
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pTarget=NULL;
	m_HitFlag=false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNeedle::~CNeedle(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CNeedle* CNeedle::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CNeedle *pNeedle;
	//インスタンスの作成
	pNeedle = new CNeedle(OBJTYPE_NEEDLE);
	//CEnemyのInitを呼び出す
	pNeedle->Init(m_pRenderer);
	//座標の設定
	pNeedle->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pNeedle->SetPos(fPosX,fPosY,fPosZ);
	m_pNeedle=m_pRenderer;
	return pNeedle;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNeedle::Init(CRenderer *pRenderer)
{
	//尻尾の針モデルの指定
	FileName="data/MODEL/player/sasori_needle.x";

	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNeedle::Uninit(void)
{
	//自身のリソースの解放
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNeedle::Update(void)
{
	m_BulletCnt++;
	if(m_BulletCnt < 10)
	{
		m_PosDest += m_speed;
	}
	if(m_HitFlag==false)
	{
		m_Pos+=(m_PosDest-m_Pos)*0.1;
	}

	CCollision *pCollision = CGame::GetCollision();
	CPlayer *pPlayer = CGame::GetPlayer();

	for(int i=0;i<6;i++)
	{
		CTarget *target = CGame::GetTarget(i);		//的のポインタの取得
		//針と的の当たり判定
		if(pCollision->SphereToSphere3D(m_Pos,3.0f,target->GetPos(),17.0f) && pPlayer->GetTailShotFlag()==true)
		{
			m_BulletCnt=30;
			CDebugProc::Print("\nヒット\n");		//デバッグ文字表示
			m_HitFlag=true;
			break;
		}
		else
		{
			if(m_BulletCnt==30 && m_HitFlag==false)		//カウントが30でかつフラグがfalseなら
			{
				pPlayer->Neutral();						//プレイヤーの状態を通常に戻す
				pPlayer->SetTailShotFlag(false);		//発射フラグの設定
			}
		}
	}
	if(m_HitFlag==true)
	{
		pPlayer->Pulled();	//当たった場合は針に引っ張られる関数を呼ぶ
	}





	CSceneX::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CNeedle::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// 針の発射関数
//=============================================================================
void CNeedle::Shot(D3DXVECTOR3 vector)
{
	m_speed = vector;
	m_BulletCnt = 0;
}

void CNeedle::Return(void)
{

}