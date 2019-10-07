#include <cstdlib>
#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
	SimpleVector() {
		data_ = nullptr;
		capacity_ = 0;
		size_ = 0;
	}
	explicit SimpleVector(const size_t& size) {
		data_ = new T[size];
		capacity_ = size;
		size_ = size;
	}
	~SimpleVector() {
		delete[] data_;
	}

	T& operator[](const size_t& index) {
		return data_[index];
	}
	const T& operator[](const size_t& index) const {
		return data_[index];
	}

	const T* begin() const {
		return data_;
	}
	const T* end() const {
		return data_ + size_;
	}
	T* begin()  {
		return data_;
	}
	T* end()  {
		return data_ + size_;
	}

	size_t Size() const {
		return size_;
	}
	size_t Capacity() const {
		return capacity_;
	}
	void PushBack(const T& value) {
		if (size_ >= capacity_) {
			if (capacity_ == 0) capacity_ = 1;
			else capacity_ *= 2;
			T* new_data = new T[capacity_];
			copy(data_, data_ + size_, new_data);
			delete[] data_;
			data_ = new_data;
		}
		data_[size_++] = value;
	}

private:
	T* data_;
	size_t capacity_;
	size_t size_;
};
