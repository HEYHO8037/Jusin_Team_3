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

	static CObj*	Create(const float& _fRandAngle)
	{
		CObj*	pObj = new T(_fRandAngle);
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

	static CObj*	Create(D3DXVECTOR3 _vPos, float _fAngle ,float _fSpeed)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_vPos);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Speed(_fSpeed);

		return pObj;
	}

	static CObj*	Create_Tile(int _iIndex)
	{
		CObj*	pObj = new T(_iIndex);
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create_Tetris(int _iIndex, TILETYPE _eTileType)
	{
		CObj*	pObj = new T(_iIndex, _eTileType);
		pObj->Initialize();

		return pObj;
	}

};

