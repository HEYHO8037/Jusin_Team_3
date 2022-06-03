#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_eDir(DIR_END)
	, m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixIdentity(&m_tInfo.matWorldP);

	/*for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&m_vArray[i], sizeof(D3DXVECTOR3));
		ZeroMemory(&m_vArrayRender[i], sizeof(D3DXVECTOR3));
	}*/
}

CObj::~CObj()
{
}