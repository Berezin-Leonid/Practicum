#include <iostream>


namespace equations {

class IntVariable {
public:
    ~IntVariable();
    IntVariable();

    int result()const;
    void set_result(int);

private:

    int res;
};

    //<<
std::ostream& operator<<(std::ostream & out, const IntVariable &obj)
{
    out << obj.result();
    return out;
}

//constructors IntVariable
IntVariable::IntVariable() {}
IntVariable::~IntVariable() {}

//metods IntVariable
int IntVariable::result() const { return res; }

void IntVariable::set_result(int x) { res = x; }

class Expression {
public:

    Expression();
    Expression(int);
    Expression(int,int);
    Expression(IntVariable &);
    Expression(const Expression &);

    bool failed()const;
    int ratio_1()const;
    int ratio_0()const;
    IntVariable* variable()const;
    
    void fail(bool);
    void revariable(IntVariable *);
private:

    int rat_1;
    int rat_0;
    bool err;
    IntVariable * var;
};


//constructors Expression

Expression::Expression()
{
    rat_1 = 0 ;
    rat_0 = 0;
    err = false;
    var = nullptr;
}

Expression::Expression(int rat_1_, int rat_0_)
{
    rat_1 = rat_1_ ;
    rat_0 = rat_0_ ;
    err = false;
    var = nullptr;
}

Expression::Expression(int num)
{
    rat_1 = 0;
    rat_0 = num;
    err = false;
    var = nullptr;
}

Expression::Expression(IntVariable & obj)
{
    rat_1 = 1;
    rat_0 = 0; 
    err = false;
    var = &obj;
}

Expression::Expression(const Expression & obj)
{
    rat_1 = obj.rat_1 ;
    rat_0 = obj.rat_0; 
    err = obj.err;
    var = obj.var;
}

//metods Expression

bool Expression::failed()const { return err; }
int Expression::ratio_1()const { return rat_1; }
int Expression::ratio_0()const { return rat_0; }
IntVariable* Expression::variable()const { return var; }

void Expression::fail(bool x) { err = x; }
void Expression::revariable(IntVariable * obj) { var = obj; }

//operations
    //+ 
Expression operator +(
        const Expression &  left,
        const Expression & right)
{
    Expression obj(left.ratio_1() + right.ratio_1(),
            left.ratio_0() + right.ratio_0());
    obj.fail(left.failed() || right.failed());
    
    if (left.variable() == nullptr) {
        obj.revariable(right.variable());

    } else if (right.variable() == nullptr) {
        obj.revariable(left.variable());

    } else if (right.variable() == left.variable()) {
        obj.revariable(left.variable());

    } else {
        obj.fail(true);

    }
    return obj;
}

    //-
Expression operator -(
        const Expression &  left,
        const Expression & right)
{
    Expression obj(left.ratio_1() - right.ratio_1(),
            left.ratio_0() - right.ratio_0());

    obj.fail(left.failed() || right.failed());
    
    if (left.variable() == nullptr) {
        obj.revariable(right.variable());

    } else if (right.variable() == nullptr) {
        obj.revariable(left.variable());

    } else if (right.variable() == left.variable()) {
        obj.revariable(left.variable());

    } else {
        obj.fail(true);

    }
    return obj;
}

Expression operator -(const Expression & obj)
{
    return 0 - obj;
}

    //*
Expression operator *(
        const Expression &  left,
        const Expression & right)
{
    int rat1, rat0;
    
    if (left.ratio_1() == 0) {
        rat1 = right.ratio_1() * left.ratio_0();
        rat0 = right.ratio_0() * left.ratio_0();
    } else {
        rat1 = left.ratio_1() * right.ratio_0();
        rat0 = left.ratio_0() * right.ratio_0();
    }

    Expression obj(rat1, rat0);

    obj.fail(left.failed() || right.failed());

    if (left.variable() == nullptr) {
        obj.revariable(right.variable());

    } else if (right.variable() == nullptr) {
        obj.revariable(left.variable());
    } else {
        obj.fail(true);
    }
    return obj;
}

class Equation {
public:
    Equation(const Expression &, const Expression &);
    Equation(bool);
    
    Expression left_expr()const;
    Expression right_expr()const;
    
private:
    Expression _left;
    Expression _right;
};

//constructors Equation
Equation::Equation(const Expression & left, const Expression & right)
{
    _left = left;
    _right = right;
}

Equation::Equation(bool x)
{
    _left = Expression();
    _right = Expression();
    _left.fail(true);

}

//metods Equation

Expression Equation::left_expr()const
{
    return _left;
}

Expression Equation::right_expr()const
{
    return _right;
}

Equation operator ==(
        const Expression& left,
        const Expression& right)
{
    Equation eq(left , right);
    return eq;
}
// operation end
int solve(const Equation & eq)
{
    Expression obj = eq.left_expr() - eq.right_expr();
    if ((obj.failed() == false)  && 
            (obj.ratio_1() != 0) && (obj.variable() != nullptr)) 
    {
        if (obj.ratio_0() % obj.ratio_1() == 0){
            obj.variable() -> set_result(-obj.ratio_0() / obj.ratio_1());
            return 0;
        }
    }
    return 1;
}

}

#ifdef LEO
int
main()
{
    equations::IntVariable x;
    equations::IntVariable y;

    equations::solve(-x - 2*4 == 3*x);
        std::cout << x << std::endl;

    equations::solve(-x - 2*4 == 0);
        std::cout << x << std::endl;

    if (equations::solve(0*x + x == 1) == 0) {
        std::cout << x << std::endl;

    } else {
        std::cerr << "No solution" << std::endl;
    }
//            4*x + 3*x + 4 == -5 + 2*x
//            100*x - 2*4 
//            101*x - 100*x == x 
//            101*x - 100*x == x
//            0*x*(x - x) == 1
//            x * x + x == x * x
//            y + x == y 
}
#endif
