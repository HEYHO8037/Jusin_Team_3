#include "stdafx.h"
#include "Player_JUN.h"

/*
�׸� �׸���, �÷��̾�� ȸ�� ����? ��?
���ϴ�����
�׷� ȸ�� �Ƚ�Ű��?
�Ƴ� ȸ�� �־�, �ֳĸ� ������ �߸������� ���� �ö󰡰�
���� �ְ�, 
*/
CPlayer_JUN::CPlayer_JUN()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_tInfo.vDir = { 0.f, -1.f, 0.f };

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	//������ �߽��� ����

	m_vBody[0] = { -20.f, -20.f, 0.f };
	m_vBody[1] = { 20.f, -20.f, 0.f };
	m_vBody[2] = { 20.f, 20.f, 0.f };
	m_vBody[3] = { -20.f, -20.f, 0.f };

	m_vBody[4] = { -10.f, 20.f, 0.f };
	m_vBody[5] = { -10.f, 40.f, 0.f };

	m_vBody[6] = { 10.f, 20.f, 0.f };
	m_vBody[7] = { 10.f, 40.f, 0.f };

}


CPlayer_JUN::~CPlayer_JUN()
{
}

void CPlayer_JUN::Initialize(void)
{
}

int CPlayer_JUN::Update(void)
{

	return OBJ_NOEVENT;
}

void CPlayer_JUN::LateUpdate(void)
{
}

void CPlayer_JUN::Render(HDC hDC)
{
}

void CPlayer_JUN::Release(void)
{
}
