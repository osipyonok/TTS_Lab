#pragma once
#include <vector>
#include <qstring.h>
#include <qchar.h>

using namespace std;

struct StringHash {
	vector<long long> suf, pows;
	long long mod;

	StringHash(QString & s, int base = 153, long long _mod = 1000000007LL) {
		int n = s.size();
		suf = vector<long long>(n + 1, 0LL);
		pows = vector<long long>(n + 1, 0LL);
		pows[1] = base;
		mod = _mod;
		for(int i = n - 1; i >= 0; --i) {
			suf[i] = (s[i].unicode() + suf[i + 1] * pows[1]) % mod;
		}
		for(int i = 2 ; i <= n; ++i) {
			pows[i] = (base * pows[i - 1]) % mod;
		}
	}

	long long str(int l, int r) { // [l , r]
		long long res = (suf[l] - suf[r + 1] * pows[r - l + 1]) % mod;
		while (res < 0)res += mod;
		return res % mod;
	}

	long long str() {
		return str(0, (int)suf.size() - 2);
	}
};