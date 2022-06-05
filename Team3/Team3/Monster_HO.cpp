#include "stdafx.h"
#include "Monster_HO.h"
#include "Bullet_HO.h"
#include "ObjMgr.h"

CMonster_HO::CMonster_HO()
{
}


CMonster_HO::~CMonster_HO()
{
}

void CMonster_HO::Initialize(void)
{
	m_tInfo.vPos = { 600.f, 500.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 25.f,  m_tInfo.vPos.y - 25.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 25.f,  m_tInfo.vPos.y - 25.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 25.f,  m_tInfo.vPos.y + 25.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 25.f,  m_tInfo.vPos.y + 25.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	// 포신
	m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 50.f, 0.f };

	m_vOriginGunPoint = m_vGunPoint;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixIdentity(&matTrans);


	m_fSpeed = 5.f;

	m_bIsRender = false;
	TickCount = NULL;

}

int CMonster_HO::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.vPos.z = 0.f;

	m_tInfo.vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fGunAngle = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float m_fGunAngle = acosf(fGunAngle);

	if (m_tInfo.vPos.x > m_pTarget->Get_Info().vPos.x)
		m_fGunAngle *= -1.f;


	D3DXMATRIX		GunMatScale, GunMatRotZ, GunMatTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixRotationZ(&GunMatRotZ, m_fGunAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);


	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	matGunWorld = matScale * GunMatRotZ* matTrans;


	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 600.f, 500.f, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	m_vGunPoint = m_vOriginGunPoint;

	m_vGunPoint -= { 600.f, 500.f, 0.f };
	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &matGunWorld);

	if (!TickCount)
	{
		TickCount = GetTickCount();
	}
	else
	{
		DWORD Tick = GetTickCount();

		if (Tick - TickCount > 1000)
		{
			TickCount = GetTickCount();
			if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).empty())
			{
				CBullet_HO* pBullet = new CBullet_HO(m_vGunPoint.x, m_vGunPoint.y, m_tInfo.vDir, MONSTER_BULLET);
				pBullet->Set_Target(CObjMgr::Get_Instance()->Get_Player());
				CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
			}
		}
	}


	return OBJ_NOEVENT;

}

void CMonster_HO::LateUpdate(void)
{
}

void CMonster_HO::Render(HDC hDC)
{
	if (m_bIsRender)
	{
		MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

		for (int i = 0; i < 4; ++i)
		{
			LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

			if (i > 0)
				continue;

		}

		LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

		// 포신 그리기

		MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);

		LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);
	}
}

void CMonster_HO::Release(void)
{
}
