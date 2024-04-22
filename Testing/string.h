#include <iostream>
#include <cstring>

class String {
public:
    String();
    String(const char *);
    String(String const &);
    ~String();

    String & operator =(String);
    const char * string()const;
private:
    void swap(String &);
    char * str;
};

String::String()
{
    str = new char[1];
    strcpy(str,"\0");
}


String::String(const char *_str)
{
    str = new char[strlen(_str) + 1];
    strcpy(str, _str);
}

String::String(String const & obj)
{
    str = new char[strlen(obj.str) + 1];
    strcpy(str, obj.str);
}

String::~String()
{
    delete []str;
}

String & String::operator =(String obj)
{
    swap(obj);
    return *this;
}

const char * String::string()const
{
    return str;
}

void String::swap(String & obj) 
{
    std::swap(this -> str, obj.str);
}

#ifdef teststring 
int
main()
{

    String str1 = "Hello bitches!";
    String str2 = "Hi Ken";

    std::cout << str1.string() << std::endl;
    str2 = str2;
    str2 = str1 = str2;
    String str3 = str2;
    std::cout << str3.string() << std::endl;
    return 0;
}
#endif
