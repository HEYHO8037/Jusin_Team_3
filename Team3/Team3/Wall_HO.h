#pragma once
#include "Obj.h"
class CWall_HO :
	public CObj
{
public:
	CWall_HO();
	CWall_HO(float fX, float fY);
	virtual ~CWall_HO();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	LateUpdate(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

public:
	D3DXVECTOR3* Get_Point() { return m_vPoint; }


private:
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vOriginPoint[4];
};

