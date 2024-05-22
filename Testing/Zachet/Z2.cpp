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
    void del(int index, T &);
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

    int i;
    try {
        for (i = 0; i < _size; i++) {
            new (&array[i]) T(obj.array[i]);
        }
    } catch(std::exception & ex) {
        for (int j = 0; j < i; ++j) {
            array[i].~T();
        }
        delete [] array;
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

    new (&array[_size]) T(elem);
    ++_size;
}




template <class T>
void MultiSet<T>::del(int index, T & t) {
    t = this -> operator [](index);
    array[index] = array[_size - 1];
    array[_size - 1].~T();
    --_size;
}

class Component {
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
    MultiSet<Component *> multi_set;
private:
    virtual const std::string & name() const = 0;
};


Component::Component(): multi_set()
{}

Component::~Component()
{}


int
Component::count () const
{
    return multi_set.size();
}

Component & Component::subcomponent(int index) {
    return *(multi_set[index]);
}

const Component & Component::subcomponent(int index) const {
    return *(multi_set[index]);
}


void Component::add(Component & obj) {
    multi_set.add(&obj); 
}


std::ostream & operator << (std::ostream & ss, const Component & obj) {
    ss << obj.name() << "(";
    for (int i = 0; i < obj.multi_set.size(); ++i) {
        ss << *(obj.multi_set[i]);
        if (i < obj.multi_set.size() - 1) {
            ss << ", ";
        }
    }
    ss << ")";
    return ss;
}


class Box: public Component {
public:
    Box(const std::string &);
    Box(const Box &);
    Box & operator = (const Box & other);
    ~Box();
private:
    const std::string & name() const;
    std::string str;
};


Box::Box(const std::string &s):
    Component(), str(s)
{}

Box::Box(const Box & other):
    Component(), str(other.str)
{}

Box & Box::operator = (const Box & other)
{
    if (this != & other) {
        multi_set.clear();
        str = other.str;
    }
    return  * this;
}

Box::~Box()
{}

const std::string & Box::name() const
{
    static std::string obj = "qwerty";
    return obj;
}

#ifdef LEO
int
main()
{
    Box b1("a"), b2("b"), b3("c");
    b1.add(b2);
    b1.add(b3);
    std::cout << b1 << std::endl;
    return 0;
}
#endif
