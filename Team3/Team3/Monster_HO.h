#pragma once
#include "Obj.h"
class CMonster_HO :
	public CObj
{
public:
	CMonster_HO();
	virtual ~CMonster_HO();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	LateUpdate(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

public:
	void		Set_Target(CObj* pPlayer) { m_pTarget = pPlayer; }
	const bool&	 Get_bIsRender() { return m_bIsRender;  }
	void	Set_bIsRender(bool bIsRender) { m_bIsRender = bIsRender;  }
	D3DXVECTOR3* Get_Point() { return m_vPoint; }

private:
	DWORD				TickCount;
	
	CObj*				m_pTarget;

	D3DXMATRIX			matGunWorld;

	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint;
	D3DXVECTOR3			m_vOriginGunPoint;

	float				m_fGunAngle = 0.f;

	bool				m_bIsRender;


};

