#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_eDir(DIR_END)
	, m_bDead(false)
	, m_fAngle(0)
	, m_bStopMove(false)
	, m_iDrawID(0)
	, m_iLocationIndex(0)
	, m_dwDownTime(GetTickCount())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixIdentity(&matTrans);
}

CObj::~CObj()
{
}