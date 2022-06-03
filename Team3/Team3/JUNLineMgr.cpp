#include "stdafx.h"
#include "JUNLineMgr.h"
#include "ObjMgr.h"

#include "RandomMgr.h"

CJUNLineMgr* CJUNLineMgr::m_pInstance = nullptr;


/*
�÷��̾� ������ ������ 30�� ��ŭ ȸ���ϰ� �ٽ� false��
�÷��̾� ������ ������ -30�� ��ŭ ȸ���ϰ� �ٽ� false��

�̰� �÷��̾� ���� ���� �����־�� �ϴϱ�...
obj �Ŵ������� �Լ� ��������, -> ���� �÷��̾�� 30�� �Ѱ���
//�׸��� 1�� �Ѿ�� ������ 4�� �̵�

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
