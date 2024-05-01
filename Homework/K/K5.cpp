#include <iostream>
#include <string.h>



class Token {
public:
    enum class Kind {
        LeftParen,
        RightParen,
        Star,
        Plus,
        VerticalBar,
        Digit,
        TerminalSymbol,
        EndOfStream
    };

    Token() noexcept = default;
    Token(Kind, char) noexcept;
    Token(Token const &) noexcept = default;
    Token & operator=(Token const &) noexcept = default;
    //Kind get_kind() const;
    //char get_repr() const;

    Kind kind;
    char repr;
private:
};

Token::Token(Kind get_kind, char get_repr) noexcept:
        kind(get_kind), repr(get_repr)
{}


class TokenStreamIterator {
public:
    TokenStreamIterator() noexcept;
    TokenStreamIterator(TokenStreamIterator const &) noexcept = default;
    TokenStreamIterator(std::istream &);
    TokenStreamIterator & operator ++();
    TokenStreamIterator operator ++(int);
    Token const & operator *()const noexcept;
    const Token * operator ->()const noexcept;
    bool operator ==(TokenStreamIterator const &)const noexcept;
    bool operator !=(TokenStreamIterator const &)const noexcept;
    
private:
    void read_next_token();
    std::istream * in;
    Token token;
};


TokenStreamIterator::TokenStreamIterator() noexcept:
        in(nullptr), token(Token::Kind::EndOfStream, '\0')
{}

TokenStreamIterator::TokenStreamIterator(std::istream & strm):
        in(& strm)
{
    read_next_token();
}

TokenStreamIterator & TokenStreamIterator::operator ++()
{
    read_next_token();
    return *this;     
}

TokenStreamIterator TokenStreamIterator::operator ++(int)
{
    TokenStreamIterator tmp(*this);
    ++(*this);
    return tmp;     
}

Token const & TokenStreamIterator::operator *()const noexcept {
    return token;
}

const Token * TokenStreamIterator::operator ->()const noexcept {
    return &token;
}

bool TokenStreamIterator::operator ==(TokenStreamIterator const & obj)const noexcept
{
    return (this -> in == obj.in);
}

bool TokenStreamIterator::operator !=(TokenStreamIterator const & obj)const noexcept
{
    return (this -> in != obj.in);
}

void TokenStreamIterator::read_next_token()
{
    static char ELEMENTS[] = "()+*\\|";

    if (!(*in)) {
        token = Token(Token::Kind::EndOfStream, '\0');
        return;
    }

    char c;
    //clear spaces
    while(in -> get(c)) {
        if (c != ' ') {
            break;
        }
    }

    if ((*in).eof()) {
        token = Token(Token::Kind::EndOfStream, '\0');
        in = nullptr;
        return;
    }

    switch (c) {
        case '(':
            token = Token(Token::Kind::LeftParen, c);
            break;
 
        case ')':
            token = Token(Token::Kind::RightParen, c);
            break;
 
        case '*':
            token = Token(Token::Kind::Star, c);
            break;
 
        case '+':
            token = Token(Token::Kind::Plus, c);
            break;
 
        case '|':
            token = Token(Token::Kind::VerticalBar, c);
            break;
 
        case '\\':
            if (!in -> get(c)) {
                throw std::exception();
 
            } else if (c == 'd') {
                token = Token(Token::Kind::Digit, c);
                break;
 
            } else if (strstr(ELEMENTS, &c)) {
                throw std::exception();
            }
            token = Token(Token::Kind::TerminalSymbol, c);
            break;
 
        default:
            token = Token(Token::Kind::TerminalSymbol, c);
            break;
    }

}

#ifdef LEO
int
main() {
    TokenStreamIterator it(std::cin);

    while(it -> kind != Token::Kind::EndOfStream) {
        std::cout << it -> repr << std::endl;
        ++it;
    }
    
    return 0;
}
#endif

