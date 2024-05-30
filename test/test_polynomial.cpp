#include "Polynomial.h"
#include <gtest.h>

TEST(Monom, can_create_empty_monom) {
	ASSERT_NO_THROW(Monom<int> obj);
}

TEST(Monom, can_create_monom) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	ASSERT_NO_THROW(Monom<int> obj(coef, var));
}

TEST(Monom, is_comparison_operator_valid) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);
	Monom<int> m2(coef, var);
	EXPECT_TRUE(m1 == m2);
}

TEST(Monom, is_plus_operator_valid) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	coef = 4;
	Monom<int> m2(coef, var); // Monom: 4*x^2

	coef = 6;
	Monom<int> res(coef, var);

	EXPECT_TRUE((m1+m2) == res);
}

TEST(Monom, is_possible_addition_with_invalid_args) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	coef = 4;
	var = { {'y', 2} };
	Monom<int> m2(coef, var); // Monom: 4*y^2

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(Monom, is_minus_operator_valid) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	coef = 4;
	Monom<int> m2(coef, var); // Monom: 4*x^2

	coef = -2;
	Monom<int> res(coef, var);

	EXPECT_TRUE((m1 - m2) == res);
}

TEST(Monom, is_mult_operator_valid) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	coef = 4;
	Monom<int> m2(coef, var); // Monom: 4*x^2

	coef = 8;
	var = { { 'x', 4 } };
	Monom<int> res(coef, var);

	EXPECT_TRUE((m1 * m2) == res);
}

TEST(Monom, is_assign_operator_valid) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);
	Monom<int> m2 = m1; 

	EXPECT_TRUE(m2 == m1);
}

TEST(Polynomial, can_create_empty_polinomial) {
	ASSERT_NO_THROW(Polynomial<int> obj);
}

TEST(Polynomial, can_add_new_monom) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj;

	ASSERT_NO_THROW(obj.push(m1));
}

TEST(Polynomial, can_addition_polynomials) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);
	var = { {'y', 2}};
	Monom<int> m11(coef, var); // Monom: 2*y^2;

	Polynomial<int> obj1;

	std::unordered_map<char, int> var2 = { {'y', 2} };
	int coef2 = 2; // Monom: 2*y^2
	Monom<int> m2(coef2, var2);
	Polynomial<int> obj2;

	obj1.push(m1);
	obj1.push(m11);
	obj2.push(m2);
	ASSERT_NO_THROW(obj1 + obj2);
}

TEST(Polynomial, can_multiply_polynomials) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;

	std::unordered_map<char, int> var2 = { {'y', 2} };
	int coef2 = 2; // Monom: 2*y^2
	Monom<int> m2(coef2, var2);
	Polynomial<int> obj2;

	obj1.push(m1);
	obj2.push(m2);
	ASSERT_NO_THROW(obj1 * obj2);
}

TEST(Polynomial, can_subtract_polynomials) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;

	std::unordered_map<char, int> var2 = { {'y', 2} };
	int coef2 = 2; // Monom: 2*y^2
	Monom<int> m2(coef2, var2);
	Polynomial<int> obj2;

	obj1.push(m1);
	obj2.push(m2);
	ASSERT_NO_THROW(obj1 - obj2);
}

TEST(Polynomial, can_multiply_polynomial_with_scalar) {
	std::unordered_map<char, int> var = { {'x', 2} };
	int coef = 2; // Monom: 2*x^2
	Monom<int> m1(coef, var);

	Polynomial<int> obj1;
	obj1.push(m1);

	ASSERT_NO_THROW(obj1 * 5);
}