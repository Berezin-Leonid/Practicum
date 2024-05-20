#include <iostream>
#include <string>
#include <cctype>

enum LexType{
    IDENT,
    COMMA,
    LEFT_BR,
    RIGTH_BR, 
    END,
    ERROR
};

class Parser {
public:
    Parser();
    void parse(const std::string &);
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
Parser::match(LexType type)
{
    if (type == cur_lex) {
        lexParse();
    } else {
        throw 1;
    }
}

Parser::Parser(){}

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
        match(RIGTH_BR);
    } else if (cur_lex == RIGTH_BR) {
        match(RIGTH_BR);
    } else {
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

void
Parser::lexParse()
{
    if (pos >= input.size()) {
        cur_lex = END;
    } else {
        while (pos < input.size() && isspace(input[pos])) {pos++;}
        if (pos < input.size()) {
            if (input[pos] == '(') {
                cur_lex = LEFT_BR;
            } else if (input[pos] == ')') {
                cur_lex = RIGTH_BR;
            } else if (input[pos] == ',') {
                cur_lex = COMMA;
            } else if (isalpha(input[pos])) {
                cur_lex = IDENT;
                while (pos < input.size() && (isalpha(input[pos]) || isdigit(input[pos]))) {pos++;}
                pos--;
            } else {
                cur_lex = ERROR;
            }
            pos++;
        } else {
            cur_lex = END;
        }
    }
}
/*
A -> n '(' P
P -> E ')' | ')'
E -> AT
T -> ',' E | eps
*/

int
main()
{
    Parser obj;
    std::string test_type;
    std::string str;
    std::cout << "1 - by string, 2 - all" << std::endl;
    std::cin >> test_type;
    if (test_type[0] == '1') {
        while (std::getline(std::cin, str)) {
            try {
                obj.parse(str);
                std::cout << "YES" << std::endl;
            } catch (...) {
                std::cout << "NO" << std::endl;
            }
        }
    } else {
        std::string temp;
        while (std::getline(std::cin, temp)) {
            str += temp;
        }
        try {
            obj.parse(str);
            std::cout << "YES" << std::endl;
        } catch (...) {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}
