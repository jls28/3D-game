//=============================================================================
//
// 敵モデル表示処理 [Enemy.h]
// Author : 稲澤俊和
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// マクロ定義
//=============================================================================


class CRenderer;
//=============================================================================
//CSceneXを継承したCEnemyクラス
//=============================================================================
class CEnemy:public CSceneX
{
	//公開メンバ
	public:
		CEnemy(OBJTYPE nObjType,int nPriority =3);		//コンストラクタ
		~CEnemy();										//デストラクタ
		HRESULT Init(CRenderer* m_pRenderer);			//初期化	
		void Uninit(void);								//終了
		void Update(void);								//更新
		void Draw(void);								//描画

		static CEnemy* CEnemy::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);		//生成

	//非公開メンバ
	private:
		D3DXVECTOR3 m_Scl;
		static CSceneX *m_pSceneDummy;

};

#endif