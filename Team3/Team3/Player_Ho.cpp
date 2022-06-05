#include "stdafx.h"
#include "Player_Ho.h"
#include "Bullet_HO.h"
#include "ObjMgr.h"

CPlayer_Ho::CPlayer_Ho()
{
}


CPlayer_Ho::~CPlayer_Ho()
{
	Release();
}

void CPlayer_Ho::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
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
	m_iHP = 3;

}

int CPlayer_Ho::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Key_Input();

	POINT MousePos;

	GetCursorPos(&MousePos);
		ScreenToClient(g_hWnd, &MousePos);


	D3DXVECTOR3 vMousePos;
	vMousePos.x = MousePos.x;
	vMousePos.y = MousePos.y;
	vMousePos.z = 0.f;
	m_tInfo.vPos.z = 0.f;

	m_tInfo.vDir = vMousePos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fGunAngle = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float m_fGunAngle = acosf(fGunAngle);

	if (m_tInfo.vPos.x > vMousePos.x)
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

		m_vPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	m_vGunPoint = m_vOriginGunPoint;

	m_vGunPoint -= { 400.f, 300.f, 0.f };
	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &matGunWorld);

	m_PovRaycast = m_vGunPoint - m_tInfo.vPos;

	D3DXVec3Normalize(&m_PovRaycast, &m_PovRaycast);

	if (m_iHP <= 0)
	{
		m_bDead = true;
	}


	return OBJ_NOEVENT;
}

void CPlayer_Ho::LateUpdate(void)
{
}

void CPlayer_Ho::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 0)
			continue;

		Ellipse(hDC,
			(int)m_vPoint[i].x - 5.f,
			(int)m_vPoint[i].y - 5.f,
			(int)m_vPoint[i].x + 5.f,
			(int)m_vPoint[i].y + 5.f);
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	// 포신 그리기

	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);

	LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);

}



void CPlayer_Ho::Release(void)
{
}

void CPlayer_Ho::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('S'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('A'))
		m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('D'))
		m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		CBullet_HO* Bullet = new CBullet_HO(m_vGunPoint.x, m_vGunPoint.y, m_PovRaycast, PLAYER_BULLET);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Bullet);
	}

}
