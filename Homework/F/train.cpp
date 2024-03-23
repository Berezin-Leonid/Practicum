#include <iostream>

//priority of perem
//
//  + 1
//  - 1
//  * 2
//  / 3
//  -() 4

enum {
    SUM_PRT = 1,
    SUB_PRT = 1,
    MUL_PRT = 2,
    DIV_PRT = 3,
    NEG_PRT = 4,
    EL_PRT = 5
};


class Expression {
public:
    Expression(int);
    virtual void print()const = 0;
    int priority()const;
private:
    int prior;
};

//class Expression
    //constructors

Expression::Expression(int pr):
    prior(pr)
{}

    //methods

int Expression::priority()const
{
    return prior;
}
//end Expression



class IntVariable {
public:
    //~IntVariable();
    IntVariable(const char *);
    const char * perem()const;
private:
    const char *perem_name;
    
};
//class IntVariable
    //constructors
IntVariable::IntVariable(const char * str):
        perem_name(str)
{}
    //methods
const char * IntVariable::perem()const
{
    return perem_name;
}
//end IntVariable



class VariableExpression: public Expression {
public:
    //~VariableExpression();
    VariableExpression(IntVariable &);
    void print()const;
private:
    const IntVariable * var;
};
//class VariableExpression
    //constructors
VariableExpression::VariableExpression(IntVariable &v):
        Expression(EL_PRT)
{
    var = &v;
}
    //methods
void VariableExpression::print()const
{
    std::cout << var -> perem();
}
//end VariableExpression

class LiteralExpression: public Expression {
public:
    //~LiteralExpression();
    LiteralExpression(int);
    void print()const;
private:
    int num;
};
//class LiteralExpression
    //constructors
LiteralExpression::LiteralExpression(int x):
        Expression(EL_PRT)
{
    num = x;
}
    //methods
void LiteralExpression::print()const
{
    std::cout << num;
}
//end LiteralExpression



class UnaryExpression: public Expression {
public:
    //~UnaryExpression();
    UnaryExpression(const Expression *, const char *, int);
    void print()const;
private:
    const Expression *middle;
    const char *sign;
};

//class UnaryExpression
    //constructors

UnaryExpression::UnaryExpression(const Expression * middle_expr,
    const char *zn, int priority):
        Expression(priority), sign(zn), middle(middle_expr)
{}

    //methods

void UnaryExpression::print()const
{
    if (middle -> priority() < priority()) {
        std::cout << "(";
        std::cout << sign;
        middle -> print();
        std::cout << ")";
    } else {
        std::cout << sign;
        middle -> print();
    }
}
//end UnaryExpression


class NegativeExpression: public UnaryExpression {
public:
    //~NegativeExpression();
    NegativeExpression(const Expression *);
private:
};

//class SumExpression

    //constructors
NegativeExpression::NegativeExpression(const Expression *middle_expr): 
        UnaryExpression(middle_expr, "-", NEG_PRT)
{}

    //methods
//end SumExpression



class BinaryExpression: public Expression {
public:
    //~BinaryExpression();
    BinaryExpression(const Expression *,const Expression *, const char *, int);
    void print()const;
private:
    const Expression *left;
    const Expression *right;
    const char *sign;
};

//class BinaryExpression
    //constructors

BinaryExpression::BinaryExpression(const Expression * left_expr,
    const Expression * right_expr, const char *zn, int priority):
        Expression(priority), sign(zn)
{
    left = left_expr;
    right = right_expr;
}

    //methods

void BinaryExpression::print()const
{
    if (left -> priority() < priority()) {
        std::cout << "(";
        left -> print();
        std::cout << ")";
    } else {
        left -> print();
    }

    std::cout << " " << sign << " ";

    if (right -> priority() <= priority()) {
        std::cout << "(";
        right -> print();
        std::cout << ")";
    } else {
        right -> print();
    }
}
//end BinaryExpression


