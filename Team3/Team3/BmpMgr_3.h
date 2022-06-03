#pragma once
#include "MyBmp_3.h"
#include "Include.h"

class CBmpMgr_3
{
public:
	CBmpMgr_3();
	~CBmpMgr_3();

public:
	void Initialize(void);
	void Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImageKey);
	HDC Find_Image(const TCHAR* pImageKey);
	void Release(void);



public:
	static CBmpMgr_3* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBmpMgr_3;
		}

		return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	static CBmpMgr_3* m_pInstance;
	map<const TCHAR*, CMyBmp_3*> m_mapBit;
	vector<HDC>	m_vecBit;
};