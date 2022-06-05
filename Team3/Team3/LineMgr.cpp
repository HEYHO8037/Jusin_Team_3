#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{

}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

float CLineMgr::Collision_Line(float& _fX, float& _fY, float* pY)
{
	// ������ ������
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if ((_fX >= iter->Get_Info().tLPoint.fX &&_fX <= iter->Get_Info().tRPoint.fX))
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	float Angle = atan2(y2 - y1, x2 - x1);

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	return Angle;
}
bool CLineMgr::Collision_VerticalLine(float & _fX, float & _fY, float * pY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX&&_fX <= iter->Get_Info().tRPoint.fX)
		{
			if (iter->Get_Info().tLPoint.fY > iter->Get_Info().tRPoint.fY)
			{
				if ((!(_fY <= iter->Get_Info().tLPoint.fY&&_fY  >= iter->Get_Info().tRPoint.fY))&&((_fY >=iter->Get_Info().tLPoint.fY)||(_fY >= iter->Get_Info().tRPoint.fY)))
				{
					pTarget = iter;
				}
				if (_fY  >=( iter->Get_Info().tRPoint.fY+ iter->Get_Info().tLPoint.fY)/2)
				{
					pTarget = iter;
				}

			}
		 if(iter->Get_Info().tLPoint.fY <= iter->Get_Info().tRPoint.fY)
			{
				if ((!(_fY <= iter->Get_Info().tRPoint.fY&&_fY >= iter->Get_Info().tLPoint.fY)) && ((_fY >= iter->Get_Info().tRPoint.fY)|| (_fY >= iter->Get_Info().tLPoint.fY)))
				{
 					pTarget = iter;
				}
				if (_fY >= (iter->Get_Info().tRPoint.fY + iter->Get_Info().tLPoint.fY) / 2)
				{
					pTarget = iter;
				}
			}
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;

	return true;
}
void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}
