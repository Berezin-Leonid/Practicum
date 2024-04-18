#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>


template <typename T>
int function(std::string const & s1, std::string const & s2)
{
    int len1 = s1.length();
    int len2 = s2.length();

    //if (len1 == len2)
// skip
    T heap;
    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            for(int k = 0; k <= len1 - i; ++k) {
                for(int m = 0; m <= len1 - i; ++m) {
                    //std::string s = s1.substr(k, i) + s2.substr(m,j);
                    //std::cout << s << std::endl;
                    if (std::find(heap.begin(), heap.end(), s1.substr(k, i) + 
                            s2.substr(m, j)) == heap.end()) {

                        heap.push_back(
                            s1.substr(k, i) + 
                            s2.substr(m, j));

                    }

                    if (std::find(heap.begin(), heap.end(), s2.substr(m, j) +
                            s1.substr(k, i)) == heap.end()) {

                        heap.push_back(
                            s2.substr(m, j) +
                            s1.substr(k, i)); 

                    }
                }
            }
        }
    }

    return heap.size();
}

/*
template <>
int function<std::set<std::string> >(std::string const & s1, std::string const & s2)
{
    int len1 = s1.length();
    int len2 = s2.length();

    //if (len1 == len2) 
// skip
    std::set<std::string> heap;
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            for(int k = 0; k < len1 - i; ++k) {
                for(int m = 0; m < len1 - j; ++m) {
                    if (std::find(heap.begin(), heap.end(), s1.substr(k, i) + 
                            s2.substr(m, j)) == heap.end()) {

                        heap.insert(
                            s1.substr(k, i) + 
                            s2.substr(m, j));

                    }
                }
            }
        }
    }

    return heap.size();
}
*/

namespace with_vector {
    int fun(std::string const & s1, std::string const & s2)
    {
        return function<std::vector<std::string> >(s1,s2);
    }
}

namespace with_list {
    int fun(std::string const & s1, std::string const & s2)
    {
        return function<std::list<std::string> >(s1,s2);
    }
}

namespace with_best {
    int fun(std::string const & s1, std::string const & s2)
    {
        return function<std::list<std::string> >(s1,s2);
    }
}


#ifdef LEO
int
main()
{
    std::cout << with_best::fun("ab","12") << std::endl;
    return 0;
}
#endif
