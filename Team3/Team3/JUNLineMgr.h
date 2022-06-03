#pragma once
#include "Include.h"

#include "JUNLine.h"
#include "LongLine.h"

class CJUNLineMgr
{
public:
	CJUNLineMgr();
	~CJUNLineMgr();


public:
	void Initialize(void);
	void Update(void);
	void LateUpdate(void);
	void Render(HDC hDC);
	void Release(void);

public:
	static CJUNLineMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CJUNLineMgr;
		}
		return m_pInstance;
	}

	static void Destroy(void)
	{
		if (m_pInstance)
		{
			Safe_Delete(m_pInstance);
		}
	}


private:
	static CJUNLineMgr* m_pInstance;

	CLongLine* m_pLongLine;

	list<CJUNLine*> m_listJUNLine;

	DWORD m_dwLineCreate;

};

