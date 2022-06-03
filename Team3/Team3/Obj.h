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

	void		Set_Dead() { m_bDead = true; }

	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void		Set_Dead(bool bDead) { m_bDead = bDead; }

	void		Set_Angle(float _Angle) { m_fAngle = _Angle; }

	void		Set_Speed(float _Speed) { m_fSpeed = _Speed; }

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

	D3DXMATRIX matScale;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;

	bool		m_bDead;

	float		m_fAngle;
	float		m_fSpeed;
};

