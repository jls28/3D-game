//=============================================================================
//
// ゲーム処理 [Game.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
typedef enum
{
	GAME=0,
	PAUSE,
	MAX
}GAME_MODE;

#define LEG_MAX (6)
#define TARGET_MAX (6)
#define FIREBALL_MAX (5)

//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CPlayer;
class CGimmick;
class CFade;
class CField;
class CPause;
class CMotionModel;
class CNeedle;
class CTailBall;
class CCollision;
class CTarget;
class CMagma;
class CGoal;
class CCreateFire;
class CFireball;
class CLeg;

//=============================================================================
//Gameクラス
//=============================================================================
class CGame
{
	//公開メンバ
	public:
		CGame();		//コンストラクタ
		~CGame();		//デストラクタ

		HRESULT Init(CRenderer* pRenderer);		//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画

		static CField* GetField(void){return pMeshField;};		//フィールドのポインタの取得
		static CPlayer* GetPlayer(void){return m_pPlayer2;};	//自機のポインタの取得
		static CGimmick* GetGimmick(void){return m_pGimmick;};	//ギミックのポインタの取得
		static CMotionModel* GetMotionModel(void){return m_pMotion;};	//ギミックのポインタの取得
		static CNeedle* GetNeedle(void){return m_pNeedle;};			//
		static CTailBall* GetTailBall(void){return m_pTailBall;};	//
		static CCollision* GetCollision(void){return m_pCollision;};
		static CTarget* GetTarget(int num){return m_pTarget[num];};			//フェードのポインタの取得
		static CGoal* GetGoal(void){return m_pGoal;}
		static CMagma* GetMagma(void){return m_pMagma;}

	//非公開メンバ
	private:
		static CPlayer* m_pPlayer2;				//自機のポインタ
		static CGimmick* m_pGimmick;			//ギミックのポインタ
		CFade* m_pFade;							//フェードのポインタ
		static CField* pMeshField;				//フィールドノポインタ
		static CMagma* m_pMagma;
		static CRenderer* m_pRenderer;
		bool PauseFlag;							//ポーズフラグ
		static GAME_MODE m_Phase;
		static GAME_MODE m_Nextphase;
		CPause* m_pPause;
		D3DXVECTOR3 ClearPos;
		static CMotionModel* m_pMotion;
		static CNeedle* m_pNeedle;
		static CTailBall* m_pTailBall;
		static CCollision* m_pCollision;
		static CTarget* m_pTarget[TARGET_MAX];
		static CGoal* m_pGoal;
		static CFireball* m_pFireball[FIREBALL_MAX];
		static CLeg* m_pLeg[LEG_MAX];




		static CCreateFire* m_pCreateFire;
		CCreateFire *lpFire;	//炎制御クラス



};

#endif