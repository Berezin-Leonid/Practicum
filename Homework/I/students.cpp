class Department
{
};

// information card about student
class Student
{
public:
    enum { MAX_GRADE = 100 };

    Student(std::string name_); // no necessary copy of std::string

    std::string const & name() const;
    int grade() const; // throws when grade was not set
    Department &department() const; // throw when department was not set

    void set_grade(int);
    void set_department(Department *);

// TODO disable copying in user code

// TODO complete the class
};

struct Application
{
    Student *student;
    std::vector<Department *> order; // may be empty

// TODO disable copying in user code
};

namespace no_algorithm
{
// students with MAX_GRADE and non empty order
//  are assigned to the department from the first item of its order
void
assign_with_max_grade(std::vector<Application *> & applications)
{
    // TODO just plain loops, no additional functions
}
}

namespace with_algorithm
{

// it is possible to add code here

// students with MAX_GRADE and non empty order
//  are assigned to the department from the first item of its order
void
assign_with_max_grade(std::vector<Application *> & applications)
{
    // TODO no loops, no recursion
}
}

// main() should be removed/commented
