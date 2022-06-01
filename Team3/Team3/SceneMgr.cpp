#include "stdafx.h"
#include "SceneMgr.h"

#include "Game_HAEHO.h"
#include "Game_JUN.h"
#include "Game_SEOK.h"
#include "Game_SON.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(GAME_MENU), m_ePreScene(GAME_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

// FSM(finite state machine) : 유한 상태 기계, 자신이 취할 수 있는 유한한 개수의 상태

void CSceneMgr::Scene_Change(GAMESCENE eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case GAME_MENU:
			m_pScene = new CMyMenu;
			break;

		case GAME_JUNKYU:
			m_pScene = new CGame_JUN;
			break;

		case GAME_SEOKGYUN:
			m_pScene = new CGame_SEOK;
			break;

		case GAME_HAEHO:
			m_pScene = new CGame_HAEHO;
			break;

		case GAME_SON:
			m_pScene = new CGame_SON;
			break;
		}

	 m_pScene->Initialize();
	 m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
