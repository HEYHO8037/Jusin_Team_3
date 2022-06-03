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

	void Keyinput(void);

	void Set_Right(const bool& _Right)
	{
		m_bRight = _Right;
	}

	void Set_Left(const bool& _Left)
	{
		m_bLeft = _Left;
	}

	const bool& Get_Right()
	{
		return m_bRight;
	}

	const bool& Get_Left()
	{
		return m_bLeft;
	}

	const float& Get_ObjAngle()
	{
		return m_fObjAngle;
	}

	void Set_ObjAngle(const float& _fObjAngle)
	{
		m_fObjAngle += _fObjAngle;
	}

private:
	D3DXVECTOR3 m_vBody[9];

	D3DXVECTOR3 m_vOriginBody[9];

	float m_fObjAngle;

	int m_iDistance;
	bool m_bRight;
	bool m_bLeft;

	bool m_bJump;

	int m_iJump_Y;

};

