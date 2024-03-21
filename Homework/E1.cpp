#include <iostream>
#include <cstring>



class Vector {
public:

    Vector(Vector const &);
    Vector(int);
    ~Vector();
    void * give(int)const; 
    void push(const void *);
    int size()const;
    Vector & operator = (Vector const &);
    void swap(Vector &);

private:

    int perem_size;
    char * ptr;
    int _size;
    int capacity;

};

class IntVector: private Vector {
public:

    IntVector();
    IntVector(IntVector const &);
    using Vector::size;
    using Vector::operator =;
    int & operator [](int);
    int const & operator [](int)const;
    void insert(int);
};

class DoubleVector: private Vector {
public:

    DoubleVector();
    DoubleVector(DoubleVector const &);
    using Vector::size;
    using Vector::operator =;
    double & operator [](int);
    double const & operator [](int)const;
    void insert(double);
};

class IntVectorVector: private Vector {
public:

    IntVectorVector();
    IntVectorVector(IntVectorVector const &);
    ~IntVectorVector();
    using Vector::size;
    IntVectorVector & operator =(IntVectorVector const &);
    IntVector & operator [](int);
    IntVector const & operator [](int)const;
    void insert(IntVector const &);
};

//class Vector
    //constructors

Vector::Vector(Vector const &obj)
{
    capacity = obj.capacity;
    perem_size = obj.perem_size;
    _size = obj._size;
    ptr = new char[capacity * perem_size];
    if (obj.ptr != nullptr && ptr != nullptr) {
        memcpy(ptr, obj.ptr, capacity * perem_size);
    }
}

Vector::Vector(int perem_s)
{
    capacity = 0;
    _size = 0;
    ptr = nullptr;
    perem_size = perem_s;
}

Vector::~Vector()
{
    delete []ptr;
}

    //methods
void * Vector::give(int i) const
{
    if ((i >= capacity) || (i < 0)) {
        std::cout << "Out of Vector [--> " << i << " <--]" << std::endl;
        exit(0);
    }

    return static_cast<void *>(ptr + perem_size * i);
}

void Vector::push(const void * p_obj)
{
    if (_size == capacity) {
        char * ptr2 = new char[perem_size * (capacity + 1) * 2];
        //nullptr
        if (ptr != nullptr) {
            memcpy(ptr2, ptr, capacity * perem_size);
            delete []ptr;
        }
        ptr = ptr2;
        capacity = (capacity + 1) * 2;
    }

    memcpy((ptr + perem_size * _size), p_obj, perem_size);
    ++_size;
}

int Vector::size()const
{
    return _size;
}

Vector & Vector::operator = (Vector const & right)
{
    if (this != &right) {
        capacity = right.capacity;
        _size = right._size;
        perem_size = right.perem_size;
        delete []ptr;
        ptr = new char [perem_size * capacity]; 
        memcpy(ptr, right.ptr,perem_size * capacity);
    }
    return *this;

}

void Vector::swap(Vector & obj)
{
    char * new_ptr = this -> ptr;
    this -> ptr = obj.ptr;
    obj.ptr = new_ptr;

    int cap = this -> capacity; 
    this -> capacity = obj.capacity;
    obj.capacity = cap;

    int size = this -> _size; 
    this -> _size = obj._size;
    obj._size = size;
    
    // is equal already int perem_size;
}


//class IntVector
    //constructors
IntVector::IntVector():
        Vector(sizeof (int))
{}

IntVector::IntVector(IntVector const & obj):
        Vector(obj)
{}

    //methods
int & IntVector::operator [](int i)
{
    return *static_cast<int *>(this -> give(i));
}

int const & IntVector::operator [](int i) const
{
    return *static_cast<int *>(this -> give(i));
}

void IntVector::insert(int x)
{
    this -> push(static_cast<void *>(&x));
}

//class DoubleVector
    //constructors
DoubleVector::DoubleVector(): Vector(sizeof (double))
{}

DoubleVector::DoubleVector(DoubleVector const &obj): Vector(obj)
{}

    //methods
double & DoubleVector::operator [](int i)
{
    return *static_cast<double *>(this -> give(i));
}

double const & DoubleVector::operator [](int i) const
{
    return *static_cast<double *>(this -> give(i));
}

void DoubleVector::insert(double x)
{
    this -> push(static_cast<void *>(&x));
}

//class IntVectorVector
    //constructors
IntVectorVector::IntVectorVector(): Vector(sizeof (IntVector))
{}

IntVectorVector::IntVectorVector(IntVectorVector const & obj): Vector(sizeof (IntVector))
{
    for (int i = 0; i < obj.size(); ++i){
        this->insert(obj[i]);
    }
}

IntVectorVector::~IntVectorVector()
{
    for(int i = 0; i < this -> size(); ++i) {
        static_cast<IntVector *> (this -> give(i))->~IntVector();
    }
}

    //methods
IntVector & IntVectorVector::operator [](int i)
{
    return *static_cast<IntVector *>(this -> give(i));
}

IntVector const & IntVectorVector::operator [](int i) const
{
    return *static_cast<IntVector *>(this -> give(i));
}


IntVectorVector & IntVectorVector::operator =(IntVectorVector const & obj)
{
    if (this != &obj) {
        IntVectorVector obj2 = obj;
        this -> Vector::swap(obj2);
    }
    return *this;
}

void IntVectorVector::insert(IntVector const & x)
{
    char * ptr_ = new char[sizeof (IntVector)];
    IntVector * p_obj = new (ptr_) IntVector(x);
    this -> push(static_cast<const void *>(p_obj));
    delete []ptr_;
}


#ifdef LEO
int
main()
{
IntVector v;
v.insert(10);
v.insert(20);
IntVectorVector m;
m.insert(v);
m[0][0] = 30;
m.insert(IntVector());
m.insert(IntVector());
// 10 20
std::cout << v[0] << ' ' << v[1] << std::endl;
// 30 20
std::cout << m[0][0] << ' ' << m[0][1] << std::endl;
// 2 3 0
std::cout << v.size() << ' ' << m.size() << m[1].size() << std::endl;
        
}
#endif
