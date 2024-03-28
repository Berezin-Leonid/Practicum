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
    int get_grade()const;

    void set_name(String const &);
    void set_surname(String const &);
    void set_grade(int);
    Student & operator =(Student);
    
private:

    String name;
    String surname;
    int grade;
};

void Student::set_name(String const & obj)
{
    name = obj;
}

void Student::set_surname(String const & obj)
{
    surname = obj;
}

void Student::set_grade(int x)
{
    grade = x;
}

const char * Student::get_name()const {return name.string();}

const char * Student::get_surname()const {return surname.string();}

int Student::get_grade()const {return grade;}


Student::Student():
        name(nullptr), surname(nullptr), grade(0)
{}

Student::Student(String const & obj1, String const & obj2, int x):
        name(obj1), surname(obj2), grade(x)
{}

Student::Student(Student const & obj)
{
    name = obj.name;
    surname = obj.surname;
    grade = obj.grade;
}

Student::~Student()
{}


Student & Student::operator =(Student obj)
{
    std::swap(name, obj.name);
    std::swap(surname, obj.surname);
    std::swap(grade, obj.grade);
    return *this;
}

#ifdef LEO
int
main()
{

    Student obj("A","B", 18);
    Student obj2("C","D", 19);
    std::cout << obj2.get_name() << " " << obj2.get_surname() << " " << 
            obj2.get_grade() << std::endl;
    //obj2 = obj;
    obj2 = obj = obj2;
    std::cout << obj2.get_name() << " " << obj2.get_surname() << " " << 
            obj2.get_grade() << std::endl;
    return 0;
}
#endif
