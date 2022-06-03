#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	CSceneMgr::Get_Instance()->Scene_Change(GAME_SEOKGYUN);
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	CSceneMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hDC);	
}