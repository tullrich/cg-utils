#include "gtest/gtest.h"
#include "vector.h"
#include <stdexcept>

using namespace cgutils;

class VectorTest : public ::testing::Test
{
protected:

	VectorTest()
	{
		/* setup v1 */
		v1.x = 1;
		v1.y = 2;
		v1.z = 3;

		/* setup v2 */
		v2.x = 3;
		v2.y = 2;
		v2.z = 5;
	}

	virtual ~VectorTest()
	{
	}

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	Vector v1, v2;
};


TEST_F(VectorTest, defaultconstructor) 
{
	Vector v;
	EXPECT_EQ(0.0, v.x);
	EXPECT_EQ(0.0, v.y);
	EXPECT_EQ(0.0, v.z);
}

TEST_F(VectorTest, constructor) 
{
	Vector v(1.0, 2.0, 3.0);
	EXPECT_EQ(1.0, v.x);
	EXPECT_EQ(2.0, v.y);
	EXPECT_EQ(3.0, v.z);
}

TEST_F(VectorTest, arrayoperator) 
{
	EXPECT_EQ(1.0, v1[0]);
	EXPECT_EQ(2.0, v1[1]);
	EXPECT_EQ(3.0, v1[2]);
}

TEST_F(VectorTest, arrayoutofbounds) 
{
	ASSERT_THROW(v1[4], std::out_of_range);
	ASSERT_THROW(v1[-1], std::out_of_range);
}

TEST_F(VectorTest, additionoperator) 
{
	Vector result = v1 + v2;

	EXPECT_EQ(4.0, result.x);
	EXPECT_EQ(4.0, result.y);
	EXPECT_EQ(8.0, result.z);
}

TEST_F(VectorTest, subtractionoperator) 
{
	Vector result = v1 - v2;

	EXPECT_EQ(-2.0, result.x);
	EXPECT_EQ(0.0, result.y);
	EXPECT_EQ(-2.0, result.z);
}

TEST_F(VectorTest, multiplicationoperator) 
{
	float scalar = 10.0;
	Vector result = v1 * scalar;

	float expected_x = 1.0 * scalar;
	EXPECT_EQ(expected_x, result.x);

	float expected_y = 2.0 * scalar;
	EXPECT_EQ(expected_y, result.y);

	float expected_z = 3.0 * scalar;
	EXPECT_EQ(expected_z, result.z);
}

TEST_F(VectorTest, divisionoperator) 
{	
	float scalar = 10.0;
	Vector result = v1 / scalar;

	float expected_x = 1.0/scalar;
	EXPECT_EQ(expected_x, result.x);

	float expected_y = 2.0/scalar;
	EXPECT_EQ(expected_y, result.y);

	float expected_z = 3.0/scalar;
	EXPECT_EQ(expected_z, result.z);
}

TEST_F(VectorTest, dotproduct) 
{
	float result = v1.dot(v2);

	EXPECT_EQ(22.0, result);
}

TEST_F(VectorTest, crossproduct) 
{
	Vector result = v1.cross(v2);

	EXPECT_EQ(4.0, result.x);
	EXPECT_EQ(4.0, result.y);
	EXPECT_EQ(-4.0, result.z);
}

TEST_F(VectorTest, magnitude) 
{
	Vector temp(0.26726124191, 0.53452248382, 0.80178372573);
	float result = temp.magnitude();

	EXPECT_EQ(1.0, result);
}

TEST_F(VectorTest, swizzle_xy) 
{
	Vector temp(0.26726124191, 0.53452248382, 0.80178372573);
	float result = temp.magnitude();

	EXPECT_EQ(1.0, result);
}