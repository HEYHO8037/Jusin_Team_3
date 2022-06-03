#include "stdafx.h"
#include "Monster_SEOK.h"
#include "Bullet_Seok.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"

CMonster_SEOK::CMonster_SEOK()
{
}


CMonster_SEOK::~CMonster_SEOK()
{
	Release();
}

void CMonster_SEOK::Initialize(void)
{
	m_tInfo.fCX = 50.f;;

	m_tInfo.vPos = { 1600.f, 400.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vFall = { 0.f, 1.f, 0.f };

	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 25.f,  m_tInfo.vPos.y - 25.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 25.f,  m_tInfo.vPos.y - 25.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 25.f,  m_tInfo.vPos.y + 25.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 25.f,  m_tInfo.vPos.y + 25.f, 0.f };


	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_vGunPoint[0] = { m_tInfo.vPos.x + 5.f,  m_tInfo.vPos.y - 5.f, 0.f };
	m_vGunPoint[1] = { m_tInfo.vPos.x + 45.f,  m_tInfo.vPos.y - 5.f, 0.f };
	m_vGunPoint[2] = { m_tInfo.vPos.x + 45.f,  m_tInfo.vPos.y + 5.f, 0.f };
	m_vGunPoint[3] = { m_tInfo.vPos.x + 5.f,  m_tInfo.vPos.y + 5.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginGunPoint[i] = m_vGunPoint[i];

	m_vBulletPoint = { 0.f,  0.f, 0.f };

	m_fSpeed = 20.f;

	m_fAngle = 1.57f;

	m_fGunAngle = 0.f;

	m_fGunSpeed = 20.f;

	fCooltimeSec = GetTickCount();
	fCooltimeSec2 = GetTickCount();

	bAngledir = true;
	bMovedir = true;
}

int CMonster_SEOK::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	D3DXMATRIX		matScaleP, matRotZP, matTransP;

	D3DXMatrixScaling(&matScaleP, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZP, m_fAngle);
	D3DXMatrixTranslation(&matTransP, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorldP = matScaleP * matRotZP * matTransP;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 1600.f, 400.f, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorldP);
	}

	D3DXMATRIX		matGunScale, matGunRotZ, matGunsTrans;

	D3DXMatrixScaling(&matGunScale, -1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matGunRotZ, m_fGunAngle);
	D3DXMatrixTranslation(&matGunsTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matGunWorld = matGunScale * matGunRotZ * matGunsTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vGunPoint[i] = m_vOriginGunPoint[i];

		m_vGunPoint[i] -= { 1600.f, 400.f, 0.f };
		D3DXVec3TransformCoord(&m_vGunPoint[i], &m_vGunPoint[i], &m_tInfo.matGunWorld);
	}

	Key_Input();


	return 0;

}

void CMonster_SEOK::LateUpdate(void)
{
	Drop();
	Line_Ride();
}

void CMonster_SEOK::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HPEN hpen;
	HPEN hpenOld;

	hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));   // 선 스타일, 굵기, 색상
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);   // 펜 선택
	MoveToEx(hDC, (int)m_vPoint[0].x + iScrollX, (int)m_vPoint[0].y + iScrollY, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x + iScrollX, (int)m_vPoint[i].y + iScrollY);

	}
	LineTo(hDC, m_vPoint[0].x + iScrollX, m_vPoint[0].y + iScrollY);
	hpen = (HPEN)SelectObject(hDC, hpenOld);   // 기존의 펜 다시 선택
	DeleteObject(hpen);   // 생성한 펜 삭제

	hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);
	MoveToEx(hDC, (int)m_vGunPoint[0].x + iScrollX, (int)m_vGunPoint[0].y + iScrollY, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vGunPoint[i].x + iScrollX, (int)m_vGunPoint[i].y + iScrollY);

	}
	LineTo(hDC, m_vGunPoint[0].x + iScrollX, m_vGunPoint[0].y + iScrollY);
	hpen = (HPEN)SelectObject(hDC, hpenOld);
	DeleteObject(hpen);

	hpen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);
	Ellipse(hDC,
		(int)m_vPoint[2].x + iScrollX - 20.f,
		(int)m_vPoint[2].y + 10 + iScrollY - 20.f,
		(int)m_vPoint[2].x + iScrollX + 20.f,
		(int)m_vPoint[2].y + 10 + iScrollY + 20.f);
	Ellipse(hDC,
		(int)m_vPoint[1].x + iScrollX - 20.f,
		(int)m_vPoint[1].y + iScrollY + 10 - 20.f,
		(int)m_vPoint[1].x + iScrollX + 20.f,
		(int)m_vPoint[1].y + iScrollY + 10 + 20.f);
	hpen = (HPEN)SelectObject(hDC, hpenOld);
	DeleteObject(hpen);

	m_vBulletPoint = { (m_vGunPoint[1].x  + m_vGunPoint[2].x) / 2,(m_vGunPoint[1].y  + m_vGunPoint[2].y) / 2, 0.f };//총알 발사 위치잡기

}

