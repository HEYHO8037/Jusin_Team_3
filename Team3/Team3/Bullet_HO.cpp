#include "stdafx.h"
#include "Bullet_HO.h"
#include "Player_Ho.h"


CBullet_HO::CBullet_HO()
{
}

CBullet_HO::CBullet_HO(float fX, float fY, D3DXVECTOR3 vDir, BULLET_TYPE eBullet)
{
	m_tInfo.vPos = { fX, fY, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_vDir = vDir;
	m_eBulletType = eBullet;

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_fSpeed = 3.f;

	m_bIsRender = true;
}


CBullet_HO::~CBullet_HO()
{
}

void CBullet_HO::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 5.f,  m_tInfo.vPos.y - 5.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 5.f,  m_tInfo.vPos.y - 5.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 5.f,  m_tInfo.vPos.y + 5.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 5.f,  m_tInfo.vPos.y + 5.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_fSpeed = 3.f;

}

int CBullet_HO::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	m_tInfo.vPos += m_vDir;





	return OBJ_NOEVENT;
}

void CBullet_HO::LateUpdate(void)
{
	if (m_eBulletType == MONSTER_BULLET)
	{
		D3DXVECTOR3 Dir = m_vPoint[0] - m_pTarget->Get_Info().vPos;

		if (abs(Dir.x) <= 100 && abs(Dir.y) <= 100)
		{
			m_bIsRender = true;
			return;
		}
		else
		{
			m_bIsRender = false;
		}
	}

}

void CBullet_HO::Render(HDC hDC)
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
	}

}

void CBullet_HO::Release(void)
{
}
