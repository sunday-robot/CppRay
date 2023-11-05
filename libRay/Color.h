#pragma once

// 色(光)
// 
// 物理的な光ではなく、単純にR、G、Bの強度を示す3つの実数からなるものでしかなく、様々な波長の光の混成などではない。
// このため、波長による屈折率の違いなどを考慮したレンダリングはできない。
// (無理にやろうとしても、3種類の波長しかないので、1本の白い光をプリズムに照射しても出ていくのは虹色の台形ではなく、赤、青、緑の3本の光となってしまう。)
// 
// 書籍ではVec3で代用していたが、3つの浮動小数点数から構成されているということが
// たまたま一致しているだけで別物(内積や外積などRGBに定義できない)というだけなので、
// 同じクラスにはしていない。
class Color {
	double _r;
	double _g;
	double _b;

public:
	static const Color black;
	static const Color cyan;

	// あえてメンバ変数を初期化しないコンストラクタ
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
