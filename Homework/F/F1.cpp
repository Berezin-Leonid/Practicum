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

class Expression {
public:
    Expression
    virtual void print()const = 0;
    virtual ~Expression();
    int priority()const;
private:
    int prior;
};


//priority of perem
//
//  + 1
//  - 1
//  * 2
//  / 3
//  -() 4

class BinaryExpression {
public:
    void print()const;
private:
    Expression *left;
    Expression *right;
    char sign;
};

void BinaryExpression::print()const
{
    if (left -> priority() < priority()) {
        std::cout << "(";
        print(left);
        std::cout << ")";
    } else {
        print(left);
    }

    std::cout << " + ";

    if (left -> priority() < priority())
    print(right);
}

class SumExpression: public BinaryExpression {
public:
    SumExpression(const Expression *, const Expression *);
private:
};

SumExpression::print()
{
}

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
}
