#include "declarations.hpp"

#define PI 3.14159265359f
#define FLOAT_MIN_PRECISION 0.001f
#define Deg2Rad(x) ((x) * (PI / 180))
#define Rad2Deg(x) ((x) * (180 / PI))
#define LERP(from, to, t) ((to) * (t) + (from) * (1 - (t)))


vector2::vector2(const vector4& xy)
    : x(xy.x), y(xy.y)
{
}
vector2::vector2(const vector3& xy)
    : x(xy.x), y(xy.y)
{
}
vector2::vector2(float x, float y)
    : x(x), y(y)
{
}

float vector2::operator[](int i) const
{
    return ((float*)this)[i];
}
float& vector2::operator[](int i)
{
    return ((float*)this)[i];
}
bool vector2::operator==(const vector2& other) const
{
    for (int i = 0; i < Size; ++i)
        if (fabsf((*this)[i] - other[i]) > FLOAT_MIN_PRECISION)
            return false;

    return true;
}
bool vector2::operator!=(const vector2& other) const
{
    return !(*this == other);
}
vector2 vector2::operator-() const
{
    return vector2(-x, -y);
}

vector2 vector2::operator+(const vector2& other) const
{
    return vector2(x + other.x, y + other.y);
}
vector2 vector2::operator-(const vector2& other) const
{
    return *this + (-other);
}
vector2 vector2::operator+(float other) const
{
    return vector2(x + other, y + other);
}
vector2 vector2::operator-(float other) const
{
    return *this + (-other);
}
vector2 vector2::operator*(float other) const
{
    return vector2(x * other, y * other);
}
vector2 vector2::operator/(float other) const
{
    return *this * (1.f / other);
}

vector2& vector2::operator+=(const vector2& other)
{
    return *this = *this + other;
}
vector2& vector2::operator-=(const vector2& other)
{
    return *this = *this - other;
}
vector2& vector2::operator+=(float other)
{
    return *this = *this + other;
}
vector2& vector2::operator-=(float other)
{
    return *this = *this - other;
}
vector2& vector2::operator*=(float other)
{
    return *this = *this * other;
}
vector2& vector2::operator/=(float other)
{
    return *this = *this / other;
}

float vector2::magnitude() const
{
    return base::memory::_sqrtf(dot(*this, *this));
}
vector2 vector2::orthagonal() const
{
    return vector2(-y, x);
}
vector2 vector2::normalized() const
{
    return *this / magnitude();
}
void vector2::normalize()
{
    *this /= magnitude();
}
float vector2::distance(const vector2& a, const vector2& b)
{
    return (a - b).magnitude();
}
float vector2::dot(const vector2& a, const vector2& b)
{
    return a.x * b.x + a.y * b.y;
}
vector2 vector2::lerp(const vector2& from, const vector2& to, float t)
{
    return LERP(from, to, t);
}
float vector2::angle(const vector2& a, const vector2& b)
{
    return Rad2Deg(base::memory::_acosf(dot(a, b) / (a.magnitude() * b.magnitude())));
}
vector2 vector2::scale(const vector2& a, const vector2& b)
{
    return vector2(a.x * b.x, a.y * b.y);
}

const vector2 vector2::one = vector2(1.f, 1.f);
const vector2 vector2::zero = vector2(0.f, 0.f);
const vector2 vector2::up = vector2(0.f, 1.f);
const vector2 vector2::down = vector2(0.f, -1.f);
const vector2 vector2::right = vector2(1.f, 0.f);
const vector2 vector2::left = vector2(-1.f, 0.f);

vector3::vector3(const vector4& xyz)
    : x(xyz.x), y(xyz.y), z(xyz.z)
{
}

vector3::vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

float vector3::operator[](int i) const
{
    return ((float*)this)[i];
}
float& vector3::operator[](int i)
{
    return ((float*)this)[i];
}
bool vector3::operator==(const vector3& other) const
{
    for (int i = 0; i < Size; ++i)
        if (base::memory::_fabsf((*this)[i] - other[i]) > FLOAT_MIN_PRECISION)
            return false;

    return true;
}
bool vector3::operator!=(const vector3& other) const
{
    return !(*this == other);
}
vector3 vector3::operator-() const
{
    return vector3(-x, -y, -z);
}

