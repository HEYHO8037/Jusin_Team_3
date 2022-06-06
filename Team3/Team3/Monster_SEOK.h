#pragma once
#include "Obj.h"
class CMonster_SEOK :
	public CObj
{
public:
	CMonster_SEOK();
	~CMonster_SEOK();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void	LateUpdate(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void    Set_Damage(void) override;
public:

	void		OffSet(void);
private:
	void		Key_Input(void);
	void		Drop(void);
	void		Line_Ride(void);
private:
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint[4];
	D3DXVECTOR3			m_vOriginGunPoint[4];

	D3DXVECTOR3			m_vBulletPoint;

	D3DXVECTOR3			m_vPowerPoint[4];
	D3DXVECTOR3			m_vOriginPowerPoint[4];

	D3DXVECTOR3			m_vHpPoint1[4];
	D3DXVECTOR3			m_vOriginHpPoint1[4];
	D3DXVECTOR3			m_vHpPoint2[4];
	D3DXVECTOR3			m_vOriginHpPoint2[4];
	D3DXVECTOR3			m_vHpPoint3[4];
	D3DXVECTOR3			m_vOriginHpPoint3[4];

	float				m_fGunAngle = 0.f;
	float				m_fGunSpeed; ;

	float                    fLineCol;
	double                   fCooltimeSec;
	double                   fCooltimeSec2;

	bool bAngledir;
	bool bMovedir;

	bool                     bMyturn = false;
};
