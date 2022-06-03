#pragma once
#include "Obj.h"
class CPlayer_JUN :
	public CObj
{
public:
	CPlayer_JUN();
	virtual ~CPlayer_JUN();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int	 Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;
	virtual void    Set_Damage(void) override;

private:
	D3DXVECTOR3 m_vBody[8];

	D3DXVECTOR3 m_vOriginBody[8];



};

