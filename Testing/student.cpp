#include <iostream>
#include <cstring>
#include "string.h"

class Student {
public:

    Student();
    Student(const char *, const char *, int);
    Student(Student const &);
    ~Student();

    const char * get_name()const;
    const char * get_surname()const;
    int get_grade()const;

    void set_name(const char *);
    void set_surname(const char *);
    void set_grade(int);
    
private:

    String name;
    String surname;
    int grade;
};

void Student::set_name(const char * obj)
{
    name = obj;
}

void Student::set_surname(const char * obj)
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

Student::Student(const char * obj1, const char * obj2, int x):
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

#ifdef LEO
int
main()
{

    Student obj("A","B", 18);
    Student obj2("C","D", 19);
    std::cout << obj2.get_name() << " " << obj2.get_surname() << " " << 
            obj2.get_grade() << std::endl;

    obj2 = obj = obj2;
    std::cout << obj2.get_name() << " " << obj2.get_surname() << " " << 
            obj2.get_grade() << std::endl;
    return 0;
}
#endif
