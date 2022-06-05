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

	const float& Get_Range()
	{
		return m_vWorldRange;
	}

	D3DXVECTOR3& Get_ColPos()
	{
		return m_vColPos_World;
	}

	void Set_GameOver(const bool& _bGameOver)
	{
		m_bGameOver = _bGameOver;
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

	D3DXVECTOR3 m_vColPos_World;
	D3DXVECTOR3 m_vColPos_Local;

	float m_vWorldRange;

	bool m_bGameOver;
};

