//=============================================================================
//
// ライト処理 [Light.cpp]
// Author : 稲澤俊和
//
//=============================================================================
#include "Light.h"
#include "Renderer.h"


//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{


}
//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{

}


//=============================================================================
// ライトの初期化
//=============================================================================
HRESULT CLight::InitLight(CRenderer* pRenderer)
{
	m_pDevice = pRenderer->GetDevice();	// デバイスへのポインタ
	D3DXVECTOR3 vecDir;

	//ライト１
	ZeroMemory(&m_aLight[0],sizeof(D3DLIGHT9));		//初期化
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	vecDir = D3DXVECTOR3(-1.0f,-1.0f,1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction,&vecDir);
	m_pDevice->SetLight(0,&m_aLight[0]);
	m_pDevice->LightEnable(0,TRUE);

	//ライト2
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	vecDir = D3DXVECTOR3(1.0f,1.0f,-1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction,&vecDir);
	m_pDevice->SetLight(1,&m_aLight[1]);
	m_pDevice->LightEnable(1,TRUE);

	//ライト3
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	vecDir = D3DXVECTOR3(-1.0f,1.0f,-1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction,&vecDir);
	m_pDevice->SetLight(2,&m_aLight[2]);
	m_pDevice->LightEnable(2,TRUE);
	

	return S_OK;
}
