
#include <iostream>
#include <cstring>

namespace equations
{

class NodeExpression;
class IntVariable;
NodeExpression *expr(IntVariable &v);
NodeExpression *expr(int v);
NodeExpression *plus(NodeExpression *left, NodeExpression *right);

enum {
    SUM_PRT = 1,
    SUB_PRT = 1,
    MUL_PRT = 3,
    DIV_PRT = 3,
    NEG_PRT = 4,
    EL_PRT = 5
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

class NodeExpression {
public:
    virtual ~NodeExpression() = default;
    virtual void print(std::ostream &)const = 0;
    virtual int priority()const = 0;
    virtual NodeExpression * clone()const = 0;
};

class LiteralExpression: public NodeExpression {
public:
    LiteralExpression(int);
    void print(std::ostream & out)const;
    virtual int priority()const;
    virtual NodeExpression * clone()const;
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

NodeExpression * LiteralExpression::clone()const
{
    return new LiteralExpression(num);
}

class VariableExpression: public NodeExpression {
public:

    VariableExpression(IntVariable &);
    void print(std::ostream & out)const;
    virtual int priority()const;
    virtual NodeExpression * clone()const;

private:

    IntVariable * var;
};

VariableExpression::VariableExpression(IntVariable &v):
        var(&v)
{}

void VariableExpression::print(std::ostream & out)const
{
    out << var -> perem();
}


int VariableExpression::priority()const { return EL_PRT; }

NodeExpression * VariableExpression::clone()const
{
    return new VariableExpression(*var);
}


class Expression {
public:

    Expression(int);
    Expression(NodeExpression *);
    Expression(IntVariable &);
    Expression(Expression const &);
    Expression & operator =(Expression);
    ~Expression();

