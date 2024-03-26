#include <iostream>
#include <cstring>

namespace equations
{

enum {
    SUM_PRT = 1,
    SUB_PRT = 1,
    MUL_PRT = 3,
    DIV_PRT = 3,
    NEG_PRT = 4,
    EL_PRT = 5
};

class Expression {
public:
    Expression() = default;
    virtual ~Expression() = default;
    Expression(int);
    virtual void print(std::ostream &)const = 0;
    virtual int priority()const = 0;
};

class IntVariable {
public:
    ~IntVariable();
    IntVariable(IntVariable const &);
    IntVariable(const char *);
    const char * perem()const;
    IntVariable & operator =(IntVariable);
    void swap(IntVariable &);
private:
    char *perem_name;
    
};
//class IntVariable
    //constructors
IntVariable::~IntVariable()
{
    delete []perem_name;
}

IntVariable::IntVariable(IntVariable const & obj)
{
    if (obj.perem() == nullptr) {
        perem_name = nullptr;
        return;
    }
    perem_name = new char[strlen(obj.perem()) + 1];
    strcpy(perem_name, obj.perem());
}

IntVariable::IntVariable(const char * str)
{
    perem_name = new char[strlen(str) + 1];
    strcpy(perem_name, str);
}

    //methods
void IntVariable::swap(IntVariable & obj)
{
    std::swap(obj.perem_name, perem_name);
}

IntVariable & IntVariable::operator =(IntVariable obj)
{
    swap(obj);
    return *this;
}

const char * IntVariable::perem()const
{
    return perem_name;
}
//end IntVariable



class VariableExpression: public Expression {
public:
    VariableExpression(IntVariable &);
    void print(std::ostream & out)const;
    virtual int priority()const;
private:
    const IntVariable * var;
};

VariableExpression::VariableExpression(IntVariable &v):
        var(&v)
{}

void VariableExpression::print(std::ostream & out)const
{
    out << var -> perem();
}

int VariableExpression::priority()const { return EL_PRT; }

class LiteralExpression: public Expression {
public:
    ~LiteralExpression() = default;
    LiteralExpression(int);
    void print(std::ostream & out)const;
    virtual int priority()const;
private:
    int num;
};

LiteralExpression::LiteralExpression(int x):
        num(x)
{}

void LiteralExpression::print(std::ostream & out)const
{
    out << num;
}

int LiteralExpression::priority()const { return EL_PRT; }


class UnaryExpression: public Expression {
public:
    ~UnaryExpression();
    UnaryExpression(const Expression *, char);
    void print(std::ostream &)const;
    virtual int priority()const = 0;
private:
    const Expression *middle;
    char sign;
};

//class UnaryExpression
    //constructors

UnaryExpression::~UnaryExpression()
{
    delete middle;
}

UnaryExpression::UnaryExpression(const Expression * middle_expr, char zn):
        sign(zn)
{
    middle = middle_expr;
}

    //methods

void UnaryExpression::print(std::ostream & out)const
{
    if (middle -> priority() < priority()) {
        out << sign;
        out << "(";
        middle -> print(out);
        out << ")";
    } else {
        out << sign;
        middle -> print(out);
    }
}
//end UnaryExpression


class NegativeExpression: public UnaryExpression {
public:
    NegativeExpression(const Expression *);
    virtual int priority()const;
private:
};

NegativeExpression::NegativeExpression(const Expression *middle_expr): 
        UnaryExpression(middle_expr, '-')
{}

int NegativeExpression::priority()const { return NEG_PRT; }


class BinaryExpression: public Expression {
public:
    ~BinaryExpression();
    BinaryExpression(const Expression *,const Expression *,char);
    void print(std::ostream &)const;
    virtual int priority()const = 0;
private:
    const Expression *left;
    const Expression *right;
    char sign;
};

//class BinaryExpression
    //constructors

BinaryExpression::~BinaryExpression()
{
    delete left;
    delete right;
}

BinaryExpression::BinaryExpression(const Expression * left_expr,
    const Expression * right_expr,char zn):
        sign(zn)
{
    left = left_expr;
    right = right_expr;
}

    //methods

void BinaryExpression::print(std::ostream & out)const
{
    if (left -> priority() < priority()) {
        out << "(";
        left -> print(out);
        out << ")";
    } else {
        left -> print(out);
    }

    out << " " << sign << " ";

    if (right -> priority() <= priority()) {
        out << "(";
        right -> print(out);
        out << ")";
    } else {
        right -> print(out);
    }
}
//end BinaryExpression


class SumExpression: public BinaryExpression {
public:
    SumExpression(const Expression *, const Expression *);
    virtual int priority()const;
private:
};

SumExpression::SumExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, '+')
{}

int SumExpression::priority()const { return SUM_PRT; }


class SubExpression: public BinaryExpression {
public:
    SubExpression(const Expression *, const Expression *);
    virtual int priority()const;
private:
};

SubExpression::SubExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, '-')
{}

int SubExpression::priority()const { return SUB_PRT; }


class MultiplyExpression: public BinaryExpression {
public:
    MultiplyExpression(const Expression *, const Expression *);
    virtual int priority()const;
private:
};


MultiplyExpression::MultiplyExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, '*')
{}

int MultiplyExpression::priority()const { return MUL_PRT; }


class DivisionExpression: public BinaryExpression {
public:
    DivisionExpression(const Expression *, const Expression *);
    virtual int priority()const;
private:
};

DivisionExpression::DivisionExpression(const Expression *left_expr,
    const Expression *right_expr): 
        BinaryExpression(left_expr, right_expr, '/')
{}

int DivisionExpression::priority()const
{
    return DIV_PRT;
}


class Printer {
public:
    Printer(Expression const &);
    const Expression * ptr_expression()const;
private:
    const Expression * expr;
};

Printer::Printer(Expression const & obj):
    expr(&obj)
{}

const Expression * Printer::ptr_expression()const { return expr; }

class PrettyPrinter {
public:
    Printer get_infix(Expression const &)const;
};

Printer PrettyPrinter::get_infix(Expression const & obj)const
{
    return Printer(obj);
}

std::ostream & operator <<(std::ostream & out, const Printer & obj)
{
    obj.ptr_expression() -> print(out);
    return out;
}

/*====================================================================*/

#ifdef LEO
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
#endif

}//end namespace equation

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

#ifdef LE
int
main()
{
    using namespace equations;
    IntVariable x("x"), y("y"), z("z");
    Expression const *expression = neg(expr(1));
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
