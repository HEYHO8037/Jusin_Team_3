#pragma once
#include "Include.h"

class CLongLine
{
public:
	CLongLine();
	CLongLine(const D3DXVECTOR3* _vPoint);
	virtual ~CLongLine();

public:
	void Initialize(void);
	void Update(void);
	void LateUpdate(void);
	void Render(HDC hDC);
	void Release(void);

	void Keyinput(void);

private:
	//점 두개
	//길이 비율

	float m_fAngle;
	float m_fAngle_Coc;
	float m_fAngle_6;

	float m_fObjAngle_Player;
	float m_fObjAngle;

	INFO m_tInfo;

	D3DXVECTOR3 m_vPoint[2];
	D3DXVECTOR3 m_vLocalPoint[2];

	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vLocalDir;
};

