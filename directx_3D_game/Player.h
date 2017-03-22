//=============================================================================
//
// 自機モデル表示処理 [Player.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ANGLE_LEFT	(D3DX_PI/2.0f)
#define ANGLE_RIGHT	(-D3DX_PI/2.0f)
#define ANGLE_FLONT	(D3DX_PI)
#define ANGLE_BACK	(0.0f)

//前方宣言
class CRenderer;
class CFade;

//=============================================================================
//CSceneXクラスを継承したCEnemyクラス
//=============================================================================
class CPlayer:public CSceneX
{
	//公開メンバ
	public:
		typedef enum
		{
			STATE_NORMAL,	//通常
			STATE_SHOT,		//撃つとき
			STATE_RETURN,	//針が戻ってくる
			STATE_PULLED,	//針にひっぱられる
			STATE_DEAD,		//死亡
			STATE_CLEAR		//クリア
		}STATES;

		CPlayer(OBJTYPE nObjType,int nPriority=3);		//コンストラクタ
		~CPlayer();										//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);			//初期化
		void Uninit(void);								//終了
		void Update(void);								//更新
		void Draw(void);								//描画

		static CPlayer* CPlayer::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//生成

		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//回転の取得

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		CScene* GetSceneLink(void){return m_pSceneLink;};		//ギミックのリンク

		static bool GetRotFlag(void){return m_RotFlag;};			//回転フラグの取得

		void AddRot(float x,float y,float z){m_Rot.x+=x;m_Rot.y+=y;m_Rot.z+=z;};			//回転の設定

		static CFade* GetGFade(void){return m_pFade;};			//フェードのポインタの取得

		int GetBulletCnt(void){return m_BulletCnt;};

		static CPlayer* GetPlayer(void){return m_pPPlayer;};		//フィールドのポインタの取得
		void Neutral(void);
		void Shot(void);
		void Return(void);
		void Pulled(void);
		void DeadDirection(void);
		void ClearDirection(void);

		void SetFrontVectol(float x,float y,float z){m_FrontVectol.x=x;m_FrontVectol.y=y;m_FrontVectol.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetFrontVectol(void){return m_FrontVectol;};											//前フレの角度の取得

		int GetTailShotFlag(void){return TailShotFlag;};
		void SetTailShotFlag(bool flag){TailShotFlag=flag;};

		bool GetDeadFlag(){return m_DeadFlag;};
		bool GetClearFlag(){return m_ClearFlag;};

		bool GetMoveFlag(){return m_MoveFlag;};



	//非公開メンバ
	private:



		D3DXVECTOR3 m_rotDestModel;				//目的の向き
		D3DXVECTOR3 m_Rot;						//モデルの向き
		D3DXVECTOR3 m_speedModel;				//モデルのスピード
		D3DXVECTOR3 m_Pos;					//モデルのスピード
		D3DXVECTOR3 m_RotDest;					//目的の向き

		static CRenderer *m_pPlayer;			//プレイヤーのポインタ
		static CPlayer* m_pPPlayer;

		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		D3DXVECTOR3 m_PosOld;		//前フレの座標
		D3DXVECTOR3 m_RotOld;		//前フレの角度

		D3DXVECTOR3 GimmickPos[4];	//ギミックの4頂点の座標

		CScene* m_pSceneLink;		//ギミックとのリンク

		static CPlayer* m_pFlag;	//
		static CFade* m_pFade;		//フェードのポインタ

		bool m_Moving;							//モデルが動いてるか
		float m_fDiffRotY;
		bool m_JFlag;	//ジャンプフラグ

		static bool m_RotFlag;		//回転フラグ
		int m_BulletCnt;
		STATES m_Mode;

		D3DXVECTOR3 m_FrontVectol;

		bool TailShotFlag;	//尻尾の発射フラグ


		bool m_DeadFlag;

		bool m_ClearFlag;

		bool m_MoveFlag;


};

#endif


////=============================================================================
////
//// 自機モデル表示処理 [Player.h]
//// Author : 稲澤俊和
////
////=============================================================================
//#ifndef _PLAYER_H_
//#define _PLAYER_H_
//
////=============================================================================
//// インクルード
////=============================================================================
//#include "main.h"
//#include "Scene.h"
//#include "SceneX.h"
//
////=============================================================================
//// マクロ定義
////=============================================================================
//#define ANGLE_LEFT	(D3DX_PI/2.0f)
//#define ANGLE_RIGHT	(-D3DX_PI/2.0f)
//#define ANGLE_FLONT	(D3DX_PI)
//#define ANGLE_BACK	(0.0f)
//
//class CRenderer;
////=============================================================================
////CEnemyクラス
////=============================================================================
//class CPlayer:public CSceneX
//{
//	public:
//		CPlayer(OBJTYPE nObjType,int nPriority=3);
//		~CPlayer();
//		HRESULT Init(CRenderer* m_pRenderer);
//		void Uninit(void);
//		void Update(void);
//		void Draw(void);
//		void Jump(void);
//		static CPlayer* CPlayer::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
//		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//座標の設定
//		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得
//		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
//		D3DXVECTOR3 GetRot(void){return m_Rot;}											//回転の取得
//		static bool GetRotFlag(void){return m_Flag;};
//		static CPlayer* GetPlayer(void){return m_pFlag;};
//
//	private:
//		D3DXVECTOR3 m_rotDestModel;				//目的の向き
//		bool m_Moving;							//モデルが動いてるか
//		float m_fDiffRotY;
//		D3DXVECTOR3 m_Rot;						//モデルの向き
//		D3DXVECTOR3 m_speedModel;				//モデルのスピード
//		D3DXVECTOR3 m_Pos;						//モデルのスピード
//		D3DXVECTOR3 m_RotDest;					//目的の向き
//		static CRenderer *m_pPlayer;
//		//D3DXVECTOR3 m_Speed;
//		static bool m_Flag;
//		static CPlayer* m_pFlag;
//
//
//
//
//
//
//};
//
//#endif