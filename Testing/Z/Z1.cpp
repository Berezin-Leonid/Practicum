#include <iostream>
#include <exception>

template <class T>
class MultiSet {
public:
    MultiSet();
    ~MultiSet();
    MultiSet(MultiSet const &, int cap = -1);
    MultiSet & operator =(MultiSet);

    enum {
        START_ARR_SIZE = 10,
        GROWTH_RATE = 2
    };

    void clear();
    int size() const;
    T & operator [](int index);
    const T & operator [](int index) const;
    void add(const T &t);
    T del(int index);
private:

    T * array;
    int capacity;
    int _size;

    void swap(MultiSet &);
};

template <class T>
MultiSet<T>::MultiSet():
        array(nullptr), capacity(0), _size(0)
{}


template <class T>
MultiSet<T>::~MultiSet() {
    for (int i = 0; i < _size; ++i) {
        array[i].~T();
    }

    delete[] reinterpret_cast<char *>(array);
}

template <class T>
MultiSet<T>::MultiSet(MultiSet<T> const & obj, int cap)
{
    _size = obj._size;
    capacity = obj.capacity;
    if (cap >= 0 && cap >= _size) {
        capacity = cap;
    }
    array = reinterpret_cast<T*> (new char[capacity * sizeof(T)]);

    try {
        for (int i = 0; i < _size; i++) {
            new (&array[i]) T(obj.array[i]);
        }
    } catch(std::exception & ex) {
        delete [] arr;
        throw;
    }
}


template<class T>
void MultiSet<T>::swap(MultiSet<T> & other)
{
    std::swap(other.array , this -> array); 
    std::swap(other._size , this -> _size); 
    std::swap(other.capacity , this -> capacity); 
}


template <class T>
MultiSet<T> & MultiSet<T>::operator =(MultiSet<T> other) {
    swap(other);
    return *this;
}


template <class T>
void MultiSet<T>::clear() {
    MultiSet<T> obj;
    swap(obj);
}

template <class T>
int MultiSet<T>::size() const {
    return _size;
}

template <class T>
T & MultiSet<T>::operator [](int index) {
    if ((index >= _size) || (index <= -1)) {
        throw std::exception();
    }
    return array[index];
}

template <class T>
T const & MultiSet<T>::operator [](int index) const {
    if ((index >= _size) || (index <= -1)) {
        throw std::exception();
    }
    return array[index];
}

template <class T>
void MultiSet<T>::add(const T & elem) {
    if (_size == capacity) {
        if (capacity == 0) {
            MultiSet obj(*this, MultiSet::START_ARR_SIZE);
            swap(obj);
        } else {
            MultiSet obj(*this, this -> capacity * MultiSet::GROWTH_RATE);
            swap(obj);
        }
    }

    new (&array[_size++]) T(elem);
}




template <class T>
T MultiSet<T>::del(int index) {
    T obj = this -> operator [](index);
    array[index] = array[_size - 1];
    array[_size - 1].~T();
    --_size;
    return obj;
}

/*
*/

#ifdef LEO
int
main()
{
    MultiSet<int> a;
    a.add(100);
    a.add(200);
    a.add(300);
    MultiSet<int> b(a,10);
    b.clear();
    b = a;

    b.del(1);
    std::cout << b[0] << std::endl;

//===================================================================

    MultiSet<std::string> a1;
    a1.add("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    a1.add("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    a1.add("cccccccccccccccccccccccccccccccccccccccccccccccccc");
    MultiSet<std::string> b1;
    b1.clear();
    b1 = a1;

    std::cout << b1[2] << std::endl;

    //const check

    MultiSet<std::string> a2;
    a2.add("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    a2.add("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    a2.add("cccccccccccccccccccccccccccccccccccccccccccccccccc");

    const MultiSet<std::string> b2 = a2;
    std::cout << b2[0] << std::endl;

    return 0;
}
#endif
