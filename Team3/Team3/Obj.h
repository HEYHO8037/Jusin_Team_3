#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(D3DXVECTOR3 _vPos)
	{
		m_tInfo.vPos = _vPos;
	}
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	//const RENDERID	Get_RenderID(void) const { return m_eRender; }

	void		Set_Dead() { m_bDead = true; }

	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void		Set_Dead(bool bDead) { m_bDead = bDead; }

	void		Set_Angle(float _Angle) { m_fAngle = _Angle; }

	void		Set_Speed(float _Speed) { m_fSpeed = _Speed; }

	// Tetris Tile
	void Set_DrawID(int _iID) { m_iDrawID = _iID; }
	const int& Get_DrawID(void) const { return m_iDrawID; }
	const bool& Get_Move(void) const { return m_bStopMove; }

	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	LateUpdate(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;
	virtual     void    Set_Damage(void)    PURE;
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;

	//RENDERID	m_eRender;

	D3DXMATRIX matScale;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;


	// Tetris Tile
	int			m_iDrawID;
	int			m_iLocationIndex;
	bool		m_bStopMove;
	DWORD		m_dwDownTime;

	bool		m_bDead;

	float		m_fAngle;
	float		m_fSpeed;

};

