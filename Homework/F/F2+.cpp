
#include <iostream>
#include <cstring>

//priority of perem
//
//  + 1
//  - 1
//  * 2
//  / 3
//  -() 4
//  element 5


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


class NodeExpression {
public:
    NodeExpression();
    virtual ~NodeExpression();
    virtual void print(std::ostream &)const = 0;
    virtual int priority()const = 0;
    virtual NodeExpression * clone()const = 0;
};

NodeExpression::NodeExpression()
{
}

//class NodeExpression
    //constructors

NodeExpression::~NodeExpression()
{}
    //methods
//end NodeExpression


class Expression {
public:

    Expression(int);
    Expression(IntVariable &);
    Expression(Expression const &);
    Expression & operator =(Expression);
    ~Expression();

    NodeExpression * get_node();
private:
    NodeExpression * node;
};

//class Expression
    //constructors
Expression::Expression(int x):
        node(new LiteralExpression(x))
{}

Expression::Expression(IntVariable &x)
        node(new VariableExpression(x))
{}

Expression::Expression(Expression const &obj):
    node(obj.node -> clone())
{}

Expression::~Expression()
{
    delete node;
}

    //methods

Expression & Expression::operator =(Expression obj)
{
    std::swap(obj.node, this -> node);    
    return *this;
}

NodeExpression::NodeExpression * get_node()
{
    return node;
}
//end Expression

class VariableExpression: public NodeExpression {
public:

    ~VariableExpression();
    VariableExpression(IntVariable &);
    void print(std::ostream & out)const;
    virtual int priority()const;
    virtual NodeExpression * clone()const;

private:

    IntVariable * var;
};
//class VariableExpression
    //constructors
VariableExpression::~VariableExpression()
{}

VariableExpression::VariableExpression(IntVariable &v)
{
    var = &v;
}
    //methods
void VariableExpression::print(std::ostream & out)const
{
    out << var -> perem();
}


int VariableExpression::priority()const
{
    return EL_PRT;
}

NodeExpression * VariableExpression::clone()const
{
    return new VariableExpression(*var);
}

//end VariableExpression

class LiteralExpression: public NodeExpression {
public:
    LiteralExpression(int);
    ~LiteralExpression();
    void print(std::ostream & out)const;
    virtual int priority()const;
    virtual NodeExpression * clone()const;
private:
    int num;
};
//class LiteralExpression
    //constructors
LiteralExpression::~LiteralExpression()
{}

LiteralExpression::LiteralExpression(int x)
{
    num = x;
}
    //methods
void LiteralExpression::print(std::ostream & out)const
{
    out << num;
}

int LiteralExpression::priority()const
{
    return EL_PRT;
}

NodeExpression * LiteralExpression::clone()const
{
    return new LiteralExpression(num);
}
//end LiteralExpression


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

//class BinaryExpression
    //constructors

BinaryExpression::~BinaryExpression()
{
    delete left;
    delete right;
}

BinaryExpression::BinaryExpression(const NodeExpression * left_expr,
    const NodeExpression * right_expr,char zn):
        sign(zn), left(left_expr), right(right_expr)
{}

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

const NodeExpression * BinaryExpression::get_left()const
{
    return left;
}

const NodeExpression * BinaryExpression::get_right()const
{
    return right;
}

//end BinaryExpression


class SumExpression: public BinaryExpression {
public:
    ~SumExpression();
    SumExpression(const NodeExpression *, const NodeExpression *);
    int priority()const;
    NodeExpression * clone()const;
private:
};

//class SumExpression

    //constructors
SumExpression::~SumExpression()
{}

SumExpression::SumExpression(const NodeExpression *left_expr,
    const NodeExpression *right_expr): 
        BinaryExpression(left_expr, right_expr, '+')
{}

    //methods
int SumExpression::priority()const
{
    return SUM_PRT;
}

NodeExpression * SumExpression::clone()const
{
    char *obj = new char[sizeof *this];
    new (obj) SumExpression(this -> get_left() -> clone(),
                            this -> get_right() -> clone());
    return static_cast<NodeExpression *>(static_cast<void *>(obj));
}
//end SumExpression


class Printer {
public:
    Printer(const NodeExpression *);
    const NodeExpression * ptr_expression()const;
private:
    const NodeExpression * expr;
};

//class Printer
    //constructors
Printer::Printer(const NodeExpression & obj):
    expr(obj)
{}
    //methods
const NodeExpression * Printer::ptr_expression()const
{
    return expr;
}
//end Printer

class PrettyPrinter {
public:
    Printer get_infix(Expression const &)const;
private:
};

//class PrettyPrinter
    //constructors
    //methods
Printer PrettyPrinter::get_infix(Expression const & obj)const
{
    return Printer(obj.get_node());
}
//end PrettyPrinter

std::ostream & operator <<(std::ostream & out, const Printer & obj)
{
    obj.ptr_expression() -> print(out);
    return out;
}


NodeExpression *expr(IntVariable &v)
{
    return new VariableExpression(v);
}

NodeExpression *expr(int v)
{
    return new LiteralExpression(v);
}

NodeExpression *plus(NodeExpression *left, NodeExpression *right)
{
    return new SumExpression(left, right);
}

Expression Expression::operator +(Expression const & left,
        Expression const & right)
{
    return new Expression(plus(left.give_node() -> clone(),
        right.give_node() -> clone()));
}
/*
Expression Expression::operator -(Expression const & left,
        Expression const & right)

Expression Expression::operator /(Expression const & left,
        Expression const & right)

Expression Expression::operator *(Expression const & left,
        Expression const & right)

*/
}//end namespace equation

#ifdef LEO
int
main()
{
    using namespace equations;
    IntVariable x("x");
    Expression expression = x + x;

    
}
#endif
