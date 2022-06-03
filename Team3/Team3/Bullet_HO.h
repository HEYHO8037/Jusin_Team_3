#pragma once
#include "Obj.h"
class CBullet_HO :
	public CObj
{
public:
	CBullet_HO();
	CBullet_HO(float fX, float fY, D3DXVECTOR3 vDir, BULLET_TYPE eBullet);
	virtual ~CBullet_HO();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	LateUpdate(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

public:
	const bool&	 Get_bIsRender() { return m_bIsRender; }
	void	Set_bIsRender(bool bIsRender) { m_bIsRender = bIsRender; }
	BULLET_TYPE Get_Type() { return m_eBulletType; }
	void		Set_Target(CObj* pPlayer) { m_pTarget = pPlayer; }
	D3DXVECTOR3* Get_Point() { return m_vPoint; }

private:
	CObj*				m_pTarget;
	bool				m_bIsRender;
	BULLET_TYPE			m_eBulletType;
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vOriginPoint[4];


};

