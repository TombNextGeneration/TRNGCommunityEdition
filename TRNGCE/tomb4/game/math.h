#pragma once

namespace tomb4
{
	constexpr long abs(long x)
	{
		return x < 0 ? -x : x;
	}

	constexpr long square(long x)
	{
		return x * x;
	}
}
