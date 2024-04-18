#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>


template <typename T>
int function(std::string const & s1, std::string const & s2)
{
    std::string::size_type len1 = s1.length();
    std::string::size_type len2 = s2.length();

    //if (len1 == len2)
// skip
    T heap;
    for (std::string::size_type i = 0; i <= len1; ++i) {
        for (std::string::size_type j = 0; j <= len2; ++j) {
            for(std::string::size_type k = 0; k <= len1 - i; ++k) {
                for(std::string::size_type m = 0; m <= len2 - j; ++m) {
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

template <>
int function<std::set<std::string> >(std::string const & s1, std::string const & s2)
{
    std::string::size_type len1 = s1.length();
    std::string::size_type len2 = s2.length();

    std::set<std::string> heap;

    for (std::string::size_type i = 0; i <= len1; ++i) {
        for (std::string::size_type j = 0; j <= len2; ++j) {
            for(std::string::size_type k = 0; k <= len1 - i; ++k) {
                for(std::string::size_type m = 0; m <= len2 - j; ++m) {
                    heap.insert(
                            s1.substr(k, i) + 
                            s2.substr(m, j));
                    heap.insert(
                            s2.substr(m, j) +
                            s1.substr(k, i)); 
                }
            }
        }
    }

    return heap.size();
}

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
        return function<std::set<std::string> >(s1,s2);
    }
}


#ifdef LEO
int
main()
{
    std::string s1 = "aaaa";
    std::string s2 = "aaaa";

    //std::cout << with_vector::fun(s1,s2) << std::endl;
    //std::cout << with_list::fun(s1,s2) << std::endl;
    std::cout << "Lenght = " << with_best::fun(s1,s2) << std::endl;
    return 0;
}
#endif
