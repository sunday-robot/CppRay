#include "saveBmp.h"

#include <ostream>
#include <fstream>
#include <algorithm>

static void writeUshort(std::ostream& s, unsigned short data) {
	unsigned char buf[2] = {
		(unsigned char)(data & 0xff),
		(unsigned char)((data >> 8) & 0xff) };
	s.write((char*)buf, sizeof(buf));
}

static void writeUint(std::ostream& s, unsigned int data) {
	unsigned char buf[4] = {
		(unsigned char)(data & 0xff),
		(unsigned char)((data >> 8) & 0xff),
		(unsigned char)((data >> 16) & 0xff),
		(unsigned char)((data >> 24) & 0xff) };
	s.write((char*)buf, sizeof(buf));
}

static void saveBitmapFileHeader(std::ostream& s, int width, int height) {
	auto bfSize = 54 + (width * 3 + 3) / 4 * 4 * height;

	s.write("BM", 2); // bfType "BM"
	writeUint(s, (unsigned int)bfSize); // ファイルサイズ
	writeUshort(s, 0);  // bfReserved1
	writeUshort(s, 0);  // bfReserved2
	writeUint(s, 54);   // ファイル先頭から画像データまでのオフセット
}

static void saveBitmapInfoHeader(std::ostream& s, int width, int height) {
	auto biSizeImage = (width * 3 + 3) / 4 * 4 * height;
	auto bi_PixPerMeter = 3780;
	writeUint(s, 40);   // ファイルサイズ
	writeUint(s, (unsigned int)width);
	writeUint(s, (unsigned int)height);
	writeUshort(s, 1);  // biPlanes
	writeUshort(s, 24); // biBitCount
	writeUint(s, 0);    // biCompression
	writeUint(s, (unsigned int)biSizeImage);
	writeUint(s, (unsigned int)bi_PixPerMeter);
	writeUint(s, (unsigned int)bi_PixPerMeter);
	writeUint(s, 0);    // biClrUsed
	writeUint(s, 0);    // biClrImportant
}

static void save24(std::ostream& s, unsigned char* data, int width, int height) {
	const char gapData[] = { 0, 0, 0, 0 };
	auto gap = 3 - (width * 3 + 3) % 4;
	for (auto i = 0; i < height; i++) {
		s.write((char*)data + ((size_t)height - 1 - i) * width * 3, (size_t)width * 3);
		s.write(gapData, gap);
	}
}

static unsigned char* createByteRgbs(const Color* data, int width, int height) {
	auto bytes = new unsigned char[(size_t)3 * width * height];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			auto p = data[x + y * width];
			auto r = (unsigned char)(std::min(sqrt(p.r()), 1.0) * 255 + 0.5);
			auto g = (unsigned char)(std::min(sqrt(p.g()), 1.0) * 255 + 0.5);
			auto b = (unsigned char)(std::min(sqrt(p.b()), 1.0) * 255 + 0.5);
			bytes[(y * width + x) * 3] = b;
			bytes[(y * width + x) * 3 + 1] = g;
			bytes[(y * width + x) * 3 + 2] = r;
		}
	}
	return bytes;
}

static void saveAsByteBgr(std::ostream& s, const Color* data, int width, int height) {
	const int dataLen = width * 3;
	const int bmpLineLen = (dataLen + 3) & (~3);
	auto bmpLine = new char[bmpLineLen];
	for (int i = dataLen; i < bmpLineLen; i++) {
		bmpLine[dataLen + i] = 0;
	}
	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {
			auto p = data[x + y * width];
			auto r = (unsigned char)(std::min(sqrt(p.r()), 1.0) * 255 + 0.5);
			auto g = (unsigned char)(std::min(sqrt(p.g()), 1.0) * 255 + 0.5);
			auto b = (unsigned char)(std::min(sqrt(p.b()), 1.0) * 255 + 0.5);
#pragma warning(push)
#pragma warning(disable : 6386)
			// VC2022のバグで、6386(バッファオーバーラン)が警告されてしまう。
			// バッファオーバーランの解析処理は以前から不完全で、VC2022でもまだ不具合が残ったままである。
			bmpLine[x * 3] = b;
			bmpLine[x * 3 + 1] = g;
			bmpLine[x * 3 + 2] = r;
#pragma warning(pop)
		}
		s.write(bmpLine, bmpLineLen);
	}
	delete[] bmpLine;
}

void saveBmp(const std::string &filePath, const Color* data, int width, int height) {
	std::ofstream fs;
	fs.open(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
	saveBitmapFileHeader(fs, width, height);
	saveBitmapInfoHeader(fs, width, height);
	saveAsByteBgr(fs, data, width, height);
	fs.close();
}

/////
// C6386に関しては不完全らしい。以下の質問は2021/4/17のもの(VCのバージョンは不明)だが、
// 現時点(2023/9/23、VS2022では質問されていた問題は修正済みらしい。
// https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q11241844646

#if false
// C6386が警告されない

#define N 5

int* h_OK(int* b) {
	int* c = new int[N * N * N];
	if (c == NULL) {
		printf("Cannot allocate memory.\n");
		return 0;
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N - 1; j++)
			for (int k = 0; k < N - 1; k++)
				c[i * N + j * (N - 1) + k] = b[(j + 1) * (N - 1) + k];
	return c;
}
#endif

#if true
// C6386が警告される
int* h_X(int* b, int n) {
	int* c = new int[(size_t)n * n * n];
	if (c == 0) {
		printf("Cannot allocate memory.\n");
		return 0;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++)
			for (int k = 0; k < n - 1; k++)
				c[i * n + j * (n - 1) + k] = b[(j + 1) * (n - 1) + k];
	return c;
}
#endif
