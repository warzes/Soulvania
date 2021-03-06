#pragma once

// TODO: ???????????? ?? ???????

namespace base
{
	struct Color
	{
	public:
		Color(int r, int g, int b);
		Color(int r, int g, int b, int alpha);

		unsigned long Get();

		int A();
		int R();
		int G();
		int B();

		std::string ToString();

		static Color Transparent();
		static Color Black();
		static Color Blue();
		static Color DimGray();
		static Color Gold();
		static Color Green();
		static Color LavenderBlue();
		static Color Magenta();
		static Color Orange();
		static Color Orchid();
		static Color Red();
		static Color White();
		static Color YellowGreen();

		Color operator*(float scale);
		bool operator==(Color other);
		bool operator!=(Color other);

		static Color FromRgb(std::string rgb);
		static Color FromArgb(std::string rgba);

	private:
		unsigned long packedValue;
	};
}