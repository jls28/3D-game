//=============================================================================
//
// 自機モデル表示処理 [Player.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _NEEDLE_H_
#define _NEEDLE_H_

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
class CCollision;
class CRenderer;
class CTarget;
class CFade;
class CPlayer;

//=============================================================================
//CSceneXクラスを継承したCEnemyクラス
//=============================================================================
class CNeedle:public CSceneX
{
	//公開メンバ
	public:
		CNeedle(OBJTYPE nObjType,int nPriority=3);		//コンストラクタ
		~CNeedle();										//デストラクタ

		HRESULT Init(CRenderer* m_pRenderer);			//初期化
		void Uninit(void);								//終了
		void Update(void);								//更新
		void Draw(void);								//描画

		static CNeedle* CNeedle::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//生成

		void SetPosition(D3DXVECTOR3 Pos){m_PosDest = Pos;};								//座標の設定
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//座標の取得

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//回転の設定
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//回転の取得


		CScene* GetSceneLink(void){return m_pSceneLink;};		//ギミックのリンク

		static bool GetRotFlag(void){return m_RotFlag;};			//回転フラグの取得

		void AddRot(float x,float y,float z){m_Rot.x+=x;m_Rot.y+=y;m_Rot.z+=z;};			//回転の設定

		static CFade* GetGFade(void){return m_pFade;};			//フェードのポインタの取得

		int GetBulletCnt(void){return m_BulletCnt;};
		void SetBulletCnt(int i){m_BulletCnt=i;};

		bool GetHitFlag(void){return m_HitFlag;};
		void SetHitFlag(bool flag){m_HitFlag=flag;};

		void Shot(D3DXVECTOR3 vector);
		void Return(void);


	//非公開メンバ
	private:
		static CRenderer *m_pNeedle;			//プレイヤーのポインタ


		CScene* m_pSceneLink;		//ギミックとのリンク

		static CNeedle* m_pFlag;	//
		static CFade* m_pFade;		//フェードのポインタ

		bool m_Moving;							//モデルが動いてるか
		float m_fDiffRotY;
		bool m_JFlag;	//ジャンプフラグ

		// スピード
		D3DXVECTOR3 m_speed;

		static bool m_RotFlag;		//回転フラグ
		int m_BulletCnt;

		D3DXVECTOR3 m_PosDest;					//目的の向き

		CCollision* m_pCollision;
		CTarget* m_pTarget;
		CPlayer* m_pPlayer;

		bool m_HitFlag;
};

#endif

