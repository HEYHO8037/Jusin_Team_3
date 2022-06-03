#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"


CTile::CTile()
{
	/*int _X = int((m_tInfo.vPos.x + float(TILECX / 2)) / TILECX);

	int _Y = int((m_tInfo.vPos.y + float(TILECY / 2)) / TILECY);

	m_iLocationIndex = _Y * TILEX + _X;*/
}

CTile::CTile(int _iIndex)
{
	m_tInfo.vPos.x = float((_iIndex % TILEX) * TILECX);
	m_tInfo.vPos.y = float((_iIndex / TILEX) * TILECY);
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_iDrawID = 0;
	m_iOption = 0;
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, fAngle);
	m_tInfo.matWorld = matScale * matRotZ;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	
	return OBJ_NOEVENT;
}

void CTile::LateUpdate(void)
{
	
}

void CTile::Render(HDC hDC)
{
	Rectangle(hDC, m_tInfo.vPos.x - (TILECX / 2), m_tInfo.vPos.y - (TILECY / 2), m_tInfo.vPos.x + (TILECX / 2), m_tInfo.vPos.y + (TILECY / 2));
}

void CTile::Release(void)
{
	
}

void CTile::Set_Damage(void)
{
}
