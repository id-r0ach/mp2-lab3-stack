#include "..\TDynamicStack.h"

#include "gtest.h"
#include <climits>
// Тесты на все конструкторы +-
// Пуш/поп
// Тесты на полноту/пустоту
// Не могу добавить в полный
// Не могу извлечь из пустого
// Посмотреть на вершину


// Конструктор
TEST(TDynamicStack, can_create_an_empty_stack)
{
  ASSERT_NO_THROW(TDynamicStack<int> st);
}
TEST(TDynamicStack, can_create_an_empty_stack_of_size_n) {
	ASSERT_NO_THROW(TDynamicStack<int> st(5));
}
TEST(TDynamicStack, cant_create_a_stack_of_zero_size) {
	ASSERT_ANY_THROW(TDynamicStack<int> st(0));
}
TEST(TDynamicStack, cant_create_stack_with_a_negative_size) {
	ASSERT_ANY_THROW(TDynamicStack<int> st(-5));
}
TEST(TDynamicStack, cant_create_a_stack_of_too_large_a_size) {
	ASSERT_ANY_THROW(TDynamicStack<int> st(UINT_MAX+1));
}


// Push/pop
TEST(TDynamicStack, can_add_an_element_to_the_stack) {
	TDynamicStack<int> st(5);
	ASSERT_NO_THROW(st.push(10));
}
TEST(TDynamicStack, cant_add_an_element_to_the_full_stack) {
	TDynamicStack<int> st(2);
	st.push(10);
	st.push(10);
	ASSERT_ANY_THROW(st.push(10));
	// дописать проверку с top
}
TEST(TDynamicStack, can_extract_an_element_from_the_stack) {
	TDynamicStack<int> st(5);
	st.push(10);
	st.push(10);
	int key = 5, res;
	st.push(key);
	ASSERT_NO_THROW(res = st.pop());
	ASSERT_EQ(key, res);
}
TEST(TDynamicStack, cant_extract_an_element_from_an_empty_stack) {
	TDynamicStack<int> st(10);
	ASSERT_ANY_THROW(st.pop());
}

// Полнота/пустота
TEST(TDynamicStack, can_check_that_the_stack_is_empty) {
	TDynamicStack<int> st(10);
	ASSERT_TRUE(st.IsEmpty());
}
TEST(TDynamicStack, can_check_that_the_stack_is_full) {
	TDynamicStack<int> st(3);
	st.push(10);
	st.push(10);
	st.push(10);
	ASSERT_TRUE(st.IsFull());
}
TEST(TDynamicStack, can_check_that_the_stack_is_not_empty) {
	TDynamicStack<int> st(10);
	st.push(10);
	ASSERT_FALSE(st.IsEmpty());
}
TEST(TDynamicStack, can_check_that_the_stack_is_incomplete) {
	TDynamicStack<int> st(5);
	st.push(10);
	st.push(10);
	st.push(10);
	ASSERT_FALSE(st.IsFull());
}


// Дополнительные конструкторы
TEST(TDynamicStack, can_copy_the_stack) {
	TDynamicStack<int> st(5);
	st.push(1);
	st.push(2);
	st.push(3);
	ASSERT_NO_THROW(TDynamicStack<int> st_copy(st));
}
TEST(TDynamicStack, can_copy_the_stack_and_they_will_be_equal) {
	TDynamicStack<int> st(5);
	st.push(1);
	st.push(2);
	st.push(3);
	TDynamicStack<int> st_copy(st);
	ASSERT_EQ(st, st_copy);
}
TEST(TDynamicStack, can_assign_one_stack_to_another) {
	TDynamicStack<int> st1(5), st2(3);
	ASSERT_NO_THROW(st1 = st2);
	ASSERT_EQ(st1, st2);
}




// Операторы сравнения
TEST(TDynamicStack, stack_is_equal_to_itself) {
	TDynamicStack<int> st(5);
	ASSERT_TRUE(st == st);
}
TEST(TDynamicStack, two_equal_stacks_are_equal) {
	TDynamicStack<int> st1(3), st2(3);
	st1.push(1);
	st2.push(1);
	st1.push(2);
	st2.push(2);
	st1.push(3);
	st2.push(3);
	ASSERT_TRUE(st1 == st2);
}
TEST(TDynamicStack, two_equal_stacks_are_unequal) {
	TDynamicStack<int> st1(3), st2(3);
	st1.push(1);
	st2.push(1);
	st1.push(2);
	st1.push(3);
	st2.push(3);
	ASSERT_TRUE(st1 == st2);
}
