#include "stdafx.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player_SON.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	m_vecTile.reserve(TILEX * TILEY);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			m_vecTile.push_back(nullptr);
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		m_iArray[i] = 0;
	}

	int iIndex = 0;
	int iLeft = 0;
	int iRight = 11;
	int iBottom = 281;
	CObj* pTile = nullptr;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (iLeft == i * TILEX + j)
			{
				pTile = CAbstractFactory<CTile>::Create_Tile(iIndex);
				dynamic_cast<CTile*>(pTile)->Set_TMap();
				m_vecTile[iIndex] = pTile;
				++iIndex;
				iLeft += 20;
			}
			else if (iRight == i * TILEX + j)
			{
				pTile = CAbstractFactory<CTile>::Create_Tile(iIndex);
				dynamic_cast<CTile*>(pTile)->Set_TMap();
				m_vecTile[iIndex] = pTile;
				++iIndex;
				iRight += 20;
			}
			else if (iBottom == i * TILEX + j)
			{
				pTile = CAbstractFactory<CTile>::Create_Tile(iIndex);
				dynamic_cast<CTile*>(pTile)->Set_TMap();
				m_vecTile[iIndex] = pTile;
				++iIndex;
				++iBottom;
			}
			else
			{
				m_vecTile[iIndex] = nullptr;
				++iIndex;
			}
		}
	}

	m_iPoint = 0;
	m_iPointCheak = 0;
	m_StopDelete = false;
}

void CTileMgr::Update()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (nullptr != m_vecTile[i * TILEX + j])
			{
				m_vecTile[i * TILEX + j]->Update();
			}
		}
	}
}

void CTileMgr::LateUpdate()
{
	int iID = 0;
	int iIDCheak = 1;
	
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (nullptr != m_vecTile[i * TILEX + j])
			{
				m_vecTile[i * TILEX + j]->LateUpdate();

				if (!m_StopDelete)
				{
					iID = i * TILEX + j;

					if (iID % TILEX > 0 && iID % TILEX < 11)
					{
						if (iID % TILEX == iIDCheak)
						{
							m_iArray[iIDCheak - 1] = iID;
							++iIDCheak;
						}
						else if (10 < iIDCheak)
						{
							for (int i = 0; i < (iIDCheak - 1); ++i)
							{
								int iTemp = m_iArray[i];
								Safe_Delete(m_vecTile[iTemp]);
								m_vecTile[iTemp] = nullptr;
								for (int j = 1; j < int(iTemp / TILEX); ++j)
								{
									if (nullptr != m_vecTile[iTemp - TILEX * j])
									{
										CObj* pTemp = m_vecTile[iTemp - TILEX * j];
										m_vecTile[iTemp - TILEX * (j - 1)] = pTemp;
										m_vecTile[iTemp - TILEX * j] = nullptr;
										m_vecTile[iTemp - TILEX * (j - 1)]->Set_DrawID(iTemp - TILEX * (j - 1));
									}
									else
									{
									}
								}
							}
							iIDCheak = 1;
							++m_iPointCheak;
							m_iPoint += 1000;

							if (10 <= m_iPointCheak)
							{
								m_iPoint += 5000;
								m_iPointCheak = 0;
							}
						}
						else
						{
							iIDCheak = 1;
						}
					}
				}

			}
		}
	}
}

void CTileMgr::Render(HDC hDC)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (nullptr != m_vecTile[i * TILEX + j])
			{
				m_vecTile[i * TILEX + j]->Render(hDC);
			}
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

void CTileMgr::Add_Tile(int _iIndex)
{
	if (TILEX * TILEY < _iIndex)
		return;

	m_vecTile[_iIndex] = CAbstractFactory<CTile>::Create_Tile(_iIndex);
}

void CTileMgr::Picking_Tile(POINT _pt, const int& _iDrawID, const int& _iOption)
{
	int		x = _pt.x / TILECX;
	int		y = _pt.y / TILECY;
	
	int	iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
}

void CTileMgr::Save_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CTileMgr::Load_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	INFO		tInfo{};
	int			iDrawID = 0, iOption = 0;
	DWORD		dwByte = 0;

	Release();
	
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		//CObj*	pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		//dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		//dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

		//m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
}