void CMonster_SEOK::Release(void)
{
}

void CMonster_SEOK::Set_Damage(void)
{
	Set_Dead();
}

void CMonster_SEOK::OffSet(void)
{
}

void CMonster_SEOK::Key_Input(void)
{
	if (fCooltimeSec + 500<GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERBULLET, CAbstractFactory<CBullet_Seok>::Create(m_vBulletPoint, (m_fGunAngle - 1.57f), m_fGunSpeed));

			if (bAngledir)
			{
				m_fGunAngle += D3DXToRadian(6.f);
				if (m_fGunAngle > -0.0753598790f)
				{
					bAngledir = false;

				}
			}
			else 
			{
				m_fGunAngle -= D3DXToRadian(6.f);
				if (m_fGunAngle < 1.30899668f)
				{
					bAngledir = true;
				}
			}
		fCooltimeSec = GetTickCount();
	}
	if (fCooltimeSec2 + 300<GetTickCount())
	{
		if (bMovedir)
		{
			if (true)
			{
				D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
				m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
				m_fAngle = fLineCol + 1.57f;
			}

		}
		else 
		{
			if (true)
			{
				D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
				m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
				m_fAngle = fLineCol + 1.57f;
			}
		}
		fCooltimeSec2 = GetTickCount();
	}
	if (GetAsyncKeyState('W'))
	{
		if (m_fGunAngle <1.30899668f)
		{
			m_fGunAngle += D3DXToRadian(3.f);
		}
	}

	if (GetAsyncKeyState('S'))
	{
		if (m_fGunAngle > -0.0753598790f)
		{
			m_fGunAngle -= D3DXToRadian(3.f);
		}
	}

	/*if (GetAsyncKeyState('A'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		m_fAngle = fLineCol + 1.57f;
		m_fGunAngle = fLineCol;
	}
	if (GetAsyncKeyState('D'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		m_fAngle = fLineCol + 1.57f;
		m_fGunAngle = fLineCol;
	}

	if (GetAsyncKeyState('Q'))
	{
		m_fAngle -= D3DXToRadian(3.f);
		m_fGunAngle -= D3DXToRadian(3.f);
	}

	if (GetAsyncKeyState('E'))
	{
		m_fAngle += D3DXToRadian(3.f);
		m_fGunAngle += D3DXToRadian(3.f);
	}*/
	//if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	//{
		//m_fGunSpeed = 10;
	//}

	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (fGunPowerCooltimeSec + 100 < GetTickCount())
		{
			if (m_fGunSpeed<50)
			{
				++m_fGunSpeed;
			}
			else if (m_fGunSpeed>10)
			{
				--m_fGunSpeed;
			}
			fGunPowerCooltimeSec = GetTickCount();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);*/
}

void CMonster_SEOK::Drop(void)
{
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vFall, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed - 1);
}

void CMonster_SEOK::Line_Ride(void)
{
	float		fY = 0.f;

	fLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos[0], m_tInfo.vPos[1], &fY);

	if (fLineCol)
	{
		m_tInfo.vPos.y = fY - 55;
	}
}
