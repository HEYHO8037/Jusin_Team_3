#include "stdafx.h"
#include "JUNLine.h"

#include "ObjMgr.h"
#include "Player_JUN.h"

#include "RandomMgr.h"

CJUNLine::CJUNLine(const float& _fRandAngle)
	: m_bDead(false)
{
	for (int i = 0; i < 2; ++i)
	{
		m_vPoint[i] = {400.f,300.f,0.f};
		m_vLocalPoint[i] = { 0.f,0.f,0.f };
		m_vPointPos[i] = { 400.f,300.f,0.f };
	}
	m_fAngle = D3DXToRadian(_fRandAngle);

	//라인 방향은 일단 무조건 아래
	m_vDir = { 0.f,1.f,0.f };
	m_vLocalDir = m_vDir;

	m_vLocalPointDir[0] = { 0.f,1.f,0.f };
	m_vLocalPointDir[1] = { 0.f,1.f,0.f };

	m_fDistanceRatio[0] = 1.f;
	m_fDistanceRatio[1] = 1.f;

	m_fPointAngle[0] = D3DXToRadian(22.5f);
	m_fPointAngle[1] = D3DXToRadian(337.5f);

	m_fObjAngle = static_cast<CPlayer_JUN*>(CObjMgr::Get_Instance()->Get_Player())->Get_ObjAngle();

	m_lColor_R = CRandom::Random(0, 255);
	m_lColor_G = CRandom::Random(0, 255);
	m_lColor_B = CRandom::Random(0, 255);
}

CJUNLine::CJUNLine(const D3DXVECTOR3 _vPoint)
	: m_bDead(false)
{
	for (int i = 0; i < 2; ++i)
	{
		//m_vPoint[i] = _vPoint[i];
		//m_vLocalPoint[i] = _vPoint[i];
	}


	//라인 방향은 일단 무조건 아래
	m_vDir = { 0.f,1.f,0.f };
	m_vLocalDir = m_vDir;

	m_fDistanceRatio[0] = 1.f;
	m_fDistanceRatio[1] = 1.f;

}

CJUNLine::~CJUNLine()
{
}

void CJUNLine::Initialize(void)
{
}

int CJUNLine::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX _matScale, _matRotZ, _matTrans, _matRotA, _matTransA;

	D3DXMatrixIdentity(&_matScale);
	D3DXMatrixIdentity(&_matRotZ);
	D3DXMatrixIdentity(&_matTrans);
	D3DXMatrixIdentity(&_matRotA);
	D3DXMatrixIdentity(&_matTransA);
	
	m_fDistanceRatio[0] *= 1.1f;


	m_fObjAngle_Player = static_cast<CPlayer_JUN*>(CObjMgr::Get_Instance()->Get_Player())->Get_ObjAngle();

	if (m_fObjAngle_Player != m_fObjAngle)
	{
		if (m_fObjAngle_Player > m_fObjAngle)
		{
			m_fObjAngle += 4.f;
			if (m_fObjAngle_Player < m_fObjAngle)
			{
				m_fObjAngle = m_fObjAngle_Player;
			}
		}
		else if (m_fObjAngle_Player < m_fObjAngle)
		{
			m_fObjAngle -= 4.f;
			if (m_fObjAngle_Player > m_fObjAngle)
			{
				m_fObjAngle = m_fObjAngle_Player;
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		D3DXMatrixScaling(&_matScale, 1.f, m_fDistanceRatio[0], 1.f);
		//D3DXMatrixRotationZ(&_matRotZ, m_fAngle + m_fPointAngle[i] + D3DXToRadian(m_fObjAngle));
		D3DXMatrixTranslation(&_matTrans, m_vPoint[i].x -400.f , m_vPoint[i].y-300.f, 0.f);
		D3DXMatrixRotationZ(&_matRotZ, m_fPointAngle[i]);

		D3DXMatrixRotationZ(&_matRotA, m_fAngle + D3DXToRadian(m_fObjAngle_Player));
		D3DXMatrixTranslation(&_matTransA, 400.f, 300.f, 0.f);

		m_matWorld = _matScale * _matRotZ * _matTrans *_matRotA * _matTransA;

		D3DXVec3TransformNormal(&m_vPointDir[i], &m_vLocalPointDir[i], &m_matWorld);
	}

	m_vPoint[0] += m_vPointDir[0] * 0.3f;
	m_vPoint[1] += m_vPointDir[1] * 0.3f;
	

	return OBJ_NOEVENT;
}

void CJUNLine::LateUpdate(void)
{
	float _fX;
	float _fY;

	//if (m_vPoint[0].x > m_vPoint[1].x)
	/*{
		_fX = m_vPoint[0].x - m_vPoint[1].x;
		_fY = m_vPoint[0].y - m_vPoint[1].y;
	}
	else
	{
		_fX = m_vPoint[1].x - m_vPoint[0].x;
		_fY = m_vPoint[1].y - m_vPoint[0].y;
	}	
*/
	if (m_vPoint[0].x > 800 || m_vPoint[0].x < 0)
	{
		m_bDead = true;
	}
	else if(m_vPoint[0].y > 600 || m_vPoint[0].y < 0)
	{
		m_bDead = true;
	}

}

void CJUNLine::Render(HDC hDC)
{
	HPEN hpen;
	HPEN hpenOld;

	hpen = CreatePen(PS_SOLID, 5, RGB(m_lColor_R, m_lColor_G, m_lColor_B));   // 선 스타일, 굵기, 색상
	hpenOld = (HPEN)::SelectObject(hDC, (HGDIOBJ)hpen);   // 펜 선택

	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);
	LineTo(hDC, m_vPoint[1].x, m_vPoint[1].y);

	hpen = (HPEN)SelectObject(hDC, hpenOld);   // 기존의 펜 다시 선택
	DeleteObject(hpen);   // 생성한 펜 삭제

	

	//Rectangle(hDC, m_vPoint[0].x - 50, m_vPoint[0].y - 50, m_vPoint[0].x + 50, m_vPoint[0].y + 50);
}

void CJUNLine::Release(void)
{
}
