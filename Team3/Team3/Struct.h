#pragma once

typedef	struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vFall;

	D3DXMATRIX		matWorld;

	D3DXMATRIX		matWorldP;//¼®±Õ¿ë
	D3DXMATRIX		matGunWorld;//¼®±Õ¿ë

}INFO;

typedef	struct	tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {	}

}LINEPOINT;

typedef	struct	tagLineInfo
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& tLeft, LINEPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight) {	}

}LINE;