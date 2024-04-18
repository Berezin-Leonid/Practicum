#include <iostream>
#include <exception>
#include <vector>


template <typename T>
typename T::value_type last3(T const & obj)
{
    if (obj.size() < 3) {
        throw std::exception();
    }

    typename T::const_iterator it = obj.end();
    --it;
    --it;
    --it;
    return *it++ + *it++ + *it++;
}


#ifdef LEO
int
main()
{
    std::vector<int> v;
    v.push_back(1); 
    v.push_back(2); 
    v.push_back(3); 
    v.push_back(4); 
    std::cout << last3(v) << std::endl;
    return 0;
}
#endif
