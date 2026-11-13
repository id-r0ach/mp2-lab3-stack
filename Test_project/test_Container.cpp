#include "..\Container.h"
#include "gtest.h"
#include <climits>

// Конструкторы
TEST(Container, can_create_container) {
	ASSERT_NO_THROW(Container<int> c);
}

TEST(Container, cant_create_container_with_zero_size) {
	ASSERT_ANY_THROW(Container<int> c(0));
}

TEST(Container, cant_create_container_with_negative_size) {
	ASSERT_ANY_THROW(Container<int> c(-1));
}

TEST(Container, cant_create_container_with_too_large_size) {
	ASSERT_ANY_THROW(Container<int> c(UINT_MAX + 1));
}

TEST(Container, can_create_copied_container) {
	Container<int> c(10);
	ASSERT_NO_THROW(Container<int> c1(c));
}

TEST(Container, copied_container_is_equal_to_source_one) {
	Container<int> c1(10);
	Container<int> c2(c1);
	ASSERT_EQ(c1, c2);
}

TEST(Container, copied_container_has_its_own_memory) {
	Container<int> c1(10);
	Container<int> c2(c1);
	c1.push_back(1);
	c2.push_back(2);
	ASSERT_NE(&c1[0], &c2[0]);
}

// Тесты для конструктора перемещения
TEST(Container, can_move_container) {
	Container<int> c1(5);
	c1.push_back(1);
	c1.push_back(2);
	int* old_ptr = &c1[0];
	Container<int> c2(std::move(c1));
	ASSERT_EQ(c2.size(), 2);
	ASSERT_EQ(c2[0], 1);
	ASSERT_EQ(c2[1], 2);
	ASSERT_EQ(&c2[0], old_ptr);
	ASSERT_EQ(c1.size(), 0);
}

TEST(Container, can_move_assign_container) {
	Container<int> c1(5);
	Container<int> c2(10);
	c1.push_back(1);
	c1.push_back(2);
	int* old_ptr = &c1[0];
	c2.push_back(10);
	c2.push_back(20);
	c2.push_back(30);
	c2 = std::move(c1);
	ASSERT_EQ(c2.size(), 2);
	ASSERT_EQ(c2[0], 1);
	ASSERT_EQ(c2[1], 2);
	ASSERT_EQ(&c2[0], old_ptr);
	ASSERT_EQ(c1.size(), 0);
}

TEST(Container, can_assign_container_to_itself) {
	Container<int> c(10);
	ASSERT_NO_THROW(c = c);
}

TEST(Container, can_assign_containers_of_different_size) {
	Container<int> c1(10);
	Container<int> c2(2);
	c1.push_back(1);
	c2.push_back(2);
	ASSERT_NE(c1, c2);
	ASSERT_NO_THROW(c1 = c2);
	ASSERT_EQ(c1, c2);
}

TEST(Container, assign_operator_change_container_size) {
	Container<int> c1(5);
	Container<int> c2(10);
	ASSERT_NO_THROW(c1 = c2);
	ASSERT_EQ(c1.size(), c2.size());
}

TEST(Container, can_assign_containers_of_equal_size) {
	Container<int> c1(5);
	Container<int> c2(5);
	ASSERT_NO_THROW(c1 = c2);
	ASSERT_EQ(c1, c2);
}

// Оператор сравнения
TEST(Container, compare_equal_containers_return_true)
{
	Container<int> c1(3);
	Container<int> c2(3);
	ASSERT_TRUE(c1 == c2);
}

TEST(Container, compare_container_with_itself_return_true)
{
	Container<int> c(3);
	ASSERT_TRUE(c == c);
	ASSERT_FALSE(c != c);
}

TEST(Container, containers_with_different_size_are_not_equal)
{
	Container<int> c1(3);
	Container<int> c2(6);
	c1.push_back(1);
	c2.push_back(2);
	c2.push_back(2);
	ASSERT_FALSE(c1 == c2);
	ASSERT_TRUE(c1 != c2);
}

TEST(Container, containers_with_same_size_and_different_elements_are_not_equal) {
	Container<int> c1(3);
	Container<int> c2(3);
	c1.push_back(1);
	c1.push_back(2);
	c2.push_back(1);
	c2.push_back(3);
	ASSERT_FALSE(c1 == c2);
	ASSERT_TRUE(c1 != c2);
}

TEST(Container, can_push_back_element) {
	Container<int> c(3);
	ASSERT_NO_THROW(c.push_back(1));
	ASSERT_NO_THROW(c.push_back(2));
	ASSERT_NO_THROW(c.push_back(3));
}

TEST(Container, can_push_back_elements_to_full_container) {
	Container<int> c(2);
	ASSERT_NO_THROW(c.push_back(1));
	ASSERT_NO_THROW(c.push_back(2));
	ASSERT_NO_THROW(c.push_back(3));
	ASSERT_NE(c.size(), 2);
}

TEST(Container, can_pop_back_element) {
	Container<int> c(3);
	int elem;
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	ASSERT_NO_THROW(elem = c.pop_back());
	ASSERT_EQ(elem, 3);
}

TEST(Container, cant_pop_back_element_from_empty_container) {
	Container<int> c(3);
	ASSERT_ANY_THROW(c.pop_back());
}

TEST(Container, can_clear_container) {
	Container<int> c(3);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	ASSERT_NE(c.size(), 0);
	c.clear();
	ASSERT_EQ(c.size(), 0);
}

TEST(Container, can_get_size) {
	Container<int> c(3);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	ASSERT_EQ(c.size(), 3);
}

// Оператор индексации
TEST(Container, can_get_element_by_index) {
	Container<int> c(3);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	int elem;
	ASSERT_NO_THROW(elem = c[1]);
	ASSERT_EQ(elem, 2);
}

TEST(Container, cant_get_element_with_negative_index) {
	Container<int> c(3);
	ASSERT_ANY_THROW(c[-1]);
}

TEST(Container, cant_get_element_with_too_large_index) {
	Container<int> c(3);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	ASSERT_ANY_THROW(c[3]);
}

TEST(Container, can_set_element_by_index) {
	Container<int> c(3);
	c.push_back(1);
	c.push_back(2);
	c[1] = 10;
	ASSERT_EQ(c[1], 10);
}