#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

public:
	const int&	Get_Point(void) const { return m_iPoint; }
	void		SetStopDelete(void) { m_StopDelete = true; }
	void		Add_Tile(int _iIndex);
	bool		Get_Tile(int _iIndex) { if (nullptr != m_vecTile[_iIndex]) { return true; } else { return false; } }
	void		Picking_Tile(POINT _pt, const int& _iDrawID, const int& _iOption);
	void		Save_Tile(void);
	void		Load_Tile(void);

public:
	static		CTileMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTileMgr;
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
	static CTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;

	int						m_iArray[10];
	bool					m_StopDelete;

	int						m_iPoint;
	int						m_iPointCheak;
};

