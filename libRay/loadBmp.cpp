#include "loadBmp.h"
#include <fstream>
#include <functional>

static unsigned short readUshort(std::istream& s) {
	unsigned char data[2]{};
	s.read((char*)data, sizeof(data));
	return ((unsigned short)data[1]) << 8 | data[0];
}

static unsigned int readUint(std::istream& s) {
	unsigned char data[4]{};
	s.read((char*)data, sizeof(data));
	return ((unsigned int)data[3]) << 24 | ((unsigned int)data[2]) << 16 | ((unsigned int)data[1]) << 8 | data[0];
}

static void loadBitmapFileHeader(std::istream& s) {
	s.seekg(2, std::ios_base::cur);  // bfType "BM"
	s.seekg(4, std::ios_base::cur);  // ファイルサイズ
	s.seekg(2, std::ios_base::cur);  // bfReserved1
	s.seekg(2, std::ios_base::cur);  // bfReserved2
	s.seekg(4, std::ios_base::cur);  // ファイル先頭から画像データまでのオフセット
}

struct BitmapInfoHeader {
	// 必要なものだけ。
	//unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	//unsigned short biPlanes;
	unsigned short biBitCount;
	//unsigned int biCompression;
	//unsigned int biSizeImage;
	//unsigned int biXPixPerMeter;
	//unsigned int biYPixPerMeter;
	//unsigned int biClrUsed;
	//unsigned int biCirImportant;
};

static struct BitmapInfoHeader loadBitmapInfoHeader(std::istream& s) {
	BitmapInfoHeader bih{};

	s.seekg(4, std::ios_base::cur);  // biSize 40
	bih.biWidth = readUint(s);
	bih.biHeight = readUint(s);
	s.seekg(2, std::ios_base::cur);  // biPlanes 1
	bih.biBitCount = readUshort(s); // 色ビット数
	s.seekg(4, std::ios_base::cur);  // biCompression
	s.seekg(4, std::ios_base::cur);  // biSizeImage
	s.seekg(4, std::ios_base::cur);  // biXPixPerMeter
	s.seekg(4, std::ios_base::cur);  // biYPixPerMeter
	s.seekg(4, std::ios_base::cur);  // biClrUsed
	s.seekg(4, std::ios_base::cur);  // biCirImportant

	return bih;
}

static unsigned char* load24(std::istream& s, int width, int height) {
	auto data = new unsigned char[(size_t)width * height * 3];
	auto gap = (4 - width * 3 % 4) % 4;
	for (auto i = 0; i < height; i++) {
		s.read((char*)data + ((size_t)height - 1 - i) * width * 3, (size_t)width * 3);
		s.seekg(gap, std::ios_base::cur);
	}

	return data;
}

void loadBmp(const std::string& filePath, unsigned char** data, int* width, int* height) {
	std::ifstream fin(filePath, std::ios::in | std::ios::binary);
	if (!fin) {
		auto s = "failed to open \"" + filePath + "\".";
		throw std::runtime_error(s);
	}

	loadBitmapFileHeader(fin);
	auto bih = loadBitmapInfoHeader(fin);

	*width = bih.biWidth;
	*height = bih.biHeight;

	std::function<unsigned char* (std::istream&, int, int) > loadData;
	switch (bih.biBitCount) {
	case 24:
		loadData = load24;
		break;
	default:
		*data = 0;
		return;
	}
	*data = loadData(fin, (int)bih.biWidth, (int)bih.biHeight);

	fin.close();
}
