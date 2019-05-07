#include "VECTOR2.h"

VECTOR2::VECTOR2()
{
	x = 0;
	y = 0;
}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;
	this->y = y;		
}

VECTOR2::VECTOR2(int x_y)
{
	this->x = x_y;
	this->y = x_y;
}

VECTOR2::~VECTOR2()
{
}

//‘ã“ü‰‰ŽZŽq
VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

//“Y‚¦Žš‰‰ŽZŽq
int & VECTOR2::operator[](int i)
{
	// 1‚ÌŽžYƒ[ƒ‚ÌŽžX‚ð‚©‚¦‚·
	if (i == 0)
	{
		return this->x;
	}
	else if(i == 1)
	{
		return this->y;
	}
	else
	{
		return this->x;		
	}
}

//”äŠr‰‰ŽZŽq
bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return (this->x == vec.x) && (this->y == vec.y);
}

bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	// !((this->x == vec.x) && (this->y == vec.y));
	return (this->x != vec.x) || (this->y != vec.y);
}

bool VECTOR2::operator<=(const VECTOR2 & vec) const
{
	return (this->x <= vec.x) && (this->y <= vec.y);
}

bool VECTOR2::operator<(const VECTOR2 & vec) const
{
	return (this->x < vec.x) && (this->y < vec.y);
}

//’P€‰‰ŽZŽq
VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}

VECTOR2 & VECTOR2::operator/=(int k)
{
	this->x /= k;
	this->y /= k;
	return *this;
}

VECTOR2 VECTOR2::operator+() const
{
	return *this;
}

VECTOR2 VECTOR2::operator-() const
{
	return VECTOR2(-this->x, -this->y);
}

// ƒxƒNƒgƒ‹‚ÆƒxƒNƒgƒ‹‚Ì‰‰ŽZ
// VECTOR2+VECTOR2
VECTOR2 operator+(const VECTOR2& vec1, const VECTOR2& vec2)
{
	return VECTOR2(vec1.x+vec2.x,vec1.y+vec2.y);
}
// VECTOR2-VECTOR2
VECTOR2 operator-(const VECTOR2 & vec1, const VECTOR2 & vec2)
{
	return VECTOR2(vec1.x - vec2.x, vec1.y - vec2.y);
}
// VECTOR2*int
VECTOR2 operator*(const VECTOR2 & vec, int i)
{
	return VECTOR2(vec.x * i, vec.y * i);
}
// int*VECTOR2
VECTOR2 operator*(int i, const VECTOR2 & vec)
{
	return VECTOR2( i * vec.x, i * vec.y);
}
// VECTOR2/int
VECTOR2 operator/(const VECTOR2 & vec, int i)
{
	return VECTOR2(vec.x / i, vec.y / i);
}

VECTOR2 operator%(const VECTOR2 & vec, int i)
{
	return VECTOR2(vec.x % i, vec.y % i);
}
