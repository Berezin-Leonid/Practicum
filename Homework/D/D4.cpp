#include <iostream>


class A {
public: 

    void set_color(int col);
    int get_color()const;

    friend std::ostream& operator<<(std::ostream & out, const A & obj);

private:
    int color;
};
//constructors A
//metods A
void A::set_color(int col)
{
    color = col;
}

int A::get_color()const
{
    return color;
}

class UniquePtr {
public:

    
    UniquePtr(A*);
    UniquePtr(UniquePtr &);
    ~UniquePtr();
    UniquePtr();

    const A * operator ->()const;
    A * operator ->();
    A& operator *();
    const A& operator *()const;
    UniquePtr& operator =(UniquePtr&);

private:
    A* adr;
};

//constructors UniquePtr
UniquePtr::UniquePtr(A* p) 
{
    adr = p;
}

UniquePtr::UniquePtr(UniquePtr &obj)
{
    adr = obj.adr;
    obj.adr = nullptr;
}


UniquePtr::~UniquePtr()
{
    if (adr != nullptr) {
        delete adr;
    }
}

UniquePtr::UniquePtr()
{
    adr = nullptr;
}

//metods UniquePtr
const A * UniquePtr::operator ->()const
{
    return adr;
}

A * UniquePtr::operator ->()
{
    return adr;
}

A& UniquePtr::operator *()
{
    return *adr;
}

const A& UniquePtr::operator *()const
{
    return *adr;
}

UniquePtr& UniquePtr::operator =(UniquePtr& obj)
{
    if (&obj == this) {
        return *this;
    }

    delete adr;
    adr = obj.adr; 
    obj.adr = nullptr;

    return *this;
}
//functions

std::ostream& operator<<(std::ostream & out, const A & obj)
{
    out << "color = " << obj.color;
    return out;
}

#ifdef LEO
int main()
{
    UniquePtr p = new A; // get ownership
    p->set_color(42);
    std::cout << *p << std::endl; // color = 42
    UniquePtr const& q = p; // ownership is not moved
    p->set_color(111);
    std::cout << q->get_color() << std::endl; // 111
    std::cout << *q << std::endl; // color = 111
    UniquePtr s = new A;
    s->set_color(31);
    std::cout << (*s).get_color() << std::endl; // 31
    s = p; // ownership is moved
    std::cout << s->get_color() << std::endl; // 111
    UniquePtr t = s; // ownership is moved
    t = t = t;
    std::cout << t->get_color() << std::endl; // 111
} // no memory leaks
#endif
