#pragma once

#include <random>
#define _USE_MATH_DEFINES	// M_PIを使用するにはこの定義が必要とのこと
#include <math.h>
#include "Ray.h"
#include "Vec3.h"
#include "util.h"

class Camera {
	const Vec3 lowerLeftCorner;
	const Vec3 horizontal;
	const Vec3 vertical;

	// カメラの位置
	const Vec3 origin;

	// カメラのX軸方向(単位ベクトル)
	const Vec3 u;

	// カメラのY軸方向(単位ベクトル)
	const Vec3 v;

	// レンズのサイズ(ボケを決めるもので、小さいほどボケない。0なら全くボケない。)
	const double lensRadius;

	const double _exposureTime;

public:
	Camera(const Vec3& lowerLeftCorner,
		const Vec3& horizontal,
		const Vec3& vertical,
		const Vec3& origin,
		const Vec3& u,	// カメラのX軸方向(単位ベクトルであること)
		const Vec3& v,	// カメラのY軸方向(単位ベクトルであること)
		double lensRadious,
		double exposureTime)	// 露光時間
		: lowerLeftCorner(lowerLeftCorner),
		vertical(vertical), horizontal(horizontal),
		origin(origin),
		u(u), v(v),
		lensRadius(lensRadious),
		_exposureTime(exposureTime) {}

	Ray ray(
		double s,	// 横方向の位置(0～1)
		double t) const;	// 縦方向の位置(0～1)

	double exposureTime() const { return _exposureTime; }

	static Camera createCamera(
		Vec3 lookFrom,			// 視点
		Vec3 lookAt,			// 注視点(視線の方向を決めるためだけのもので、ピントがあう場所ではない。ピント位置は、focusDistで指定する。)
		Vec3 vup,				// 上方向を示すベクトル(視点、注視点のベクトルと同じ方向でなければよい。直交している必要もないし、長さも適当でよい)
		double verticalFov,		// 縦方向の視野(角度[°]]
		double aspect,			// 縦横比(幅/高さ)
		double aperture,		// 絞り(ボケ具体を決めるもの。0なら全くボケない。)
		double exposureTime);	// 露光時間
};
