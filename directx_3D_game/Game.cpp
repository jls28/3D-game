//=============================================================================
//
// メイン処理 [Manager.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Game.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneX.h"
#include "Enemy.h"
#include "MeshWall.h"
#include "CMeshField.h"
#include "Player.h"
#include "Cylinder.h"
#include "Dome.h"
#include "Gimmick.h"
#include "Fade.h"
#include "Input.h"
#include "Pause.h"
#include "Timer.h"
#include "Score.h"
#include "sound.h"
#include "Goal.h"
#include "Shadow.h"
#include "Enemy.h"
#include "MotionModel.h"
#include "TailBall.h"
#include "Needle.h"
#include "Collision.h"
#include "Target.h"
#include "Magma.h"
#include "Fireball.h"
#include "Collision.h"
#include "CreateFire.h"
#include "Leg.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
CField* CGame::pMeshField=NULL;
CPlayer* CGame::m_pPlayer2=NULL;
CGimmick* CGame::m_pGimmick=NULL;
CRenderer* CGame::m_pRenderer=NULL;
CMotionModel* CGame::m_pMotion;
CNeedle* CGame::m_pNeedle=NULL;
CTailBall* CGame::m_pTailBall=NULL;
CCollision* CGame::m_pCollision=NULL;
CTarget* CGame::m_pTarget[]={NULL};
CMagma* CGame::m_pMagma=NULL;
CGoal* CGame::m_pGoal=NULL;
CFireball* CGame::m_pFireball[]={NULL};
CLeg* CGame::m_pLeg[]={NULL};


CCreateFire* CGame::m_pCreateFire=NULL;
CCreateFire Fire;

