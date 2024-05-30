#include <gtest.h>
#include "List.h"
#include <vector>

TEST(List, can_create_int_empty_list) {
	EXPECT_NO_THROW(List<int> list);
}

TEST(List, can_push_back_to_int_list) {
	List<int> list;
	EXPECT_NO_THROW(list.PushBack(5));
}

TEST(List, is_added_value_to_list_correct) {
	List<int> list;
	list.PushBack(5);
	EXPECT_EQ(*list.Begin(), 5);
}

TEST(List, can_create_list_from_int_vector) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	EXPECT_NO_THROW(List<int> list(data));
}

TEST(List, is_added_values_from_vector_correct) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list(data);
	int sum = 0;
	for (auto i = list.Begin(); i != list.End(); ++i) { sum += i.target->value; }
	EXPECT_EQ(sum, 21);
}

TEST(List, can_copy_list_with_constructor) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	EXPECT_NO_THROW(List<int> list2(list1));
}

TEST(List, is_copy_list_correct) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	List<int> list2(list1);

	int sum = 0;
	for (auto i = list2.Begin(); i != list2.End(); ++i) { sum += i.target->value; }
	EXPECT_EQ(sum, 21);
}

TEST(List, can_copy_list_with_operator) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	EXPECT_NO_THROW(List<int> list2 = list1);
}

TEST(List, is_copy_list_correct_op) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	List<int> list2 = list1;

	int sum = 0;
	for (auto i = list2.Begin(); i != list2.End(); ++i) { sum += i.target->value; }
	EXPECT_EQ(sum, 21);
}

TEST(List, can_empty_check) {
	List<int> list1;
	EXPECT_NO_THROW(list1.IsEmpty());
}

TEST(List, is_empty_check_correct) {
	List<int> list1;
	EXPECT_TRUE(list1.IsEmpty());
}

TEST(List, can_push_front_to_int_list) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	EXPECT_NO_THROW(list1.PushFront(1));
}

TEST(List, is_push_front_to_int_list_correct) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	list1.PushFront(2);
	EXPECT_EQ(list1.Begin().target->value, 2);
}

TEST(List, can_pop_front_from_int_list) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	EXPECT_NO_THROW(list1.PopFront());
}

TEST(List, is_pop_front_from_int_list_correct) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	list1.PopFront();
	EXPECT_EQ(list1.Begin().target->value, 2);
}

TEST(List, can_pop_back_from_int_list) {
	std::vector<int> data = { 1,2,3,4,5,6 };
	List<int> list1(data);
	EXPECT_NO_THROW(list1.PopBack());
}

TEST(List, is_pop_back_from_int_list_correct) {
	std::vector<int> data = { 1,2,3 };
	List<int> list1(data);
	list1.PopBack();
	int sum = 0;
	for (auto i = list1.Begin(); i != list1.End(); ++i) { sum += i.target->value; }
	EXPECT_EQ(sum, 3);
}

TEST(List, can_push_after_elem) {
	std::vector<int> data = { 1,2,3 };
	List<int> list1(data);

	auto i = list1.Begin();
	i++;

	EXPECT_NO_THROW(list1.PushAfter(i, 4)); // 1 2 4 3
}

TEST(List, is_push_after_correct) {
	std::vector<int> data = { 1,2,3 };
	List<int> list1(data);

	auto i = list1.Begin();
	i++;

	list1.PushAfter(i, 4); // 1 2 4 3
	i++;
	EXPECT_EQ(i.target->value, 4);
}

TEST(List, can_erase_elem_from_int_list) {
	std::vector<int> data = { 1,2,3 };
	List<int> list1(data);

	auto i = list1.Begin();
	i++;
	EXPECT_NO_THROW(list1.Erase(i));
}

TEST(List, is_erase_correct) {
	std::vector<int> data = { 1,2,3 };
	List<int> list1(data);

	auto i = list1.Begin();
	i++;
	list1.Erase(i); // 1 3
	i = list1.Begin();
	i++;
	EXPECT_EQ(i.target->value, 3);
}