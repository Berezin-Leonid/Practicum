#include <iostream>
#include <cstring>
#include "string.h"

class Student {
public:

    Student();
    Student(String const &, String const &, int);
    Student(Student const &);
    ~Student();

    const char * get_name()const;
    const char * get_surname()const;
    int get_age()const;

    void set_name(String const &);
    void set_surname(String const &);
    void set_age(int);
    Student & operator =(Student const &);
    
private:

    String name;
    String surname;
    int age;
};

void Student::set_name(String const & obj)
{
    name = obj;
}

void Student::set_surname(String const & obj)
{
    name = obj;
}

void Student::set_age(int x)
{
    age = x;
}

const char * Student::get_name()const {return name.string();}

const char * Student::get_surname()const {return surname.string();}

int Student::get_age()const {return age;}


Student::Student():
        name(nullptr), surname(nullptr), age(0)
{}

Student::Student(String const & obj1, String const & obj2, int x):
        name(obj1), surname(obj2), age(x)
{}

Student::Student(Student const & obj): Student()
{
    name = obj.name;
    surname = obj.surname;
    age = obj.age;
}

Student::~Student()
{}


Student & Student::operator =(Student const & obj)
{
    name = obj.name;
    surname = obj.surname;
    age = obj.age;
    return *this;
}

#ifdef LEO
int
main()
{

    Student obj("A","B", 18);
    Student obj2("C","D", 19);
    std::cout << obj2.get_name() << " " << obj2.get_surname() << " " << 
            obj2.get_age() << std::endl;
    //obj2 = obj;
    obj2 = obj = obj2;
    std::cout << obj2.get_name() << " " << obj2.get_surname() << " " << 
            obj2.get_age() << std::endl;
    return 0;
}
#endif
