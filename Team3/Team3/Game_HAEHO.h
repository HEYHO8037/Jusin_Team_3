#pragma once
#include "Scene.h"
class CGame_HAEHO :
	public CScene
{
public:
	CGame_HAEHO();
	virtual ~CGame_HAEHO();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

