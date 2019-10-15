#pragma once

// 二次元構造体
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x, int y);	// 引数付きｺﾝｽﾄﾗｸﾀｰ
	VECTOR2(int x_y);		// 引数付きｺﾝｽﾄﾗｸﾀｰ

	~VECTOR2();

	int x;
	int y;

	//代入演算子
	VECTOR2& operator = (const VECTOR2& vec);

	//添え字演算子
	int& operator[](int i);

	//比較演算子
	bool operator==(const VECTOR2& vec) const;
	bool operator!=(const VECTOR2& vec) const;

	//単項演算子
	VECTOR2& operator+=(const VECTOR2& vec);
	VECTOR2& operator-=(const VECTOR2& vec);
	VECTOR2& operator*=(int i);
	VECTOR2& operator/=(int i);

	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
};

// ベクトルの演算
//VECTOR2+VECTOR2
VECTOR2 operator+(const VECTOR2& vec1, const VECTOR2& vec2);
// VECTOR2-VECTOR2
VECTOR2 operator-(const VECTOR2& vec1, const VECTOR2& vec2);
// VECTOR2*int
VECTOR2 operator*(const VECTOR2& vec, int i);
// int*VECTOR2
VECTOR2 operator*(int i, const VECTOR2& vec);
// VECTOR2/int
VECTOR2 operator/(const VECTOR2& vec, int i);
// VECTOR2/int
VECTOR2 operator%(const VECTOR2& vec, int i);

