// òåñòû äëÿ ñòåêà

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TStack <int> v(5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> v(MAXSIZE + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> v(-5));
}

TEST(TStack, can_create_copied_stack)
{
	TStack <int> v(10);

	ASSERT_NO_THROW(TStack <int> v1(v));
}
TEST(TStack, can_include_new_element)
{
	TStack <int> v(2);
	v.Push(5);
	EXPECT_EQ(5, v.Get());
}

TEST(TStack, can_exclude_element)
{
	TStack <int> v(2);
	v.Push(5);
	EXPECT_EQ(5, v.Pop());
	EXPECT_EQ(-1, v.End());
}

TEST(TStack, can_get_element)
{
	TStack <int> v(2);
	v.Push(5);
	EXPECT_EQ(5, v.Get());
	EXPECT_EQ(0, v.End());
}

TEST(TStack, cant_get_element_when_stack_is_empty)
{
	TStack <int> v(2);
	ASSERT_ANY_THROW(v.Get());
}

TEST(TStack, cant_exclude_element_when_stack_is_empty)
{
	TStack <int> v(2);
	ASSERT_ANY_THROW(v.Pop());
}

TEST(TStack, new_stack_is_empty)
{
	TStack<int> v(2);
	EXPECT_EQ(true, v.IsEmpty());
}

TEST(TStack, can_check_full_stack)
{
	TStack<int> v(2);
	v.Push(5);
	v.Push(7);
	EXPECT_EQ(false, v.IsEmpty());
}
