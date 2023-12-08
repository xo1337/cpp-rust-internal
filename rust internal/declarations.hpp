#pragma once
#include <imgui.h>

#define M_PI 3.14159265358979323846264338327950288419716939937510
#define DEG_TO_RAD(x) x * (M_PI / 180.f)

#define RAD2DEG(x) ((float)(x) * (float)(180.f / (float)(M_PI)))

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
#define LOBYTE(x)   (*((BYTE*)&(x))) 
#define LOWORD(x)   (*((WORD*)&(x)))  
#define LODWORD(x)  (*((DWORD*)&(x)))  
#define HIBYTE(x)   (*((BYTE*)&(x)+1))
#define HIWORD(x)   (*((WORD*)&(x)+1))
#define HIDWORD(x)  (*((DWORD*)&(x)+1))

typedef unsigned __int64 _QWORD;
typedef unsigned char _BYTE;
typedef DWORD _DWORD;

class vector2;
class vector3;
class vector4;

class vector2
{
public:
	float x, y;

	vector2(const vector4& xy);
	vector2(const vector3& xy);
	vector2(float x = 0.f, float y = 0.f);

	float operator[](int i) const;
	float& operator[](int i);
	bool operator==(const vector2& other) const;
	bool operator!=(const vector2& other) const;
	vector2 operator-() const;

	vector2 operator+(const vector2& other) const;
	vector2 operator-(const vector2& other) const;
	vector2 operator+(float other) const;
	vector2 operator-(float other) const;
	vector2 operator*(float other) const;
	vector2 operator/(float other) const;

	vector2& operator+=(const vector2& other);
	vector2& operator-=(const vector2& other);
	vector2& operator+=(float other);
	vector2& operator-=(float other);
	vector2& operator*=(float other);
	vector2& operator/=(float other);

	float magnitude() const;
	vector2 orthagonal() const;
	vector2 normalized()const;
	void normalize();

	static float distance(const vector2& a, const vector2& b);
	static float dot(const vector2& a, const vector2& b);
	static vector2 lerp(const vector2& from, const vector2& to, float t);
	static float angle(const vector2& from, const vector2& to);
	static vector2 scale(const vector2& a, const vector2& b);

	static const vector2 one;
	static const vector2 zero;
	static const vector2 up;
	static const vector2 down;
	static const vector2 right;
	static const vector2 left;

private:
	static const int Size = 2;
};

class vector3
{
public:
	float x, y, z;

	vector3(const vector4& xyz);
	vector3(float x = 0.f, float y = 0.f, float z = 0.f);

	float operator[](int i) const;
	float& operator[](int i);
	bool operator==(const vector3& other) const;
	bool operator!=(const vector3& other) const;
	vector3 operator-() const;

	vector3 operator+(const vector3& other) const;
	vector3 operator-(const vector3& other) const;
	vector3 operator+(float other) const;
	vector3 operator-(float other) const;
	vector3 operator*(float other) const;
	vector3 operator/(float other) const;

	vector3& operator+=(const vector3& other);
	vector3& operator-=(const vector3& other);
	vector3& operator+=(float other);
	vector3& operator-=(float other);
	vector3& operator*=(float other);
	vector3& operator/=(float other);

	float magnitude() const;
	vector3 normalized() const;
	void normalize();

	static float distance(const vector3& a, const vector3& b);
	static float dot(const vector3& a, const vector3& b);
	static vector3 cross(const vector3& a, const vector3& b);
	static vector3 lerp(const vector3& from, const vector3& to, float t);
	static float angle(const vector3& from, const vector3& to);
	static vector3 scale(const vector3& a, const vector3& b);

	static const vector3 one;
	static const vector3 zero;
	static const vector3 up;
	static const vector3 down;
	static const vector3 right;
	static const vector3 left;
	static const vector3 forward;
	static const vector3 backWard;

private:
	static const int Size = 3;
};

class vector4
{
public:
	float x, y, z, w;

