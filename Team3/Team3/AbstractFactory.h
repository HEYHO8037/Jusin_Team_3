#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create(void)
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create(D3DXVECTOR3 _vPos, DIRECTION eDir = DIR_END)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_vPos);

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}

	static CObj*	Create(D3DXVECTOR3 _vPos, float _fAngle)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_vPos);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

