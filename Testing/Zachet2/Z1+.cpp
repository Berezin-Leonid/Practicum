#include <iostream>
#include <exception>

template<typename T>
class MultiSet
{
public:
	MultiSet();
	MultiSet(const MultiSet &, int new_size = -1);
	MultiSet & operator = (MultiSet);
	~MultiSet();

    enum {
        START_ARR_SIZE = 10,
        GROWTH_RATE = 2
    };

	void clear();
	int size() const;
	T & operator [] (int index);
	const T & operator [] (int index) const;
	void add(const T &t);
	void del(int index, T & t);
private:
	T *array;
	int capacity;
	int _size;

    void swap(MultiSet &);
};

template<typename T>
MultiSet<T>::MultiSet() : array(nullptr), capacity(0), _size(0)
{}

template<typename T>
MultiSet<T>::MultiSet(const MultiSet &obj, int cap) : array(nullptr),
		capacity(obj.capacity), _size(obj._size)
{
    if (cap >= 0 && cap >= _size) {
        capacity = cap;
    }
    array = new T[capacity];

	try {
		for (int i = 0; i < _size; ++i) {
			array[i] = obj.array[i];
		}
	} catch (std::exception &ex) {
		delete [] array;
		throw;
	}
}

template <class T>
void MultiSet<T>::swap(MultiSet<T> & other) {
    std::swap(other.array, this -> array);
    std::swap(other._size, this -> _size);
    std::swap(other.capacity, this -> capacity);
}

template<typename T>
MultiSet<T> & MultiSet<T>::operator = (MultiSet obj)
{
    swap(obj);
	return *this;
}

template<typename T>
MultiSet<T>::~MultiSet()
{
	delete [] array;
}

template<typename T>
void
MultiSet<T>::clear()
{
	_size = 0;
}

template<typename T>
int
MultiSet<T>::size() const
{
	return _size;
}

template<typename T>
T & MultiSet<T>::operator [] (int index)
{
	if (index < 0 || index >= _size) {
		throw std::exception();
	}
	return array[index];
}

template<typename T>
const T &
MultiSet<T>::operator [] (int index) const
{
	if (index < 0 || index >= _size) {
		throw std::exception();
	}
	return array[index];
}

template<typename T>
void
MultiSet<T>::add(const T &elem)
{

    if (_size == capacity) {
        if (capacity == 0) {
            MultiSet obj(*this, MultiSet::START_ARR_SIZE);
            swap(obj);
        } else {
            MultiSet obj(*this, this -> capacity * MultiSet::GROWTH_RATE);
            swap(obj);
        }
    }

    try {
        array[_size] = elem;
        ++_size;
    } catch(const std::exception &err) {
        throw;
    }
}

template<typename T>
void MultiSet<T>::del(int index, T & t)
{
	t = this -> operator [](index);
    MultiSet<T> copy = *this;

    try {
	    array[index] = array[_size - 1];
	    --_size;
    } catch(const std::exception & e) {
        swap(copy);
        throw;
    }
}

#ifdef LEO
int
main()
{
	try {
		MultiSet<int> x, y;
		x.add(1);
		x.add(2);
		x.add(3);
        for (int i = 0; i < 3; ++i) {
            std::cout << x[i];
        }
        std::cout << std::endl;
		y = x;
        int in;
		x.del(0, in);
		std::cout << x[0] << x[1] << std::endl;
		std::cout << y[0] << y[1] << y[2] << std::endl;
	} catch(...) {
		std::cout << std::endl << "Exception!" << std::endl;
	}
}
#endif
