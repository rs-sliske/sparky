#include "vec3.h"

namespace sparky { namespace maths {

	vec3::vec3(const float x, const float y, const float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	vec3::vec3():vec3(0,0,0)
	{

	}

	vec3& vec3::add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subtract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	vec3& vec3::multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::multiply(const float& amt)
	{
		x *= amt;
		y *= amt;
		z *= amt;
		return *this;
	}

	vec3& vec3::divide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3& vec3::divide(const float& amt)
	{
		x /= amt;
		y /= amt;
		z /= amt;
		return *this;
	}

	bool vec3::equals(const vec3& other) {
		if (x == other.x){
			if (y == other.y){
				if (z == other.z){
					return true;
				}
			}
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector){
		stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

	vec3 operator+(vec3 left, const vec3& right){
		return left.add(right);
	}
	vec3 operator-(vec3 left, const vec3& right){
		return left.subtract(right);
	}
	vec3 operator*(vec3 left, const vec3& right){
		return left.multiply(right);
	}
	vec3 operator/(vec3 left, const vec3& right){
		return left.divide(right);
	}

	vec3 operator*(vec3 left, const float& right){
		return left.multiply(right);
	}
	vec3 operator/(vec3 left, const float& right){
		return left.divide(right);
	}

	vec3& vec3::operator+=(const vec3& other){
		return add(other);
	}
	vec3& vec3::operator-=(const vec3& other){
		return subtract(other);
	}
	vec3& vec3::operator*=(const vec3& other){
		return multiply(other);
	}

	

	vec3& vec3::operator/=(const vec3& other){
		return divide(other);
	}
	bool vec3::operator==(const vec3& other){
		return equals(other);
	}
	bool vec3::operator!=(const vec3& other){
		return !equals(other);
	}

	
}}