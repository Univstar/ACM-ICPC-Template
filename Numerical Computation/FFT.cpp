#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

namespace IO
{
	const int MAXL = 1 << 15;
	char buf[MAXL], *S, *T, ch;

	inline char Getch()
	{
		if (S == T) T = (S = buf) + fread(buf, 1, MAXL, stdin);
		return S == T ? EOF : *S++;
	}

	inline void Read(int &x)
	{
		x = 0;
		while (!isdigit(ch = Getch()));
		do { x = x * 10 + (ch ^ '0'); } while (isdigit(ch = Getch()));
	}
}

typedef double LD;

const int MAXN = 100010;
const LD PI = acos(-(LD)1);

int a[MAXN], b[MAXN], n, m;

struct Complex
{
	LD real, imag;
	Complex(LD _real = 0, LD _imag = 0): real(_real), imag(_imag) { }
	Complex operator+(const Complex &o) const { return Complex(real + o.real, imag + o.imag); }
	Complex operator-(const Complex &o) const { return Complex(real - o.real, imag - o.imag); }
	Complex operator*(const Complex &o) const { return Complex(real * o.real - imag * o.imag, real * o.imag + imag * o.real); }
	Complex operator/=(const double o)
	{
		real /= o, imag /= o;
		return *this;
	}
};

namespace FFT
{
	const int MAXL = 270000;

	Complex c[MAXL], w[MAXL];

	inline int GetLen(int n)
	{
		int ret = 1;
		while (ret <= n) ret <<= 1;
		return ret;
	}

	inline void Solve(Complex num[], int len, int flag)
	{
		for (int i = 1, j = len >> 1; i < len - 1; ++i)
		{
			if (i < j) swap(num[i], num[j]);
			int k = len >> 1;
			while (j >= k) j ^= k, k >>= 1;
			j += k;
		}
		w[0] = Complex(1, 0);
		for (int i = 2; i <= len; i <<= 1)
		{
			Complex g(cos(2 * PI / i), -flag * sin(2 * PI / i));
			for (int j = i >> 1; j >= 0; j -= 2) w[j] = w[j >> 1];
			for (int j = 1; j < i >> 1; j += 2) w[j] = w[j - 1] * g;
			for (int j = 0; j < len; j += i)
			{
				Complex *alpha = num + j, *beta = alpha + (i >> 1);
				for (int k = 0; k < i >> 1; ++k)
				{
					Complex t = w[k] * beta[k];
					beta[k] = alpha[k] - t;
					alpha[k] = alpha[k] + t;
				}
			}
		}
		if (!~flag)
			for (int i = 0; i < len; ++i) num[i] /= len;
	}
}

using namespace FFT;

inline void Init()
{
	IO::Read(n), IO::Read(m);
	for (int i = 0; i <= n; ++i) IO::Read(a[i]);
	for (int i = 0; i <= m; ++i) IO::Read(b[i]);
}

int main()
{
	Init();
	int len = GetLen(n + m);
	for (int i = 0; i <= max(n, m); ++i) c[i] = Complex(a[i] + b[i], a[i] - b[i]);
	Solve(c, len, 1);
	for (int i = 0; i < len; ++i) c[i] = c[i] * c[i];
	Solve(c, len, -1);
	for (int i = 0; i <= n + m; ++i) printf("%d ", (int)round(c[i].real * 0.25));
	printf("\n");
	return 0;
}