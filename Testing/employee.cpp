#include <iostream>
#include <cstring>
#include "string.h"



class Employee{
public:

    Employee(int, String const &);
    int id()const;
    const char * name()const;
    
private:
    int _id;
    String _name;
    
};

class ContractedEmployee: public Employee {
public:

    ContractedEmployee(int, String const &,
            int, int, String const &);
    int end_date()const;
    int salary()const;
    const char * recruitment()const;
private:

    int date;
    int sal;
    String recr;

};

//class Employee

    //constructors
Employee::Employee(int x, String const & obj):
        _id(x), _name(obj)
{}

    //methods

int Employee::id()const { return _id; }

const char * Employee::name()const { return _name.string(); }

//class ContractedEmployee

    //constructors
ContractedEmployee::ContractedEmployee(int x, String const & obj,
        int _date, int _sal, String const & obj2):
        Employee(x, obj)
{
    date = _date;
    sal = _sal;
    recr = obj2;
}

    //methods

int ContractedEmployee::end_date()const
{
    return date;
}

int ContractedEmployee::salary()const
{
    return sal;
}

const char * ContractedEmployee::recruitment()const
{
    return recr.string();
}

#ifdef LEO
int
main()
{
/*
    Employee obj(28, "Evgen");
    Employee obj2 = obj;
    obj2 = Employee(23, "Berezin");
    obj2 = obj2;
    std::cout << obj2.name();
*/
    ContractedEmployee obj(28, "Evgen", 1 ,2,  "GG");
    ContractedEmployee obj2 = obj;
    obj2 = ContractedEmployee(23, "Berezin", 3, 4, "VP");
    obj2 = obj2;
    std::cout << obj2.name();
    return 0;
}

#endif
