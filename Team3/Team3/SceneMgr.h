#pragma once

//#include "Stage.h"
#include "MyMenu.h"
#include "Tetris.h"
#include "Game_SEOK.h"
#include "Scene.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(GAMESCENE eID);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	GAMESCENE		Get_SceneID(void) { return m_eCurScene; }

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;

	GAMESCENE					m_eCurScene;
	GAMESCENE					m_ePreScene;

};

