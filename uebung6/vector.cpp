#include <iostream>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Vector3d
{
	double x_;
	double y_;
	double z_;
public:
	Vector3d(double x = 0, double y = 0, double z = 0) {
		x_ = x;
		y_ = y;
		z_ = z;
	}
	~Vector3d() {};

	double& operator[](std::size_t idx){
		switch (idx) {
		case 0: return x_;
		case 1: return y_;
		case 2: return z_;
		default: throw new std::out_of_range("Vector3d only has 3 elements");
		}
	}
	double operator[](std::size_t idx) const {
		switch (idx) {
		case 0: return x_;
		case 1: return y_;
		case 2: return z_;
		default: throw new std::out_of_range("Vector3d only has 3 elements");
		}
	}

	double length() const
	{
		return std::sqrt(dot(*this));
	}

	double dot(const Vector3d& v1) const
	{
		return v1.x_ *x_ + v1.y_ * y_ + v1.z_ * z_;
	}
	void normalize()
	{
		double len = length();
		*this = *this/len;
	}
	Vector3d cross(const Vector3d& v1) const
	{
		return Vector3d{
			v1.y_ * z_ - v1.z_ * y_,
			v1.z_ * x_ - v1.x_ * z_,
			v1.x_ * y_ - v1.y_ * x_ };
	}

	
	Vector3d operator=(const Vector3d& v)
	{
		if (this != &v) {
			x_ = v[0];
			y_ = v[1];
			z_ = v[2];
		}
		return *this;
	}
	Vector3d operator+(const Vector3d& v) const
	{
		return Vector3d{ v[0] + x_, v[1] + y_ , v[2] + z_ };
	}
	Vector3d operator+=(const Vector3d& v)
	{
		return *this=(*this + v);
	}	
	Vector3d operator-(const Vector3d& v) const
	{
		return Vector3d{ v[0] - x_, v[1] - y_ , v[2] - z_ };
	}
	Vector3d operator-() const
	{
		return Vector3d{-x_, -y_ , -z_ };
	}
	Vector3d operator-=(const Vector3d& v)
	{
		return *this = (*this - v);
	}
	Vector3d operator*(double scalar) const
	{
		return Vector3d{ x_ * scalar, y_ * scalar, z_ * scalar };
	}
	Vector3d operator/(double scalar) const
	{
		assert(scalar);
		return Vector3d{ x_ / scalar, y_ / scalar, z_ / scalar };
	}
	bool operator==(Vector3d& v1) const
	{
		return v1[0] == x_ && v1[1] == y_ && v1[2] == x_;
	}
	bool operator!=(Vector3d& v1) const
	{
		return !(*this == v1);
	}
	
};

std::ostream& operator<<(std::ostream& os, const Vector3d& v) {
	os << "(" << v[0] << "," << v[1] << "," << v[2] << ")" << std::endl;
	return os;
}
/*
Vector3d operator+(const Vector3d& v1, const Vector3d& v2)
{
	return v1 + v2;
}

Vector3d operator-(const Vector3d& v1, const Vector3d& v2)
{
	return v1 - v2;
}*/

Vector3d operator*(double scalar, const Vector3d& v)
{
	return v*scalar;
}

Vector3d cross(const Vector3d& v1, const Vector3d& v2)
{
	return v1.cross(v2);
}

double dot(const Vector3d& v1, const Vector3d& v2)
{
	return v1.dot(v2);
}

double length(const Vector3d& v)
{
	return std::sqrt(dot(v, v));
}
/*
void normalize(Vector3d& v)
{
	double len = length(v);
	v = divide(v, len);
}*/

/*void print(Vector3d& v)
{
	std::cout << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")" << std::endl;
}*/

