#include <iostream>

class A {
public:
    A();
    ~A();
    A(A const &, int size = -1);
    int _size;
};


A::~A() {
}

A::A() {
}

A::A(A const & obj, int size) {
    if (size >= 0 && size >= obj._size) {
        _size = size;
    } else {
        _size = obj._size;
    }
}


int
main()
{
    A a;
    a._size = 4;

    A b = a;
    std::cout << b._size << std::endl;
    return 0;
};
