#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"

#include "BmpMgr_3.h"

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

	//CSceneMgr::Get_Instance()->Scene_Change(GAME_JUNKYU);

	//CSceneMgr::Get_Instance()->Scene_Change(GAME_SON);

	CBmpMgr_3::Get_Instance()->Initialize();

	hBackDC = CBmpMgr_3::Get_Instance()->Find_Image(L"BACK");

	hGroundDC = CBmpMgr_3::Get_Instance()->Find_Image(L"GROUND");

#if(0)
	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif



	//CSceneMgr::Get_Instance()->Scene_Change(GAME_HAEHO);
	CSceneMgr::Get_Instance()->Scene_Change(GAME_MENU);

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
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	
	CSceneMgr::Get_Instance()->Render(hBackDC);
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hDC);
}