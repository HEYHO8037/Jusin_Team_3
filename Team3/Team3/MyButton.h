#pragma once
#include "Obj.h"
class CMyButton : public CObj
{
public:
	CMyButton(const float& _fX, const float& _fY, const GAMESCENE& _eButton);
	virtual ~CMyButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_Click()
	{
		m_bClick = true;
	}

private:
	GAMESCENE m_eButton;
	bool	  m_bClick;
};

