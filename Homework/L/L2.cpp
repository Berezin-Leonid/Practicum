#include <iostream>
#include <sstream>

class Parser {
public:
    Parser() = default;
    bool parse(std::istream &);
private:
    std::istream * in;
    char c;
    void A();
    void B();
    void S();
    void gc();
};


void Parser::gc() {
    if (!in -> get(c)) {
        c = 0;
    }
}

void Parser::S() {
    //"S-->AS | B"
    if (c == 'b' || c == 'c') {
        A();
        S(); 
    } else {
        B();
    }
    
}


void Parser::A() {
    //"A-->b | c"
    if (c == 'b' || c == 'c') {
        gc(); 
    } else {
        throw c;
    }
}

void Parser::B() {
    //"B--> dBf | a | eps"
    if (c == 'd') {
        gc();
        B();
        if (c == 'f') {
            gc();
        }
        else {throw c;}
    } else if (c == 'a') {
        gc();
    }
}



bool Parser::parse(std::istream & _in)
{
    in = &_in;
    try {
        gc();
        S();
        if (in -> eof() == false) {
            throw c;
        }
        return true; 
    } catch (char x) {
        return false;
    }
}


int
main()
{
    Parser parser;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss;
        ss << line;
        if (parser.parse(ss)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }

    return 0;
}
