#pragma once
#include <random>
#include <math.h>

class CRandom
{
public:

	CRandom()
	{
	}

	~CRandom()
	{
	}

	static const int Random(const int& _iNum1, const int& _iNum2)
	{
		std::random_device random;
		std::mt19937 rd(random());
		std::uniform_int_distribution<int> range(_iNum1, _iNum2);
		int iNum = range(random);
		return iNum;
	}
};

