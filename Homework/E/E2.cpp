#include <iostream>
#include <cstring>


enum{
    BEGIN_CAP = 1
};

class Person {
public:
    Person(const char *, int, bool);
    ~Person();
    const char * name()const;
    int age()const;
    bool man()const;
private:
    const char * name_;
    int age_;
    bool man_;
};

class PersonView {
public:

    PersonView(Person *, int);
    class Iterator;
protected:
    int index;
    Person * array;
    int size;
private:
};


class MenPersonView : public PersonView {
public:

    MenPersonView(Person * _array, int _size);
    MenPersonView::Iterator begin() const;
    PersonView::Iterator end() const;

private:
};

class YoungPersonView : public PersonView {
public:

    YoungPersonView(Person * _array, int _size);
    YoungPersonView::Iterator begin() const;
    PersonView::Iterator end() const;

private:
};

bool MenCondition(Person const & obj)
{
    return obj.man();
}

bool YoungCondition(Person const & obj)
{
    return ((18 <= obj.age()) && (obj.age() <= 35));
}

class Persons {
public:

    const Person & give(int)const;
    Persons();
    ~Persons();
    MenPersonView men()const;
    YoungPersonView young()const;
    void add(Person const &);
private:
    Person * list;
    int capacity;
    int size;
};

class PersonView::Iterator {
    public:
        Iterator();
        Iterator(bool (*)(Person const &), const Person *, int, int);
        Iterator(Iterator const & obj);

        const Person & give(int)const;
        int search(int);
        bool operator ==(Iterator const &);
        bool operator !=(Iterator const &);
        Iterator & operator ++();
        Iterator operator ++(int);
        const Person * operator ->()const;
        
    protected:
        
        bool (*condition)(Person const &);
        int index;
        const Person * mas;
        int size;
};

//class PersonView

    //constructors
PersonView::PersonView(Person * mas, int _size)
{
    array = mas;
    size = _size;
}
    //methods

//class PersonView::Iterator;
    //constructors 
PersonView::Iterator::Iterator():
        condition(nullptr)
{
    index = -1;
    mas = nullptr;
    size = 0;
}

PersonView::Iterator::Iterator(bool (*cond)(Person const &),
            const Person * array, int _size, int ind = -1):
        condition(cond)
{
    index = ind;
    mas = array;
    size = _size ;
}

PersonView::Iterator::Iterator(PersonView::Iterator const & obj):
        condition(obj.condition)
{
    index = obj.index;
    mas = obj.mas;
    size = obj.size;
}

    //methods

const Person & PersonView::Iterator::give(int i)const
{
    return mas[i];
}
const Person * PersonView::Iterator::operator ->()const 
{
    return &mas[index];
}

int PersonView::Iterator::search(int x) {
    if (mas == nullptr) {
        std::cout << "nullptr in Iterator" << std::endl; 
        exit(0);
    }

    int i;
    for (i = x; i < size; ++i) {
        if(condition(mas[i])) {
            break;
        }
    }

    if (i == size) {
        return -1;
    }
    return i;
}

bool PersonView::Iterator::operator ==(Iterator const & right)
{
    return this -> index == right.index;
}

bool PersonView::Iterator::operator !=(Iterator const & right)
{
    return !(*this == right);
}

PersonView::Iterator & PersonView::Iterator::operator++()
{
    ++index;
    index = search(index);
    return *this;
}

PersonView::Iterator PersonView::Iterator::operator++(int)
{
    Iterator obj = *this;
    ++(*this);
    return obj;
}

/*
PersonView::Iterator & PersonView::Iterator::operator =(Iterator const & right)
{
    index = right.index;
    mas = right.mas;
    return *this;
}
*/



//class Persons
    //constructors

Persons::Persons()
{
    capacity = 0;
    size = 0;
    list = nullptr;
}

Persons::~Persons()
{
    operator delete [](list);
}

    //methods
