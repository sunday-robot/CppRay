#pragma once

#include "Color.h"
#include "Hittable.h"
#include "Camera.h"

/// <summary>
/// レンダリングを行う。
/// </summary>
/// <param name="world">物体群</param>
/// <param name="background">どの物体にもヒットしない場合に返す色。nullableだが、nullの場合はレンダラーで適当に定義した色を返す。</param>
/// <param name="camera">カメラの情報</param>
/// <param name="width">生成する画像の横方向の画素数</param>
/// <param name="height">生成する画像の縦方向の画素数</param>
/// <param name="maxDepth">レイの反射を追跡する最大数</param>
/// <param name="sampleCount">１画素あたりに投げるレイの数</param>
/// <returns>生成された画像(Colorの配列。本関数でnewするので、呼び出し側で開放が必要。)</returns>
Color* render(Hittable* world, Color* background, const Camera& camera, int width, int height, int maxDepth, int sampleCount);
