#include "stdafx.h"
#include "JUNLineMgr.h"
#include "ObjMgr.h"

#include "RandomMgr.h"

CJUNLineMgr* CJUNLineMgr::m_pInstance = nullptr;


/*
플레이어 우측이 켜지면 30도 만큼 회전하고 다시 false로
플레이어 좌측이 켜지면 -30도 만큼 회전하고 다시 false로

이걸 플레이어 말고 전부 갖고있어야 하니까...
obj 매니저에서 함수 가져오고, -> ㄴㄴ 플레이어에서 30씩 넘겨줘
//그리고 1도 넘어올 때마다 4씩 이동

*/

CJUNLineMgr::CJUNLineMgr()
{
	m_pLongLine = new CLongLine;
	m_listJUNLine.push_back(new CJUNLine(CRandom::Random(0,7)*45.f));
	m_dwLineCreate = GetTickCount();
}


CJUNLineMgr::~CJUNLineMgr()
{
	Release();
}

void CJUNLineMgr::Initialize(void)
{
	
}

void CJUNLineMgr::Update(void)
{
	if (m_dwLineCreate + 60 < GetTickCount())
	{
		m_listJUNLine.push_back(new CJUNLine(CRandom::Random(0, 7)*45.f));
		m_dwLineCreate = GetTickCount();
	}

	m_pLongLine->Update();

	for (list<CJUNLine*>::iterator& iter = m_listJUNLine.begin();
		iter != m_listJUNLine.end(); )
	{
		if ((*iter)->Update() == OBJ_DEAD)
		{
			Safe_Delete(*iter);
			iter = m_listJUNLine.erase(iter);
		}
		else
		{
			++iter;
		}
	}
		
}

void CJUNLineMgr::LateUpdate(void)
{
	m_pLongLine->LateUpdate();

	for (auto& iter : m_listJUNLine)
		iter->LateUpdate();
}

void CJUNLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_listJUNLine)
		iter->Render(hDC);

	m_pLongLine->Render(hDC);
}

void CJUNLineMgr::Release(void)
{
	Safe_Delete(m_pLongLine);

	for (auto& iter : m_listJUNLine)
		Safe_Delete(iter);
}
