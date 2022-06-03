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

	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void		Set_Dead(bool bDead) { m_bDead = bDead; }

	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	LateUpdate(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;

	D3DXMATRIX matScale;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;

	bool		m_bDead;

	float		m_fAngle;
	float		m_fSpeed;
};