class SumExpression: public BinaryExpression {
public:
    //~SumExpression();
    SumExpression(const Expression *, const Expression *);
private:
};

//class SumExpression

    //constructors
SumExpression::SumExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, "+", SUM_PRT)
{}

    //methods
//end SumExpression



class SubExpression: public BinaryExpression {
public:
    //~SubExpression();
    SubExpression(const Expression *, const Expression *);
private:
};

//class SubExpression

    //constructors
SubExpression::SubExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, "-", SUB_PRT)
{}

    //methods
//end SubExpression


class MultiplyExpression: public BinaryExpression {
public:
    //~MultiplyExpression();
    MultiplyExpression(const Expression *, const Expression *);
private:
};

//class MultiplyExpression

    //constructors
MultiplyExpression::MultiplyExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, "*", MUL_PRT)
{}

    //methods
//end MultiplyExpression



class DivisionExpression: public BinaryExpression {
public:
    //~DivisionExpression();
    DivisionExpression(const Expression *, const Expression *);
private:
};

//class DivisionExpression

    //constructors
DivisionExpression::DivisionExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, "/", DIV_PRT)
{}

    //methods
//end DivisionExpression




class Printer {
public:
    Printer(Expression const &);
    const Expression * ptr_expression()const;
private:
    const Expression * expr;
};

//class Printer
    //constructors
Printer::Printer(Expression const & obj):
    expr(&obj)
{}
    //methods
const Expression * Printer::ptr_expression()const
{
    return expr;
}
//end Printer

class PrettyPrinter {
public:
    Printer get_infix(Expression const &);
private:
};

//class PrettyPrinter
    //constructors
    //methods
Printer PrettyPrinter::get_infix(Expression const & obj)
{
    return Printer(obj);
}
//end PrettyPrinter

std::ostream & operator <<(std::ostream & out, const Printer & obj)
{
    obj.ptr_expression() -> print();
    return out;
}

namespace equations
{
Expression *expr(IntVariable &v)
{
    return new VariableExpression(v);
}

Expression *expr(int v)
{
    return new LiteralExpression(v);
}

Expression *plus(Expression *left, Expression *right)
{
    return new SumExpression(left, right);
}

Expression *minus(Expression *left, Expression *right)
{
    return new SubExpression(left, right);
}

Expression *mult(Expression *left, Expression *right)
{
    return new MultiplyExpression(left, right);
}

Expression *div(Expression *left, Expression *right)
{
    return new DivisionExpression(left, right);
}

Expression *neg(Expression *operand)
{
    return new NegativeExpression(operand);
}

}

#ifdef LE
int
main()
{
    using namespace equations;
    IntVariable x("x"), y("y"), z("z");
    Expression const * expression = 
        plus(
            plus(expr(y), expr(z)),
            expr(x));

    PrettyPrinter printer;

    std::cout << printer.get_infix(*expression) << std::endl;
    delete expression;

    return 0;
}
#endif

#ifdef LEO
int
main()
{
    using namespace equations;
    IntVariable x("x"), y("y"), z("z");
    Expression const *expression = neg(expr(1));
    return 0;
}
#endif

#ifdef LE
int
main()
{
    using namespace equations;
    IntVariable x("x"), y("y"), z("z");
    Expression const * expression =
        plus(
            minus(
                neg(expr(x)), 
                mult(
                    plus(
                        plus(expr(x), expr(x)),
                        plus(expr(-1), expr(y))),
                    expr(x))), 
             minus(expr(2), neg(expr(z))));
    PrettyPrinter printer;
    // -x - (x + x + (-1 + y)) * x + (2 - -z)
    std::cout << printer.get_infix(*expression) << std::endl;
    // using associativity:
    // ((x + y) + z) -> x + y + z
    // ((x + y) - z) -> x + y - z
    // (x + (y + z)) -> x + (y + z)
    // using precedence:
    // ((x * y) + z) -> x * y + z
    // (x * (y + z)) -> x * (y + z)
    delete expression;

    return 0;
}
#endif
