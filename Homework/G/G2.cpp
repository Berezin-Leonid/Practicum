#include <iostream>
#include <cstring>


enum {
    TOKEN_SIZE = 10
};

void fill_by_different_strings(std::string *, size_t, size_t);

class TokenPool {
public:
    TokenPool(size_t);
    ~TokenPool();
    size_t token_length()const;
    void get_token(char * addr);
    void return_token(const char * addr);
private:
    size_t capacity;
    size_t len_token;
    std::string *buf_token;
    bool* is_free_buf;
};

TokenPool::TokenPool(size_t len):
    capacity(len), len_token(TOKEN_SIZE), buf_token(nullptr), is_free_buf(nullptr)
{
    try {
        buf_token = new std::string[capacity];
        is_free_buf = new bool[capacity];
        fill_by_different_strings(buf_token, capacity, len_token);
        for (size_t i = 0; i < capacity; ++i) {
            is_free_buf[i] = true;
        }
    } catch(std::exception &) {
        delete[] buf_token;
        delete[] is_free_buf;
        throw; 
    }
}


TokenPool::~TokenPool()
{
    delete[] buf_token;
    delete[] is_free_buf;
}

size_t TokenPool::token_length()const
{
    return len_token;
}

void TokenPool::get_token(char * addr)
{
    for (size_t i = 0; i < capacity; ++i) {
        if (is_free_buf[i]) {
            is_free_buf[i] = false;
            strcpy(addr, buf_token[i].c_str());
            return;
        }
    }
    throw std::out_of_range("No empty token");
}

void TokenPool::return_token(const char * addr)
{
    for (size_t i = 0; i < capacity; ++i) {
        if(strcmp(buf_token[i].c_str(), addr) == 0) {
            if (is_free_buf[i] == false) {
                is_free_buf[i] = true;
                return;
            }
            break;
        }
    }
    throw std::logic_error("Can't return this token");
}


#ifdef LEO2
int
main()
{
    TokenPool tok(10);
    char *str = new char[TOKEN_SIZE];
    tok.get_token(str);
    std::cout << str << std::endl;
    tok.return_token(str);
    return 0;
}
#endif
