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
#include "Player.h"
#include "Needle.h"
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
CRenderer* CTailBall::m_pTailBall=NULL;
bool CTailBall::m_RotFlag;
CFade* CTailBall::m_pFade=NULL;
CTailBall* CTailBall::m_pFlag;

//=============================================================================
// コンストラクタ
//=============================================================================
CTailBall::CTailBall(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_pTailBall=NULL;
	m_pSceneLink=NULL;
	m_pFlag=NULL;
	m_pFade=NULL;
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_pNeedle=NULL;
	m_pPlayer=NULL;
	m_Ratio=0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTailBall::~CTailBall(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CTailBall* CTailBall::Create(float Ratio,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CTailBall *pTailBall;
	//インスタンスの作成
	pTailBall = new CTailBall(OBJTYPE_TAILBALL);
	//CEnemyのInitを呼び出す
	pTailBall->Init(m_pRenderer);
	//座標の設定
	pTailBall->SetRatio(Ratio);
	pTailBall->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pTailBall->SetPos(fPosX,fPosY,fPosZ);
	m_pTailBall=m_pRenderer;
	return pTailBall;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTailBall::Init(CRenderer *pRenderer)
{
	//自機モデルの指定
	FileName="data/MODEL/player/sasori_Tail1.x";

	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTailBall::Uninit(void)
{
	//自身のリソースの解放
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTailBall::Update(void)
{
	D3DXVECTOR3 VecToNeedle;	//針に向かうベクトル

	VecToNeedle=CGame::GetNeedle()->GetPos()-CGame::GetPlayer()->GetPos();
	m_Pos=CGame::GetPlayer()->GetPos()+(VecToNeedle*m_Ratio);

	CSceneX::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTailBall::Draw(void)
{

	CSceneX::Draw();


}

