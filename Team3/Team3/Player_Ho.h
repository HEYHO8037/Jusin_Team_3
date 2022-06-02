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

private:
	void Key_Input(void);


private:
	D3DXMATRIX			matGunWorld;

	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint;
	D3DXVECTOR3			m_vOriginGunPoint;

	float				m_fGunAngle = 0.f;


};

