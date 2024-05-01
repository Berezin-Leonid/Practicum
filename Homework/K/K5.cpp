#include <iostream>
#include <string>

enum class TokenKind {
    LeftParen,
    RightParen,
    Star,
    Plus,
    VerticalBar,
    Digit,
    TerminalSymbol,
    EndOfStream
};

class Token {
public:
    Token(TokenKind, const std::string& ); TokenKind get_kind() const;
    const std::string& get_repr() const;

private:
    TokenKind kind;
    char repr;
};

Token::Token(TokenKind get_kind, const std::string& get_repr):
        kind(get_kind), repr(get_repr)
{}


TokenKind Token::get_kind() const
{ return kind; }

const std::string& get_repr() const
{ return repr; }



class TokenStreamIterator {
public:
    TokenStreamIterator(std::istream &);
    TokenStreamIterator & operator ++();
private:
    void read_next_token();
    std::istream stream;
    Token token;
};



TokenStreamIterator::TokenStreamIterator(std::istream & strm):
        stream(strm)
{
    ++(*this);     
}

TokenStreamIterator & TokenStreamIterator::operator ++()
{
     
}

void TokenStreamIterator::read_next_token()
{
    if (!in) {
        token = Token(Token::EndOfStream, '0');
        return;
    }

    char c;

    //clear spaces
    while(in.get(c)) {
        if (c != ' ') {
            break;
        }        
    }

    switch (c) {

    case '(':
        token = Token(Token::LeftParen, c);
        break;

    case ')':
        token = Token(Token::RightParen, c);
        break;

    case '*':
        token = Token(Token::star, c);
        break;

    case '+':
        token = Token(Token::Plus, c);
        break;

    case '|':
        token = Token(Token::VerticalBar, c);
        break;

    case '\\':
        //digit
        //pred symbols
        in.get(c);
        switch (c) {
        case 'd':
            token = Token(Toked
        }
        token = Token(Token::Termianl, c);
        break;

    Star,
    Plus,
    VerticalBar,
    Digit,
    TerminalSymbol,
    EndOfStream

    }
}
