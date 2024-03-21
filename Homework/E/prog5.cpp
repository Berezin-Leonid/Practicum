#include <iostream>

#ifdef LEO
class A {
public: void g(int);
private: void h();
};

class B: A {
public: void f() { /*1*/ h(); }
protected: void f(char x) { /*2*/ f(-x); }
private: void f(int);
         void h(int);
};

class C: public B {
public:    void h(double);
protected: void t() { /*3*/ f('0'); }
           void h() { /*4*/ f(3); }
};

int main() {
    B b;
    /*5*/ b.f();
    /*6*/ b.g(2);
    C c;
    /*7*/ c.f(1);
    /*8*/ c.h();
    /*9*/ c.f();
    /*10*/ c.h(1);
    B *p = &c;
    /*11*/ p->h(.0);
}
#endif

int
main()
{
    std::cout << "1 0" << std::endl;
    std::cout << "2 B" << std::endl;
    std::cout << "3 B" << std::endl;
    std::cout << "4 " << std::endl;
    std::cout << "5 " << std::endl;

    std::cout << "6 " << std::endl;
    std::cout << "7 " << std::endl;
    std::cout << "8 " << std::endl;
    std::cout << "9 " << std::endl;
    std::cout << "10C" << std::endl;
    std::cout << "110" << std::endl;

}

