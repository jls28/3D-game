//=============================================================================
//
// メイン処理 [Scene.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_


#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define LIST_NUM (8)

//オブジェクトの種類
typedef enum
{
	OBJTYPE_NONE=0,
	OBJTYPE_2D,
	OBJTYPE_3D,
	OBJTYPE_BILLBOARD,
	OBJTYPE_ENEMY,
	OBJTYPE_PLAYER,
	OBJTYPE_X,
	OBJTYPE_MESHWALL,
	OBJTYPE_MESHFIELD,
	OBJTYPE_MESHMAGMA,
	OBJTYPE_DOME,
	OBJTYPE_CYLINDER,
	OBJTYPE_BULLET,
	OBJTYPE_EXPLOSION,
	OBJTYPE_GIMMICK,
	OBJTYPE_FADE,
	OBJTYPE_SCORE,
	OBJTYPE_TIMER,
	OBJTYPE_SHADOW,
	OBJTYPE_TARGET,
	OBJTYPE_TAILBALL,
	OBJTYPE_LEG,
	OBJTYPE_NEEDLE,
	OBJTYPE_EFFECT,
	OBJTYPE_FIREBALL,
	OBJTYPE_MOTIONMODEL
}OBJTYPE;

//前方宣言
class CRenderer;

//=============================================================================
//CSceneクラス
//=============================================================================
class CScene
{
	public:
		CScene(OBJTYPE nObjType,int nPriority =3);
		virtual ~CScene();

		virtual HRESULT Init(CRenderer* m_pRenderer) = 0;
		virtual void Uninit(void) = 0;
		virtual void Draw(void) = 0;
		virtual void Update(void) = 0;

		virtual void SetPos(float x,float y,float z)=0;
		virtual D3DXVECTOR3 GetPos(void)=0;

		virtual void SetRot(float x,float y,float z)=0;
		virtual D3DXVECTOR3 GetRot(void)=0;

		virtual void SetPositionOld(float x,float y,float z)=0;
		virtual D3DXVECTOR3 GetPositionOld(void)=0;

		virtual void SetRotitionOld(float x,float y,float z)=0;
		virtual D3DXVECTOR3 GetRotitionOld(void)=0;

		virtual D3DXVECTOR3 GetVertexMin(void)=0;
		virtual D3DXVECTOR3 GetVertexMax(void)=0;

		static void UpdateAll(void);
		static void DrawAll(void);
		static void ReleaseAll(void);

		void UnlinkList(void);

		void Release(void);

		D3DXVECTOR3 CrossProduct(D3DXVECTOR3 Vector1,D3DXVECTOR3 Vector2,D3DXVECTOR3 Vector3);

		static CScene* GetScene(OBJTYPE Obj);

		OBJTYPE GetObjType(void){return m_ObjType;};

		static void SetPauseFlag(bool PauseFlag){m_PauseFlag=PauseFlag;};	//ポーズの設定
		static bool GetPauseFlag(void){return m_PauseFlag;};				//ポーズフラグの取得


	private:
		//リスト管理用
		static CScene* m_pTop[LIST_NUM];		//リストの先頭アドレス
		static CScene* m_pCur[LIST_NUM];		//リストの現在位置のアドレス

		CScene* m_pPrev;						//前のオブジェクトへのアドレス
		CScene* m_pNext;						//次のオブジェクトへのアドレス

		bool m_bDelete;							//オブジェクト削除フラグ

		int m_nPriority;						//プライオリティ

		OBJTYPE m_ObjType;
		static bool m_PauseFlag;				//ポーズフラグ

};
#endif