#include "..\TDynamicStack.h"

#include "gtest.h"

// Тесты на все конструкторы
// Пуш/поп
// Тесты на полноту/пустоту
// Не могу добавить в полный
// Не могу извлечь из пустого
// Посмотреть на вершину

TEST(TDynamicStack, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicStack<int> bf);
}
