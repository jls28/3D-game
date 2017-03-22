//=============================================================================
//
// 自機モデル表示処理 [Player.cpp]
// Author : 稲澤俊和
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Fireball.h"
#include "main.h"
#include "Effect.h"
#include "debugproc.h"
//#include "Renderer.h"


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

//=============================================================================
// コンストラクタ
//=============================================================================
CFireball::CFireball(OBJTYPE nObjType,int nPriority):CSceneBillboard(nObjType,nPriority)
{
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);		//座標
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);		//角度
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);		//大きさ
	m_Angle=D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CFireball::~CFireball(void)
{
	
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CFireball* CFireball::Create(int Pattern,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CFireball *pFireball;
	//インスタンスの作成
	pFireball = new CFireball(OBJTYPE_FIREBALL);
	pFireball->m_Pattern=Pattern;
	//座標の設定
	pFireball->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pFireball->SetPos(fPosX,fPosY,fPosZ);
	//CEnemyのInitを呼び出す
	pFireball->Init(m_pRenderer);
	return pFireball;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFireball::Init(CRenderer *pRenderer)
{
	this->CSceneBillboard::SetSize(5,5,5);
	CSceneBillboard::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFireball::Uninit(void)
{
	//自身のリソースの解放
	CSceneBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFireball::Update(void)
{
	m_Angle.y+=0.01f;
	m_Angle.x+=0.01f;
	/*m_Pos.x = m_Pos.x+cosf(m_Angle.y)*50;
	m_Pos.y = m_Pos.y+cosf(m_Angle.x)*40;
	m_Pos.z = m_Pos.z+sinf(m_Angle.y)*50;

			m_posCameraR.x = m_posCameraP.x+cosf(m_rotCamera.y)*0.1f;
			m_posCameraR.y = m_posCameraP.y+cosf(m_rotCamera.x)*0.1f;
			m_posCameraR.z = m_posCameraP.z+sinf(m_rotCamera.y)*0.1f;

	m_Angle.x+=0.5f;
	m_Angle.y+=0.5f;
	m_Angle.z+=0.5f;*/

	//弾にエフェクトをセット
	CEffect::Create(255,30,10,m_Pos.x,m_Pos.y,m_Pos.z,pRenderer);


	//m_Pos.y +=0.1f;
	switch(m_Pattern)
	{
		case 0:		//みぎから左
			m_Pos.x = m_Pos.x+sinf(m_Angle.y)*0.5f;
			m_Pos.y = m_Pos.y+cosf(m_Angle.x)*3.5f;
		break;
		case 1://おくから手前
			m_Pos.z = m_Pos.z+sinf(m_Angle.y)*0.5f;
			m_Pos.y = m_Pos.y+cosf(m_Angle.x)*3.5f;
		break;
		case 2:		//左から右
			m_Pos.x = m_Pos.x-sinf(m_Angle.y)*0.5f;
			m_Pos.y = m_Pos.y+cosf(m_Angle.x)*3.5f;
		break;
	}
	//m_Pos.z = m_Pos.z+sinf(m_Angle.y)*0.8f;



	//CDebugProc::Print("\n弾の座標: (%f %f %f)\n" , m_Pos.x,m_Pos.y,m_Pos.z );
	this->CSceneBillboard::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	CSceneBillboard::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFireball::Draw(void)
{
		//高さが30以下になったら消去
	if(m_Pos.y<30)
	{
		CSceneBillboard::Draw();
	}
	


}