	vector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f);
	vector4(const vector2& xy, float z = 0.f, float w = 0.f);
	vector4(const vector3& xyz, float w = 0.f);

	float operator[](int i) const;
	float& operator[](int i);
	bool operator==(const vector4& other) const;
	bool operator!=(const vector4& other) const;
	vector4 operator-() const;

	vector4 operator+(const vector4& other) const;
	vector4 operator-(const vector4& other) const;
	vector4 operator+(float other) const;
	vector4 operator-(float other) const;
	vector4 operator*(float other) const;
	vector4 operator/(float other) const;

	vector4& operator+=(const vector4& other);
	vector4& operator-=(const vector4& other);
	vector4& operator+=(float other);
	vector4& operator-=(float other);
	vector4& operator*=(float other);
	vector4& operator/=(float other);

	float magnitude() const;
	vector4 normalized()const;
	void normalize();

	static float distance(const vector4& a, const vector4& b);
	static float dot(const vector4& a, const vector4& b);
	static vector4 lerp(const vector4& from, const vector4& to, float t);
	static vector4 scale(const vector4& a, const vector4& b);

	static const vector4 One;
	static const vector4 Zero;

private:
	static const int Size = 4;
};

class matrix4x4
{
public:
	matrix4x4(
		float mm00 = 0.f, float mm01 = 0.f, float mm02 = 0.f, float mm03 = 0.f,
		float mm10 = 0.f, float mm11 = 0.f, float mm12 = 0.f, float mm13 = 0.f,
		float mm20 = 0.f, float mm21 = 0.f, float mm22 = 0.f, float mm23 = 0.f,
		float mm30 = 0.f, float mm31 = 0.f, float mm32 = 0.f, float mm33 = 0.f
	);
	static matrix4x4 from_rows(const vector4& row0, const vector4& row1, const vector4& row2, const vector4& row3);
	static matrix4x4 from_columns(const vector4& column0, const vector4& column1, const vector4& column2, const vector4& column3);

	float operator()(int i) const;
	float& operator()(int i);
	float operator()(int i, int j) const;
	float& operator()(int i, int j);
	bool operator==(const matrix4x4& other) const;
	bool operator!=(const matrix4x4& other) const;
	matrix4x4 operator-() const;

	matrix4x4 operator+(const matrix4x4& other) const;
	matrix4x4 operator-(const matrix4x4& other) const;
	matrix4x4 operator*(const matrix4x4& other) const;
	vector4 operator*(const vector4& other) const;
	matrix4x4 operator*(float other) const;
	matrix4x4 operator/(float other) const;

	matrix4x4& operator+=(const matrix4x4& other);
	matrix4x4& operator-=(const matrix4x4& other);
	matrix4x4& operator*=(const matrix4x4& other);
	matrix4x4& operator*=(float other);
	matrix4x4& operator/=(float other);

	vector4 get_row(int i) const;
	vector4 get_column(int i) const;
	void set_row(int i, const vector4& row);
	void set_column(int i, const vector4& column);

	float determinant() const;
	matrix4x4 transpose() const;
	matrix4x4 minor(int i, int j) const;
	matrix4x4 adjoint() const;
	matrix4x4 inverse() const;

	static matrix4x4 translation(const vector3& point);
	static matrix4x4 scale(const vector3& scales);
	static matrix4x4 rotation(const vector3& angs);
	static matrix4x4 rotationX(float pitch);
	static matrix4x4 rotationY(float yaw);
	static matrix4x4 rotationZ(float roll);
	static matrix4x4 aspectRatio(float ratio);

	static const matrix4x4 identity;
	static const matrix4x4 zero;

private:
	union
	{
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};

		float m[4][4];
	};

	static const int rows = 4;
	static const int columns = 4;

	static float det(const matrix4x4& matrix, int n);
};

