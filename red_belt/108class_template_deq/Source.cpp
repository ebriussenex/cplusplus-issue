#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <vector>
#include <stdexcept>

#include "test_runner.h"

template <typename T>
class Deque {
public:
	Deque() = default;
	bool Empty() const;
	size_t Size() const;
	void PushFront(const T& x);
	void PushBack(const T& x);
	T& operator [](const size_t& index);
	const T& operator[](const size_t& index) const;
	T& Front();
	T& Back();
	const T& Front() const;
	const T& Back() const;
	T& At(const size_t& index);
	T& At(const size_t& index) const;
	/*void Print() const;*/
private:
	std::vector <T> v_front_;
	std::vector <T> v_back_;
};

template<typename T>
bool Deque<T>::Empty() const
{
	return v_front_.empty() && v_back_.empty();
}

template<typename T>
size_t Deque<T>::Size() const
{
	return (v_front_.size() + v_back_.size());
}

template<typename T>
void Deque<T>::PushFront(const T& x) {
	v_front_.push_back(x);
}

template<typename T>
void Deque<T>::PushBack(const T& x) {
	v_back_.push_back(x);
}

template<typename T>
T& Deque<T>::operator[](const size_t& index)
{
	if (index >= v_front_.size() + v_back_.size()) throw std::out_of_range("Index is out of range");
	if (index < v_front_.size()) return v_front_[v_front_.size() - index - 1];
	else return v_back_[index - v_front_.size()];
}

template<typename T>
const T& Deque<T>::operator[](const size_t& index) const
{
	if (index >= v_front_.size() + v_back_.size()) throw std::out_of_range("Index is out of range");
	if (index < v_front_.size()) return v_front_[v_front_.size() - index - 1];
	else return v_back_[index - v_front_.size()];
}

template<typename T>
T& Deque<T>::Front()
{
	if (v_front_.empty()) {
		if (v_back_.empty()) throw std::out_of_range("Out of range Front");
		else return v_back_.front();
	}
	return v_front_.back();
}

template<typename T>
T& Deque<T>::Back()
{
	if (v_back_.empty()) {
		if (v_front_.empty()) throw std::out_of_range("Out of range Back");
		else return v_front_.front();
	}
	return v_back_.back();
}

template<typename T>
const T& Deque<T>::Front() const
{
	if (v_front_.empty()) {
		if (v_back_.empty()) throw std::out_of_range("Out of range Front");
		else return v_back_.front();
	}
	return v_front_.back();
}

template<typename T>
const T& Deque<T>::Back() const
{
	if (v_back_.empty()) {
		if (v_front_.empty()) throw std::out_of_range("Out of range Back");
		else return v_front_.front();
	}
	return v_back_.back();
}

template<typename T>
T& Deque<T>::At(const size_t& index)
{
	if (index >= v_front_.size() + v_back_.size()) throw std::out_of_range("Index is out of range");
	if (index < v_front_.size()) return v_front_[v_front_.size() - index - 1];
	else return v_back_[index - v_front_.size()];
}

template<typename T>
T& Deque<T>::At(const size_t& index) const
{
	if (index >= v_front_.size() + v_back_.size()) throw std::out_of_range("Index is out of range");
	if (index < v_front_.size()) return v_front_[v_front_.size() - index - 1];
	else return v_back_[index - v_front_.size()];
}

//template<typename T>
//void Deque<T>::Print() const
//{
//	for (auto it = v_front_.end(); it != v_front_.begin(); it--) {
//		std::cout << *it << " ";
//	}
//	for (auto it = v_back_.begin(); it != v_back_.end(); it++) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;
//}

