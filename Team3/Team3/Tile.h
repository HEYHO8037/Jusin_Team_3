#pragma once

#include "Obj.h"

class CTile :	public CObj
{
public:
	CTile();
	CTile(int _iIndex);
	virtual ~CTile();

public:
	const int& Get_Option(void) { return m_iOption; }
public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }
	void		Set_TMap(void) { m_bTMap = true; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int			m_iOption;
	bool		m_bTMap;
};