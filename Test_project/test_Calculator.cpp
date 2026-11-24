#include "..\sln\Calculator.h"
#include "gtest.h"
#include <cmath>

// Конструктор
TEST(Calculator, can_create_empty_calculator) {
	Calculator c;
	ASSERT_EQ(c.getInfix(), "");
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



TEST(Calculator, throws_when_converting_empty_calculator) {
	Calculator c;
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_converting_whitespace_only_expression) {
	Calculator c("    ");
	ASSERT_EQ(c.getInfix(), "    ");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_extra_closing_bracket_at_end) {
	Calculator c("2 + 3)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_unclosed_opening_bracket_at_start) {
	Calculator c("(2 + 3");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_extra_closing_bracket_after_group) {
	Calculator c("(2 + 3) * 4)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_nested_opening_bracket_unclosed) {
	Calculator c("((2 + 3) * 4");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_inner_nested_bracket_unclosed) {
	Calculator c("(2 + (3 * 4)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_multiple_extra_closing_brackets) {
	Calculator c("(((2 + 3))))");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_multiple_unclosed_opening_brackets) {
	Calculator c("((((2 + 3)))");
	ASSERT_ANY_THROW(c.Calc());
}


// Calc
TEST(Calculator, calculates_simple_addition) {
	Calculator c("2 + 3");
	ASSERT_EQ(c.Calc(), 2 + 3);
}

TEST(Calculator, calculates_simple_multiplication) {
	Calculator c("2 * 4");
	ASSERT_EQ(c.Calc(), 2 * 4);
}

TEST(Calculator, respects_precedence_during_calculation) {
	Calculator c("2 + 3 * 4");
	ASSERT_EQ(c.Calc(), 2 + 3 * 4);
}

TEST(Calculator, calculates_division_and_multiplication) {
	Calculator c("2 / 6 + 3 * 4");
	ASSERT_EQ(c.Calc(), (double)2 / 6 + 3 * 4);
}

TEST(Calculator, calculates_expression_with_parentheses_first) {
	Calculator c("(2 + 3) * 4");
	ASSERT_EQ(c.Calc(), (2 + 3) * 4);
}

TEST(Calculator, calculates_expression_with_inner_parentheses) {
	Calculator c("2 + (3 * 4)");
	ASSERT_EQ(c.Calc(), 2 + (3 * 4));
}

TEST(Calculator, calculates_expression_wrapped_in_parentheses) {
	Calculator c("(2 + 3 * 4)");
	ASSERT_EQ(c.Calc(), (2 + 3 * 4));
}


TEST(Calculator, calculates_power_operation) {
	Calculator c("2 ^ 3");
	ASSERT_EQ(c.Calc(), pow(2, 3));
}


TEST(Calculator, calculates_right_associative_power) {
	Calculator c("2 ^ 3 ^ 4");
	ASSERT_EQ(c.Calc(), pow(2, pow(3, 4)));
}

TEST(Calculator, calculates_complex_expression_with_floats) {
	Calculator c("12.5 + .05 + 2 ^ 4 * 3");
	ASSERT_EQ(c.Calc(), (12.5 + .05 + pow(2, 4) * 3));
}

TEST(Calculator, calculates_single_number) {
	Calculator c("2");
	ASSERT_EQ(c.Calc(), 2);
}


TEST(Calculator, throws_when_dividing_by_zero) {
	Calculator c("10 / 0");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_dividing_by_zero_expression) {
	Calculator c("10 / (5 - 5)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_trailing_operator) {
	Calculator c("2 + ");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_consecutive_operators) {
	Calculator c("2 +* 4");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_missing_operator_between_numbers) {
	Calculator c("2 * 4 5");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, calculates_leading_unary_minus) {
	Calculator c("-2 + 3");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, 1);
}

TEST(Calculator, calculates_unary_minus_after_operator) {
	Calculator c("2 * -3");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, calculates_sin) {
	Calculator c("sin(2)");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, sin(2));
}

TEST(Calculator, calculates_cos) {
	Calculator c("cos(2)");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, cos(2));
}

TEST(Calculator, calculates_tg) {
	Calculator c("tg(2)");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, sin(2) / cos(2));
}

TEST(Calculator, calculates_ctg) {
	Calculator c("ctg(2)");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, cos(2) / sin(2));
}

TEST(Calculator, calculates_exp) {
	Calculator c("exp(2)");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, exp(2));
}

TEST(Calculator, calculates_ln) {
	Calculator c("ln(2)");
	double res;
	ASSERT_NO_THROW(res = c.Calc());
	ASSERT_EQ(res, log(2));
}

TEST(Calculator, throws_when_ctg_of_zero) {
	Calculator c("ctg(0)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_tg_at_pi_2) {
	Calculator c("tg(1.5707963267948966)");
	ASSERT_ANY_THROW(c.Calc());
}


TEST(Calculator, throws_when_ln_of_zero) {
	Calculator c("ln(0)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_ln_of_negative_number) {
	Calculator c("ln(-5)");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, calculates_nested_functions_with_expression) {
	Calculator c("sin(cos(0) + 1)");
	ASSERT_EQ(c.Calc(), sin(cos(0) + 1));
}

TEST(Calculator, calculates_complex_expression_with_functions_and_unary_minus) {
	Calculator c("- 2 * sin(0) + exp(1) * cos(0) - tg(0) + ctg(1)");
	ASSERT_EQ(c.Calc(), -2 * sin(0) + exp(1) * cos(0) - (sin(0) / cos(0)) + (cos(1) / sin(1)));
}

TEST(Calculator, throws_when_leading_multiplication_operator) {
	Calculator c("* 2 + 3");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_leading_division_operator) {
	Calculator c("/ 2 + 3");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_leading_power_operator) {
	Calculator c("^ 2 + 3");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_number_has_multiple_dots) {
	Calculator c("1.2.3");
	ASSERT_ANY_THROW(c.Calc());
}

TEST(Calculator, throws_when_expression_has_consecutive_dots) {
	Calculator c("1..2 + 3");
	ASSERT_ANY_THROW(c.Calc());
}