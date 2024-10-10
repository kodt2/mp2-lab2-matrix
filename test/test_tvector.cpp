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
	int size = 10;
	TDynamicVector<int> v1(size);
	v1[9] = 5;
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int size = 10;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(v1);
	v1[9] = 5;
	v2[2] = 5;
	TDynamicVector<int> res(size);
	res[2] = 5;
	EXPECT_EQ(v2, res);
}

TEST(TDynamicVector, can_get_size)
{
	int size = 4;
  TDynamicVector<int> v(size);

  EXPECT_EQ(size, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	int size = 4;
	TDynamicVector<int> v(size);

	ASSERT_ANY_THROW(v.at(-2));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	int size = 4;
	TDynamicVector<int> v(size);

	ASSERT_ANY_THROW(v.at(100));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int size = 4;
	TDynamicVector<int> v(size);
	ASSERT_NO_THROW(v=v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int size = 4;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	v2 = v1;

	EXPECT_EQ(v1,v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int size1 = 4, size2 = 7;
	TDynamicVector<int> v1(size2);
	TDynamicVector<int> v2(size1);
	v2 = v1;

	EXPECT_EQ(v2.size(), size2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int size1 = 4, size2 = 7;
	TDynamicVector<int> v1(size2);
	v1[6] = 1;
	TDynamicVector<int> v2(size1);
	v2 = v1;
	TDynamicVector<int> res(size2);
	res[6] = 1;

	EXPECT_EQ(v2,res);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int size1 = 4, size2 = 7;
	TDynamicVector<int> v1(size2);
	v1[6] = 1;
	TDynamicVector<int> v2(size1);
	v2 = v1;
	EXPECT_EQ(v2==v1, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int size1 = 4;
	TDynamicVector<int> v1(size1);
	v1[2] = 1;
	EXPECT_EQ(v1 == v1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int size1 = 4, size2 = 7;
	TDynamicVector<int> v1(size2);
	TDynamicVector<int> v2(size1);
	EXPECT_EQ(v1 == v2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int size1 = 2;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> res(size1);
	res[0] = 1;
	res[1] = 1;
	EXPECT_EQ(v+1, res);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int size1 = 2;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> res(size1);
	res[0] = -1;
	res[1] = -1;
	EXPECT_EQ(v - 1, res);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int size1 = 2;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> res(size1);
	v[0] = 5;
	v[1] = 5;
	res[0] = 10;
	res[1] = 10;
	EXPECT_EQ(v*2, res);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int size1 = 2;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size1);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 2;
	v2[1] = 1;
	TDynamicVector<int> res(size1);
	res[0] = 3;
	res[1] = 3;
	EXPECT_EQ(v1+v2, res);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int size1 = 2, size2=4;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 2;
	v2[1] = 1;
	v2[2] = 1;
	v2[3] = 1;
	TDynamicVector<int> res(size2);
	res[0] = 3;
	res[1] = 3;
	res[2] = 1;
	res[3] = 1;
	EXPECT_EQ(v1 + v2, res);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int size1 = 2;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size1);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 2;
	v2[1] = 1;
	TDynamicVector<int> res(size1);
	res[0] = -1;
	res[1] = 1;
	EXPECT_EQ(v1 - v2, res);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int size1 = 2, size2 = 4;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 2;
	v2[1] = 1;
	v2[2] = 1;
	v2[3] = 1;
	TDynamicVector<int> res(size2);
	res[0] = -1;
	res[1] = 1;
	res[2] = -1;
	res[3] = -1;
	EXPECT_EQ(v1 - v2, res);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int size1 = 2;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size1);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 2;
	v2[1] = 1;
	int res = 4;
	EXPECT_EQ(v1 * v2, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int size1 = 2, size2 = 4;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 2;
	v2[1] = 1;
	v2[2] = 1;
	v2[3] = 1;
	int res = 4;
	EXPECT_EQ(v1 * v2, res);
}
TEST(TDynamicVector, move_constructor_check)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v3(v1);
    
    TDynamicVector<int> v2(std::move(v1));

    ASSERT_EQ(v2, v3);
    ASSERT_EQ(v1.data(), nullptr);
    ASSERT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, move_opertor_check)
{
    const int size = 10;
    TDynamicVector<int> v1(size);
    for (int i = 0; i < size; i++)
        v1[i] = i;
    TDynamicVector<int> v3(v1);

    TDynamicVector<int> v2 = std::move(v1);

    ASSERT_EQ(v2, v3);
    ASSERT_EQ(v1.data(), nullptr);
    ASSERT_EQ(v1.size(), 0);
}
