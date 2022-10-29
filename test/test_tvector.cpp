#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int>v1(3);
	TDynamicVector<int>v2(v1);

	EXPECT_EQ(v1,v2);
	// ????
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	// ????
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(3);

	EXPECT_EQ(3, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(3);

	ASSERT_ANY_THROW(v[-3] = 2);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(3);

	ASSERT_ANY_THROW(v[4] = 2);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  // ????
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	const int size = 3;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);

	v2 = v1;

	EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);

	EXPECT_NE(v1.size(), v2.size());
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	const int size = 3;

	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int count = 0; count < size; count++) {
		v1[count] == count;
		v2[count] == count;
	}
	EXPECT_EQ(true, v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(3);

	for (int count = 0; count < v1.size(); count++) {
		v1[count] == count;
	}
	EXPECT_EQ(true, v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);

	EXPECT_EQ(false, v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	for (size_t count = 0; count < size; count++) {
		v1[count] = 1;
	}

	v1 = v1 + 3;

	TDynamicVector<int> v2(size);

	for (size_t count = 0; count < size; count++) {
		v2[count] = 1 + 3;
	}

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	for (size_t count = 0; count < size; count++) {
		v1[count] = 1;
	}

	v1 = v1 - 3;

	TDynamicVector<int> v2(size);

	for (size_t count = 0; count < size; count++) {
		v2[count] = 1 - 3;
	}

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	for (size_t count = 0; count < size; count++) {
		v1[count] = 1;
	}

	v1 = v1 * 3;

	TDynamicVector<int> v2(size);

	for (size_t count = 0; count < size; count++) {
		v2[count] = 1 * 3;
	}

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);

	v1[0] = 3;
	v2[0] = 3;

	TDynamicVector<int> v3 = (v1 + v2);
	TDynamicVector<int> v4(3);
	v4[0] = 6;

	EXPECT_EQ(v4, v3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);

	
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);

	v1[0] = 3;
	v2[0] = 3;

	TDynamicVector<int> v3 = (v1 - v2);
	TDynamicVector<int> v4(3);
	v4[0] = 0;

	EXPECT_EQ(v4, v3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);


	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);

	v1[1] = 1;
	v2[1] = 3;

	size_t result = v1 * v2;
	
	EXPECT_EQ(3, result);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);


	ASSERT_ANY_THROW(v1 * v2);
}

