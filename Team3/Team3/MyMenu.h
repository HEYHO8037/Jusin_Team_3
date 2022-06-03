#pragma once

#include "Scene.h"
#include "Timer.h"

#include "MyButton.h"

class CLabel;

class CMyMenu : public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CMyButton* m_pGameStart[4];
};

