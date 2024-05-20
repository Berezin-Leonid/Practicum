#include <iostream>
#include <string>
#include <cctype>



class Parser {
public:
    Parser();
    void parse(const std::string &);
    enum LexType {
        LEFT_BR,
        RIGHT_BR,
        END,
        ERR,
        COMMA,
        IDENT
    };
private:
    void A();
    void P();
    void E();
    void T();
    void lexParse();
    void match(LexType);
    std::string input{};
    LexType cur_lex{};
    size_t pos{};
    
};


void
Parser::match(LexType type) {
    if (type == cur_lex) {
        lexParse();
    } else {
        throw 1;
    }
}


Parser::Parser()
{}


void
Parser::parse(const std::string & in)
{
    input = in;
    pos = 0;
    lexParse();
    try {
        A();
        if (cur_lex != END) {
            throw 1;
        }
    } catch (...) {
        throw 1;
    }
}

void
Parser::lexParse()
{
    if (pos >= input.size()) {
        cur_lex = END;
    } else {
        while (pos < input.size() && isspace(input[pos])) {
            ++pos;
        }

        if (pos < input.size()) {
            switch (input[pos]) {
                case '(': 
                        cur_lex = LEFT_BR;
                        ++pos;
                        break;
                case ')':
                        cur_lex = RIGHT_BR;
                        ++pos;
                        break;
                case ',':
                        cur_lex = COMMA;
                        ++pos;
                        break;
                default:
                        if (isalpha(input[pos])) {
                            cur_lex = IDENT;
                            while (pos < input.size() && 
                                    (isalpha(input[pos]) ||
                                    isdigit(input[pos]))) {
                                ++pos;
                            }
                        } else {
                            cur_lex = ERR;
                        }
            }
        } else {
            cur_lex = END;
        }
    }
}


/*
    A -> name '(' P
    P -> E ')' | ')'
    E -> AT
    T -> ',' E | eps
*/


void
Parser::A()
{
    if (cur_lex == IDENT) {
        match(IDENT);
        match(LEFT_BR);
        P();
    } else {
        throw 1;
    }
}

void
Parser::P()
{
    if (cur_lex == IDENT) {
        E();
        match(RIGHT_BR);
    } else 

    switch (cur_lex) {
        case IDENT:
                E();
                match(RIGHT_BR);
                break;
        case RIGHT_BR:
                match(RIGHT_BR);
                break;
        default:
                throw 1;
    }
}


void
Parser::E()
{
    A();
    T();
}


void
Parser::T()
{
    if (cur_lex == COMMA) {
        match(COMMA);
        E();
    }
}



#ifdef LEO
int
main()
{
    Parser parser;
    std::string test1 = "a(b(), c())";
    std::string test2 = "a(b(c()))";
    std::string test3 = "a(";
    try {
        parser.parse(test1);
        std::cout << "YES" << std::endl;
    } catch (...) {
        std::cout << "NO" << std::endl;
    }

    try {
        parser.parse(test2);
        std::cout << "YES" << std::endl;
    } catch (...) {
        std::cout << "NO" << std::endl;
    }

    try {
        parser.parse(test3);
        std::cout << "YES" << std::endl;
    } catch (...) {
        std::cout << "NO" << std::endl;
    }
    
    return 0;
}
#endif
