#include <iostream>
#include <utility>

template<typename T>
class MultiSet
{
public:
	MultiSet();
	MultiSet(const MultiSet &, int new_size = -1);
	MultiSet & operator = (MultiSet);
	~MultiSet();
	void clear();
	int size() const;
	T & operator [] (int index);
	const T & operator [] (int index) const;
	void add(const T &t);
	T del(int index);
private:
	T *arr;
	int real_size;
	int len;
};

template<typename T>
MultiSet<T>::MultiSet() : arr(nullptr), real_size(1), len(0)
{
	arr = new T[real_size];
}

template<typename T>
MultiSet<T>::MultiSet(const MultiSet &other, int new_size) : arr(nullptr),
		real_size(other.real_size), len(other.len)
{
	if (new_size <= real_size) {
		arr = new T[real_size];
	} else {
		arr = new T[new_size];
		real_size = new_size;
	}
	try {
		for (int i = 0; i < len; ++i) {
			arr[i] = other.arr[i];
		}
	} catch (std::exception &ex) {
		delete [] arr;
		throw;
	}
}

template<typename T>
MultiSet<T> &
MultiSet<T>::operator = (MultiSet other)
{
	std::swap(arr, other.arr);
	std::swap(real_size, other.real_size);
	std::swap(len, other.len);
	return *this;
}

template<typename T>
MultiSet<T>::~MultiSet()
{
	delete [] arr;
}

template<typename T>
void
MultiSet<T>::clear()
{
	len = 0;
}

template<typename T>
int
MultiSet<T>::size() const
{
	return len;
}

template<typename T>
T &
MultiSet<T>::operator [] (int index)
{
	if (index < 0 || index >= len) {
		throw std::exception();
	}
	return arr[index];
}

template<typename T>
const T &
MultiSet<T>::operator [] (int index) const
{
	if (index < 0 || index >= len) {
		throw std::exception();
	}
	return arr[index];
}

template<typename T>
void
MultiSet<T>::add(const T &t)
{
	if (len >= real_size) {
		MultiSet<T> new_multiset(*this, real_size * 2);
		new_multiset.arr[len] = t;
		++new_multiset.len;
		std::swap(arr, new_multiset.arr);
		std::swap(real_size, new_multiset.real_size);
		std::swap(len, new_multiset.len);
	} else {
		arr[len] = t;
		++len;
	}
}

template<typename T>
T
MultiSet<T>::del(int index)
{
	T tmp = (*this)[index];
	arr[index] = arr[len - 1];
	--len;
	return tmp;
}

int
main()
{
	try {
		MultiSet<int> x, y;
		x.add(1);
		x.add(2);
		x.add(3);
		std::cout << x[0] << x[1] << x[2] << std::endl;
		y = x;
		x.del(0);
		std::cout << x[0] << x[1] << std::endl;
		std::cout << y[0] << y[1] << y[2] << std::endl;
	} catch(...) {
		std::cout << std::endl << "Exception!" << std::endl;
	}
}