void TestTable() {

	Deque<int> deque;

	deque.PushFront(1);

	deque.PushBack(2);

	ASSERT_EQUAL(deque.Size(), 2u);

	ASSERT_EQUAL(deque.Front(), 1);

	ASSERT_EQUAL(deque.Back(), 2);

	ASSERT_EQUAL(deque[0], 1);

	ASSERT_EQUAL(deque[1], 2);

	deque.PushFront(3);

	deque.PushBack(4); //{3, 1, 2, 4}

	ASSERT_EQUAL(deque.Size(), 4u);

	ASSERT_EQUAL(deque.Front(), 3);

	ASSERT_EQUAL(deque.Back(), 4);

	ASSERT_EQUAL(deque[0], 3);

	ASSERT_EQUAL(deque[1], 1);

	ASSERT_EQUAL(deque[2], 2);

	ASSERT_EQUAL(deque[3], 4);

	deque.PushBack(-4);

	deque.PushBack(100);

	deque.PushBack(-100);

	deque.PushFront(-3);

	deque.PushFront(-2);

	deque.PushFront(-1);

	//{-1, -2, -3, 3, 1, 2, 4, -4, 100, -100}

	ASSERT_EQUAL(deque[0], -1);

	ASSERT_EQUAL(deque[1], -2);

	ASSERT_EQUAL(deque[2], -3);

	ASSERT_EQUAL(deque[3], 3);

	ASSERT_EQUAL(deque[4], 1);

	ASSERT_EQUAL(deque[5], 2);

	ASSERT_EQUAL(deque[6], 4);

	ASSERT_EQUAL(deque[7], -4);

	ASSERT_EQUAL(deque[8], 100);

	ASSERT_EQUAL(deque[9], -100);

	ASSERT_EQUAL(deque.Size(), 10u);

	ASSERT_EQUAL(deque.Front(), -1);

	ASSERT_EQUAL(deque.Back(), -100);

	//--------------------------------------

	deque[0] = 0;

	deque[1] = 1;

	deque[2] = 2;

	deque[3] = 3;

	deque[4] = 4;

	deque[5] = 5;

	deque[6] = 6;

	deque[7] = 7;

	deque[8] = 8;

	deque[9] = 9;

	ASSERT_EQUAL(deque[0], 0);

	ASSERT_EQUAL(deque[1], 1);

	ASSERT_EQUAL(deque[2], 2);

	ASSERT_EQUAL(deque[3], 3);

	ASSERT_EQUAL(deque[4], 4);

	ASSERT_EQUAL(deque[5], 5);

	ASSERT_EQUAL(deque[6], 6);

	ASSERT_EQUAL(deque[7], 7);

	ASSERT_EQUAL(deque[8], 8);

	ASSERT_EQUAL(deque[9], 9);

	//----------------------------------------

	int a;

	try {

		a = 1 + deque[10];

	}

	catch (std::out_of_range& ex) { a = 1; }

	ASSERT_EQUAL(a, 1);

	try {

		a = 1 + deque[-1];

	}

	catch (std::out_of_range& ex) { a = 2; }

	ASSERT_EQUAL(a, 2);

	//---------------------------------

	/*deque.Print();*/

	//-------------------------------------------

	Deque<int> deq;

	try {

		deq.Front() = -666;

		deq.Back() = -999;

	}

	catch (std::out_of_range& ex) {}

	try {

		ASSERT_EQUAL(deq[0], -666);

	}

	catch (std::out_of_range& ex) {}

	try {

		ASSERT_EQUAL(deq.Front(), -666);

	}

	catch (std::out_of_range& ex) {}

	try {

		ASSERT_EQUAL(deq.Back(), -999);

	}

	catch (std::out_of_range& ex) {}

	//-------------------------------------------

	Deque<int> deque1;

	deque1.PushBack(1);

	deque1.PushBack(2);

	deque1.PushBack(3);

	deque1.PushBack(4);

	deque1.PushBack(5);

	deque1.PushBack(6);

	deque1.Front() = 0;

	deque1.Back() = 0;

	Deque<int> deque2;

	deque2.PushFront(1);

	deque2.PushFront(2);

	deque2.PushFront(3);

	deque2.PushFront(4);

	deque2.PushFront(5);

	deque2.PushFront(6);

	deque2.Front() = 0;

	deque2.Back() = 0;

}

int main() {
	TestRunner tr;
	tr.RunTest(TestTable, "test deque");
	return 0;
}
