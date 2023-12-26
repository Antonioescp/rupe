//
// Created by Toni on 23/12/2023.
//

#include <random>

#include <gtest/gtest.h>

#include "math/Vector3.hpp"

using namespace Rupe::Math;

template <typename T>
class Vector3Test : public ::testing::Test {
public:
    Vector3<T> a;
    Vector3<T> b;
    Vector3<T> c;
    Vector3<T> xAxis{1, 0, 0};
    Vector3<T> yAxis{0, 1, 0};
    Vector3<T> zero{};

    std::random_device randomDevice{};
    std::default_random_engine randomEngine{randomDevice() };
    std::uniform_real_distribution<T> realDist{ -10, 10 };

    using Vector = Vector3<T>;

    T getRandomNumber() {
        return this->realDist(this->randomEngine);
    }

    Vector3<T> getRandomVector() {
        return {
            this->getRandomNumber(),
            this->getRandomNumber(),
            this->getRandomNumber()
        };
    }

protected:
    void SetUp() override {
        a = this->getRandomVector();
        b = this->getRandomVector();
        c = this->getRandomVector();
    }
};

using VectorTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(Vector3Test, VectorTypes);

namespace Rupe::Math {
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
        os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
        return os;
    }
}

TYPED_TEST(Vector3Test, AdditionProperties) {
    Vector3<TypeParam> result = this->a + this->b;

    // Additive identity property
    EXPECT_FLOAT_EQ(result.x, this->a.x + this->b.x);
    EXPECT_FLOAT_EQ(result.y, this->a.y + this->b.y);
    EXPECT_FLOAT_EQ(result.z, this->a.z + this->b.z);

    // Commutative property
    Vector3<TypeParam> result2 = this->b + this->a;
    EXPECT_FLOAT_EQ(result.x, result2.x);
    EXPECT_FLOAT_EQ(result.y, result2.y);
    EXPECT_FLOAT_EQ(result.z, result2.z);

    // Associative property
    Vector3<TypeParam> result3 = result + this->c;
    Vector3<TypeParam> result4 = this->a + (this->b + this->c);
    EXPECT_FLOAT_EQ(result3.x, result4.x);
    EXPECT_FLOAT_EQ(result3.y, result4.y);
    EXPECT_FLOAT_EQ(result3.z, result4.z);
}

TYPED_TEST(Vector3Test, SubtractionProperties) {
    Vector3<TypeParam> result = this->a - this->b;

    // Additive identity property
    EXPECT_FLOAT_EQ(result.x, this->a.x - this->b.x);
    EXPECT_FLOAT_EQ(result.y, this->a.y - this->b.y);
    EXPECT_FLOAT_EQ(result.z, this->a.z - this->b.z);

    // Commutative property
    Vector3<TypeParam> result2 = this->b - this->a;
    EXPECT_FLOAT_EQ(result.x, -result2.x);
    EXPECT_FLOAT_EQ(result.y, -result2.y);
    EXPECT_FLOAT_EQ(result.z, -result2.z);

    // Associative property
    Vector3<TypeParam> result3 = result - this->c;
    Vector3<TypeParam> result4 = this->a - (this->b + this->c);
    EXPECT_FLOAT_EQ(result3.x, result4.x);
    EXPECT_FLOAT_EQ(result3.y, result4.y);
    EXPECT_FLOAT_EQ(result3.z, result4.z);
}

TYPED_TEST(Vector3Test, DotProductProperties) {
    // Commutative property
    TypeParam result1 = this->a.dot(this->b);
    TypeParam result2 = this->b.dot(this->a);
    EXPECT_FLOAT_EQ(result1, result2);

    // Distributive property
    TypeParam result3 = (this->a + this->b).dot(this->c);
    TypeParam result4 = this->a.dot(this->c) + this->b.dot(this->c);
    EXPECT_FLOAT_EQ(result3, result4);

    // Identity property
    Vector3<TypeParam> unitVector = this->a.normalized();
    TypeParam result5 = unitVector.dot(unitVector);
    EXPECT_FLOAT_EQ(result5, TypeParam{1});

    // Dot product with zero vector
    Vector3<TypeParam> zeroVector;
    TypeParam result6 = zeroVector.dot(this->a);
    EXPECT_FLOAT_EQ(result6, TypeParam{0});
}

TYPED_TEST(Vector3Test, CrossProductProperties) {
    // Anticommutative property
    Vector3<TypeParam> result1 = this->a.cross(this->b);
    Vector3<TypeParam> result2 = -(this->b.cross(this->a));
    EXPECT_FLOAT_EQ(result1.x, result2.x);
    EXPECT_FLOAT_EQ(result1.y, result2.y);
    EXPECT_FLOAT_EQ(result1.z, result2.z);

    // Distributive property
    Vector3<TypeParam> result3 = (this->a + this->b).cross(this->c);
    Vector3<TypeParam> result4 = this->a.cross(this->c) + this->b.cross(this->c);
    EXPECT_FLOAT_EQ(result3.x, result4.x);
    EXPECT_FLOAT_EQ(result3.y, result4.y);
    EXPECT_FLOAT_EQ(result3.z, result4.z);

    // Cross product with zero vector
    Vector3<TypeParam> zeroVector;
    Vector3<TypeParam> result5 = zeroVector.cross(this->a);
    EXPECT_FLOAT_EQ(result5.x, zeroVector.x);
    EXPECT_FLOAT_EQ(result5.y, zeroVector.y);
    EXPECT_FLOAT_EQ(result5.z, zeroVector.z);

    // Cross product with the zero vector
    Vector3<TypeParam> result6 = this->a.cross(zeroVector);
    Vector3<TypeParam> result7 = -(zeroVector.cross(this->a));
    EXPECT_FLOAT_EQ(result6.x, -result7.x);
    EXPECT_FLOAT_EQ(result6.y, -result7.y);
    EXPECT_FLOAT_EQ(result6.z, -result7.z);
    EXPECT_FLOAT_EQ(result7.x, -result6.x);
    EXPECT_FLOAT_EQ(result7.y, -result6.y);
    EXPECT_FLOAT_EQ(result7.z, -result6.z);
}