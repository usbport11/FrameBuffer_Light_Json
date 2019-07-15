#ifndef resolutionH
#define resolutionH

#include <functional>

struct stResolution
{
	unsigned int X;
	unsigned int Y;
};

struct stFindResolution: std::unary_function<stResolution, bool>
{
	stResolution Resolution;
	stFindResolution(stResolution inResolution)
	{
		Resolution = inResolution;
	}
	bool operator()(stResolution const& R) const
	{
		return (R.X == Resolution.X && R.Y == Resolution.Y);
	}
};

bool ResolutionSort(stResolution A, stResolution B);

#endif
