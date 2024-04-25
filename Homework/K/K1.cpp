#include <iostream>
#include <set>
#include <cstring>

std::set<std::pair<char, std::string> > g3()
{
    return {
        {'S', "Bc"}, {'S', "d"},
        {'A', "Sa"},
        {'B', "Ab"}
    };
}

std::set<std::pair<char, std::string> > g4()
{
    return {
        {'S', "A_"}, {'S', "B_"},
        {'A', "Aa"}, {'A', "a"},
        {'B', "Bb"}, {'B', "Ab"}
    };
}

#ifdef LEO
int
main()
{
    return 0;
}
#endif
