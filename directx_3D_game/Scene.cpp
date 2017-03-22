//=============================================================================
//
// メイン処理 [Scene.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Scene.h"
#include "Renderer.h"

//=============================================================================
// グローバル変数
//=============================================================================
CScene* CScene::m_pTop[LIST_NUM];
CScene* CScene::m_pCur[LIST_NUM];
bool CScene::m_PauseFlag=false;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(OBJTYPE ObjType,int nPriority)
{
	m_bDelete=false;
	//何もないとき
	if(m_pTop[nPriority] ==NULL && m_pCur[nPriority] ==NULL)
	{
		m_pTop[nPriority] =this;
		m_pCur[nPriority] =this;
		m_pPrev =NULL;
		m_pNext =NULL;
	}
	//何かあるとき
	else
	{
		m_pCur[nPriority] ->m_pNext=this;
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority] = this;
		m_pNext = NULL;
	}
	m_nPriority =nPriority;
	m_ObjType=ObjType;

}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// リリース
//=============================================================================
void CScene::Release(void)
{
	//削除フラグを立てる
	m_bDelete=true;
}

//=============================================================================
// 更新
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene;


	for(int i=0;i<LIST_NUM;i++)
	{
		pScene = m_pTop[i];

		if(m_PauseFlag==true && i<6)
		{
			continue;	//for文を一回飛ばす
		}

		while(1)
		{
			//pSceneの中に何か入っていたら
			if(pScene)
			{
				CScene *pScene2 =pScene->m_pNext;
				if(!pScene->m_bDelete)
				{
					pScene->Update();
				}
				
				//削除フラグが立っていたら
				if(pScene->m_bDelete)
				{
					pScene->UnlinkList();		//リストをつなげる
					delete pScene;				//デリート
				}
				pScene = pScene2;
			}
			else
			{
				break;
			}
		}
	}
}


//=============================================================================
// 描画
//=============================================================================
void CScene::DrawAll(void)
{
	CScene *pScene;
	for(int i=0;i<LIST_NUM;i++)
	{
		pScene =m_pTop[i];
		while(1)
		{
			//pSceneの中に何か入っていたら
			if(pScene)
			{
				pScene->Draw();
				pScene = pScene->m_pNext;
			}
			//pSceneの中が空なら
			else
			{
				break;
			}
		}
	}
}

//=============================================================================
// リリースオール
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene;
	for(int i=0;i<LIST_NUM;i++)
	{
		pScene = m_pTop[i];

		while(1)
		{
			//pSceneの中になにか入っていたら
			if(pScene)
			{
				pScene->Uninit();
				//削除フラグが立っていたら
				if(pScene->m_bDelete)
				{
					pScene->UnlinkList();		//リストをつなげる
					delete pScene;				//デリート
				}
				pScene = m_pTop[i];
			}
			//pSceneが空なら
			else
			{
				break;
			}
		}
	}
}

//=============================================================================
// UnlinkList
//=============================================================================
void CScene::UnlinkList(void)
{
	// 一つのみの時
	if(this->m_pPrev == NULL && this->m_pNext == NULL)
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
	}

	// 先頭だった場合
	else if(this->m_pPrev == NULL && this->m_pNext !=NULL)
	{
		m_pTop[m_nPriority] = this->m_pNext;
		this->m_pNext ->m_pPrev = NULL;
	}
	// 中間の処理
	else if(this->m_pPrev != NULL && this->m_pNext != NULL)
	{
		this->m_pPrev->m_pNext = this->m_pNext;
		this->m_pNext->m_pPrev = this->m_pPrev;
	}
	// 最後尾だったら
	else if(this->m_pNext ==NULL && this->m_pPrev != NULL)
	{
		m_pCur[m_nPriority] = this->m_pPrev;
		this->m_pPrev ->m_pNext = NULL;
	}
}


D3DXVECTOR3 CScene::CrossProduct(D3DXVECTOR3 Vector1,D3DXVECTOR3 Vector2,D3DXVECTOR3 Vector3)
{
	D3DXVECTOR3 VecLine,VecToTarget,Vec1;

	VecLine=Vector2-Vector1;
	VecToTarget=Vector3-Vector1;
	//外積の算出
	D3DXVec3Cross(&Vec1,&VecLine,&VecToTarget);
	return Vec1;
}


CScene* CScene::GetScene(OBJTYPE Obj)
{
	CScene *pScene;
	for(int i=0;i<LIST_NUM;i++)
	{
		pScene = m_pTop[i];
		while(1)
		{
			//pSceneの中に何か入っていたら
			if(pScene)
			{
				if(pScene->GetObjType()==Obj)
				{
					return pScene;
				}
				pScene = pScene->m_pNext;
			}
			else
			{
				break;
			}
		}
	}
	return pScene;

}