#include <iostream>
#ifdef OMYGOD
class A {
    int i;
public:
    A(int x) : i(x) { puts("abba"); }
    virtual ~A() { puts("bear"); }
    int f() const { return i + g() + h(); }
    virtual int g() const { return i; }
    int h() const { return 18; }
};
class B : public A {
public:
    B() : A(50) { puts("central"); }
    ~B() { puts("diameter"); }
    int f() const { return g() - 2; }
    virtual int g() const { return 8; }
    int h() const { return 9; }
};

int main() {
    B b;
    A* p = &b;
    std::cout << "result = (" << p->f() << ';' << b.f() << ')' << std::endl;
    return 0;
}




int
main()
{
//A()
    puts("abba");
//B()
    puts("central");

    std::cout << "result = (" << 76/*p->f()*/ << ';' << 6/*b.f()*/ << ')' << std::endl;



//p -> f()
//A::f
    //return i + g() + h(); i = 50; in summ = 50 + 8 + 18 = 76;
//virtual g() 
    //return 8;
//h()
    //return 18;
//b.f()
//B::f
    //return g() - 2; 8 - 2 = 6;

//~B()

    puts("diameter");
    puts("bear");
//~A()
    return 0;
}

#endif

int
main()
{
/*
puts("abba");
puts("central");
puts("result = (76;6)");
puts("diameter");
puts("abba");
*/
    
puts("bear");
puts("diameter");
puts("result = (76;6)");
puts("central");
puts("abba");
    return 0;
}
