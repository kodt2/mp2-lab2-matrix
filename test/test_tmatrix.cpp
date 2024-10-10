#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	int size = 2;
	TDynamicMatrix<int> m1(size);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(size);
	m2 = m1;
	EXPECT_EQ(m1,m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	int size = 2;
	TDynamicMatrix<int> m1(size);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(size);
	TDynamicMatrix<int> res(size);
	res[1][1] = 1;
	m2 = m1;
	m1[1][1] = 2;
	EXPECT_EQ(m2,res);
}

TEST(TDynamicMatrix, can_get_size)
{
	size_t size = 5;
	TDynamicMatrix<int> m(size);
	EXPECT_EQ(size, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	int size = 2;
	int elem = 1;
	TDynamicMatrix<int> m1(size);
	m1[1][1] = elem;
	EXPECT_EQ(elem, m1[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	int size = 2;
	TDynamicMatrix<int> m(size);
	ASSERT_ANY_THROW(m[-1][-1]=1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	int size = 2;
	TDynamicMatrix<int> m(size);
	ASSERT_ANY_THROW(m[10][10]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	int size = 2;
	TDynamicMatrix<int> m(size);
	ASSERT_NO_THROW(m=m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	int size = 2;
	TDynamicMatrix<int> m2(size);
	TDynamicMatrix<int> m1(size);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	int size1 = 2, size2 =4;
	TDynamicMatrix<int> m2(size2);
	TDynamicMatrix<int> m1(size1);
	m1 = m2;
	EXPECT_EQ(size2, m1.size());
  
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	int size1 = 2, size2 = 4;
	TDynamicMatrix<int> m2(size2);
	TDynamicMatrix<int> m1(size1);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	int size = 2;
	TDynamicMatrix<int> m1(size);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(size);
	m2[1][1] = 1;
	EXPECT_EQ(true, m1==m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	int size = 2;
	TDynamicMatrix<int> m1(size);
	m1[1][1] = 1;
	EXPECT_EQ(true, m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(4);
	EXPECT_EQ(false, m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1;
	TDynamicMatrix<int> res(2);
	res[1][1] = 1;
	res[0][0] = 1;
	EXPECT_EQ(res, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 1;
	TDynamicMatrix<int> res(4);
	res[1][1] = 1;
	res[0][0] = 1;
	EXPECT_EQ(res, m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1;
	TDynamicMatrix<int> res(2);
	res[1][1] = 1;
	res[0][0] = -1;
	EXPECT_EQ(res, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[1][1] = 1;
	TDynamicMatrix<int> m2(4);
	m2[0][0] = 1;
	TDynamicMatrix<int> res(4);
	res[1][1] = 1;
	res[0][0] = -1;
	EXPECT_EQ(res, m1 - m2);
}
TEST(TDynamicMatrix, move_constructor_check)
{
    const int size = 10;
    TDynamicMatrix<int> v1(size);
    TDynamicMatrix<int> res(v1);
    
    TDynamicMatrix<int> v2(std::move(v1));

    EXPECT_EQ(v2, res);
}

TEST(TDynamicMatrix, move_opertor_check)
{
    const int size = 2;
    TDynamicMatrix<int> v1(size);
    TDynamicMatrix<int> res(v1);

    TDynamicMatrix<int> v2 = std::move(v1);

    EXPECT_EQ(v2, res);
}
