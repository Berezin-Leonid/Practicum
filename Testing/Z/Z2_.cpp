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

class Component
{
public:
	Component();
	Component(const Component &) = delete;
	Component & operator = (const Component &) = delete;
	virtual ~Component();
	int count() const;
	Component & subcomponent(int);
	const Component & subcomponent(int) const;
	void add(Component &);
	friend std::ostream & operator << (std::ostream &, const Component &);
protected:
	MultiSet<Component *> multiset;
private:
	virtual const std::string & name() const = 0;
};

Component::Component() : multiset() {}

Component::~Component() {}

int
Component::count() const
{
	return multiset.size();
}

Component &
Component::subcomponent(int index)
{
	return *(multiset[index]);
}

const Component &
Component::subcomponent(int index) const
{
	return *(multiset[index]);
}

void
Component::add(Component &new_component)
{
	multiset.add(&new_component);
}

std::ostream &
operator << (std::ostream &stream, const Component &comp)
{
	stream << comp.name() << '(';
	for (int i = 0; i < comp.multiset.size(); ++i) {
		stream << *(comp.multiset[i]);
		if (i < comp.multiset.size() - 1) {
			stream << ", ";
		}
	}
	stream << ')';
	return stream;
}

class Box: public Component
{
public:
	Box(const std::string &);
	Box(const Box &);
	Box & operator = (const Box &);
	~Box();
private:
	const std::string & name() const;
	std::string str;
};

Box::Box(const std::string &s) : Component(), str(s) {}

Box::Box(const Box &other) : Component(), str(other.str) {}

Box &
Box::operator = (const Box &other)
{
	if (this != &other) {
		multiset.clear();
		str = other.str;
	}
	return *this;
}

Box::~Box() {}

const std::string &
Box::name() const
{
	return str;
}

int
main()
{
	Box b1("a"), b2("b"), b3("c");
	b1.add(b2);
	b1.add(b3);
	std::cout << b1 << std::endl;
	return 0;
}