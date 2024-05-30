#pragma once
#include <stdexcept>
#include <vector>

template <typename type>
class List;
template <typename type>
class Iterator;

template <typename type>
struct TNode {
    TNode<type>* pNext;
	type value;

    bool operator==(const TNode<type>& node) { return this->value == node.value; }
    bool operator!=(const TNode<type>& node) { return this->value != node.value; }

    TNode(type val, TNode<type>* nextPtr = nullptr) : value(val), pNext(nextPtr) {}
};

template <typename type>
class List {

	template <typename t>
	friend class Iterator;

private:
    TNode<type>* root;

public:
	List() : root(nullptr) {}
	List(const std::vector<type>& vec);
	List(const List& list);
	List(List&& list) noexcept;

	List<type>& operator=(const List& list);
	List<type>& operator=(List&& list) noexcept;

	Iterator<type> Begin() const;
	Iterator<type> End() const;

	~List();

	bool IsEmpty() const noexcept { return root == nullptr; }

	void PushFront(const type& val);
	void PopFront() noexcept;
	void PushBack(const type& val);
	void PopBack() noexcept;

	void PushAfter(const Iterator<type>& it, const type& value);
	void Erase(const Iterator<type>& it);

	void Clear();
};

template <typename type>
class Iterator {
public:
    TNode<type>* target;

	Iterator() : target(nullptr) {}
    Iterator(TNode<type>* node) : target(node) {}
	Iterator(const Iterator& it) : target(it.target) {}
	Iterator(Iterator&& it) noexcept;

	Iterator<type>& operator=(const Iterator& it);
	Iterator<type>& operator=(Iterator&& it) noexcept;

	~Iterator() { target = nullptr; }

	type& operator*() const;
	type* operator->() const;

	Iterator<type>& operator++();
	const Iterator<type> operator++(int);

	bool operator==(const Iterator& it) const noexcept;
	bool operator!=(const Iterator& it) const noexcept;

};

template<typename type>
List<type>::List(const std::vector<type>& vec) {
	root = nullptr;
    for (std::size_t i = 0; i < vec.size(); i++) {
		this->PushBack(vec[i]);
	}
}

template<typename type>
List<type>::List(const List& list) {
	root = nullptr;
	for (auto i = list.Begin(); i != list.End(); ++i) {
		this->PushBack(i.target->value);
	}
}

template<typename type>
List<type>::List(List&& list) noexcept {
	this->root = list.root;
	list.root = nullptr;
}

template<typename type>
List<type>& List<type>::operator=(const List& list)
{
	this->Clear();
	for (auto i = list.Begin(); i != list.End(); ++i) {
		this->PushBack(i.target->value);
	}
	return *this;
}

template<typename type>
List<type>& List<type>::operator=(List&& list) noexcept
{
	this->Clear();
	this->root = list.root;
	list.root = nullptr;
	return *this;
}

template<typename type>
Iterator<type> List<type>::Begin() const {
	Iterator<type> it(root);
	return it;
}

template<typename type>
Iterator<type> List<type>::End() const {
	Iterator<type> it(nullptr);
	return it;
}

template<typename type>
List<type>::~List() {
	Clear();
}

template<typename type>
void List<type>::PushFront(const type& val) {
    TNode<type>* oldRoot = root;
    root = new TNode<type>(val, oldRoot);
}

template<typename type>
void List<type>::PopFront() noexcept {
    TNode<type>* toDelete = root;
	root = root->pNext;
	toDelete->pNext = nullptr;
	delete toDelete;
}

template<typename type>
void List<type>::PushBack(const type& val) {
    if (root == nullptr) { root = new TNode<type>(val); return; }
    TNode<type>* current = root;
	while (current->pNext) {
		current = current->pNext;
	}
    current->pNext = new TNode<type>(val);
}

template<typename type>
void List<type>::PopBack() noexcept {
	if (root == nullptr) return;
	auto i = this->Begin();
	if (i.target->pNext == nullptr) { root = nullptr; return; }

	for (i; i.target->pNext->pNext != nullptr; i++) {}
    TNode<type>* toDelete = i.target->pNext;
	i.target->pNext = nullptr;
	delete toDelete;
}

template<typename type>
void List<type>::PushAfter(const Iterator<type>& it, const type& value) {
    if (it.target == nullptr) throw std::out_of_range("Invalid iterator!");
    if (root == nullptr) { PushFront(value); return; }

	auto i = this->Begin();
    while (i != this->End() && i != it) { i++; }
	if (i == this->End()) throw std::out_of_range("Invalid iterator");

    TNode<type>* next = i.target->pNext;
    i.target->pNext = new TNode<type>(value, next);

}

template<typename type>
void List<type>::Erase(const Iterator<type>& it) {
	if (root == nullptr) throw std::out_of_range("Empty list!");
	if (it == nullptr) throw std::out_of_range("Invalid iterator!");

    if (root == it.target && root->pNext != nullptr) {
        TNode<type>* next = root->pNext;
		root->pNext = nullptr;
		delete root;
		root = next;
		return;
    } else if (root->pNext == nullptr) {
        delete root;
        root = nullptr;
        return;
    }

	Iterator<type> current(root);

	while ((current != this->End()) && (current.target->pNext != it.target)) {
		++current;
	}

	if (current.target->pNext == nullptr) throw std::out_of_range("Invalid iterator");
    TNode<type>* toDelete = current.target->pNext;
	current.target->pNext = toDelete->pNext;
	toDelete->pNext = nullptr;
	delete toDelete;
}

template<typename type>
void List<type>::Clear() {
    TNode<type>* current = root;
	while (current != nullptr) {
        TNode<type>* next = current->pNext;
        current->pNext = nullptr;
		delete current;
		current = next;
	}
	root = nullptr;
}

template<typename type>
Iterator<type>::Iterator(Iterator&& it) noexcept {
	this->target = it.target;
	it.target = nullptr;
}

template<typename type>
Iterator<type>& Iterator<type>::operator=(const Iterator& it) {
	this->target = it.target;
	return *this;
}

template<typename type>
Iterator<type>& Iterator<type>::operator=(Iterator&& it) noexcept {
	this->target = it.target;
	it.target = nullptr;
	return *this;
}

template<typename type>
type& Iterator<type>::operator*() const {
	return target->value;
}

template<typename type>
type* Iterator<type>::operator->() const {
	return &target->value;
}

template<typename type>
Iterator<type>& Iterator<type>::operator++() {
	if (target == nullptr) throw std::out_of_range("Invalid iterator!");
	target = target->pNext;
	return *this;
}

template<typename type>
const Iterator<type> Iterator<type>::operator++(int) {
	if (target == nullptr) throw std::out_of_range("Invalid iterator!");
	Iterator<type> it(*this);
	target = target->pNext;
	return it;
}

template<typename type>
bool Iterator<type>::operator==(const Iterator& it) const noexcept {
	return this->target == it.target;
}

template<typename type>
bool Iterator<type>::operator!=(const Iterator& it) const noexcept {
	return this->target != it.target;
}
