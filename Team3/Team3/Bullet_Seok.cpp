#include "stdafx.h"
#include "Bullet_Seok.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CBullet_Seok::CBullet_Seok()
{
}


CBullet_Seok::~CBullet_Seok()
{
	Release();
}

void CBullet_Seok::Initialize(void)
{
	m_tInfo.fCX = 20.f;;

	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_bThrow = true;
	m_fThrowPower = 15.f;
	m_fThrowTime = 0.f;
}

int CBullet_Seok::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	m_tInfo.vDir = { sinf(m_fAngle),-cosf(m_fAngle), 0.f };
 	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed ;

	Line_Collision();
	Throw();
	return 0;
}

void CBullet_Seok::LateUpdate(void)
{
}

void CBullet_Seok::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Ellipse(hDC,
		int(m_tInfo.vPos.x+iScrollX+ - 10.f),
		int(m_tInfo.vPos.y + iScrollY - 10.f),
		int(m_tInfo.vPos.x + iScrollX + 10.f),
		int(m_tInfo.vPos.y + iScrollY +10.f));
}

void CBullet_Seok::Release(void)
{

}

void CBullet_Seok::Set_Damage(void)
{
	Set_Dead();
}

void CBullet_Seok::Throw()
{
	float		fY = 0.f;

	if (m_bThrow)
	{
		m_tInfo.vPos[1] -=  (-9.8f) * m_fThrowTime * m_fThrowTime * 0.5f;
		m_fThrowTime += 0.1f;

	}
}

void CBullet_Seok::Line_Collision(void)
{

	float		fY = -500.f;

	bool bLineCol = CLineMgr::Get_Instance()->Collision_VerticalLine(m_tInfo.vPos.x, m_tInfo.vPos.y, &fY);

	if (bLineCol)
	{
 		Set_Dead();
	}
	if (fY>= m_tInfo.vPos.y)
	{
		Set_Dead();
	}
	
}
