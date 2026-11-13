#include "..\Calculator.h"
#include "gtest.h"
#include <cmath>

// Конструктор
TEST(Calculator, can_create_empty_calculator) {
	Calculator c;
	ASSERT_EQ(c.getPostfix(), "");
}

TEST(Calculator, can_create_calculator_with_expression) {
	Calculator c("2 + 3");
	ASSERT_EQ(c.getInfix(), "2 + 3");
}

TEST(Calculator, throws_when_expression_has_single_dot) {
	ASSERT_ANY_THROW(Calculator c("."));
}

TEST(Calculator, throws_when_expression_has_invalid_character) {
	ASSERT_ANY_THROW(Calculator c("2 + a"));
}

// to_postfix
TEST(Calculator, can_convert_simple_expression_to_postfix) {
	Calculator c("2 + 3");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 +");
}

TEST(Calculator, can_reset_and_convert_new_infix_expression) {
	Calculator c("2 + 3");
	c.to_postfix();
	c.set_infix("3 + 2");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "3 2 +");
}

TEST(Calculator, respects_operator_precedence_in_postfix) {
	Calculator c("2 + 3 * 4");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 4 * +");
}

TEST(Calculator, respects_parentheses_in_postfix) {
	Calculator c("(2 + 3) * 4");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 + 4 *");
}

TEST(Calculator, converts_expression_with_redundant_inner_parentheses) {
	Calculator c("2 + (3 * 4)");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 4 * +");
}

TEST(Calculator, converts_expression_wrapped_in_outer_parentheses) {
	Calculator c("(2 + 3 * 4)");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 4 * +");
}

TEST(Calculator, converts_power_operation_to_postfix) {
	Calculator c("2 ^ 3");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 ^");
}

TEST(Calculator, respects_right_associativity_of_power_in_postfix) {
	Calculator c("2 ^ 3 ^ 4");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "2 3 4 ^ ^");
}

TEST(Calculator, converts_complex_expression_with_spaces_and_floats) {
	Calculator c("  12.5 + .05   + 2    ^ 4 *    3          ");
	c.to_postfix();
	ASSERT_EQ(c.getPostfix(), "12.5 .05 + 2 4 ^ 3 * +");
}

TEST(Calculator, throws_when_converting_empty_calculator) {
	Calculator c;
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_converting_whitespace_only_expression) {
	Calculator c("    ");
	ASSERT_EQ(c.getInfix(), "    ");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_extra_closing_bracket_at_end) {
	Calculator c("2 + 3)");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_unclosed_opening_bracket_at_start) {
	Calculator c("(2 + 3");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_extra_closing_bracket_after_group) {
	Calculator c("(2 + 3) * 4)");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_nested_opening_bracket_unclosed) {
	Calculator c("((2 + 3) * 4");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_inner_nested_bracket_unclosed) {
	Calculator c("(2 + (3 * 4)");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_multiple_extra_closing_brackets) {
	Calculator c("(((2 + 3))))");
	ASSERT_ANY_THROW(c.to_postfix());
}

TEST(Calculator, throws_when_multiple_unclosed_opening_brackets) {
	Calculator c("((((2 + 3)))");
	ASSERT_ANY_THROW(c.to_postfix());
}


// CalcPostfix
TEST(Calculator, calculates_simple_addition) {
	Calculator c("2 + 3");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), 2 + 3);
}

TEST(Calculator, calculates_simple_multiplication) {
	Calculator c("2 * 4");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), 2 * 4);
}

TEST(Calculator, respects_precedence_during_calculation) {
	Calculator c("2 + 3 * 4");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), 2 + 3 * 4);
}

TEST(Calculator, calculates_division_and_multiplication) {
	Calculator c("2 / 6 + 3 * 4");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), (double)2 / 6 + 3 * 4);
}

TEST(Calculator, calculates_expression_with_parentheses_first) {
	Calculator c("(2 + 3) * 4");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), (2 + 3) * 4);
}

TEST(Calculator, calculates_expression_with_inner_parentheses) {
	Calculator c("2 + (3 * 4)");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), 2 + (3 * 4));
}

TEST(Calculator, calculates_expression_wrapped_in_parentheses) {
	Calculator c("(2 + 3 * 4)");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), (2 + 3 * 4));
}


TEST(Calculator, calculates_power_operation) {
	Calculator c("2 ^ 3");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), pow(2, 3));
}


TEST(Calculator, calculates_right_associative_power) {
	Calculator c("2 ^ 3 ^ 4");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), pow(2, pow(3, 4)));
}

TEST(Calculator, calculates_complex_expression_with_floats) {
	Calculator c("12.5 + .05 + 2 ^ 4 * 3");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), (12.5 + .05 + pow(2, 4) * 3));
}

TEST(Calculator, calculates_single_number) {
	Calculator c("2");
	c.to_postfix();
	ASSERT_EQ(c.CalcPostfix(), 2);
}



TEST(Calculator, throws_when_calculating_without_to_postfix) {
	Calculator c("2 + 3");
	ASSERT_ANY_THROW(c.CalcPostfix());
}

TEST(Calculator, throws_when_dividing_by_zero) {
	Calculator c("10 / 0");
	c.to_postfix();
	ASSERT_ANY_THROW(c.CalcPostfix());
}

TEST(Calculator, throws_when_dividing_by_zero_expression) {
	Calculator c("10 / (5 - 5)");
	c.to_postfix();
	ASSERT_ANY_THROW(c.CalcPostfix());
}

TEST(Calculator, throws_when_trailing_operator) {
	Calculator c("2 + ");
	c.to_postfix();
	ASSERT_ANY_THROW(c.CalcPostfix());
}

TEST(Calculator, throws_when_consecutive_operators) {
	Calculator c("2 +* 4");
	c.to_postfix();
	ASSERT_ANY_THROW(c.CalcPostfix());
}

TEST(Calculator, throws_when_missing_operator_between_numbers) {
	Calculator c("2 * 4 5");
	c.to_postfix();
	ASSERT_ANY_THROW(c.CalcPostfix());
}