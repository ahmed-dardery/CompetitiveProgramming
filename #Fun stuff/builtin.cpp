template<typename __T>
__T
__gcd(__T __m, __T __n)
{
	while (__n != 0)
	{
		__T __t = __m % __n;
		__m = __n;
		__n = __t;
	}
	return __m;
}
int  __builtin_popcountll(unsigned long long x) {
	x = (x & 0x5555555555555555ULL) + ((x >> 1) & 0x5555555555555555ULL);
	x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
	x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL);
	return (x * 0x0101010101010101ULL) >> 56;
}

template<typename _Tp, typename _Integer, typename _MonoidOperation>
_Tp
__power(_Tp __x, _Integer __n, _MonoidOperation __monoid_op)
{
	if (__n == 0)
		return identity_element(__monoid_op);
	else
	{
		while ((__n & 1) == 0)
		{
			__n >>= 1;
			__x = __monoid_op(__x, __x);
		}

		_Tp __result = __x;
		__n >>= 1;
		while (__n != 0)
		{
			__x = __monoid_op(__x, __x);
			if ((__n & 1) != 0)
				__result = __monoid_op(__result, __x);
			__n >>= 1;
		}
		return __result;
	}
}