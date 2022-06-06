#include "stdafx.h"
#include "MyMenu.h"
#include "KeyMgr.h"
#include "UIManager.h"

#include "BmpMgr_3.h"
#include "KeyMgr.h"

CMyMenu::CMyMenu()
{
	for (auto& iter : m_pGameStart)
	{
		iter = nullptr;
	}

	m_hMemDC = CBmpMgr_3::Get_Instance()->Find_Image(L"MENU");
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	for (int i = 1; i < GAME_END ; ++i)
	{
		m_pGameStart[i-1] = new CMyButton(150.f * float(i), 500.f, GAMESCENE(i));
	}

	m_vRightEye[0] = { 320.f, 235.f, 0.f };
	m_vRightEye[1] = { 320.f, 235.f, 0.f };

	m_vLeftEye[0] = { 545.f, 245.f, 0.f };
	m_vLeftEye[1] = { 545.f, 245.f, 0.f };

	m_vOriginDir[0] = { 0.f,1.f,0.f };

	m_bClick = false;

	//m_vArrive = { 0.f,0.f,0.f };

	//m_vPos[0] = { 0.f,0.f,0.f };
	//m_vPos[1] = { 0.f,0.f,0.f };

	m_fSpeed = 5.f;
}

void CMyMenu::Update(void)
{
	for (auto& iter : m_pGameStart)
	{
		iter->Update();
	}

	if (m_bClick)
	{
		D3DXMATRIX _matScale, _matRotZ, _matTrans;

		D3DXMatrixScaling(&_matScale, 1.f, 1.f, 1.f);

		//---간디 기준 오른눈
		m_vDir[0] = m_vArrive - m_vRightEye[0];

		D3DXVec3Normalize(&m_vDir[0], &m_vDir[0]);

		float m_fAngle = D3DXVec3Dot( &m_vDir[0], &m_vOriginDir[0] );		

		D3DXMatrixRotationZ(&_matRotZ, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&_matTrans, m_vRightEye[1].x, m_vRightEye[1].y, 0.f);

		m_matWorld = _matScale * _matRotZ * _matTrans;

		D3DXVec3TransformCoord(&m_vRightEye[1], &D3DXVECTOR3({ 0.f,0.f,0.f }), &m_matWorld);

		float m_fDistance_Right = sqrtf
					((m_vRightEye[0].x - m_vArrive.x) * (m_vRightEye[0].x - m_vArrive.x)
						+
					(m_vRightEye[0].y - m_vArrive.y) * (m_vRightEye[0].y - m_vArrive.y));

		m_vRightEye[1] += m_vDir[0] * m_fSpeed;


		//---간디 기준 왼눈
		m_vDir[1] = m_vArrive - m_vLeftEye[0];

		D3DXVec3Normalize(&m_vDir[1], &m_vDir[1]);

		m_fAngle = D3DXVec3Dot(&m_vDir[1], &m_vOriginDir[1]);



		D3DXMatrixRotationZ(&_matRotZ, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&_matTrans, m_vLeftEye[1].x, m_vLeftEye[1].y, 0.f);

		m_matWorld = _matScale * _matRotZ* _matTrans;

		D3DXVec3TransformCoord(&m_vLeftEye[1], &D3DXVECTOR3({0.f,0.f,0.f}), &m_matWorld);

		float m_fDistance_Left = sqrtf
					((m_vLeftEye[0].x - m_vArrive.x) * (m_vLeftEye[0].x - m_vArrive.x)
						+
					(m_vLeftEye[0].y - m_vArrive.y) * (m_vLeftEye[0].y - m_vArrive.y));


		m_vLeftEye[1] += m_vDir[1] * m_fSpeed * (m_fDistance_Left / m_fDistance_Right);
	}
}

void CMyMenu::LateUpdate(void)
{
	for (auto& iter : m_pGameStart)
	{
		iter->LateUpdate();
	}

	if (m_bClick)
	{
		int i = 0;
		RECT _rcTemp{};
		RECT _pt{ 
			(LONG)m_vArrive.x - 5,
			(LONG)m_vArrive.y - 5,
			(LONG)m_vArrive.x + 5,
			(LONG)m_vArrive.y + 5
		};
		RECT _eye{
			(LONG)m_vRightEye[1].x - 5,
			(LONG)m_vRightEye[1].y - 5,
			(LONG)m_vRightEye[1].x + 5,
			(LONG)m_vRightEye[1].y + 5
		};
		if (IntersectRect(&_rcTemp, &_pt, &_eye))
		{
			m_vRightEye[1] = m_vArrive;
				
			++i;
		}

		_eye = {
			(LONG)m_vLeftEye[1].x - 5,
			(LONG)m_vLeftEye[1].y - 5,
			(LONG)m_vLeftEye[1].x + 5,
			(LONG)m_vLeftEye[1].y + 5
		};
		if (IntersectRect(&_rcTemp, &_pt, &_eye))
		{
			m_vLeftEye[1] = m_vArrive;
			++i;
		}
		if (i > 1)
		{
			if (m_vRightEye[1] == m_vLeftEye[1])
			{
				m_bClick = false;
				m_vRightEye[1] = m_vRightEye[0];
				m_vLeftEye[1] = m_vLeftEye[0];

				for (int i = 0; i < 4; ++i)
				{
					if (IntersectRect(&_rcTemp, &_pt, &m_pGameStart[i]->Get_Rect()))
					{
						m_pGameStart[i]->Set_Click();
					}
				}


			}	
		}
	}
	else
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			POINT	pt{};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);

			m_vArrive = { (float)pt.x, (float)pt.y, 0.f };

			m_bClick = true;
		}
	}
}

void CMyMenu::Render(HDC hDC)
{
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
	
	for (auto& iter : m_pGameStart)
	{
		iter->Render(m_hMemDC);
	}

	if (m_bClick)
	{
		HPEN hpen;
		HPEN hpenOld;

		hpen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));   // 선 스타일, 굵기, 색상
		hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);   // 펜 선택

		MoveToEx(hDC, m_vRightEye[0].x, m_vRightEye[0].y, nullptr);
		LineTo(hDC, m_vRightEye[1].x, m_vRightEye[1].y);

		MoveToEx(hDC, m_vLeftEye[0].x, m_vLeftEye[0].y, nullptr);
		LineTo(hDC, m_vLeftEye[1].x, m_vLeftEye[1].y);

		hpen = (HPEN)SelectObject(hDC, hpenOld);   // 기존의 펜 다시 선택
		DeleteObject(hpen);   // 생성한 펜 삭제
	}

	for (int i = 1; i < GAME_END; ++i)
	{
		switch (i)
		{
		case 1:
			TextOut(hDC, 150.f * float(i) - 20, 490.f, L"RUN 3", 5);
			break;
		case 2:
			TextOut(hDC, 150.f * float(i) - 30, 490.f, L"포트리스", 4);
			break;
		case 3:
			TextOut(hDC, 150.f * float(i)-45 , 490.f, L"도어 킥커스2", 7);
			break;
		case 4:
			TextOut(hDC, 150.f * float(i) - 30, 490.f, L"테트리스", 4);
			break;
		default:
			break;
		}
	}
}

void CMyMenu::Release(void)
{
	for (auto& iter : m_pGameStart)
	{
		Safe_Delete(iter);
	}
	ReleaseDC(g_hWnd, m_hMemDC);
}


