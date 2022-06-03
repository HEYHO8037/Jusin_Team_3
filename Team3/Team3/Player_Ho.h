#pragma once
#include "Obj.h"
class CPlayer_Ho :
	public CObj
{
public:
	CPlayer_Ho();
	virtual ~CPlayer_Ho();

public:
	virtual		void	Initialize(void)	override;
	virtual		int		Update(void)		override;
	virtual		void	LateUpdate(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

public:
	D3DXVECTOR3 Get_GunPoint() { return m_vGunPoint; }
	D3DXVECTOR3 Get_PovRayCast() { return m_PovRaycast; }
	D3DXVECTOR3* Get_Point() { return m_vPoint; }

private:
	void Key_Input(void);


private:
	D3DXMATRIX			matGunWorld;

	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint;
	D3DXVECTOR3			m_vOriginGunPoint;

	D3DXVECTOR3			m_PovRaycast;

	float				m_fGunAngle = 0.f;


};