vector3 vector3::operator+(const vector3& other) const
{
    return vector3(x + other.x, y + other.y, z + other.z);
}
vector3 vector3::operator-(const vector3& other) const
{
    return *this + (-other);
}
vector3 vector3::operator+(float other) const
{
    return vector3(x + other, y + other, z + other);
}
vector3 vector3::operator-(float other) const
{
    return *this + (-other);
}
vector3 vector3::operator*(float other) const
{
    return vector3(x * other, y * other, z * other);
}
vector3 vector3::operator/(float other) const
{
    return *this * (1.f / other);
}

vector3& vector3::operator+=(const vector3& other)
{
    return *this = *this + other;
}
vector3& vector3::operator-=(const vector3& other)
{
    return *this = *this - other;
}
vector3& vector3::operator+=(float other)
{
    return *this = *this + other;
}
vector3& vector3::operator-=(float other)
{
    return *this = *this - other;
}
vector3& vector3::operator*=(float other)
{
    return *this = *this * other;
}
vector3& vector3::operator/=(float other)
{
    return *this = *this / other;
}

float vector3::magnitude() const
{
    return base::memory::_sqrtf(dot(*this, *this));
}
vector3 vector3::normalized() const
{
    return *this / magnitude();
}
void vector3::normalize()
{
    *this /= magnitude();
}

