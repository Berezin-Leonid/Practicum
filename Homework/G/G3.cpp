#include <iostream>
#ifdef LEO
#include "G2.cpp"
#endif

class Action {
public:
    virtual ~Action() = default;
    virtual void run() = 0;
};

class TokenizedAction {
public:
    TokenizedAction(TokenPool &, Action &);    
    ~TokenizedAction();
    void run();
private:
    TokenPool tok_obj;
    std::string token;
    Action & action;
};


TokenizedAction::TokenizedAction(TokenPool & tok, Action & act):
    tok_obj(tok), action(act)
{
    token.resize(tok_obj.token_length());
    tok_obj.get_token(token.data());
}


TokenizedAction::~TokenizedAction()
{
    tok_obj.return_token(token.data());
}

void TokenizedAction::run() {
    action.run();
}

#ifdef LEO
int
main()
{
    return 0;
}
#endif
