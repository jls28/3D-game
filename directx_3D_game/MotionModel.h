//=============================================================================
//
// モデルの動き [MotionModel.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PART_MAX (6)	//パーツの最大数
#define KEY_MAX (3)		//キーフレームの最大数
#define MOVE_SPEED (0.5f)

struct KEY_DATA
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Scl;
	D3DXVECTOR3 Rot;
};

struct KEY_ANIME
{
	int Frame;				//次のキーまでのフレーム数
	KEY_DATA Key[PART_MAX];
};

//前方宣言
class CRenderer;
class CSubModel;
class CScene3D;
class CPlayer;
class CScene;
class CFade;
//=============================================================================
//CMotionModelクラス
//=============================================================================
class CMotionModel:public CScene
{
	public:
		CMotionModel(OBJTYPE nObjType,int nPriority=3);
		~CMotionModel();
		HRESULT Init(CRenderer* pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};

		void PartsInit(void);
		void DrawDebug(void);
		void WaitMotion(void);		//待機モーション
		void WaitMotion2(void);
		void RunningMotion(void);	//ランニングモーション
		void PunchMotion(void);		//パンチモーション
		void DownMotion(void);		//やられモーション

		static CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};				//座標の取得
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;}				//回転の取得
		void CMotionModel::WriteAnime(void);				//アニメの書き出し

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得


		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXVECTOR3 m_Rot;				//モデルの向き
		D3DXVECTOR3 m_Scl;				//モデルの大きさ
		D3DXVECTOR3 m_Pos;				//モデルの座標
		D3DXMATRIX m_mtxWorld;			//ワールドマトリックス
		static CRenderer* m_pMotion;

		CSubModel* m_Part[PART_MAX];
		CSubModel* m_Part2[PART_MAX];

		int m_MotionKey;

		float m_MotionTime;
		int m_KeyMax;
		bool m_AnimLoopFlag;			//アニメーションのループフラグ

		KEY_ANIME m_Anime[KEY_MAX];
		KEY_ANIME m_Anime2[KEY_MAX];

		void Linear(void);

		bool m_BlendFlag;		//モーションブレンドのフラグ

		float m_Ratios;		//比率

		int m_Key;
		bool m_PunchFlag;

		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		D3DXVECTOR3 m_RotDest;					//目的の向き


		D3DXVECTOR3 GimmickPos[4];	//ギミックの4頂点の座標
		static CFade* m_pFade;		//フェードのポインタ
		static CPlayer* m_pFlag;	//
		CScene* m_pSceneLink;		//ギミックとのリンク

		bool m_Moving;							//モデルが動いてるか
		float m_fDiffRotY;
		bool m_JFlag;	//ジャンプフラグ

		static bool m_RotFlag;		//回転フラグ
		int m_BulletCnt;

};

#endif
















////=============================================================================
////
//// モデルの動き [MotionModel.h]
//// Author : 稲澤俊和
////
////=============================================================================
//#ifndef _MOTIONMODEL_H_
//#define _MOTIONMODEL_H_
//
////=============================================================================
//// インクルード
////=============================================================================
//#include "main.h"
//#include "Scene.h"
////=============================================================================
//// マクロ定義
////=============================================================================
//#define PART_MAX (10)	//パーツの最大数
//#define KEY_MAX (3)		//キーフレームの最大数
//#define MOVE_SPEED (0.5f)
//
//struct KEY_DATA
//{
//	D3DXVECTOR3 Pos;
//	D3DXVECTOR3 Scl;
//	D3DXVECTOR3 Rot;
//};
//
//struct KEY_ANIME
//{
//	int Frame;				//次のキーまでのフレーム数
//	KEY_DATA Key[PART_MAX];
//};
//
////前方宣言
//class CRenderer;
//class CSubModel;
//class CScene3D;
////=============================================================================
////CMotionModelクラス
////=============================================================================
//class CMotionModel:public CScene
//{
//	public:
//		CMotionModel(OBJTYPE nObjType,int nPriority=3);
//		~CMotionModel();
//		HRESULT Init(CRenderer* pRenderer);
//		void Uninit(void);
//		void Update(void);
//		void Draw(void);
//		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};
//
//		void PartsInit(void);
//		void DrawDebug(void);
//		void WaitMotion(void);		//待機モーション
//		void WaitMotion2(void);
//		void RunningMotion(void);	//ランニングモーション
//		void PunchMotion(void);		//パンチモーション
//		void DownMotion(void);		//やられモーション
//
//		static CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
//		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//座標の設定
//		D3DXVECTOR3 GetPos(void){return m_Pos;};				//座標の取得
//		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
//		D3DXVECTOR3 GetRot(void){return m_Rot;}				//回転の取得
//		void CMotionModel::WriteAnime(void);				//アニメの書き出し
//
//		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//前フレの座標の設定
//		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//前フレの座標の取得
//
//		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//前フレの角度の設定
//		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//前フレの角度の取得
//
//		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
//		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};
//
//	private:
//		LPDIRECT3DDEVICE9 m_pDevice;
//		D3DXVECTOR3 m_Rot;				//モデルの向き
//		D3DXVECTOR3 m_Scl;				//モデルの大きさ
//		D3DXVECTOR3 m_Pos;				//モデルの座標
//		D3DXMATRIX m_mtxWorld;			//ワールドマトリックス
//		static CRenderer* m_pMotion;
//
//		CSubModel* m_Part[PART_MAX];
//		CSubModel* m_Part2[PART_MAX];
//
//		int m_MotionKey;
//
//		float m_MotionTime;
//		int m_KeyMax;
//		bool m_AnimLoopFlag;			//アニメーションのループフラグ
//
//		KEY_ANIME m_Anime[KEY_MAX];
//		KEY_ANIME m_Anime2[KEY_MAX];
//
//		void Linear(void);
//
//		bool m_BlendFlag;		//モーションブレンドのフラグ
//
//		float m_Ratios;		//比率
//
//		int m_Key;
//		bool m_PunchFlag;
//
//		D3DXVECTOR3 m_PosOld;						//ポリゴンの座標
//		D3DXVECTOR3 m_RotOld;						//ポリゴンの回転角度
//		D3DXVECTOR3 m_VtxMin;
//		D3DXVECTOR3 m_VtxMax;
//
//};
//
//#endif