#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"


CTile::CTile()
{
}

CTile::CTile(int _iIndex)
{
	m_iDrawID = _iIndex;
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tInfo.vPos.x = float((m_iDrawID % TILEX) * TILECX + (TILECX / 2));
	m_tInfo.vPos.y = float((m_iDrawID / TILEX) * TILECY + (TILECY / 2));
	m_iLocationIndex = m_iDrawID;
	m_iOption = 0;
	m_bTMap = false;
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	m_tInfo.matWorld = matScale * matRotZ;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	
	return OBJ_NOEVENT;
}

void CTile::LateUpdate(void)
{
	m_tInfo.vPos.x = float((m_iDrawID % TILEX) * TILECX + (TILECX / 2));
	m_tInfo.vPos.y = float((m_iDrawID / TILEX) * TILECY + (TILECY / 2));
}

void CTile::Render(HDC hDC)
{
	if (m_bTMap)
	{
		Rectangle(hDC, (int)m_tInfo.vPos.x - (TILECX / 2), (int)m_tInfo.vPos.y - (TILECY / 2), (int)m_tInfo.vPos.x + (TILECX / 2), (int)m_tInfo.vPos.y + (TILECY / 2));
	}
	else
	{
		SelectObject(hDC, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hDC, RGB(0, 0, 0));
		Rectangle(hDC, (int)m_tInfo.vPos.x - (TILECX / 2), (int)m_tInfo.vPos.y - (TILECY / 2), (int)m_tInfo.vPos.x + (TILECX / 2), (int)m_tInfo.vPos.y + (TILECY / 2));
		SetDCBrushColor(hDC, RGB(255, 255, 255));
	}
}

void CTile::Release(void)
{
	
}

void CTile::Set_Damage(void)
{
}
