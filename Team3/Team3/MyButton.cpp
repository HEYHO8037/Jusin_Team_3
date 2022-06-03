#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton(const float& _fX, const float& _fY, const GAMESCENE& _eButton)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_tInfo.fCX = 170.f;
	m_tInfo.fCY = 70.f;
	m_bDead = false;
	m_eButton = _eButton;
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{

}

int CMyButton::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tRect = {
		LONG(m_tInfo.fX - m_tInfo.fCX*0.5f),
		LONG(m_tInfo.fY - m_tInfo.fCY*0.5f),
		LONG(m_tInfo.fX + m_tInfo.fCX*0.5f),
		LONG(m_tInfo.fY + m_tInfo.fCY*0.5f)
	};
	return OBJ_NOEVENT;
}

void CMyButton::LateUpdate(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);



	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			switch (m_eButton)
			{
			case GAME_JUNKYU:
				CSceneMgr::Get_Instance()->Set_SceneID(GAME_JUNKYU);
				break;
			case GAME_SEOKGYUN:
				CSceneMgr::Get_Instance()->Set_SceneID(GAME_SEOKGYUN);
				break;
			case GAME_HAEHO:
				CSceneMgr::Get_Instance()->Set_SceneID(GAME_HAEHO);
				break;
			case GAME_SON:
				CSceneMgr::Get_Instance()->Set_SceneID(GAME_SON);
				break;
			}
			return;
		}
	}


}

void CMyButton::Render(HDC hDC)
{

	Rectangle(hDC, 
		LONG(m_tInfo.fX - m_tInfo.fCX*0.5f),
		LONG(m_tInfo.fY - m_tInfo.fCY*0.5f),
		LONG(m_tInfo.fX + m_tInfo.fCX*0.5f),
		LONG(m_tInfo.fY + m_tInfo.fCY*0.5f)
		);

}

void CMyButton::Release(void)
{

}
