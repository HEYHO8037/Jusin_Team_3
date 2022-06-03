#pragma once

#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(void);
	void Update(void);
	void LateUpdate(void);
	void Render(void);
	void Release(void);

private:
	HDC		m_hDC;

	HDC		hBackDC;
	HDC		hGroundDC;
};

