#pragma once

#include "Scene.h"

class CTetris : public CScene
{
public:
	CTetris();
	virtual ~CTetris();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

