#include "stdafx.h"
#include "BmpMgr_3.h"

CBmpMgr_3* CBmpMgr_3::m_pInstance = nullptr;

CBmpMgr_3::CBmpMgr_3()
{

}


CBmpMgr_3::~CBmpMgr_3()
{
	Release();
}

void CBmpMgr_3::Initialize(void)
{
	Insert_Bmp(L"../Resource/BACK.bmp",L"BACK");
	Insert_Bmp(L"../Resource/GROUND.bmp", L"GROUND");
}

void CBmpMgr_3::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImageKey)
{
	auto& iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())
	{
		CMyBmp_3* pBmp = new CMyBmp_3;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImageKey, pBmp);
	}
}

HDC CBmpMgr_3::Find_Image(const TCHAR * pImageKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr_3::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
