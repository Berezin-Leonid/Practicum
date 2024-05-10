#include <iostream>
#include <sstream>



class Parser {
public:
    bool parse(std::istream &);
private:
    std::istream * in;
    void S();
    void A();
    void gc();
    int c;
    int count_a;
    int count_b;
};

bool Parser::parse(std::istream & obj) {
    in = &obj;
    try {
        gc();
        S();
        if (in -> eof() == false) {
            throw c;
        }
        return true;
    } catch (int x) {
        return false;
    }
}

void Parser::gc() {
    c = in -> get();
}

void Parser::S()
{
    count_a = count_b = 0;
    A();
}


void Parser::A()
{
    switch (c) {
        case 'a':
                ++count_a;
                gc();
                A();
                break;
        case 'b':
                ++count_b;
                gc();
                A();
                break;
        case EOF:
                if (count_a != 2 * count_b) {
                    throw c;
                }
                break;
        default:
                throw c;
                break;
    }

}

int
main()
{
    std::cout << 2 << std::endl;
    std::string line;
    Parser parser;
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
