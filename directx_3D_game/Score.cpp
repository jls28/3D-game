//=============================================================================
//
// スコア処理 [Score.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include"Score.h"
#include "Renderer.h"

//=============================================================================
// グローバル変数
//=============================================================================
CRenderer* CScore::m_pScore=NULL;
int CScore::m_nScore=NULL;
CNumber* CScore::m_pNumber=NULL;



//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pDevice=NULL;
	m_pD3DScoreVtxBuff=NULL;
	m_pD3DScore=NULL;
	m_nScore=0;
	m_pScore=NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore(void)
{
	
}
//=============================================================================
// スコアの初期化
//=============================================================================
HRESULT CScore::Init(CRenderer *pRenderer)
{
	//スコアの桁数分のインスタンスを作る
	m_pNumber=new CNumber[DIGIT];
	for(int i=0;i<DIGIT;i++)
	{
		m_pNumber[i].SetPos(m_Pos.x+(i*20),m_Pos.y,0.0f);
		m_pNumber[i].Init(pRenderer);
	}
	return S_OK;
}
//=============================================================================
// スコアの終了処理
//=============================================================================
void CScore::Uninit(void)
{
	if(m_pD3DScore != NULL)
	{
		m_pD3DScore ->Release();
		m_pD3DScore = NULL;
	}
	if(m_pD3DScoreVtxBuff !=NULL)
	{
		m_pD3DScoreVtxBuff ->Release();
		m_pD3DScoreVtxBuff = NULL;
	}
	for(int i=0;i<DIGIT;i++)
	{
		m_pNumber[i].Uninit();
	}
	delete[] m_pNumber;
	CScene::Release();
}
//=============================================================================
// スコアの更新処理
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
// スコアの描画処理
//=============================================================================
void CScore::Draw(void)
{
	for(int i=0;i<DIGIT;i++)
	{
		m_pNumber[i].Draw();
	}

}

//=============================================================================
// スコアの加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore+=nValue;
	if(m_nScore >= SCORE_MAX)
	{
		m_nScore = SCORE_MAX;
	}
	if(m_nScore < 0)
	{
		m_nScore = 0;
	}
		for(int nCntPlace=0;nCntPlace<DIGIT;nCntPlace++)
		{
			int nNumber;
			int num1,num2;
			num1 = (int)pow(10,(double)DIGIT-nCntPlace);
			num2 = (int)pow(10,(double)DIGIT-nCntPlace-1);
			if(nCntPlace == 0)
			{
				nNumber = m_nScore / num2;
			}
			else
			{
				nNumber = m_nScore % num1 / num2;
			}
			m_pNumber[nCntPlace].UpdateNumber(nNumber);
		}
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CScore* CScore::Create(float fPosX,float fPosY,CRenderer* m_pRenderer)
{
	CScore *pScore;
	//インスタンスの作成
	pScore = new CScore(OBJTYPE_SCORE);
	//座標の設定
	pScore->m_Pos = D3DXVECTOR3(fPosX,fPosY,0);
	//CEnemyのInitを呼び出す
	pScore->Init(m_pRenderer);
	
	m_pScore=m_pRenderer;
	return pScore;
}
