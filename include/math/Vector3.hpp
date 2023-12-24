//
// Created by Toni on 23/12/2023.
//

#ifndef RUPE_VECTOR3_HPP
#define RUPE_VECTOR3_HPP

#include <cmath>

#include "Concepts.hpp"

// TODO: Document
namespace Rupe::Math {
    template <typename T> requires std::is_arithmetic_v<T>
    struct Vector3 {
    public:
        T x{};
        T y{};
        T z{};

        Vector3() = default;

        Vector3(const Vector3&) = default;
        Vector3& operator=(const Vector3&) = default;
        Vector3(Vector3&&) = default;
        Vector3& operator=(Vector3&&) = default;

        Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } { }

        template <typename TSource>
        requires Concepts::NonNarrowingConversion<TSource, T>
        explicit Vector3(const Vector3<TSource>& source) : x{ source.x }, y{ source.y }, z{ source.z } {}

        // Vector-Vector operations
        Vector3 operator-() const {
            return { -x, -y, -z };
        }

        Vector3 operator+(const Vector3& rhs) const {
            return { x + rhs.x, y + rhs.y, z + rhs.z };
        }

        const Vector3& operator+=(const Vector3& rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        Vector3 operator-(const Vector3& rhs) const {
            return { x - rhs.x, y - rhs.y, z - rhs.z };
        }

        const Vector3& operator-=(const Vector3& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        T dot(const Vector3& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        Vector3 cross(const Vector3& rhs) const {
            return {
                x * rhs.y - y * rhs.x,
                y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z
            };
        }

        const Vector3& crossAssign(const Vector3& rhs) {
            x = x * rhs.y - y * rhs.x;
            y = y * rhs.z - z * rhs.y;
            z = z * rhs.x - x * rhs.z;
            return *this;
        }

        T angleBetween(const Vector3& rhs) const {
            return std::acos(this->dot(rhs) / this->magnitude() * rhs.magnitude());
        }

        bool operator==(const Vector3& rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        // Vector-Scalar operations
        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        Vector3 operator*(Scalar rhs) const {
            return {
                x * rhs,
                y * rhs,
                z * rhs
            };
        }


        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        const Vector3& operator*=(Scalar rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        Vector3 operator/(Scalar rhs) const {
            return {
                x / rhs.x,
                y / rhs.y,
                z / rhs.z
            };
        }

        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        const Vector3& operator/=(Scalar rhs) {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }

        // Vector properties
        T magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        T squareMagnitude() const {
            return x * x + y * y + z * z;
        }

        Vector3 normalized() const {
            const auto mag = this->magnitude();
            const auto result{ *this };
            if (mag > 0){
                (result) /= mag;
            }
            return result;
        }

        const Vector3& normalize() {
            const auto mag = this->magnitude();
            if (mag > 0) {
                (*this) /= mag;
            }
            return *this;
        }
    };
}

#endif //RUPE_VECTOR3_HPP
