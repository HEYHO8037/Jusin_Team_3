#include "stdafx.h"
#include "MyMenu.h"
#include "KeyMgr.h"
#include "UIManager.h"

CMyMenu::CMyMenu()
{
	for (auto& iter : m_pGameStart)
	{
		iter = nullptr;
	}
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	for (int i = 1; i < GAME_END ; ++i)
	{
		m_pGameStart[i-1] = new CMyButton(200.f, 100.f * float(i), GAMESCENE(i));
	}
}

void CMyMenu::Update(void)
{
	for (auto& iter : m_pGameStart)
	{
		iter->Update();
	}
}

void CMyMenu::LateUpdate(void)
{
	for (auto& iter : m_pGameStart)
	{
		iter->LateUpdate();
	}
}

void CMyMenu::Render(HDC hDC)
{
	for (auto& iter : m_pGameStart)
	{
		iter->Render(hDC);
	}
}

void CMyMenu::Release(void)
{
	for (auto& iter : m_pGameStart)
	{
		Safe_Delete(iter);
	}
}