int FireForce=800;	//炎の強さ
int FireLife=400;	//炎の寿命
bool sFlag=false;		//炎が収束するかどうかのフラグ
double WindForce=0;	//風力の強さ
void OnDraw(HWND hwnd,HDC hdc);	//画面の描画
//炎のパラメータFirePara1=6;FirePara2=50;
int FirePara1=6,FirePara2=50;
//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	lpFire=NULL;
	pMeshField=NULL;
	m_pRenderer = NULL;
	PauseFlag=false;
	m_pPause=NULL;
	ClearPos=D3DXVECTOR3(605,50,-241);

}
//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(CRenderer* pRenderer)
{

	m_pRenderer=pRenderer;

	//インタンス作成
	m_pFade = new CFade(OBJTYPE_FADE);

	m_pCollision = new CCollision();
	//フェードの初期化
	m_pFade->Init(pRenderer);
	COLOR Color;
	Color.R=255;
	Color.G=255;
	Color.B=255;
	Color.A=255;
	m_pFade->FadeStart(FADE_IN,60,Color);



	//2Dポリゴン(操作説明)作成
	CScene2D::Create(100,100,200,200,"data/TEXTURE/sousa2.png",m_pRenderer);
	//ドームの生成
	CDome::Create(1200,1200,50,50,500,0,-600,pRenderer);
	//シリンダー作成
	//左上
	CCylinder::Create(10,40,20,20,35,0,-88,pRenderer);
	//左下
	CCylinder::Create(10,40,20,20,8.5,0,-995,pRenderer);
	//右上
	CCylinder::Create(10,40,20,20,894,0,-30,pRenderer);
	//右下
	CCylinder::Create(10,40,20,20,989,0,-993,pRenderer);

	//フィールド作成
	pMeshField=CField::Create(pRenderer,0,0,0);

		//ギミック(動く床)作成
	m_pGimmick=CGimmick::Create(894,60,-730,pRenderer);
	
	//影　必ずフィールド・影・キャラの順番で描画する
	CShadow::Create(80,50,-962,m_pRenderer);

	//自機作成
	m_pPlayer2=CPlayer::Create(80,60,-962,pRenderer);			//胴体
	m_pTailBall=CTailBall::Create(0.2f,80,60,-952,pRenderer);	//尻尾の玉
	m_pTailBall=CTailBall::Create(0.4f,80,60,-952,pRenderer);	//尻尾の玉
	m_pTailBall=CTailBall::Create(0.6f,80,60,-952,pRenderer);	//尻尾の玉
	m_pTailBall=CTailBall::Create(0.8f,80,60,-952,pRenderer);	//尻尾の玉
	m_pNeedle=CNeedle::Create(150,100,-982,pRenderer);			//針
	
	//足
	m_pLeg[0]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[1]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[2]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[3]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[4]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[5]=CLeg::Create(0.4f,83,60,-949,pRenderer);

	//的
	m_pTarget[0] = CTarget::Create(300,80,-942,pRenderer);
	m_pTarget[1] = CTarget::Create(500,100,-442,pRenderer);
	m_pTarget[2] = CTarget::Create(500,150,-942,pRenderer);
	m_pTarget[3] = CTarget::Create(800,80,-942,pRenderer);
	m_pTarget[4] = CTarget::Create(700,80,-282,pRenderer);
	m_pTarget[5] = CTarget::Create(100,80,-42,pRenderer);


	//敵作成
	//CEnemy::Create(80,60,-962,pRenderer);

	//ゴールの目印のモデル作成
	m_pGoal=CGoal::Create(605.5f,50.0f,-241.6f,pRenderer);

	//BGM再生
	//PlaySound(SOUND_LABEL_GAME);

	m_pFireball[0]=CFireball::Create(1,586,150,-531,pRenderer);
	m_pFireball[1]=CFireball::Create(1,586,40,-531,pRenderer);
	m_pFireball[2]=CFireball::Create(0,586,40,-531,pRenderer);
	m_pFireball[3]=CFireball::Create(0,586,60,-531,pRenderer);
	m_pFireball[4]=CFireball::Create(2,586,20,-531,pRenderer);


	//マグマの生成
	m_pMagma=CMagma::Create(m_pRenderer->GetDevice(),300,30,200);

	//タイマーの生成
	CTimer::Create(730,0,m_pRenderer);


	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{	
	//StopSound(SOUND_LABEL_GAME);

	if(m_pPause!=NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause=NULL;
	}

	pMeshField=NULL;
	m_pPlayer2=NULL;
	m_pGimmick=NULL;
	m_pFade=NULL;
	
	
	m_pCollision=NULL;
	for(int i=0;i<LEG_MAX;i++)
	{
		m_pLeg[i]=NULL;
		m_pTarget[i]=NULL;
	}
	for(int i=0;i<FIREBALL_MAX;i++)
	{
		m_pFireball[i]=NULL;
	}
	m_pMagma=NULL;
	m_pRenderer=NULL;

	CScene::ReleaseAll();
	//delete pMeshField;
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//フェードが終わったら
	if(m_pFade->GetFade()==FADE_OUT_FINISH)
	{
		//ポーズ状態の時
		if(m_pPause!=NULL)
		{
			//ポーズ内選択肢
			switch(m_pPause->GetMenu())
			{
				//タイトルに戻る
				case RETURN_TITLE:
					CManager::SetNextPhase(MODE_TITLE);
					break;

				//リトライ
				case RETRY:
					CManager::SetNextPhase(MODE_RESET);
					break;
			}
		}
		else
		{
			// ゲームオーバーかクリアかフラグで判断
			CManager::SetNextPhase(MODE_RESULT);
		}
		//ポーズフラグをfalseに
		CManager::SetPauseFlag(false);
	}
	//もしポーズフラグがtrueなら
	if(CManager::GetPauseFlag()==true)
	{
		m_pPause->Update();
		//ポーズからゲームの戻ったら
		if(m_pPause->GetMenu()==RETURN_GAME)
		{
			CManager::SetPauseFlag(false);
			m_pPause->Uninit();
			delete m_pPause;
			m_pPause=NULL;
		}
		else if((m_pPause->GetMenu()==RETURN_TITLE || m_pPause->GetMenu()==RETRY) && m_pFade->GetFade()==FADE_NONE)
		{
			COLOR Color;
			Color.R=255;
			Color.G=255;
			Color.B=255;
			Color.A=0;
			m_pFade->FadeStart(FADE_OUT,60,Color);
		}
		return;
	}
	//Pボタンが押されたら
	if(GetKeyboardTriger(DIK_P))
	{
		CManager::SetPauseFlag(true);
		m_pPause= new CPause;
		m_pPause->Init(m_pRenderer);
	}

	CPlayer* pPlayer=CGame::GetPlayer();
	CGoal* pGoal = CGame::GetGoal();
	CCollision* pCollision = CGame::GetCollision();

	//クリア条件
	//ゴールの座標に着いたら
	if(pPlayer->GetClearFlag() == true && m_pFade->GetFade()==FADE_NONE)
	{
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);
	}

	//ゲームオーバーの時
	//溶岩に落ちたら
	if(pPlayer->GetDeadFlag() == true && m_pFade->GetFade()==FADE_NONE)
	{
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
		HDC hdc;
	PAINTSTRUCT ps;
	HWND hWnd;

	hdc=BeginPaint(hWnd,&ps);
	OnDraw(hWnd,hdc);			//画面描画
	EndPaint(hWnd,&ps);
}
void OnDraw(HWND hwnd,HDC hdc)
{
	Fire.MoveFire(FireForce,FireLife,sFlag,WindForce);
	Fire.DrawImage(hdc,0,100,500,500,0,100);
}