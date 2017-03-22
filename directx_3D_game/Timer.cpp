//=============================================================================
//
// スコア処理 [Score.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include"Score.h"
#include "Renderer.h"
#include "Timer.h"
//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CTimer::m_pTimer=NULL;
int CTimer::m_nTimer=NULL;
CNumber* CTimer::m_pNumber=NULL;
int Cnt=0;



//=============================================================================
// コンストラクタ
//=============================================================================
CTimer::CTimer(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_nTimer=0;
	m_pTimer=NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTimer::~CTimer(void)
{
	
}
//=============================================================================
// スコアの初期化
//=============================================================================
HRESULT CTimer::Init(CRenderer *pRenderer)
{
	m_pNumber=new CNumber[TIMER_DIGIT];

	for(int i=0;i<TIMER_DIGIT;i++)
	{
		m_pNumber[i].SetPos(m_Pos.x+(i*20),m_Pos.y,0.0f);
		m_pNumber[i].Init(pRenderer);
	}
	return S_OK;
}
//=============================================================================
// スコアの終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	for(int i=0;i<TIMER_DIGIT;i++)
	{
		m_pNumber[i].Uninit();
	}
	delete[] m_pNumber;
	CScene::Release();
}
//=============================================================================
// スコアの更新処理
//=============================================================================
void CTimer::Update(void)
{
	Cnt++;
	if(Cnt==60)
	{
		AddTimer(1);
		Cnt=0;
	}
}

//=============================================================================
// スコアの描画処理
//=============================================================================
void CTimer::Draw(void)
{
	for(int i=0;i<TIMER_DIGIT;i++)
	{
		m_pNumber[i].Draw();
	}

}

//=============================================================================
// スコアの加算
//=============================================================================
void CTimer::AddTimer(int nValue)
{
	m_nTimer+=nValue;
	if(m_nTimer >= TIMER_MAX)
	{
		m_nTimer = TIMER_MAX;
	}
	if(m_nTimer < 0)
	{
		m_nTimer = 0;
	}
		for(int nCntPlace=0;nCntPlace<TIMER_DIGIT;nCntPlace++)
		{
			int nNumber;
			int num1,num2;
			num1 = (int)pow(10,(double)TIMER_DIGIT-nCntPlace);
			num2 = (int)pow(10,(double)TIMER_DIGIT-nCntPlace-1);
			if(nCntPlace == 0)
			{
				nNumber = m_nTimer / num2;
			}
			else
			{
				nNumber = m_nTimer % num1 / num2;
			}
			m_pNumber[nCntPlace].UpdateNumber(nNumber);
		}
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CTimer* CTimer::Create(float fPosX,float fPosY,CRenderer* m_pRenderer)
{
	CTimer *pTimer;
	//インスタンスの作成
	pTimer = new CTimer(OBJTYPE_TIMER);
	//座標の設定
	pTimer->m_Pos = D3DXVECTOR3(fPosX,fPosY,0);
	//CEnemyのInitを呼び出す
	pTimer->Init(m_pRenderer);
	
	m_pTimer=m_pRenderer;
	return pTimer;
}
