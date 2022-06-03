#pragma once
#include "Include.h"

class CJUNLine
{
public:
	CJUNLine(const float& _fRandAngle);

	CJUNLine(const D3DXVECTOR3 _vPoint);

	virtual ~CJUNLine();

public:
	void Initialize(void);
	int Update(void);
	void LateUpdate(void);
	void Render(HDC hDC);
	void Release(void);

private:
	bool m_bDead;
	//점 두개
	//길이 비율

	float m_fDistanceRatio[2];
	float m_fAngle;

	float m_fPointAngle[2];

	D3DXVECTOR3 m_vPoint[2];

	D3DXVECTOR3 m_vPointPos[2];

	D3DXVECTOR3 m_vLocalPoint[2];

	D3DXVECTOR3 m_vPointDir[2];
	D3DXVECTOR3 m_vLocalPointDir[2];

	float m_fObjAngle_Player;
	float m_fObjAngle;

	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vLocalDir;

	D3DXMATRIX m_matWorld;

	LONG m_lColor_R;
	LONG m_lColor_G;
	LONG m_lColor_B;
};

