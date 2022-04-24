#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <random>
#include <complex>
#include <assert.h>

using namespace std;

////////////////	型名など
typedef long long ll;
#define endl '\n'

////////////////	各種定数
const ll INF = 1LL << 60;
const double EPS = 1e-12;

////////////////	便利なテンプレート関数
template <typename T>
inline bool chmin(T &x, T a)
{
	if (x >= a)
	{
		x = a;
		return true;
	}
	return false;
}

template <typename T>
inline bool chmax(T &x, T a)
{
	if (x <= a)
	{
		x = a;
		return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	std::cin.tie(0);

	return 0;
}