//
// some tests for Vector3d
//
void test()
{
	// test default constructor
	Vector3d v1;
	std::cout << "test: default ctor" << std::endl;
	std::cout << "(0.0,0.0,0.0):\t" << v1 << std::endl;
	assert(v1[0] == 0.0 && v1[1] == 0.0 && v1[2] == 0.0);

	// test init-list
	std::cout << "\ntest: init-list ctor" << std::endl;
	Vector3d v2 {2.0, 3.0, 4.0};
	std::cout << "(2.0,3.0,4.0):\t" << v2 << std::endl;
	assert(v2[0] == 2.0 && v2[1] == 3.0 && v2[2] == 4.0);

	// test assignment
	std::cout << "\ntest: assignment" << std::endl;
	Vector3d v3;
	v3 = v2;
	std::cout << "(2.0,3.0,4.0):\t" << v3 << std::endl;
	assert(v3[0] == 2.0 && v3[1] == 3.0 && v3[2] == 4.0);

	// test init-list for containers
	std::cout << "\ntest: init list for container" << std::endl;
	std::cout << "the x, y, and z axis:" << std::endl;
	std::vector<Vector3d> vc {{1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}};
	for(auto v : vc) std::cout << v << "\t"; std::cout << std::endl;
	assert(vc[0][0] == 1.0 && vc[0][1] == 0.0 && vc[0][2] == 0.0);
	assert(vc[1][0] == 0.0 && vc[1][1] == 1.0 && vc[1][2] == 0.0);
	assert(vc[2][0] == 0.0 && vc[2][1] == 0.0 && vc[2][2] == 1.0);

	// scalar multiplication
	std::cout << "\ntest: scalar scaling" << std::endl;
	std::cout << "scaling by 0.5" << std::endl;
	for(auto& v : vc) v = 0.5*v;
	for(auto v : vc) std::cout << v << "\t"; std::cout << std::endl;
	assert(vc[0][0] == 0.5 && vc[0][1] == 0.0 && vc[0][2] == 0.0);
	assert(vc[1][0] == 0.0 && vc[1][1] == 0.5 && vc[1][2] == 0.0);
	assert(vc[2][0] == 0.0 && vc[2][1] == 0.0 && vc[2][2] == 0.5);

	// normalization
	std::cout << "\ntest: normalization" << std::endl;
	std::cout << "scaling by 0.5" << std::endl;
	for(auto& v : vc) v.normalize();
	for(auto v : vc) std::cout << v << "\t"; std::cout << std::endl;

	// vector addition
	std::cout << "\ntest: addition" << std::endl;
	Vector3d v4 {0,0,0};
	for(auto& v : vc) v4 += v;
	for(auto v : vc) std::cout << v << "\t";
	std::cout << " all added ==> " << v4 << std::endl;
	assert(v4[0] == 1.0 && v4[1] == 1.0 && v4[2] == 1.0);

	// vector subtraction
	std::cout << "\ntest: subtraction" << std::endl;
	Vector3d v5 {0,0,0};
	for(auto& v : vc) v5 -= v;
	for(auto v : vc) std::cout << v << "\t";
	std::cout << " all subtracted ==> " << v5 << std::endl;
	assert(v5[0] == -1.0 && v5[1] == -1.0 && v5[2] == -1.0);

	// unary minus
	std::cout << "\ntest: unary minus" << std::endl;
	Vector3d v7 {1,2,3};
	Vector3d v8;
	v8 = -v7;
	std::cout << "-" << v7 << " = " << v8 << std::endl;
	assert(v8[0] == -1.0 && v8[1] == -2.0 && v8[2] == -3.0);

	// cross product
	std::cout << "\ntest: cross product" << std::endl;
	Vector3d v100 {1,0,0};
	Vector3d v010 {0,1,0};
	Vector3d v001 = cross(v100, v010);
	std::cout << v100 << "x" << v010 << " = " << v001 << std::endl;
	assert(v001[0] == 0.0 && v001[1] == 0.0 && v001[2] == 1.0);

	// scalar product
	std::cout << "\ntest: dot product" << std::endl;
	double sp1 = dot(v100,v010);
	std::cout << v100 << "." << v010 << " = " << sp1 << std::endl;
	assert(sp1 == 0);
	double sp2 = dot(v100,v100);
	std::cout << v100 << "." << v100 << " = " << sp2 << std::endl;
	assert(sp2 == 1);
}

int main(int argc, char** argv)
{
	//test();
	return 0;
}
