#pragma once

// �F(��)
// 
// �����I�Ȍ��ł͂Ȃ��A�P����R�AG�AB�̋��x������3�̎�������Ȃ���̂ł����Ȃ��A�l�X�Ȕg���̌��̍����Ȃǂł͂Ȃ��B
// ���̂��߁A�g���ɂ����ܗ��̈Ⴂ�Ȃǂ��l�����������_�����O�͂ł��Ȃ��B
// (�����ɂ�낤�Ƃ��Ă��A3��ނ̔g�������Ȃ��̂ŁA1�{�̔��������v���Y���ɏƎ˂��Ă��o�Ă����͓̂��F�̑�`�ł͂Ȃ��A�ԁA�A�΂�3�{�̌��ƂȂ��Ă��܂��B)
// 
// ���Ђł�Vec3�ő�p���Ă������A3�̕��������_������\������Ă���Ƃ������Ƃ�
// ���܂��܈�v���Ă��邾���ŕʕ�(���ς�O�ςȂ�RGB�ɒ�`�ł��Ȃ�)�Ƃ��������Ȃ̂ŁA
// �����N���X�ɂ͂��Ă��Ȃ��B
class Color {
	double _r;
	double _g;
	double _b;

public:
	static const Color black;
	static const Color cyan;

	// �����ă����o�ϐ������������Ȃ��R���X�g���N�^
#pragma warning(push)
#pragma warning(disable:26495)
	Color() {}
#pragma warning(pop)

	Color(double r, double g, double b) :_r(r), _g(g), _b(b) {}

	Color operator +(Color a) const { return Color(_r + a._r, _g + a._g, _b + a._b); }

	Color operator *(Color a) const { return Color(_r * a._r, _g * a._g, _b * a._b); }

	Color operator *(double a) const { return Color(_r * a, _g * a, _b * a); }

	Color operator /(double a) const { return Color(_r / a, _g / a, _b / a); }

	Color operator =(const Color& a) {
		_r = a._r;
		_g = a._g;
		_b = a._b;
		return *this;
	}

	Color operator +=(const Color& a) {
		_r += a._r;
		_g += a._g;
		_b += a._b;
		return *this;
	}

	double r() const { return _r; }
	double g() const { return _g; }
	double b() const { return _b; }

	//public override string ToString()
	//{
	//	return $"({R:0.000}, {G:0.000}, {B:0.000})";
	//}
};

inline Color operator* (double a, const Color& b) { return b * a; }