namespace base
{
	inline void draw_text(ImFont* font, int x, int y, ImColor color, const char* str)
	{
		if (font == nullptr)
		{
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, str);
		}
		else
		{
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), str);
			ImGui::GetBackgroundDrawList()->AddText(font, font->FontSize, ImVec2(x, y), color, str);
		}
	}

	inline void normalize_angles(float& Yaw, float& Pitch) 
	{
		if (Pitch < -89) Pitch = -89;
		else if (Pitch > 89) Pitch = 89;
		if (Yaw < -180) Yaw += 360;
		else if (Yaw > 180) Yaw -= 360;
	}

	inline vector2 calc_angles(const vector3& Src, const vector3& Dst) 
	{
		vector3 dir = Src - Dst;
		auto length = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);

		return vector2{ RAD2DEG(asin(dir.y / length)), RAD2DEG(-atan2(dir.x, -dir.z)) };
	}

	inline float distance_2d(float fromX, float fromY, float toX, float toY)
	{
		float a = memory::_abs(fromX - toX);
		float b = memory::_abs(fromY - toY);
		return memory::_sqrt((a * a) + (b * b));
	}

	inline bool in_fov(int fovX, int fovY, int aimFOV, int x, int y)
	{
		float dist = memory::_sqrt(memory::_abs(fovX - x) * memory::_abs(fovX - x) + memory::_abs(fovY - y) * memory::_abs(fovY - y));
		return (dist < aimFOV) ? true : false;
	}

	inline void draw_corner_box(ImDrawList* drawlist, ImVec2 pos, ImVec2 dim, ImColor col, int thick)
	{
		if (!drawlist) return;

		float cornersizex = dim.x / 3;
		float cornersizey = dim.y / 4;

		drawlist->AddLine(ImVec2(pos), ImVec2(pos.x - cornersizex, pos.y), col, thick);
		drawlist->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2((pos.x - dim.x) + cornersizex, pos.y), col, thick);
		drawlist->AddLine(ImVec2(pos.x - dim.x, pos.y), ImVec2(pos.x - dim.x, pos.y - cornersizey), col, thick);
		drawlist->AddLine(ImVec2(pos.x - dim.x, (pos.y - dim.y)), ImVec2(pos.x - dim.x, (pos.y - dim.y) + cornersizey), col, thick);
		drawlist->AddLine(ImVec2(pos.x - dim.x, (pos.y - dim.y)), ImVec2((pos.x - dim.x) + cornersizex, pos.y - dim.y), col, thick);
		drawlist->AddLine(ImVec2(pos.x, (pos.y - dim.y)), ImVec2(pos.x - cornersizex, pos.y - dim.y), col, thick);
		drawlist->AddLine(ImVec2(pos.x, (pos.y - dim.y)), ImVec2(pos.x, (pos.y - dim.y) + cornersizey), col, thick);
		drawlist->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y - cornersizey), col, thick);
	}

	inline void draw_outlined_rect(ImDrawList* draw_list, const ImVec2& pos_start, const ImVec2& pos_end, const ImColor& foreground_color = ImColor(255, 255, 255, 255), const ImColor& background_color = ImColor(0, 0, 0, 255), const float& offset = 1.f, const float& thickness = 1.f, const float& rounding = 0.f, const ImDrawFlags& flags = 0)
	{
		draw_list->AddRect(ImVec2(pos_start.x - offset * thickness, pos_start.y - offset * thickness), ImVec2(pos_end.x + offset * thickness, pos_end.y + offset * thickness), background_color, rounding, flags, thickness);
		draw_list->AddRect(ImVec2(pos_start.x + offset * thickness, pos_start.y + offset * thickness), ImVec2(pos_end.x - offset * thickness, pos_end.y - offset * thickness), background_color, rounding, flags, thickness);
		draw_list->AddRect(pos_start, pos_end, foreground_color, rounding, flags, thickness);
	}

	inline ImColor convert_color(float* color)
	{
		return ImColor(color[0], color[1], color[2], color[3]);
	}

}