    const NodeExpression * get_node()const;
private:
    NodeExpression * node;
};

Expression::Expression(int x):
        node(new LiteralExpression(x))
{}

Expression::Expression(NodeExpression * obj):
    node(obj)
{}

Expression::Expression(IntVariable &x):
        node(new VariableExpression(x))
{}

Expression::Expression(Expression const &obj):
    node(obj.node -> clone())
{}

Expression::~Expression()
{
    delete node;
}


Expression & Expression::operator =(Expression obj)
{
    std::swap(obj.node, this -> node);    
    return *this;
}

const NodeExpression* Expression::get_node()const
{
    return node;
}

class UnaryExpression: public NodeExpression {
public:
    ~UnaryExpression();
    UnaryExpression(const NodeExpression *,char);
    void print(std::ostream &)const;
    const NodeExpression * get_middle()const;
    virtual int priority()const = 0;
    virtual NodeExpression * clone()const = 0;
private:
    const NodeExpression *middle;
    char sign;
};

UnaryExpression::~UnaryExpression()
{
    delete middle;
}

UnaryExpression::UnaryExpression(const NodeExpression * middle_expr, char zn):
        middle(middle_expr)
{
    sign = zn;
}

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

const NodeExpression * UnaryExpression::get_middle()const { return middle; }

class NegativeExpression: public UnaryExpression {
public:
    NegativeExpression(const NodeExpression *);
    int priority()const;
    NodeExpression * clone()const;
};

NegativeExpression::NegativeExpression(const NodeExpression *middle_expr): 
        UnaryExpression(middle_expr, '-')
{}

int NegativeExpression::priority()const { return NEG_PRT; }

NodeExpression * NegativeExpression::clone()const
{
    return new NegativeExpression(this -> get_middle() -> clone());
}

class BinaryExpression: public NodeExpression {
public:
    ~BinaryExpression();
    BinaryExpression(const NodeExpression *,const NodeExpression *,char);
    void print(std::ostream &)const;
    const NodeExpression * get_left()const;
    const NodeExpression * get_right()const;
    virtual int priority()const = 0;
    virtual NodeExpression * clone()const = 0;
private:
    const NodeExpression *left;
    const NodeExpression *right;
    char sign;
};

BinaryExpression::~BinaryExpression()
{
    delete left;
    delete right;
}

BinaryExpression::BinaryExpression(const NodeExpression * left_expr,
    const NodeExpression * right_expr, char zn):
        left(left_expr), right(right_expr)
{
    sign = zn;
}

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

const NodeExpression * BinaryExpression::get_left()const { return left; }

const NodeExpression * BinaryExpression::get_right()const { return right; }

class SumExpression: public BinaryExpression {
public:
    SumExpression(const NodeExpression *, const NodeExpression *);
    int priority()const;
    NodeExpression * clone()const;
};

SumExpression::SumExpression(const NodeExpression *left_expr,
    const NodeExpression *right_expr): 
        BinaryExpression(left_expr, right_expr, '+')
{}

int SumExpression::priority()const { return SUM_PRT; }

NodeExpression * SumExpression::clone()const
{
    return new SumExpression(this -> get_left() -> clone(),
                            this -> get_right() -> clone());
}

class SubExpression: public BinaryExpression {
public:
    SubExpression(const NodeExpression *, const NodeExpression *);
    int priority()const;
    NodeExpression * clone()const;
};

SubExpression::SubExpression(const NodeExpression *left_expr,
    const NodeExpression *right_expr): 
        BinaryExpression(left_expr, right_expr, '-')
{}

int SubExpression::priority()const { return SUB_PRT; }

NodeExpression * SubExpression::clone()const
{
    return new SubExpression(this -> get_left() -> clone(),
                            this -> get_right() -> clone());
}

class MultiplyExpression: public BinaryExpression {
public:
    MultiplyExpression(const NodeExpression *, const NodeExpression *);
    int priority()const;
    NodeExpression * clone()const;
};

MultiplyExpression::MultiplyExpression(const NodeExpression *left_expr,
    const NodeExpression *right_expr): 
        BinaryExpression(left_expr, right_expr, '*')
{}

int MultiplyExpression::priority()const { return MUL_PRT; }

NodeExpression * MultiplyExpression::clone()const
{
    return new MultiplyExpression(this -> get_left() -> clone(),
                            this -> get_right() -> clone());
}

class DivisionExpression: public BinaryExpression {
public:
    DivisionExpression(const NodeExpression *, const NodeExpression *);
    int priority()const;
    NodeExpression * clone()const;
};

DivisionExpression::DivisionExpression(const NodeExpression *left_expr,
    const NodeExpression *right_expr): 
        BinaryExpression(left_expr, right_expr, '/')
{}

int DivisionExpression::priority()const { return DIV_PRT; }

NodeExpression * DivisionExpression::clone()const
{
    return new DivisionExpression(this -> get_left() -> clone(),
                            this -> get_right() -> clone());
}

class Printer {
public:
    Printer(const NodeExpression *);
    const NodeExpression * ptr_expression()const;
private:
    const NodeExpression * expr;
};

Printer::Printer(const NodeExpression * obj):
    expr(obj)
{}

const NodeExpression * Printer::ptr_expression()const
{
    return expr;
}

class PrettyPrinter {
public:
    Printer get_infix(Expression const &)const;
private:
};

Printer PrettyPrinter::get_infix(Expression const & obj)const
{
    return Printer(obj.get_node());
}

std::ostream & operator <<(std::ostream & out, const Printer & obj)
{
    obj.ptr_expression() -> print(out);
    return out;
}

Expression operator +(Expression const & left, Expression const & right)
{
    return new SumExpression(left.get_node() -> clone(),
                right.get_node() -> clone());
}

Expression operator -(Expression const & left, Expression const & right)
{
    return new SubExpression(left.get_node() -> clone(),
                right.get_node() -> clone());
}

Expression operator *(Expression const & left, Expression const & right)
{
    return new MultiplyExpression(left.get_node() -> clone(),
                right.get_node() -> clone());
}

Expression operator /(Expression const & left, Expression const & right)
{
    return new DivisionExpression(left.get_node() -> clone(),
                right.get_node() -> clone());
}

Expression operator -(Expression const & middle)
{
    return new NegativeExpression(middle.get_node() -> clone());
}


}//end namespace equation

#ifdef LEO
int
main()
{
    using namespace equations;
    IntVariable x("x");
    Expression expr1 = x + (x + x) ;
    Expression expr2 = expr1 - expr1;
    Expression expr3 = expr1 * expr2;
    Expression expr4 = expr1 / expr2;
    Expression expr5 = -expr4;
    PrettyPrinter printer;
    std::cout<< printer.get_infix(-expr1) << std::endl;
    //std::cout<< printer.get_infix(expr2) << std::endl;
    //std::cout<< printer.get_infix(expr3) << std::endl;
    //std::cout<< printer.get_infix(expr4) << std::endl;

    
}
#endif