float vector3::distance(const vector3& a, const vector3& b)
{
    return (a - b).magnitude();
}
float vector3::dot(const vector3& a, const vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
vector3 vector3::cross(const vector3& a, const vector3& b)
{
    return vector3(a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x, a.x * b.y - a.y * b.x);
}
vector3 vector3::lerp(const vector3& from, const vector3& to, float t)
{
    return LERP(from, to, t);
}
float vector3::angle(const vector3& a, const vector3& b)
{
    return Rad2Deg(base::memory::_acosf(dot(a, b) / (a.magnitude() * b.magnitude())));
}
vector3 vector3::scale(const vector3& a, const vector3& b)
{
    return vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

const vector3 vector3::one = vector3(1.f, 1.f, 1.f);
const vector3 vector3::zero = vector3(0.f, 0.f, 0.f);
const vector3 vector3::up = vector3(0.f, 1.f, 0.f);
const vector3 vector3::down = vector3(0.f, -1.f, 0.f);
const vector3 vector3::right = vector3(1.f, 0.f, 0.f);
const vector3 vector3::left = vector3(-1.f, 0.f, 0.f);
const vector3 vector3::forward = vector3(0.f, 0.f, 1.f);
const vector3 vector3::backWard = vector3(0.f, 0.f, -1.f);

vector4::vector4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
{
}
vector4::vector4(const vector2& xy, float z, float w)
    : x(xy.x), y(xy.y), z(z), w(w)
{
}
vector4::vector4(const vector3& xyz, float w)
    : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
{
}

float vector4::operator[](int i) const
{
    return ((float*)this)[i];
}
float& vector4::operator[](int i)
{
    return ((float*)this)[i];
}
bool vector4::operator==(const vector4& other) const
{
    for (int i = 0; i < Size; ++i)
        if (base::memory::_fabsf((*this)[i] - other[i]) > FLOAT_MIN_PRECISION)
            return false;

    return true;
}
bool vector4::operator!=(const vector4& other) const
{
    return !(*this == other);
}
vector4 vector4::operator-() const
{
    return vector4(-x, -y, -z, -w);
}

vector4 vector4::operator+(const vector4& other) const
{
    return vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}
vector4 vector4::operator-(const vector4& other) const
{
    return *this + (-other);
}
vector4 vector4::operator+(float other) const
{
    return vector4(x + other, y + other, z + other, w + other);
}
vector4 vector4::operator-(float other) const
{
    return *this + (-other);
}
vector4 vector4::operator*(float other) const
{
    return vector4(x * other, y * other, z * other, w * other);
}
vector4 vector4::operator/(float other) const
{
    return *this * (1.f / other);
}

vector4& vector4::operator+=(const vector4& other)
{
    return *this = *this + other;
}
vector4& vector4::operator-=(const vector4& other)
{
    return *this = *this - other;
}
vector4& vector4::operator+=(float other)
{
    return *this = *this + other;
}
vector4& vector4::operator-=(float other)
{
    return *this = *this - other;
}
vector4& vector4::operator*=(float other)
{
    return *this = *this * other;
}
vector4& vector4::operator/=(float other)
{
    return *this = *this / other;
}

float vector4::magnitude() const
{
    return base::memory::_sqrtf(dot(*this, *this));
}
vector4 vector4::normalized() const
{
    return *this / magnitude();
}
void vector4::normalize()
{
    *this /= magnitude();
}

float vector4::distance(const vector4& a, const vector4& b)
{
    return (a - b).magnitude();
}
float vector4::dot(const vector4& a, const vector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
vector4 vector4::lerp(const vector4& from, const vector4& to, float t)
{
    return LERP(from, to, t);
}
vector4 vector4::scale(const vector4& a, const vector4& b)
{
    return vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

const vector4 vector4::One = vector4(1.f, 1.f, 1.f, 1.f);
const vector4 vector4::Zero = vector4(0.f, 0.f, 0.f, 0.f);

matrix4x4::matrix4x4(
    float mm00, float mm01, float mm02, float mm03,
    float mm10, float mm11, float mm12, float mm13,
    float mm20, float mm21, float mm22, float mm23,
    float mm30, float mm31, float mm32, float mm33
)
    : m{
        mm00, mm01, mm02, mm03,
        mm10, mm11, mm12, mm13,
        mm20, mm21, mm22, mm23,
        mm30, mm31, mm32, mm33
}
{
}
matrix4x4 matrix4x4::from_rows( // can use for loop
    const vector4& row0,
    const vector4& row1,
    const vector4& row2,
    const vector4& row3
)
{
    return matrix4x4(
        row0.x, row0.y, row0.z, row0.w,
        row1.x, row1.y, row1.z, row1.w,
        row2.x, row2.y, row2.z, row2.w,
        row3.x, row3.y, row3.z, row3.w
    );
}
matrix4x4 matrix4x4::from_columns( // can use for loop
    const vector4& column0,
    const vector4& column1,
    const vector4& column2,
    const vector4& column3
)
{
    return matrix4x4(
        column0.x, column1.x, column2.x, column3.x,
        column0.y, column1.y, column2.y, column3.y,
        column0.z, column1.z, column2.z, column3.z,
        column0.w, column1.w, column2.w, column3.w
    );
}

float matrix4x4::operator()(int i) const
{
    return ((float*)m)[i];
}
float& matrix4x4::operator()(int i)
{
    return ((float*)m)[i];
}
float matrix4x4::operator()(int i, int j) const
{
    return m[i][j];
}
float& matrix4x4::operator()(int i, int j)
{
    return m[i][j];
}
bool matrix4x4::operator==(const matrix4x4& other) const
{
    for (int i = 0; i < rows; ++i)
        if (get_row(i) != other.get_row(i))
            return false;

    return true;
}
bool matrix4x4::operator!=(const matrix4x4& other) const
{
    return !(*this == other);
}
matrix4x4 matrix4x4::operator-() const // can use for loop
{
    return matrix4x4(
        -m[0][0], -m[0][1], -m[0][2], -m[0][3],
        -m[1][0], -m[1][1], -m[1][2], -m[1][3],
        -m[2][0], -m[2][1], -m[2][2], -m[2][3],
        -m[3][0], -m[3][1], -m[3][2], -m[3][3]
    );
}

matrix4x4 matrix4x4::operator+(const matrix4x4& other) const // can use for loop
{
    return matrix4x4(
        m[0][0] + other(0, 0), m[0][1] + other(0, 1), m[0][2] + other(0, 2), m[0][3] + other(0, 3),
        m[1][0] + other(1, 0), m[1][1] + other(1, 1), m[1][2] + other(1, 2), m[1][3] + other(1, 3),
        m[2][0] + other(2, 0), m[2][1] + other(2, 1), m[2][2] + other(2, 2), m[2][3] + other(2, 3),
        m[3][0] + other(3, 0), m[3][1] + other(3, 1), m[3][2] + other(3, 2), m[3][3] + other(3, 3)
    );
}
matrix4x4 matrix4x4::operator-(const matrix4x4& other) const
{
    return *this + (-other);
}
matrix4x4 matrix4x4::operator*(const matrix4x4& other) const // can use for loop
{
    return matrix4x4(
        vector4::dot(get_row(0), other.get_column(0)),
        vector4::dot(get_row(0), other.get_column(1)),
        vector4::dot(get_row(0), other.get_column(2)),
        vector4::dot(get_row(0), other.get_column(3)),

        vector4::dot(get_row(1), other.get_column(0)),
        vector4::dot(get_row(1), other.get_column(1)),
        vector4::dot(get_row(1), other.get_column(2)),
        vector4::dot(get_row(1), other.get_column(3)),

        vector4::dot(get_row(2), other.get_column(0)),
        vector4::dot(get_row(2), other.get_column(1)),
        vector4::dot(get_row(2), other.get_column(2)),
        vector4::dot(get_row(2), other.get_column(3)),

        vector4::dot(get_row(3), other.get_column(0)),
        vector4::dot(get_row(3), other.get_column(1)),
        vector4::dot(get_row(3), other.get_column(2)),
        vector4::dot(get_row(3), other.get_column(3))
    );
}
vector4 matrix4x4::operator*(const vector4& other) const // can use for loop
{
    return vector4(
        vector4::dot(get_row(0), other),
        vector4::dot(get_row(1), other),
        vector4::dot(get_row(2), other),
        vector4::dot(get_row(3), other)
    );
}
matrix4x4 matrix4x4::operator*(float other) const // can use for loop
{
    return matrix4x4(
        m[0][0] * other, m[0][1] * other, m[0][2] * other, m[0][3] * other,
        m[1][0] * other, m[1][1] * other, m[1][2] * other, m[1][3] * other,
        m[2][0] * other, m[2][1] * other, m[2][2] * other, m[2][3] * other,
        m[3][0] * other, m[3][1] * other, m[3][2] * other, m[3][3] * other
    );
}
matrix4x4 matrix4x4::operator/(float other) const
{
    return *this * (1.f / other);
}

matrix4x4& matrix4x4::operator+=(const matrix4x4& other)
{
    return *this = *this + other;
}
matrix4x4& matrix4x4::operator-=(const matrix4x4& other)
{
    return *this = *this - other;
}
matrix4x4& matrix4x4::operator*=(const matrix4x4& other)
{
    return *this = *this * other;
}
matrix4x4& matrix4x4::operator*=(float other)
{
    return *this = *this * other;
}
matrix4x4& matrix4x4::operator/=(float other)
{
    return *this = *this / other;
}

vector4 matrix4x4::get_row(int i) const // can use for loop
{
    return vector4(m[i][0], m[i][1], m[i][2], m[i][3]);
}
vector4 matrix4x4::get_column(int i) const // can use for loop
{
    return vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
}
void matrix4x4::set_row(int i, const vector4& row) // can use for loop
{
    m[i][0] = row.x;
    m[i][1] = row.y;
    m[i][2] = row.z;
    m[i][3] = row.w;
}
void matrix4x4::set_column(int i, const vector4& column) // can use for loop
{
    m[0][i] = column.x;
    m[1][i] = column.y;
    m[2][i] = column.z;
    m[3][i] = column.w;
}

float matrix4x4::determinant() const
{
    return det(*this, columns);
}
matrix4x4 matrix4x4::transpose() const // can use for loop
{
    return matrix4x4::from_rows(
        get_column(0),
        get_column(1),
        get_column(2),
        get_column(3)
    );
}
matrix4x4 matrix4x4::minor(int i, int j) const
{
    matrix4x4 mat = zero;
    for (int minorRow = 0, row = 0; row < columns; ++minorRow, ++row)
    {
        if (row == i)
        {
            --minorRow;
            continue;
        }

        for (int minorCol = 0, col = 0; col < rows; ++minorCol, ++col)
        {
            if (col == j)
            {
                --minorCol;
                continue;
            }

            mat(minorRow, minorCol) = m[row][col];
        }
    }

    return mat;
}
matrix4x4 matrix4x4::adjoint() const
{
    matrix4x4 adjoint = zero;

    int sign = 1;
    for (int row = 0; row < rows; ++row) // cofactor matrix
    {
        for (int col = 0; col < columns; ++col)
        {
            sign = ((row + col) & 1) ? -1 : 1;

            matrix4x4 min = minor(row, col);
            adjoint(row, col) = sign * (det(min, columns - 1));
        }
    }

    return adjoint.transpose();
}
matrix4x4 matrix4x4::inverse() const
{
    return adjoint() / determinant();
}

matrix4x4 matrix4x4::translation(const vector3& point)
{
    return matrix4x4(
        1.f, 0.f, 0.f, point.x,
        0.f, 1.f, 0.f, point.y,
        0.f, 0.f, 1.f, point.z,
        0.f, 0.f, 0.f, 1.f
    );
}
matrix4x4 matrix4x4::scale(const vector3& scales)
{
    return matrix4x4(
        scales.x, 0.f, 0.f, 0.f,
        0.f, scales.y, 0.f, 0.f,
        0.f, 0.f, scales.z, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}
matrix4x4 matrix4x4::rotation(const vector3& angs) // PROB NOT CORRECT
{
    return
        matrix4x4::rotationX(angs.x) *
        matrix4x4::rotationY(angs.y) *
        matrix4x4::rotationZ(angs.z);
}
matrix4x4 matrix4x4::rotationX(float pitch)
{
    pitch = Deg2Rad(pitch);
    return matrix4x4(
        1.f, 0.f, 0.f, 0.f,
        0.f, base::memory::_cosf(pitch), -base::memory::_sinf(pitch), 0.f,
        0.f, base::memory::_sinf(pitch), base::memory::_cosf(pitch), 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}
matrix4x4 matrix4x4::rotationY(float yaw)
{
    yaw = Deg2Rad(yaw);
    return matrix4x4(
        base::memory::_cosf(yaw), 0.f, base::memory::_sinf(yaw), 0.f,
        0.f, 1.f, 0.f, 0.f,
        -base::memory::_sinf(yaw), 0.f, base::memory::_cosf(yaw), 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}
matrix4x4 matrix4x4::rotationZ(float roll)
{
    roll = Deg2Rad(roll);
    return matrix4x4(
        base::memory::_cosf(roll), -base::memory::_sinf(roll), 0.f, 0.f,
        base::memory::_sinf(roll), base::memory::_cosf(roll), 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );
}
matrix4x4 matrix4x4::aspectRatio(float ratio)
{
    matrix4x4 ret = identity;
    ret(0, 0) = 1 / ratio;
    return ret;
}

const matrix4x4 matrix4x4::identity = matrix4x4(
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
);
const matrix4x4 matrix4x4::zero = matrix4x4(
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f
);

float matrix4x4::det(const matrix4x4& matrix, int n)
{
    if (n == 1)
        return matrix(0, 0);

    float d = 0;

    int sign = 1;
    for (int i = 0; i < n; ++i)
    {
        matrix4x4 min = matrix.minor(0, i);

        d += matrix(0, i) * sign * det(min, n - 1);
        sign = -sign;
    }

    return d;
}