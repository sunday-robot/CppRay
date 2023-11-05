#include "util.h"
#include <random>
#include <tuple>

static std::mt19937 generateMt19937() {
	std::random_device randomDevice; // �c������������ł͂Ȃ��A���s�̂��тɈقȂ�l��Ԃ����̂炵���B(�����x���̂ŋc�������������̃V�[�h�擾�Ɏ擾����)
	return std::mt19937(randomDevice());
}

static std::mt19937 mt19937 = generateMt19937();

// ���_�𒆐S�Ƃ��锼�a1��XY���ʏ�̉~�̒��̃����_���Ȉʒu
Vec3 randomInUnitDisk() {
	std::uniform_real_distribution<double> rd(-1, 1);
	for (;;) {
		auto p = Vec3(rd(mt19937), rd(mt19937), 0);
		if (p.squaredLength() < 1)
			return p;
	}
}

double getRandomDouble() {
	std::uniform_real_distribution<double> rd(0, 1);
	return rd(mt19937);
}

double getRandomDouble(double min, double max) {
	std::uniform_real_distribution<double> rd(min, max);
	return rd(mt19937);
}

unsigned int getRandomInt() {
	return mt19937();
}

int getRandomInt(int min, int max) {
	return min + (mt19937() % (max - min));
}

// ���_�𒆐S�Ƃ��锼�a1�̋����̃����_���ȍ��W
Vec3 randomInUnitSphere() {
	std::uniform_real_distribution<double> rd(-1, 1);
	for (;;) {
		auto p = Vec3(rd(mt19937), rd(mt19937), rd(mt19937));
		if (p.squaredLength() < 1)
			return p;
	}
}

Color randomHueColor(double s, double v) {
	auto min = (1 - s) * v;
	auto range = v - min;
	auto h6 = getRandomDouble(0, 6);
	if (h6 < 1) {
		auto g = h6 * range + min;
		return Color(v, g, min);
	}
	if (h6 < 2) {
		auto r = (2 - h6) * range + min;
		return  Color(r, v, min);
	}
	if (h6 < 3) {
		auto b = (h6 - 2) * range + min;
		return  Color(min, v, b);
	}
	if (h6 < 4) {
		auto g = (4 - h6) * range + min;
		return  Color(min, g, v);
	}
	if (h6 < 5) {
		auto r = (h6 - 4) * range + min;
		return  Color(r, min, v);
	}
	auto b = (6 - h6) * range + min;
	return  Color(v, min, b);
}
