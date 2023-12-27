//
// Created by Toni on 23/12/2023.
//

#ifndef RUPE_VECTOR3_HPP
#define RUPE_VECTOR3_HPP

#include <cmath>

#include "Concepts.hpp"

namespace Rupe::Math {
    /// A Vector with 3 dimensions
    /// \tparam T An arithmetic type like float, double and so on
    template <typename T> requires std::is_arithmetic_v<T>
    struct Vector3 {
    public:
        T x{};
        T y{};
        T z{};

        /// Default-constructs the vector
        Vector3() = default;

        Vector3(const Vector3&) = default;
        Vector3& operator=(const Vector3&) = default;
        Vector3(Vector3&&) = default;
        Vector3& operator=(Vector3&&) = default;

        Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } { }

        /// Copies a vector with a different type
        /// \tparam TSource The type of the other vector, must be assignable without narrowing
        /// \param source The source vector
        template <typename TSource>
        requires Concepts::NonNarrowingConversion<TSource, T>
        explicit Vector3(const Vector3<TSource>& source) : x{ source.x }, y{ source.y }, z{ source.z } {}

        ///
        /// \return A copy of the vector negated
        Vector3 operator-() const {
            return { -x, -y, -z };
        }

        ///
        /// \param rhs The vector to sum with
        /// \return A new vector with the sum of the vectors respective components
        Vector3 operator+(const Vector3& rhs) const {
            return { x + rhs.x, y + rhs.y, z + rhs.z };
        }

        /// Assigns the sum of the vector respective components
        /// \param rhs The vector to sum
        /// \return A reference to itself
        const Vector3& operator+=(const Vector3& rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        ///
        /// \param rhs The vector to subtract
        /// \return A new vector with the resulting subtraction
        Vector3 operator-(const Vector3& rhs) const {
            return { x - rhs.x, y - rhs.y, z - rhs.z };
        }

        /// Assigns the results of the subtraction
        /// \param rhs The vector to subtract
        /// \return A reference to itself
        const Vector3& operator-=(const Vector3& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        ///
        /// \param rhs The vector to apply the product with
        /// \return The dot product between the vectors
        T dot(const Vector3& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        ///
        /// \param rhs The vector to apply the product with
        /// \return The cross product between vectors
        Vector3 cross(const Vector3& rhs) const {
            return {
                y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x
            };
        }

        /// Assigns the result of the cross product between the vectors
        /// \param rhs The other vector
        /// \return A reference to itself
        const Vector3& crossAssign(const Vector3& rhs) {
            x = y * rhs.z - z * rhs.y;
            y = z * rhs.x - x * rhs.z;
            z = x * rhs.y - y * rhs.x;
            return *this;
        }

        /// Calculates the angle between vectors
        /// \param rhs The other vector
        /// \return The angle in radians
        T angleBetween(const Vector3& rhs) const {
            return std::acos(this->dot(rhs) / this->magnitude() * rhs.magnitude());
        }

        /// Compares every field
        /// \param rhs The other vector
        /// \return true if equal, false otherwise
        bool operator==(const Vector3& rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        /// Multiplies the vector with the given scalar
        /// \tparam Scalar The scalar type, must not be a narrowing conversion
        /// \param rhs The scalar to multiply by
        /// \return A new vector with the result of the multiplication
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

        /// Multiplies the vector by a scalar value
        /// \tparam Scalar The scalar type, must not be a narrowing conversion
        /// \param rhs The scalar to multiply by
        /// \return a reference to itself
        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        const Vector3& operator*=(Scalar rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        /// Divides the vector by the scalar
        /// \tparam Scalar The scalar type, must not be a narrowing conversion
        /// \param rhs The scalar to divide by
        /// \return A new vector with the result
        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        Vector3 operator/(Scalar rhs) const {
            return {
                x / rhs,
                y / rhs,
                z / rhs
            };
        }

        /// Divides the vector by a scalar and assigns the result
        /// \tparam Scalar The scalar type, must not be a narrowing conversion
        /// \param rhs The scalar value
        /// \return A reference to itself
        template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
                 && Concepts::NonNarrowingConversion<Scalar, T>
        const Vector3& operator/=(Scalar rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        ///
        /// \return the vector magnitude
        T magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        ///
        /// \return The vector square magnitude
        T squareMagnitude() const {
            return x * x + y * y + z * z;
        }

        ///
        /// \return A copy of the vector normalized
        Vector3 normalized() const {
            const auto mag = this->magnitude();
            Vector3 result{ *this };
            if (mag > 0){
                (result) /= mag;
            }
            return result;
        }

        /// Normalizes the vector in-place
        /// \return A reference to itself
        const Vector3& normalize() {
            const auto mag = this->magnitude();
            if (mag > 0) {
                (*this) /= mag;
            }
            return *this;
        }

        /// Multiplies each vector component respectively
        /// \param rhs The other vector
        /// \return A new vector with the result
        Vector3 componentProduct(const Vector3& rhs) {
            return { x * rhs.x, y * rhs.y, z * rhs.z };
        }

        /// Multiplies each vector component respectively and assigns it
        /// \param rhs The other vector
        /// \return A reference to itself
        const Vector3& componentProductAssign(const Vector3& rhs) {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }
    };
}

#endif //RUPE_VECTOR3_HPP
