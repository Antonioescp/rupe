//
// Created by Toni on 23/12/2023.
//

#include <random>
#include <numbers>

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

TYPED_TEST(Vector3Test, VectorVectorOperations) {
    ASSERT_EQ(this->a - this->a, this->zero) << "Subtraction by itself should be zero";
    ASSERT_EQ(this->a + this->zero, this->a) << "Addition with zero vector should return the same value";

    ASSERT_FLOAT_EQ(this->xAxis.dot(this->yAxis), 0) << "Dot on orthogonal vectors should be 0";
    ASSERT_FLOAT_EQ(this->xAxis.dot(this->xAxis), 1) << "Dot on parallels vectors should be 1";
    ASSERT_FLOAT_EQ(this->xAxis.dot(-this->xAxis), -1) << "Dot on anti-parallels vectors should be -1";
    ASSERT_FLOAT_EQ(this->a.dot(this->a), this->a.squareMagnitude()) << "Dot by itself should be square magnitude";
    ASSERT_FLOAT_EQ(this->a.dot(this->b), this->b.dot(this->a)) << "Dot should be commutative";
    ASSERT_FLOAT_EQ(this->a.dot(this->a + this->b), this->a.dot(this->a) + this->a.dot(this->b))
        << "Dot should be distributive";


}