const Person & Persons::give(int i)const
{
    return list[i];
}
void Persons::add(Person const & obj)
{
    if (size == capacity) {
        Person * ptr2 =static_cast<Person *> 
                (operator new[]((capacity * 2 + BEGIN_CAP) * sizeof(Person)));

        if (list != nullptr) {
            std::memcpy( static_cast<void *>(ptr2), static_cast<void *>(list),
                    capacity * sizeof(Person));
        }
        operator delete [](list);
        list = static_cast<Person *>(static_cast<void *>(ptr2)); 
        capacity = (capacity * 2 + BEGIN_CAP);
    }
    
    list[size++] = obj;
}

MenPersonView Persons::men()const
{
    MenPersonView obj(list, size);
    return obj;
} 

YoungPersonView Persons::young()const
{
    YoungPersonView obj(list, size);
    return obj;
} 


//class MenPersonView
    //constructors
MenPersonView::MenPersonView(Person * _array, int _size): 
        PersonView(_array, _size)
{}
    //methods

MenPersonView::Iterator MenPersonView::begin()const 
{
    MenPersonView::Iterator obj(MenCondition, array, size);
    ++obj;
    return obj;
}

MenPersonView::Iterator MenPersonView::end()const  
{
/*
    int i;
    for (i = size - 1;  i > 0; --i) {
        if (MenCondition(array[i])) {
            break;
        }
    }

    MenPersonView::Iterator obj(MenCondition, array, size, i);

    return obj;
*/
    MenPersonView::Iterator obj(MenCondition, array, size, -1);

    return obj;
}

//class YoungPersonView
    //constructors
YoungPersonView::YoungPersonView(Person * _array, int _size): 
        PersonView(_array, _size)
{}
    //methods

YoungPersonView::Iterator YoungPersonView::begin()const 
{
    YoungPersonView::Iterator obj(YoungCondition, array, size);
    ++obj;
    return obj;
}

YoungPersonView::Iterator YoungPersonView::end()const  
{
/*
    int i;
    for (i = size - 1;  i > 0; --i) {
        if (MenCondition(array[i])) {
            break;
        }
    }

    MenPersonView::Iterator obj(MenCondition, array, size, i);

    return obj;
*/
    YoungPersonView::Iterator obj(YoungCondition, array, size, -1);

    return obj;
}

//class Person
    //constructors

Person::Person(const char * nam, int ag, bool ma)
{
    
    name_ = nam; 
    age_ = ag;
    man_ = ma;
}

Person::~Person()
{}

    //methods
const char * Person::name()const
{
    return name_;
}

int Person::age()const
{
    return age_;
}

bool Person::man()const
{
    return man_;
}

#ifdef LEO
int
main()
{
    Persons org;
    org.add(Person("Ivanov", 20, true));
    org.add(Person("Ivanova", 30, false));
    org.add(Person("Petrov", 50, true));
    org.add(Person("Sidorov", 32, true));

    std::cout << "Men:" << std::endl;
    MenPersonView men = org.men();
    for (MenPersonView::Iterator it = men.begin(); it != men.end(); ++it) {
        std::cout << it->name() << std::endl;
    }
    std::cout << "Young:" << std::endl;
    YoungPersonView young = org.young();
    for (YoungPersonView::Iterator it = young.begin(); it != young.end(); ++it) {
        std::cout << it->name() << std::endl;
    }
    return 0;
}
#endif

#ifdef LEO2
int
main()
{
    Persons org;
    org.add(Person("Ivanov" ,20 , true));
    org.add(Person("Ivanova" ,30 , false));
    org.add(Person("Petrov" ,20 , true));
    org.add(Person("Ivanova1" ,30 , false));
    org.add(Person("Ivanova2" ,30 , false));
    org.add(Person("Ivanova3" ,30 , false));
    org.add(Person("Ivanova4" ,30 , false));
    org.add(Person("KORNYHYN" ,30 , true));
    org.add(Person("Ivanova5" ,30 , false));

    //std::cout << org.give(0).name() << std::endl;
    //std::cout << org.give(1).name() << std::endl;
    MenPersonView men = org.men();
    MenPersonView::Iterator it = men.begin();
    //std::cout << it.give(0).name() << std::endl;

    std::cout << "iterator : " << it -> name() << std::endl;
/*
    ++it;
*/
    std::cout << "iterator : " << men.end() -> name() << std::endl;
    return 0;
}

#endif
