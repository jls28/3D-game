//=============================================================================
//
// モーション処理 [MotionModel.cpp]
// Author : 稲澤俊和
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "MotionModel.h"
#include "Scene.h"
#include "SceneX.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "SubModel.h"
#include "Scene3D.h"

#include "Bullet.h"
#include "CMeshField.h"
#include "Gimmick.h"
#include "Camera.h"
#include "Game.h"
#include "Fade.h"
#include "Score.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define ROT_SPEED  (0.01f)	//回転速度

CRenderer* CMotionModel::m_pMotion;
//D3DXVECTOR3 Speed=D3DXVECTOR3(0.0f,0.0f,0.0f);
bool CMotionModel::m_RotFlag;
CFade* CMotionModel::m_pFade=NULL;
CPlayer* CMotionModel::m_pFlag;


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
CMotionModel::CMotionModel(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pDevice=NULL;
	for(int i=0;i<PART_MAX;i++)
	{
		m_Part[i]=NULL;
		m_Part2[i]=NULL;
	}
	for(int i=0;i<KEY_MAX;i++)
	{
		m_Anime[i].Frame=60;
		m_Anime2[i].Frame=60;
	}

	m_pMotion=NULL;
	m_MotionKey=0;
	m_MotionTime=0.0f;
	m_KeyMax=KEY_MAX;


	m_AnimLoopFlag=false;
	m_BlendFlag=false;
	m_PunchFlag=false;
	m_Ratios=0.0f;
	m_Key=0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMotionModel::~CMotionModel(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMotionModel::Init(CRenderer* pRenderer)
{
	m_pDevice=CManager::GetRenderer()->GetDevice();

	m_Part[0]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_body.x",pRenderer);			//胴体
	m_Part[1]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail1.x",pRenderer);			//尻尾1

	m_Part[2]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail2.x",pRenderer);		//尻尾1
	m_Part[3]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail3.x",pRenderer);		//尻尾1

	m_Part[4]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail4.x",pRenderer);		//尻尾1
	m_Part[5]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_needle.x",pRenderer);		//針

	/*m_Part[6]=CSubModel::Create(503,66,-500,"data/MODEL/leg_l.x",pRenderer);		//針
	m_Part[7]=CSubModel::Create(497,66,-500,"data/MODEL/leg_r.x",pRenderer);		//右足

	m_Part[8]=CSubModel::Create(503,62,-500,"data/MODEL/foot_l.x",pRenderer);		//左足先
	m_Part[9]=CSubModel::Create(497,62,-500,"data/MODEL/foot_r.x",pRenderer);		//右足先*/
	
	WaitMotion2();

	PartsInit();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMotionModel::Uninit(void)
{
	Release();
	for(int i=0;i<PART_MAX;i++)
	{
		//自身のリソースの解放
		if(m_Part[i]!=NULL)
		{
			m_Part[i]->Uninit();
			delete m_Part[i];
			m_Part[i] = nullptr;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMotionModel::Update(void)
{
	bool flag=false;
	//デバッグ文字表示
	DrawDebug();

	//操作するパーツの選択
	if(GetKeyboardPress(DIK_0)){m_MotionKey=0;}		//胴体
	if(GetKeyboardPress(DIK_1)){m_MotionKey=1;}		//頭
	if(GetKeyboardPress(DIK_2)){m_MotionKey=2;}		//左腕
	if(GetKeyboardPress(DIK_3)){m_MotionKey=3;}		//右腕
	if(GetKeyboardPress(DIK_4)){m_MotionKey=4;}		//左手
	if(GetKeyboardPress(DIK_5)){m_MotionKey=5;}		//右手
	//if(GetKeyboardPress(DIK_6)){m_MotionKey=6;}		//左足
	//if(GetKeyboardPress(DIK_7)){m_MotionKey=7;}		//右足
	//if(GetKeyboardPress(DIK_8)){m_MotionKey=8;}		//左足先
	//if(GetKeyboardPress(DIK_9)){m_MotionKey=9;}		//右足先

	//選択したパーツの座標と角度の取得
	D3DXVECTOR3 Pos=m_Part[m_MotionKey]->GetPos();
	D3DXVECTOR3 Rot=m_Part[m_MotionKey]->GetRot();

	//移動
	//右
	if(GetKeyboardPress(DIK_D))
	{
		Pos.x+=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//左
	if(GetKeyboardPress(DIK_A))
	{
		Pos.x-=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//前
	if(GetKeyboardPress(DIK_W))
	{
		Pos.z+=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}

	//後ろ
	if(GetKeyboardPress(DIK_S))
	{
		Pos.z-=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//上
	if(GetKeyboardPress(DIK_O))
	{
		Pos.y+=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}

	//下
	if(GetKeyboardPress(DIK_L))
	{
		Pos.y-=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//回転
	if(GetKeyboardPress(DIK_Z))
	{
		Rot.z+=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
	//回転2
	if(GetKeyboardPress(DIK_X))
	{
		Rot.z-=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}

	//回転2
	if(GetKeyboardPress(DIK_C))
	{
		Rot.y-=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
		//回転2
	if(GetKeyboardPress(DIK_V))
	{
		Rot.y+=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
	//回転2
	if(GetKeyboardPress(DIK_B))
	{
		Rot.x+=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
	if(GetKeyboardPress(DIK_N))
	{
		Rot.x-=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}

	//モデルの回転
	if(GetKeyboardPress(DIK_Z))
	{
		Rot.y-=ROT_SPEED;
		m_Part[0]->SetRot(Rot.x,Rot.y,Rot.z);
	}

	/*if(GetKeyboardTriger(DIK_F1)){m_MotionTime=0;}
	if(m_BlendFlag==false)
	{
		if(GetKeyboardTriger(DIK_F2))
		{
			WaitMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;

		}
		if(GetKeyboardTriger(DIK_F3)&&m_PunchFlag==false)
		{
			PunchMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;
		}
		if(GetKeyboardTriger(DIK_F4))
		{
			RunningMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;
		}		//ランニング
		if(GetKeyboardTriger(DIK_F5))
		{
			DownMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;
		}			//やられ
	}

	int i = (int)m_MotionTime;  // i に全体アニメ時間の整数部分を代入
	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
	float dt = 1.0f / m_Anime[i].Frame;
	if(m_BlendFlag==false)
	{
		for(int j = 0; j < PART_MAX; j++)
		{
			D3DXVECTOR3 KeyRot,KeyRot2;
			KeyRot.x=(m_Anime[i+1].Key[j].Rot.x - m_Anime[i].Key[j].Rot.x);
			KeyRot.y=(m_Anime[i+1].Key[j].Rot.y - m_Anime[i].Key[j].Rot.y);
			KeyRot.z=(m_Anime[i+1].Key[j].Rot.z - m_Anime[i].Key[j].Rot.z);

			//正規化
			if(KeyRot.x > D3DX_PI)
			{
				KeyRot.x -= D3DX_PI*2; 
			}
			if(KeyRot.x < -D3DX_PI)
			{
				KeyRot.x += D3DX_PI*2; 
			}
			if(KeyRot.y > D3DX_PI)
			{
				KeyRot.y -= D3DX_PI*2; 
			}
			if(KeyRot.y < -D3DX_PI)
			{
				KeyRot.y += D3DX_PI*2; 
			}
			if(KeyRot.z > D3DX_PI)
			{
				KeyRot.z -= D3DX_PI*2; 
			}
			if(KeyRot.z < -D3DX_PI)
			{
				KeyRot.z += D3DX_PI*2; 
			}


			//線形補間
			// trans x 補間
			m_Pos.x= m_Anime[i].Key[j].Pos.x +											//前のキーフレーム位置
								(m_Anime[i+1].Key[j].Pos.x - m_Anime[i].Key[j].Pos.x)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - i);								//に全体アニメ時間の小数点以下の割合をかける
			// trans y 補間
			m_Pos.y = m_Anime[i].Key[j].Pos.y +											//前のキーフレーム位置
								(m_Anime[i+1].Key[j].Pos.y - m_Anime[i].Key[j].Pos.y)	//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
			// trans z 補間
			m_Pos.z = m_Anime[i].Key[j].Pos.z +											//前のキーフレーム位置
								(m_Anime[i+1].Key[j].Pos.z - m_Anime[i].Key[j].Pos.z)	//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
			// scale x 補間 
			m_Scl.x = m_Anime[i].Key[j].Scl.x +											//前のキーフレーム位置
								(m_Anime[i+1].Key[j].Scl.x - m_Anime[i].Key[j].Scl.x)	//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
			// scale y 補間
			m_Scl.y = m_Anime[i].Key[j].Scl.y +											//前のキーフレーム位置
								(m_Anime[i+1].Key[j].Scl.y - m_Anime[i].Key[j].Scl.y)	//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
			// scale z 補間
			m_Scl.z = m_Anime[i].Key[j].Scl.z +											//前のキーフレーム位置
								(m_Anime[i+1].Key[j].Scl.z - m_Anime[i].Key[j].Scl.z)	//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
			// rotation 補間
			m_Rot.x = m_Anime[i].Key[j].Rot.x +											//前のキーフレーム位置
									KeyRot.x											//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
			// rotation 補間 
			m_Rot.y = m_Anime[i].Key[j].Rot.y +											//前のキーフレーム位置
									KeyRot.y											//前のキーフレームと次のキーフレームの差分
										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかけ		// rotation 補間 
			m_Rot.z = m_Anime[i].Key[j].Rot.z +											//前のキーフレーム位置
									KeyRot.z											//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
				//上で計算した数値を設定する
			m_Part[j]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
			//m_Part[j]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
			m_Part[j]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	

		}
	}
	else
	{
		Linear();
	}

		
		


		//上
		if(GetKeyboardPress(DIK_W))
		{
			Pos.z+=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
			if(GetKeyboardTriger(DIK_W))
			{
				RunningMotion();
			}
		}
		//右
		if(GetKeyboardPress(DIK_D))
		{
			Pos.x+=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
		}
		//下
		if(GetKeyboardPress(DIK_S))
		{
			Pos.z-=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
		}
		//左
		if(GetKeyboardPress(DIK_A))
		{
			Pos.x-=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
		}

		if(GetKeyboardPress(DIK_Z))
		{
			Rot.y-=MOVE_SPEED;
			m_Part[0]->SetRot(Rot.x,Rot.y,Rot.z);

		}*/
		
	


	
	/*if(m_BlendFlag==false)
	{
		m_MotionTime += dt;
	}
	if( m_MotionTime > m_KeyMax - 1.0f )
	{
		m_MotionTime = m_KeyMax - 1.0f;
		if(m_AnimLoopFlag==true)
		{
			m_MotionTime=0;
		}
		else
		{
			WaitMotion();
		}
	}*/
	
	for(int i=0;i<PART_MAX;i++)
	{
		m_Part[i]->Update();
	}
	//CDebugProc::Print("(%f)\n" , m_MotionTime);


}

//=============================================================================
// 描画処理
//=============================================================================
void CMotionModel::Draw(void)
{
	/*
	// key & frame 表示
	int Key = (int)m_MotionTime;  // i に全体アニメ時間の整数部分を代入

	if( Key > m_KeyMax - 2 ){Key = m_KeyMax - 2;}

	float dt = 1.0f / m_Anime[Key].Frame;
	float rest = m_MotionTime - Key;
	int Frame = rest / dt;
	CDebugProc::Print("\nKey:%d  frame:%d\n" ,Key,Frame);
	*/

	for(int i=0;i<PART_MAX;i++)
	{
		m_Part[i]->Draw();
	}
}
//=============================================================================
// バインドポーズ
//=============================================================================
void CMotionModel::PartsInit(void)
{
	// データ初期化 尻尾1
	m_Part[1]->SetPos(0.0f,23.0f,45.0f);
	m_Part[1]->SetParent(m_Part[0]);

	// part 胴体
	m_Part[0]->SetPos(500.0f,70.0f,-500.0f);
	m_Part[0]->SetParent(NULL);

	//part2尻尾2
	m_Part[2]->SetPos(0.0f,10.0f,15.0f); 
	 // 重要　親登録
	m_Part[2]->SetParent(m_Part[1]);


	// part 尻尾3
	m_Part[3]->SetPos(0.0f,20.0f,0.0f);
	// 重要　親登録
	m_Part[3]->SetParent(m_Part[2]);


	//左手尻尾4
	m_Part[4]->SetPos(0.0f,18.0f,-8.0f);
	// 重要　親登録
	m_Part[4]->SetParent(m_Part[3]);

	// 針
	m_Part[5]->SetPos(500.0f,70.0f,-520.0f);
	// 重要　親登録
	m_Part[5]->SetParent(NULL);

	//左足
	//m_Part[6]->SetPos(4.0f,-1.0f,0.0f);
	//
	//// 重要　親登録
	//m_Part[6]->SetParent(m_Part[0]);
	//
	////右足
	//m_Part[7]->SetPos(-4.0f,-1.0f,0.0f);
	//
	//// 重要　親登録
	//m_Part[7]->SetParent(m_Part[0]);
	//
	////左足先
	//m_Part[8]->SetPos(0.0f,-12.0f,0.0f);
	//
	//// 重要　親登録
	//m_Part[8]->SetParent(m_Part[6]);
	//
	////右足先
	//m_Part[9]->SetPos(0.0f,-12.0f,0.0f);
	//
	//// 重要　親登録
	//m_Part[9]->SetParent(m_Part[7]);
}
//=============================================================================
// クリエイト
//=============================================================================
CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CMotionModel *pObje;
	//インスタンスの作成
	pObje = new CMotionModel(OBJTYPE_MOTIONMODEL);
	//SceneXの初期化
	pObje->Init(m_pRenderer);
	//座標の設定
	pObje->SetPos(fPosX,fPosY,fPosZ);
	return pObje;
}
//=============================================================================
//デバッグ文字の表示
//=============================================================================
void CMotionModel::DrawDebug(void)
{
	CDebugProc::Print("\n0胴体 : (%f,%f,%f)\n", m_Part[0]->GetPos().x,m_Part[0]->GetPos().y,m_Part[0]->GetPos().z);
	CDebugProc::Print("1尻尾1 : (%f,%f,%f)\n"   ,  m_Part[1]->GetPos().x,m_Part[1]->GetPos().y,m_Part[1]->GetPos().z);
	CDebugProc::Print("2尻尾2 : (%f,%f,%f)\n" ,  m_Part[2]->GetPos().x,m_Part[2]->GetPos().y,m_Part[2]->GetPos().z);
	CDebugProc::Print("3尻尾3 : (%f,%f,%f)\n" ,  m_Part[3]->GetPos().x,m_Part[3]->GetPos().y,m_Part[3]->GetPos().z);
	CDebugProc::Print("4尻尾4 : (%f,%f,%f)\n" ,  m_Part[4]->GetPos().x,m_Part[4]->GetPos().y,m_Part[4]->GetPos().z);
	CDebugProc::Print("5針 : (%f,%f,%f)\n" ,  m_Part[5]->GetPos().x,m_Part[5]->GetPos().y,m_Part[5]->GetPos().z);

	/*CDebugProc::Print("\n0胴体 : (%f,%f,%f)\n", m_Part[0]->GetRot().x,m_Part[0]->GetRot().y,m_Part[0]->GetRot().z);
	CDebugProc::Print("1頭 : (%f,%f,%f)\n"   ,  m_Part[1]->GetRot().x,m_Part[1]->GetRot().y,m_Part[1]->GetRot().z);
	CDebugProc::Print("2左腕 : (%f,%f,%f)\n" ,  m_Part[2]->GetRot().x,m_Part[2]->GetRot().y,m_Part[2]->GetRot().z);
	CDebugProc::Print("3右腕 : (%f,%f,%f)\n" ,  m_Part[3]->GetRot().x,m_Part[3]->GetRot().y,m_Part[3]->GetRot().z);
	CDebugProc::Print("4左手 : (%f,%f,%f)\n" ,  m_Part[4]->GetRot().x,m_Part[4]->GetRot().y,m_Part[4]->GetRot().z);
	CDebugProc::Print("5右手 : (%f,%f,%f)\n" ,  m_Part[5]->GetRot().x,m_Part[5]->GetRot().y,m_Part[5]->GetRot().z);
	CDebugProc::Print("6左腿 : (%f,%f,%f)\n" ,  m_Part[6]->GetRot().x,m_Part[6]->GetRot().y,m_Part[6]->GetRot().z);
	CDebugProc::Print("7右腿 : (%f,%f,%f)\n" ,  m_Part[7]->GetRot().x,m_Part[7]->GetRot().y,m_Part[7]->GetRot().z);
	CDebugProc::Print("8左足 : (%f,%f,%f)\n" ,  m_Part[8]->GetRot().x,m_Part[8]->GetRot().y,m_Part[8]->GetRot().z);
	CDebugProc::Print("9右足 : (%f,%f,%f)\n" ,  m_Part[9]->GetRot().x,m_Part[9]->GetRot().y,m_Part[9]->GetRot().z);
	*/

	CDebugProc::Print("\n操作方法:WASD:平行移動\nOL:上昇下降\nZ軸回転:とXZ\nY軸回転:CとV\n" );
	CDebugProc::Print("カメラ操作:→←↑↓\n上昇下降：IとK\nF1:データの書き込み" );
	CDebugProc::Print("\nカメラ旋回：N,M" );
	CDebugProc::Print("\nF2:待機\n\F3:パンチ\nF4：歩く\nF5:やられ" );

}


//=============================================================================
//待機モーションの表示
//=============================================================================
void CMotionModel::WaitMotion2(void)
{		
	m_AnimLoopFlag=true;
	//待機モーション
	// part 胴体
	m_Anime[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4右腕
	m_Anime[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//左手
	m_Anime[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	// part 胴体
	m_Anime[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
	// データ初期化 頭
	m_Anime[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
	//part2左腕
	m_Anime[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
	m_Anime[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
	// part 4右腕
	m_Anime[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
	//左手
	m_Anime[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	//待機モーション
	// part 胴体
	m_Anime[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4右腕
	m_Anime[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//左手
	m_Anime[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

}

//=============================================================================
//待機モーションの表示
//=============================================================================
void CMotionModel::WaitMotion(void)
{		
	m_AnimLoopFlag=true;
	//待機モーション
	// part 胴体
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4右腕
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//左手
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	// part 胴体
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
	//part2左腕
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
	// part 4右腕
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
	//左手
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	//待機モーション
	// part 胴体
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4右腕
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//左手
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_BlendFlag=true;

}
//=============================================================================
//パンチモーションの表示
//=============================================================================
void CMotionModel::PunchMotion(void)
{
	//m_PunchFlag=true;
	m_AnimLoopFlag=false;
	//パンチモーション
	// part 胴体
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,-1.18f);
	// part 4右腕
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,1.16f);
	//左手
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

		// part 胴体
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,-0.17f,0.0f);
	// データ初期化 頭
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.0f,-0.05f,-1.14f);
	// part 4右腕
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,-3.3f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.0f,-1.55f,-0.11f);
	//左手
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,1.53f,0.03f);
	// 右手
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(-0.22f,0.0f,0.0f);
	//右足
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.74f,0.08f,0.0f);
	//左足先
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.49f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.8f,7.5f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.30f,0.30f);

		//パンチモーション
	// part 胴体
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.0f,0.0f,-1.18f);
	// part 4右腕
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.0f,0.0f,1.16f);
	//左手
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_BlendFlag=true;
	//m_PunchFlag=false;
}
//=============================================================================
//ランニングモーションの表示
//=============================================================================
void CMotionModel::RunningMotion(void)
{
	m_AnimLoopFlag=true;
	//ランニングモーション
	// part 胴体
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
	// part 4右腕
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
	//左手
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
	// 右手
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
	//左足
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
	//右足
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
	//左足先
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
	//右足先
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);

	//ランニングモーション
	// part 胴体
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.6f,12.0f,-2.4f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(-0.74f,-0.28f,-1.29f);
	// part 4右腕
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-8.1f,12.5f,-0.3f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(-2.23f,0.2f,-1.27f);
	//左手
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
	// 右手
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,0.02f);
	//左足
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.61f,0.0f,0.0f);
	//右足
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(-0.8f,0.0f,0.0f);
	//左足先
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
	//右足先
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);

	
	// part 胴体
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// データ初期化 頭
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
	// part 4右腕
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
	//左手
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
	// 右手
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
	//左足
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
	//右足
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
	//左足先
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
	//右足先
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
		m_BlendFlag=true;

}
//=============================================================================
//やられモーションの表示
//=============================================================================
void CMotionModel::DownMotion(void)
{
	m_AnimLoopFlag=false;
	//やられモーション
	// part 胴体
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,76.5f,-476.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.929f,0.02f,0.0f);
	// データ初期化 頭
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2左腕
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	// part 4右腕
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
	//左手
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.0f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	// part 胴体
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,59.0f,-476.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(1.5f,0.002f,0.0f);
	// データ初期化 頭
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,23.5f,2.5f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.12f,1.07f,-0.03f);
	//part2左腕
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	// part 4右腕
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	//左手
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	
	// part 胴体
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,59.5f,-476.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(1.5f,-0.02f,0.0f);
	// データ初期化 頭
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(-30.0f,23.5f,2.5f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(-0.12f,2.08f,0.0f);
	//part2左腕
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	// part 4右腕
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
	//左手
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 右手
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//左足先
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//右足先
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BlendFlag=true;

}
//=============================================================================
// アニメ書き出し
//=============================================================================
void CMotionModel::WriteAnime(void)
{
	int i = (int)m_MotionTime;  // i に全体アニメ時間の整数部分を代入
	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
	float dt = 1.0f / m_Anime[i].Frame;

	FILE *fp;
	fp = fopen("data.txt","a+");
	if( fp==NULL )
	return;

	fprintf(fp,"// key data\n");
	fprintf(fp,"\t{ 60,\t// frame count\n");

	fprintf(fp,"\t\t{\n");

	for (int j = 0; j < PART_MAX; j++)
	{
		fprintf(fp,"\t\t\t// part %d\n",i);
		fprintf(fp,"\t\t\t{ D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// trans\n",m_Anime[i].Key[j].Pos.x,m_Anime[i].Key[j].Pos.y,m_Anime[i].Key[j].Pos.z);
		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// scale\n",m_Anime[i].Key[j].Scl.x,m_Anime[i].Key[j].Scl.y,m_Anime[i].Key[j].Scl.z);
		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// rotation\n",m_Anime[i].Key[j].Rot.x,m_Anime[i].Key[j].Rot.y,m_Anime[i].Key[j].Rot.z);
		fprintf(fp,"\t\t\t},\n");
	}
	fprintf(fp,"\t\t}\n");
	fprintf(fp,"\t},\t// end of key\n");

	fclose(fp);
}



void CMotionModel::Linear(void)
{
	int k = (int)m_MotionTime;  // k に全体アニメ時間の整数部分を代入
	if( k > m_KeyMax - 2 ){k = m_KeyMax - 2;}
	for(int l = 0; l < PART_MAX; l++)
	{
		D3DXVECTOR3 KeyRot,KeyRot2;
		KeyRot.x=(m_Anime[m_Key+1].Key[l].Rot.x - m_Anime[m_Key].Key[l].Rot.x);
		KeyRot.y=(m_Anime[m_Key+1].Key[l].Rot.y - m_Anime[m_Key].Key[l].Rot.y);
		KeyRot.z=(m_Anime[m_Key+1].Key[l].Rot.z - m_Anime[m_Key].Key[l].Rot.z);
		KeyRot2.x=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
		KeyRot2.y=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
		KeyRot2.z=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);

		if(KeyRot.x > D3DX_PI)
		{
			KeyRot.x -= D3DX_PI*2; 
		}
		if(KeyRot.x < -D3DX_PI)
		{
			KeyRot.x += D3DX_PI*2; 
		}

		if(KeyRot.y > D3DX_PI)
		{
			KeyRot.y -= D3DX_PI*2; 
		}
		if(KeyRot.y < -D3DX_PI)
		{
			KeyRot.y += D3DX_PI*2; 
		}

		if(KeyRot.z > D3DX_PI)
		{
			KeyRot.z -= D3DX_PI*2; 
		}
		if(KeyRot.z < -D3DX_PI)
		{
			KeyRot.z += D3DX_PI*2; 
		}
		//2こめ
		if(KeyRot2.x > D3DX_PI)
		{
			KeyRot2.x -= D3DX_PI*2; 
		}
		if(KeyRot2.x < -D3DX_PI)
		{
			KeyRot2.x += D3DX_PI*2; 
		}

		if(KeyRot2.y > D3DX_PI)
		{
			KeyRot2.y -= D3DX_PI*2; 
		}
		if(KeyRot2.y < -D3DX_PI)
		{
			KeyRot2.y += D3DX_PI*2; 
		}

		if(KeyRot2.z > D3DX_PI)
		{
			KeyRot2.z -= D3DX_PI*2; 
		}
		if(KeyRot2.z < -D3DX_PI)
		{
			KeyRot2.z += D3DX_PI*2; 
		}


		//線形補間
		m_Pos.x= (m_Anime[m_Key].Key[l].Pos.x +												//前のキーフレーム位置
							(m_Anime[m_Key+1].Key[l].Pos.x - m_Anime[m_Key].Key[l].Pos.x)	//前のキーフレームと次のキーフレームの差分
								* (m_MotionTime - k))*(1.0-m_Ratios);								//に全体アニメ時間の小数点以下の割合をかける
		// trans y 補間
		m_Pos.y = (m_Anime[m_Key].Key[l].Pos.y +											//前のキーフレーム位置
							(m_Anime[m_Key+1].Key[l].Pos.y - m_Anime[m_Key].Key[l].Pos.y)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// trans z 補間
		m_Pos.z = (m_Anime[m_Key].Key[l].Pos.z +											//前のキーフレーム位置
							(m_Anime[m_Key+1].Key[l].Pos.z - m_Anime[m_Key].Key[l].Pos.z)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// scale x 補間 
		m_Scl.x = (m_Anime[m_Key].Key[l].Scl.x +											//前のキーフレーム位置
							(m_Anime[m_Key+1].Key[l].Scl.x - m_Anime[m_Key].Key[l].Scl.x)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// scale y 補間
		m_Scl.y = (m_Anime[m_Key].Key[l].Scl.y +											//前のキーフレーム位置
							(m_Anime[m_Key+1].Key[l].Scl.y - m_Anime[m_Key].Key[l].Scl.y)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// scale z 補間
		m_Scl.z = (m_Anime[m_Key].Key[l].Scl.z +											//前のキーフレーム位置
							(m_Anime[m_Key+1].Key[l].Scl.z - m_Anime[m_Key].Key[l].Scl.z)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
									
		// Rotatkon 補間
		m_Rot.x = (m_Anime[m_Key].Key[l].Rot.x +											//前のキーフレーム位置
									KeyRot.x												//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);					//に全体アニメ時間の小数点以下の割合をかける
		// Rotatkon 補間 
		m_Rot.y = (m_Anime[m_Key].Key[l].Rot.y +											//前のキーフレーム位置
									KeyRot.y												//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// Rotatkon 補間 
		m_Rot.z = (m_Anime[m_Key].Key[l].Rot.z +											//前のキーフレーム位置
									KeyRot.z												//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(1.0-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける

		//2番目
		// trans x 補間
		m_Pos.x+= (m_Anime2[0].Key[l].Pos.x +											//前のキーフレーム位置
							(m_Anime2[0+1].Key[l].Pos.x - m_Anime2[0].Key[l].Pos.x)	//前のキーフレームと次のキーフレームの差分
								* (m_MotionTime - k))*(m_Ratios);								//に全体アニメ時間の小数点以下の割合をかける
		// trans y 補間
		m_Pos.y+= (m_Anime2[0].Key[l].Pos.y +											//前のキーフレーム位置
							(m_Anime2[0+1].Key[l].Pos.y - m_Anime2[0].Key[l].Pos.y)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// trans z 補間
		m_Pos.z += (m_Anime2[0].Key[l].Pos.z +											//前のキーフレーム位置
							(m_Anime2[0+1].Key[l].Pos.z - m_Anime2[0].Key[l].Pos.z)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// scale x 補間 
		m_Scl.x+= (m_Anime2[0].Key[l].Scl.x +											//前のキーフレーム位置
							(m_Anime2[0+1].Key[l].Scl.x - m_Anime2[0].Key[l].Scl.x)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// scale y 補間
		m_Scl.y+= (m_Anime2[0].Key[l].Scl.y +											//前のキーフレーム位置
							(m_Anime2[0+1].Key[l].Scl.y - m_Anime2[0].Key[l].Scl.y)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// scale z 補間
		m_Scl.z += (m_Anime2[0].Key[l].Scl.z +											//前のキーフレーム位置
							(m_Anime2[0+1].Key[l].Scl.z - m_Anime2[0].Key[l].Scl.z)	//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
									
		// Rotatkon 補間
		m_Rot.x+= (m_Anime2[0].Key[l].Rot.x +											//前のキーフレーム位置
									KeyRot2.x													//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// Rotatkon 補間 
		m_Rot.y+= (m_Anime2[0].Key[l].Rot.y +											//前のキーフレーム位置
									KeyRot2.y													//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
		// Rotatkon 補間 
		m_Rot.z += (m_Anime2[0].Key[l].Rot.z +											//前のキーフレーム位置
									KeyRot2.z											//前のキーフレームと次のキーフレームの差分
									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける

		//上で計算した数値を設定する
		m_Part[l]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
		//m_Part[l]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
		m_Part[l]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);

	}

	m_Ratios+=0.02f;
	if(m_Ratios>=1.0f)
	{
		m_Ratios=0.0f;
		m_BlendFlag=false;
		for(int i=0;i<KEY_MAX;i++)
		{
			m_Anime[i]=m_Anime2[i];
		}
	}
	//CDebugProc::Print("比率：(%f)\n" , m_Ratios);

}























////=============================================================================
////
//// モーション処理 [MotionModel.cpp]
//// Author : 稲澤俊和
////
////=============================================================================
//
////=============================================================================
//// インクルード
////=============================================================================
//#include <stdio.h>
//#include "main.h"
//#include "MotionModel.h"
//#include "Scene.h"
//#include "SceneX.h"
//#include "Manager.h"
//#include "Renderer.h"
//#include "Input.h"
//#include "SubModel.h"
//#include "Scene3D.h"
////=============================================================================
//// マクロ定義
////=============================================================================
//#define ROT_SPEED  (0.01f)	//回転速度
//
//CRenderer* CMotionModel::m_pMotion;
//
////=============================================================================
//// グローバル変数
////=============================================================================
//
////=============================================================================
//// コンストラクタ
////=============================================================================
//CMotionModel::CMotionModel(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
//{
//	m_pDevice=NULL;
//	for(int i=0;i<PART_MAX;i++)
//	{
//		m_Part[i]=NULL;
//		m_Part2[i]=NULL;
//	}
//	for(int i=0;i<KEY_MAX;i++)
//	{
//		m_Anime[i].Frame=60;
//		m_Anime2[i].Frame=60;
//	}
//
//	m_pMotion=NULL;
//	m_MotionKey=0;
//	m_MotionTime=0.0f;
//	m_KeyMax=KEY_MAX;
//
//
//	m_AnimLoopFlag=false;
//	m_BlendFlag=false;
//	m_PunchFlag=false;
//	m_Ratios=0.0f;
//	m_Key=0;
//}
//
////=============================================================================
//// デストラクタ
////=============================================================================
//CMotionModel::~CMotionModel(void)
//{
//
//}
//
//
////=============================================================================
//// 初期化処理
////=============================================================================
//HRESULT CMotionModel::Init(CRenderer* pRenderer)
//{
//	m_pDevice=CManager::GetRenderer()->GetDevice();
//
//	m_Part[0]=CSubModel::Create(500,66,-500,"data/MODEL/body.x",pRenderer);			//胴体
//	m_Part[1]=CSubModel::Create(500,70,-500,"data/MODEL/head.x",pRenderer);			//頭
//
//	m_Part[2]=CSubModel::Create(505,70,-500,"data/MODEL/arm_l.x",pRenderer);		//左腕
//	m_Part[3]=CSubModel::Create(497,70,-500,"data/MODEL/arm_r.x",pRenderer);		//右腕
//
//	m_Part[4]=CSubModel::Create(511,70,-500,"data/MODEL/hand_l.x",pRenderer);		//左手
//	m_Part[5]=CSubModel::Create(492,70,-500,"data/MODEL/hand_r.x",pRenderer);		//右手
//
//	m_Part[6]=CSubModel::Create(503,66,-500,"data/MODEL/leg_l.x",pRenderer);		//左足
//	m_Part[7]=CSubModel::Create(497,66,-500,"data/MODEL/leg_r.x",pRenderer);		//右足
//
//	m_Part[8]=CSubModel::Create(503,62,-500,"data/MODEL/foot_l.x",pRenderer);		//左足先
//	m_Part[9]=CSubModel::Create(497,62,-500,"data/MODEL/foot_r.x",pRenderer);		//右足先
//	
//	WaitMotion2();
//
//	PartsInit();
//
//	return S_OK;
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void CMotionModel::Uninit(void)
//{
//	Release();
//	for(int i=0;i<PART_MAX;i++)
//	{
//		//自身のリソースの解放
//		if(m_Part[i]!=NULL)
//		{
//			m_Part[i]->Uninit();
//			delete m_Part[i];
//			m_Part[i] = nullptr;
//		}
//	}
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void CMotionModel::Update(void)
//{
//	bool flag=false;
//	//デバッグ文字表示
//	DrawDebug();
//
//	//操作するパーツの選択
//	/*if(GetKeyboardPress(DIK_0)){m_MotionKey=0;}		//胴体
//	if(GetKeyboardPress(DIK_1)){m_MotionKey=1;}		//頭
//	if(GetKeyboardPress(DIK_2)){m_MotionKey=2;}		//左腕
//	if(GetKeyboardPress(DIK_3)){m_MotionKey=3;}		//右腕
//	if(GetKeyboardPress(DIK_4)){m_MotionKey=4;}		//左手
//	if(GetKeyboardPress(DIK_5)){m_MotionKey=5;}		//右手
//	if(GetKeyboardPress(DIK_6)){m_MotionKey=6;}		//左足
//	if(GetKeyboardPress(DIK_7)){m_MotionKey=7;}		//右足
//	if(GetKeyboardPress(DIK_8)){m_MotionKey=8;}		//左足先
//	if(GetKeyboardPress(DIK_9)){m_MotionKey=9;}		//右足先
//	*/
//
//	//選択したパーツの座標と角度の取得
//	D3DXVECTOR3 Pos=m_Part[m_MotionKey]->GetPos();
//	D3DXVECTOR3 Rot=m_Part[m_MotionKey]->GetRot();
//
//	//移動
//	//右
//	/*if(GetKeyboardPress(DIK_D))
//	{
//		Pos.x+=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//左
//	if(GetKeyboardPress(DIK_A))
//	{
//		Pos.x-=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//前
//	if(GetKeyboardPress(DIK_W))
//	{
//		Pos.z+=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//
//	//後ろ
//	if(GetKeyboardPress(DIK_S))
//	{
//		Pos.z-=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//上
//	if(GetKeyboardPress(DIK_O))
//	{
//		Pos.y+=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//
//	//下
//	if(GetKeyboardPress(DIK_L))
//	{
//		Pos.y-=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//回転
//	if(GetKeyboardPress(DIK_Z))
//	{
//		Rot.z+=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//	//回転2
//	if(GetKeyboardPress(DIK_X))
//	{
//		Rot.z-=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//
//	//回転2
//	if(GetKeyboardPress(DIK_C))
//	{
//		Rot.y-=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//		//回転2
//	if(GetKeyboardPress(DIK_V))
//	{
//		Rot.y+=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//	//回転2
//	if(GetKeyboardPress(DIK_B))
//	{
//		Rot.x+=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//	if(GetKeyboardPress(DIK_N))
//	{
//		Rot.x-=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}*/
//
//	//モデルの回転
//	if(GetKeyboardPress(DIK_Z))
//	{
//		Rot.y-=ROT_SPEED;
//		m_Part[0]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//
//	if(GetKeyboardTriger(DIK_F1)){m_MotionTime=0;}
//	if(m_BlendFlag==false)
//	{
//		if(GetKeyboardTriger(DIK_F2))
//		{
//			WaitMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//
//		}
//		if(GetKeyboardTriger(DIK_F3)&&m_PunchFlag==false)
//		{
//			PunchMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//		}
//		if(GetKeyboardTriger(DIK_F4))
//		{
//			RunningMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//		}		//ランニング
//		if(GetKeyboardTriger(DIK_F5))
//		{
//			DownMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//		}			//やられ
//	}
//
//	int i = (int)m_MotionTime;  // i に全体アニメ時間の整数部分を代入
//	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
//	float dt = 1.0f / m_Anime[i].Frame;
//	if(m_BlendFlag==false)
//	{
//		for(int j = 0; j < PART_MAX; j++)
//		{
//			D3DXVECTOR3 KeyRot,KeyRot2;
//			KeyRot.x=(m_Anime[i+1].Key[j].Rot.x - m_Anime[i].Key[j].Rot.x);
//			KeyRot.y=(m_Anime[i+1].Key[j].Rot.y - m_Anime[i].Key[j].Rot.y);
//			KeyRot.z=(m_Anime[i+1].Key[j].Rot.z - m_Anime[i].Key[j].Rot.z);
//
//			//正規化
//			if(KeyRot.x > D3DX_PI)
//			{
//				KeyRot.x -= D3DX_PI*2; 
//			}
//			if(KeyRot.x < -D3DX_PI)
//			{
//				KeyRot.x += D3DX_PI*2; 
//			}
//			if(KeyRot.y > D3DX_PI)
//			{
//				KeyRot.y -= D3DX_PI*2; 
//			}
//			if(KeyRot.y < -D3DX_PI)
//			{
//				KeyRot.y += D3DX_PI*2; 
//			}
//			if(KeyRot.z > D3DX_PI)
//			{
//				KeyRot.z -= D3DX_PI*2; 
//			}
//			if(KeyRot.z < -D3DX_PI)
//			{
//				KeyRot.z += D3DX_PI*2; 
//			}
//
//
//			//線形補間
//			// trans x 補間
//			m_Pos.x= m_Anime[i].Key[j].Pos.x +											//前のキーフレーム位置
//								(m_Anime[i+1].Key[j].Pos.x - m_Anime[i].Key[j].Pos.x)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - i);								//に全体アニメ時間の小数点以下の割合をかける
//			// trans y 補間
//			m_Pos.y = m_Anime[i].Key[j].Pos.y +											//前のキーフレーム位置
//								(m_Anime[i+1].Key[j].Pos.y - m_Anime[i].Key[j].Pos.y)	//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//			// trans z 補間
//			m_Pos.z = m_Anime[i].Key[j].Pos.z +											//前のキーフレーム位置
//								(m_Anime[i+1].Key[j].Pos.z - m_Anime[i].Key[j].Pos.z)	//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//			// scale x 補間 
//			m_Scl.x = m_Anime[i].Key[j].Scl.x +											//前のキーフレーム位置
//								(m_Anime[i+1].Key[j].Scl.x - m_Anime[i].Key[j].Scl.x)	//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//			// scale y 補間
//			m_Scl.y = m_Anime[i].Key[j].Scl.y +											//前のキーフレーム位置
//								(m_Anime[i+1].Key[j].Scl.y - m_Anime[i].Key[j].Scl.y)	//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//			// scale z 補間
//			m_Scl.z = m_Anime[i].Key[j].Scl.z +											//前のキーフレーム位置
//								(m_Anime[i+1].Key[j].Scl.z - m_Anime[i].Key[j].Scl.z)	//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//			// rotation 補間
//			m_Rot.x = m_Anime[i].Key[j].Rot.x +											//前のキーフレーム位置
//									KeyRot.x											//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//			// rotation 補間 
//			m_Rot.y = m_Anime[i].Key[j].Rot.y +											//前のキーフレーム位置
//									KeyRot.y											//前のキーフレームと次のキーフレームの差分
//										* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかけ		// rotation 補間 
//			m_Rot.z = m_Anime[i].Key[j].Rot.z +											//前のキーフレーム位置
//									KeyRot.z											//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - i);							//に全体アニメ時間の小数点以下の割合をかける
//				//上で計算した数値を設定する
//			m_Part[j]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
//			//m_Part[j]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
//			m_Part[j]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
//		}
//	}
//	else
//	{
//		Linear();
//	}
//
//	//上
//	if(GetKeyboardPress(DIK_W))
//	{
//		Pos.z+=MOVE_SPEED;
//		
//		if(GetKeyboardTriger(DIK_W))
//		{
//			RunningMotion();
//		}
//	}
//	//右
//	if(GetKeyboardPress(DIK_D))
//	{
//		Pos.x+=MOVE_SPEED;
//		if(GetKeyboardTriger(DIK_D))
//		{
//			RunningMotion();
//		}
//	}
//	//下
//	if(GetKeyboardPress(DIK_S))
//	{
//		Pos.z-=MOVE_SPEED;
//		if(GetKeyboardTriger(DIK_S))
//		{
//			RunningMotion();
//		}
//	}
//	//左
//	if(GetKeyboardPress(DIK_A))
//	{
//		Pos.x-=MOVE_SPEED;
//		if(GetKeyboardTriger(DIK_A))
//		{
//			RunningMotion();
//		}
//	}
//
//	if(GetKeyboardPress(DIK_Z))
//	{
//		Rot.y-=MOVE_SPEED;
//
//	}
//	CDebugProc::Print("\n(%f,%f,%f)\n" , Pos.x, Pos.y, Pos.z);
//	
//	if(m_BlendFlag==false)
//	{
//		m_MotionTime += dt;
//	}
//	if( m_MotionTime > m_KeyMax - 1.0f )
//	{
//		m_MotionTime = m_KeyMax - 1.0f;
//		if(m_AnimLoopFlag==true)
//		{
//			m_MotionTime=0;
//		}
//		else
//		{
//			WaitMotion();
//		}
//	}
//	
//	for(int i=0;i<PART_MAX;i++)
//	{
//		m_Part[i]->Update();
//	}
//	//CDebugProc::Print("(%f)\n" , m_MotionTime);
//	//座標の更新
//	m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
//
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void CMotionModel::Draw(void)
//{
//	/*
//	// key & frame 表示
//	int Key = (int)m_MotionTime;  // i に全体アニメ時間の整数部分を代入
//
//	if( Key > m_KeyMax - 2 ){Key = m_KeyMax - 2;}
//
//	float dt = 1.0f / m_Anime[Key].Frame;
//	float rest = m_MotionTime - Key;
//	int Frame = rest / dt;
//	CDebugProc::Print("\nKey:%d  frame:%d\n" ,Key,Frame);
//	*/
//
//	for(int i=0;i<PART_MAX;i++)
//	{
//		m_Part[i]->Draw();
//	}
//}
////=============================================================================
//// バインドポーズ
////=============================================================================
//void CMotionModel::PartsInit(void)
//{
//	// データ初期化 頭
//	m_Part[1]->SetPos(0.0f,15.0f,0.0f);
//	m_Part[1]->SetParent(m_Part[0]);
//
//	// part 胴体
//	m_Part[0]->SetPos(500.0f,70.0f,-500.0f);
//	m_Part[0]->SetParent(NULL);
//
//	//part2左腕
//	m_Part[2]->SetPos(7.5f,12.0f,0.0f); 
//	 // 重要　親登録
//	m_Part[2]->SetParent(m_Part[0]);
//
//
//	// part 4右腕
//	m_Part[3]->SetPos(-7.5f,12.0f,0.0f);
//	// 重要　親登録
//	m_Part[3]->SetParent(m_Part[0]);
//
//
//	//左手
//	m_Part[4]->SetPos(10.0f,0.0f,0.0f);
//	// 重要　親登録
//	m_Part[4]->SetParent(m_Part[2]);
//
//	// 右手
//	m_Part[5]->SetPos(-10.0f,0.0f,0.0f);
//
//	// 重要　親登録
//	m_Part[5]->SetParent(m_Part[3]);
//
//	//左足
//	m_Part[6]->SetPos(4.0f,-1.0f,0.0f);
//
//	// 重要　親登録
//	m_Part[6]->SetParent(m_Part[0]);
//
//	//右足
//	m_Part[7]->SetPos(-4.0f,-1.0f,0.0f);
//
//	// 重要　親登録
//	m_Part[7]->SetParent(m_Part[0]);
//
//	//左足先
//	m_Part[8]->SetPos(0.0f,-12.0f,0.0f);
//
//	// 重要　親登録
//	m_Part[8]->SetParent(m_Part[6]);
//
//	//右足先
//	m_Part[9]->SetPos(0.0f,-12.0f,0.0f);
//
//	// 重要　親登録
//	m_Part[9]->SetParent(m_Part[7]);
//}
////=============================================================================
//// クリエイト
////=============================================================================
//CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
//{
//	CMotionModel *pObje;
//	//インスタンスの作成
//	pObje = new CMotionModel(OBJTYPE_MOTIONMODEL);
//	//SceneXの初期化
//	pObje->Init(m_pRenderer);
//	//座標の設定
//	pObje->SetPos(fPosX,fPosY,fPosZ);
//	return pObje;
//}
////=============================================================================
////デバッグ文字の表示
////=============================================================================
//void CMotionModel::DrawDebug(void)
//{
//	/*CDebugProc::Print("\n0胴体 : (%f,%f,%f)\n", m_Part[0]->GetPos().x,m_Part[0]->GetPos().y,m_Part[0]->GetPos().z);
//	CDebugProc::Print("1頭 : (%f,%f,%f)\n"   ,  m_Part[1]->GetPos().x,m_Part[1]->GetPos().y,m_Part[1]->GetPos().z);
//	CDebugProc::Print("2左腕 : (%f,%f,%f)\n" ,  m_Part[2]->GetPos().x,m_Part[2]->GetPos().y,m_Part[2]->GetPos().z);
//	CDebugProc::Print("3右腕 : (%f,%f,%f)\n" ,  m_Part[3]->GetPos().x,m_Part[3]->GetPos().y,m_Part[3]->GetPos().z);
//	CDebugProc::Print("4左手 : (%f,%f,%f)\n" ,  m_Part[4]->GetPos().x,m_Part[4]->GetPos().y,m_Part[4]->GetPos().z);
//	CDebugProc::Print("5右手 : (%f,%f,%f)\n" ,  m_Part[5]->GetPos().x,m_Part[5]->GetPos().y,m_Part[5]->GetPos().z);
//	CDebugProc::Print("6左腿 : (%f,%f,%f)\n" ,  m_Part[6]->GetPos().x,m_Part[6]->GetPos().y,m_Part[6]->GetPos().z);
//	CDebugProc::Print("7右腿 : (%f,%f,%f)\n" ,  m_Part[7]->GetPos().x,m_Part[7]->GetPos().y,m_Part[7]->GetPos().z);
//	CDebugProc::Print("8左足 : (%f,%f,%f)\n" ,  m_Part[8]->GetPos().x,m_Part[8]->GetPos().y,m_Part[8]->GetPos().z);
//	CDebugProc::Print("9右足 : (%f,%f,%f)\n" ,  m_Part[9]->GetPos().x,m_Part[9]->GetPos().y,m_Part[9]->GetPos().z);
//
//	CDebugProc::Print("\n0胴体 : (%f,%f,%f)\n", m_Part[0]->GetRot().x,m_Part[0]->GetRot().y,m_Part[0]->GetRot().z);
//	CDebugProc::Print("1頭 : (%f,%f,%f)\n"   ,  m_Part[1]->GetRot().x,m_Part[1]->GetRot().y,m_Part[1]->GetRot().z);
//	CDebugProc::Print("2左腕 : (%f,%f,%f)\n" ,  m_Part[2]->GetRot().x,m_Part[2]->GetRot().y,m_Part[2]->GetRot().z);
//	CDebugProc::Print("3右腕 : (%f,%f,%f)\n" ,  m_Part[3]->GetRot().x,m_Part[3]->GetRot().y,m_Part[3]->GetRot().z);
//	CDebugProc::Print("4左手 : (%f,%f,%f)\n" ,  m_Part[4]->GetRot().x,m_Part[4]->GetRot().y,m_Part[4]->GetRot().z);
//	CDebugProc::Print("5右手 : (%f,%f,%f)\n" ,  m_Part[5]->GetRot().x,m_Part[5]->GetRot().y,m_Part[5]->GetRot().z);
//	CDebugProc::Print("6左腿 : (%f,%f,%f)\n" ,  m_Part[6]->GetRot().x,m_Part[6]->GetRot().y,m_Part[6]->GetRot().z);
//	CDebugProc::Print("7右腿 : (%f,%f,%f)\n" ,  m_Part[7]->GetRot().x,m_Part[7]->GetRot().y,m_Part[7]->GetRot().z);
//	CDebugProc::Print("8左足 : (%f,%f,%f)\n" ,  m_Part[8]->GetRot().x,m_Part[8]->GetRot().y,m_Part[8]->GetRot().z);
//	CDebugProc::Print("9右足 : (%f,%f,%f)\n" ,  m_Part[9]->GetRot().x,m_Part[9]->GetRot().y,m_Part[9]->GetRot().z);
//	*/
//
//	CDebugProc::Print("\n操作方法:WASD:平行移動\nOL:上昇下降\nZ軸回転:とXZ\nY軸回転:CとV\n" );
//	CDebugProc::Print("カメラ操作:→←↑↓\n上昇下降：IとK\nF1:データの書き込み" );
//	CDebugProc::Print("\nカメラ旋回：N,M" );
//	CDebugProc::Print("\nF2:待機\n\F3:パンチ\nF4：歩く\nF5:やられ" );
//
//}
//
//
////=============================================================================
////待機モーションの表示
////=============================================================================
//void CMotionModel::WaitMotion2(void)
//{		
//	m_AnimLoopFlag=true;
//	//待機モーション
//	// part 胴体
//	m_Anime[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4右腕
//	m_Anime[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//左手
//	m_Anime[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	// part 胴体
//	m_Anime[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
//	//part2左腕
//	m_Anime[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
//	m_Anime[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
//	// part 4右腕
//	m_Anime[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
//	//左手
//	m_Anime[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	//待機モーション
//	// part 胴体
//	m_Anime[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4右腕
//	m_Anime[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//左手
//	m_Anime[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//}
//
////=============================================================================
////待機モーションの表示
////=============================================================================
//void CMotionModel::WaitMotion(void)
//{		
//	m_AnimLoopFlag=true;
//	//待機モーション
//	// part 胴体
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4右腕
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//左手
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	// part 胴体
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
//	// part 4右腕
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
//	//左手
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	//待機モーション
//	// part 胴体
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4右腕
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//左手
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	m_BlendFlag=true;
//
//}
////=============================================================================
////パンチモーションの表示
////=============================================================================
//void CMotionModel::PunchMotion(void)
//{
//	//m_PunchFlag=true;
//	m_AnimLoopFlag=false;
//	//パンチモーション
//	// part 胴体
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,-1.18f);
//	// part 4右腕
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,1.16f);
//	//左手
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//		// part 胴体
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,-0.17f,0.0f);
//	// データ初期化 頭
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.0f,-0.05f,-1.14f);
//	// part 4右腕
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,-3.3f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.0f,-1.55f,-0.11f);
//	//左手
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,1.53f,0.03f);
//	// 右手
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(-0.22f,0.0f,0.0f);
//	//右足
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.74f,0.08f,0.0f);
//	//左足先
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.49f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.8f,7.5f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.30f,0.30f);
//
//		//パンチモーション
//	// part 胴体
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.0f,0.0f,-1.18f);
//	// part 4右腕
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.0f,0.0f,1.16f);
//	//左手
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	m_BlendFlag=true;
//	//m_PunchFlag=false;
//}
////=============================================================================
////ランニングモーションの表示
////=============================================================================
//void CMotionModel::RunningMotion(void)
//{
//	m_AnimLoopFlag=true;
//	//ランニングモーション
//	// part 胴体
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
//	// part 4右腕
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
//	//左手
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
//	// 右手
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
//	//左足
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
//	//右足
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
//	//左足先
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
//	//右足先
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
//
//	//ランニングモーション
//	// part 胴体
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.6f,12.0f,-2.4f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(-0.74f,-0.28f,-1.29f);
//	// part 4右腕
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-8.1f,12.5f,-0.3f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(-2.23f,0.2f,-1.27f);
//	//左手
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
//	// 右手
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,0.02f);
//	//左足
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.61f,0.0f,0.0f);
//	//右足
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(-0.8f,0.0f,0.0f);
//	//左足先
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
//	//右足先
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
//
//	
//	// part 胴体
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// データ初期化 頭
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
//	// part 4右腕
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
//	//左手
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
//	// 右手
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
//	//左足
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
//	//右足
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
//	//左足先
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
//	//右足先
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
//		m_BlendFlag=true;
//
//}
////=============================================================================
////やられモーションの表示
////=============================================================================
//void CMotionModel::DownMotion(void)
//{
//	m_AnimLoopFlag=false;
//	//やられモーション
//	// part 胴体
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,76.5f,-476.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.929f,0.02f,0.0f);
//	// データ初期化 頭
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2左腕
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	// part 4右腕
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
//	//左手
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.0f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	// part 胴体
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,59.0f,-476.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(1.5f,0.002f,0.0f);
//	// データ初期化 頭
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,23.5f,2.5f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.12f,1.07f,-0.03f);
//	//part2左腕
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	// part 4右腕
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	//左手
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	
//	// part 胴体
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,59.5f,-476.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(1.5f,-0.02f,0.0f);
//	// データ初期化 頭
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(-30.0f,23.5f,2.5f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(-0.12f,2.08f,0.0f);
//	//part2左腕
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	// part 4右腕
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
//	//左手
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// 右手
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//左足先
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//右足先
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	m_BlendFlag=true;
//
//}
////=============================================================================
//// アニメ書き出し
////=============================================================================
//void CMotionModel::WriteAnime(void)
//{
//	int i = (int)m_MotionTime;  // i に全体アニメ時間の整数部分を代入
//	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
//	float dt = 1.0f / m_Anime[i].Frame;
//
//	FILE *fp;
//	fp = fopen("data.txt","a+");
//	if( fp==NULL )
//	return;
//
//	fprintf(fp,"// key data\n");
//	fprintf(fp,"\t{ 60,\t// frame count\n");
//
//	fprintf(fp,"\t\t{\n");
//
//	for (int j = 0; j < PART_MAX; j++)
//	{
//		fprintf(fp,"\t\t\t// part %d\n",i);
//		fprintf(fp,"\t\t\t{ D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// trans\n",m_Anime[i].Key[j].Pos.x,m_Anime[i].Key[j].Pos.y,m_Anime[i].Key[j].Pos.z);
//		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// scale\n",m_Anime[i].Key[j].Scl.x,m_Anime[i].Key[j].Scl.y,m_Anime[i].Key[j].Scl.z);
//		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// rotation\n",m_Anime[i].Key[j].Rot.x,m_Anime[i].Key[j].Rot.y,m_Anime[i].Key[j].Rot.z);
//		fprintf(fp,"\t\t\t},\n");
//	}
//	fprintf(fp,"\t\t}\n");
//	fprintf(fp,"\t},\t// end of key\n");
//
//	fclose(fp);
//}
//
//
//
//void CMotionModel::Linear(void)
//{
//	int k = (int)m_MotionTime;  // k に全体アニメ時間の整数部分を代入
//	if( k > m_KeyMax - 2 ){k = m_KeyMax - 2;}
//	for(int l = 0; l < PART_MAX; l++)
//	{
//		D3DXVECTOR3 KeyRot,KeyRot2;
//		KeyRot.x=(m_Anime[m_Key+1].Key[l].Rot.x - m_Anime[m_Key].Key[l].Rot.x);
//		KeyRot.y=(m_Anime[m_Key+1].Key[l].Rot.y - m_Anime[m_Key].Key[l].Rot.y);
//		KeyRot.z=(m_Anime[m_Key+1].Key[l].Rot.z - m_Anime[m_Key].Key[l].Rot.z);
//		KeyRot2.x=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
//		KeyRot2.y=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
//		KeyRot2.z=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
//
//		if(KeyRot.x > D3DX_PI)
//		{
//			KeyRot.x -= D3DX_PI*2; 
//		}
//		if(KeyRot.x < -D3DX_PI)
//		{
//			KeyRot.x += D3DX_PI*2; 
//		}
//
//		if(KeyRot.y > D3DX_PI)
//		{
//			KeyRot.y -= D3DX_PI*2; 
//		}
//		if(KeyRot.y < -D3DX_PI)
//		{
//			KeyRot.y += D3DX_PI*2; 
//		}
//
//		if(KeyRot.z > D3DX_PI)
//		{
//			KeyRot.z -= D3DX_PI*2; 
//		}
//		if(KeyRot.z < -D3DX_PI)
//		{
//			KeyRot.z += D3DX_PI*2; 
//		}
//		//2こめ
//		if(KeyRot2.x > D3DX_PI)
//		{
//			KeyRot2.x -= D3DX_PI*2; 
//		}
//		if(KeyRot2.x < -D3DX_PI)
//		{
//			KeyRot2.x += D3DX_PI*2; 
//		}
//
//		if(KeyRot2.y > D3DX_PI)
//		{
//			KeyRot2.y -= D3DX_PI*2; 
//		}
//		if(KeyRot2.y < -D3DX_PI)
//		{
//			KeyRot2.y += D3DX_PI*2; 
//		}
//
//		if(KeyRot2.z > D3DX_PI)
//		{
//			KeyRot2.z -= D3DX_PI*2; 
//		}
//		if(KeyRot2.z < -D3DX_PI)
//		{
//			KeyRot2.z += D3DX_PI*2; 
//		}
//
//
//		//線形補間
//		m_Pos.x= (m_Anime[m_Key].Key[l].Pos.x +												//前のキーフレーム位置
//							(m_Anime[m_Key+1].Key[l].Pos.x - m_Anime[m_Key].Key[l].Pos.x)	//前のキーフレームと次のキーフレームの差分
//								* (m_MotionTime - k))*(1.0f-m_Ratios);								//に全体アニメ時間の小数点以下の割合をかける
//		// trans y 補間
//		m_Pos.y = (m_Anime[m_Key].Key[l].Pos.y +											//前のキーフレーム位置
//							(m_Anime[m_Key+1].Key[l].Pos.y - m_Anime[m_Key].Key[l].Pos.y)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// trans z 補間
//		m_Pos.z = (m_Anime[m_Key].Key[l].Pos.z +											//前のキーフレーム位置
//							(m_Anime[m_Key+1].Key[l].Pos.z - m_Anime[m_Key].Key[l].Pos.z)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// scale x 補間 
//		m_Scl.x = (m_Anime[m_Key].Key[l].Scl.x +											//前のキーフレーム位置
//							(m_Anime[m_Key+1].Key[l].Scl.x - m_Anime[m_Key].Key[l].Scl.x)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// scale y 補間
//		m_Scl.y = (m_Anime[m_Key].Key[l].Scl.y +											//前のキーフレーム位置
//							(m_Anime[m_Key+1].Key[l].Scl.y - m_Anime[m_Key].Key[l].Scl.y)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// scale z 補間
//		m_Scl.z = (m_Anime[m_Key].Key[l].Scl.z +											//前のキーフレーム位置
//							(m_Anime[m_Key+1].Key[l].Scl.z - m_Anime[m_Key].Key[l].Scl.z)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//									
//		// Rotatkon 補間
//		m_Rot.x = (m_Anime[m_Key].Key[l].Rot.x +											//前のキーフレーム位置
//									KeyRot.x												//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);					//に全体アニメ時間の小数点以下の割合をかける
//		// Rotatkon 補間 
//		m_Rot.y = (m_Anime[m_Key].Key[l].Rot.y +											//前のキーフレーム位置
//									KeyRot.y												//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// Rotatkon 補間 
//		m_Rot.z = (m_Anime[m_Key].Key[l].Rot.z +											//前のキーフレーム位置
//									KeyRot.z												//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//
//		//2番目
//		// trans x 補間
//		m_Pos.x+= (m_Anime2[0].Key[l].Pos.x +											//前のキーフレーム位置
//							(m_Anime2[0+1].Key[l].Pos.x - m_Anime2[0].Key[l].Pos.x)	//前のキーフレームと次のキーフレームの差分
//								* (m_MotionTime - k))*(m_Ratios);								//に全体アニメ時間の小数点以下の割合をかける
//		// trans y 補間
//		m_Pos.y+= (m_Anime2[0].Key[l].Pos.y +											//前のキーフレーム位置
//							(m_Anime2[0+1].Key[l].Pos.y - m_Anime2[0].Key[l].Pos.y)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// trans z 補間
//		m_Pos.z += (m_Anime2[0].Key[l].Pos.z +											//前のキーフレーム位置
//							(m_Anime2[0+1].Key[l].Pos.z - m_Anime2[0].Key[l].Pos.z)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// scale x 補間 
//		m_Scl.x+= (m_Anime2[0].Key[l].Scl.x +											//前のキーフレーム位置
//							(m_Anime2[0+1].Key[l].Scl.x - m_Anime2[0].Key[l].Scl.x)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// scale y 補間
//		m_Scl.y+= (m_Anime2[0].Key[l].Scl.y +											//前のキーフレーム位置
//							(m_Anime2[0+1].Key[l].Scl.y - m_Anime2[0].Key[l].Scl.y)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// scale z 補間
//		m_Scl.z += (m_Anime2[0].Key[l].Scl.z +											//前のキーフレーム位置
//							(m_Anime2[0+1].Key[l].Scl.z - m_Anime2[0].Key[l].Scl.z)	//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//									
//		// Rotatkon 補間
//		m_Rot.x+= (m_Anime2[0].Key[l].Rot.x +											//前のキーフレーム位置
//									KeyRot2.x													//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// Rotatkon 補間 
//		m_Rot.y+= (m_Anime2[0].Key[l].Rot.y +											//前のキーフレーム位置
//									KeyRot2.y													//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//		// Rotatkon 補間 
//		m_Rot.z += (m_Anime2[0].Key[l].Rot.z +											//前のキーフレーム位置
//									KeyRot2.z											//前のキーフレームと次のキーフレームの差分
//									* (m_MotionTime - k))*(m_Ratios);							//に全体アニメ時間の小数点以下の割合をかける
//
//		//上で計算した数値を設定する
//		m_Part[l]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
//		//m_Part[l]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
//		m_Part[l]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
//
//	}
//
//	m_Ratios+=0.02f;
//	if(m_Ratios>=1.0f)
//	{
//		m_Ratios=0.0f;
//		m_BlendFlag=false;
//		for(int i=0;i<KEY_MAX;i++)
//		{
//			m_Anime[i]=m_Anime2[i];
//		}
//	}
//	//CDebugProc::Print("比率：(%f)\n" , m_Ratios);
//
//}
