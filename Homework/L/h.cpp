#include <iostream>
#include <sstream>
#include <cstring>


const char NO_TERMINAL[] = "ABCDEFG";

int
main()
{
    char c;
    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << "abCde";
    //while(ss1.get(c)) {
    while(std::cin.get(c)) {
        if (strstr(NO_TERMINAL, &c)) {
            switch (c) {
                case 'A':
                    ss2 << "AAAA";
                    break;

                case 'C':
                    ss2 << "CCCC";
                    break;

                default:
                    break;
            }
        } else {
            ss2 << c;
        }
    }
    std::string str;
    ss2 >> str;
    std::cout << str << std::endl;
    return 0;
}
