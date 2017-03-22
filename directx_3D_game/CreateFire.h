//////////////////////////////
//	[CreateFire.h]			//
//	炎を作成するクラス		//
//	2000.03.05	Y.Yutaka	//
//////////////////////////////

#ifndef _CREATEFIRE_H
#define _CREATEFIRE_H

#include <windows.h>

typedef struct stRGBTbl{
	int R,G,B;
} RGBTbl;

#define MAX_PARTICLECOU	1000

class CCreateFire
{
private:

	HDC OffScreenDC;
	HBITMAP OffScreenBMP;
	void *lpOSBits;
	HBITMAP OffScreenoldBMP;
	int ScrWidth,ScrHeight;

	bool CreateOffScreeen(int width,int height);

	//粒子のデータ
	typedef struct{
		float fx,fy;	//力の向き（加速度）
		int LifeCou;	//消去までのカウント
		float sx,sy;	//粒子の開始位置
		float x,y;		//粒子の位置
		float DiffTime;	//経過時間
		float Syusoku;	//炎のX方向が収束するための係数
	} PARTICLE;
	PARTICLE ParticleDat[MAX_PARTICLECOU];
	
	int StPosX,StPosY;	//発火の中心座標
	int StRenX,stRenY;	//発火の範囲
	double GravVal;		//重力値（地球の場合重力加速度=9.8）

	void DrawParticle(int x,int y,int col);	//粒子を描画する

public:
	CCreateFire();
	~CCreateFire();

	//初期化処理
	bool InitScreen(int width,int height);

	//パレットの色を取得する
	bool GetFirePal(int num,int *rR,int *rG,int *rB);

	//画像の転送
	void DrawImage(HDC hdc,int dx,int dy,int width,int height,int sx,int sy);

	//画面をクリア
	void ClearScreen();

	//発火の中心座標を指定
	void SetCenterPos(int sx, int sy);

	//１ターン分の炎の処理を行う
	void MoveFire(int PtCou,int PtLife,bool sFlag,double wind);

};

#endif
