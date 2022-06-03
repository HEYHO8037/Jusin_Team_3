#pragma once
#include "Obj.h"
class CItem_JUN :
	public CObj
{
public:
	CItem_JUN(const float& _fRandAngle);
	virtual ~CItem_JUN();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

private:
	D3DXVECTOR3		m_vWorldPos[4];
	D3DXVECTOR3		m_vLocalPos[4];

	D3DXVECTOR3		m_vWorldTrans;

	D3DXVECTOR3		m_vWorldCollision;
	D3DXVECTOR3		m_vLocalCollision;

	int		m_vWorldRange;
	int		m_vLocalRange;

	D3DXVECTOR3		m_vWorldDir;
	D3DXVECTOR3		m_vLocalDir;

	float m_fObjAngle_Player;
	float m_fObjAngle;

	float m_fRatio_X;
	float m_fRatio_Y;

	float m_fSpeed;

	float m_fAngle;
};

