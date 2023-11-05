#include "perlinNoise.h"
#include <math.h>
#include <random>

struct Vec3 {
	double x;
	double y;
	double z;
};

static inline double dotProduct(const Vec3& a, const Vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static std::mt19937 generateMt19937() {
	std::random_device randomDevice; // 議事乱数生成器ではなく、実行のたびに異なる値を返すものらしい。(多分遅いので議事乱数生成期のシード取得に取得する)
	return std::mt19937(randomDevice());
}

static std::mt19937 mt19937 = generateMt19937();

unsigned int getRandomInt() {
	return mt19937();
}

double getRandomDouble(double min, double max) {
	std::uniform_real_distribution<double> rd(min, max);
	return rd(mt19937);
}

//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

struct Perm {
	Vec3 ranvec[256];
	int permX[256];
	int permY[256];
	int permZ[256];
};

static void perlinGeneratePerm(int perm[]) {
	for (int i = 0; i < 256; i++)
		perm[i] = i;

	for (int i = 255; i > 0; i--) {
		int target = getRandomInt() % i;
		auto tmp = perm[i];
		perm[i] = perm[target];
		perm[target] = tmp;
	}
}

static Perm* createPerm() {
	Perm* p = new Perm();

	for (int i = 0; i < 256; ++i) {
		auto x = getRandomDouble(-1, 1);
		auto y = getRandomDouble(-1, 1);
		auto z = getRandomDouble(-1, 1);
		auto len = sqrt(x * x + y * y + z * z);
		p->ranvec[i].x = x / len;
		p->ranvec[i].y = y / len;
		p->ranvec[i].z = z / len;
	}
	perlinGeneratePerm(p->permX);
	perlinGeneratePerm(p->permY);
	perlinGeneratePerm(p->permZ);

	return p;
}

static Perm* perm = createPerm();

static double perlinInterp(Vec3 c[2][2][2], double u, double v, double w) {
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);
	auto accum = 0.0;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++) {
				Vec3 weightY{ u - i,  v - j,  w - k };
				accum += (i * uu + (1.0 - i) * (1.0 - uu)) *
					(j * vv + (1.0 - j) * (1.0 - vv)) *
					(k * ww + (1.0 - k) * (1.0 - ww)) * dotProduct(c[i][j][k], weightY);
			}

	return accum;
}

static	double noise(double x, double y, double z) {
	auto u = x - floor(x);
	auto v = y - floor(y);
	auto w = z - floor(z);
	auto i = (int)(floor(x));
	auto j = (int)(floor(y));
	auto k = (int)(floor(z));
	auto c = new Vec3[2][2][2];

	for (int di = 0; di < 2; di++)
		for (int dj = 0; dj < 2; dj++)
			for (int dk = 0; dk < 2; dk++)
				c[di][dj][dk] = perm->ranvec[
					perm->permX[(i + di) & 255] ^
						perm->permY[(j + dj) & 255] ^
						perm->permZ[(k + dk) & 255]
				];

	return perlinInterp(c, u, v, w);
}

extern double perlinNoise2(double x, double y, double z, int depth) {
	auto accum = 0.0;
	auto weight = 1.0;

	for (int i = 0; i < depth; i++) {
		accum += weight * noise(x, y, z);
		weight *= 0.5;
		x *= 2;
		y *= 2;
		z *= 2;
	}

	return fabs(accum);
}
