#include <iostream>
#include <cstring>

namespace containers {
    class DynArray {
    public:

        DynArray();
        DynArray(DynArray const &);
        ~DynArray();

        int & add();
        const int & operator [](int) const;
        DynArray & operator =(const DynArray&);
        int size() const;
    private:
        int capacity;
        int size_;
        int * array;
    };

//constructors
    DynArray::DynArray()
    {
        capacity = 1;
        size_ = 0;
        array = new int[capacity];
    }

    DynArray::DynArray(DynArray const &obj)
    {
        capacity = obj.capacity;
        size_ = obj.size_;
        array = new int[capacity];
        memcpy(array, obj.array, sizeof (int) * capacity);
    }

    DynArray::~DynArray()
    {
        delete []array;
    }


//metods
    int & DynArray::add()
    {
/*
        if ((i >= capacity) || (i < 0)) {
            std::cout << "Out of DynArray: array[" << i << "]" << std::endl;
            exit(0);
        }
        if (size_ == i) {
            ++size_;
        }
*/
        if (++size_ == capacity) { // have to expand mas
            int * p = new int[capacity * 2];
            memcpy(p, array,sizeof (int) * capacity);
            delete []array;
            array = p;
            capacity = capacity * 2;
        }
        return array[size_ - 1];
    }

    const int & DynArray::operator [](int i)const
    {
        if ((i >= capacity) || (i < 0)) {
            std::cout << "Out of DynArray: array[" << i << "]" << std::endl;
            exit(0);
        }
        return array[i];
    }

/*
    int & DynArray::operator [](int i)
    {
        if ((i >= capacity) || (i < 0)) {
            std::cout << "Out of DynArray: array[" << i << "]" << std::endl;
            exit(0);
        }
        return array[i];
    }
*/
    
    DynArray & DynArray::operator =(DynArray const & obj)
    {
        if (this == &obj) {
            return *this;
        }
        
        size_ = obj.size_;
        capacity = obj.capacity;

        delete []array;
        array = new int[capacity];
        memcpy(array, obj.array, sizeof(int) * capacity);
        return *this;
    }



    int DynArray::size() const
    {
        return size_;
    }

}

namespace iterators {
    class InputIterator {
    public:

        InputIterator();
        InputIterator(std::istream &);
        InputIterator(InputIterator const &);
        ~InputIterator();

        //friend int main();
        InputIterator operator ++(int);
        InputIterator & operator ++();
        int operator *()const;
        bool end()const;
    private:

        std::istream & stream;
        bool beyond_end;
        int * box;
    };
//constructors

    InputIterator::InputIterator(): stream(std::cin)
    {
        box = nullptr;
        beyond_end = true;
    }

    InputIterator::InputIterator(std::istream & in_s): stream(in_s)
    {
        box = new int;
        beyond_end = false;
        if (!(stream >> *box)) {
            beyond_end = true;
        }
    }

    InputIterator::InputIterator(InputIterator const & obj): stream(obj.stream)
    {
        box = new int;
        *box = *obj.box;
        beyond_end = obj.beyond_end;
    }

    InputIterator::~InputIterator()
    {
        if (box != nullptr) {
         
            //std::cout << "free box 115 = " << *box << std::endl;
            delete box;
            box = nullptr;
        }
    }

//metods
    //operations with class

    InputIterator & InputIterator::operator++ ()
    {
        if (!(stream >> *box)) {
            beyond_end = true;
        }
        return *this;
    }

    InputIterator InputIterator::operator++(int)
    {
        InputIterator obj = *this;
        ++(*this);
        return obj;
    }

    int InputIterator::operator *()const
    {
        return *box;
    }

    bool InputIterator::end()const
    {
        return beyond_end;
    }

    class InserterIterator {
    public:

        InserterIterator();
        InserterIterator(containers::DynArray &);
        InserterIterator(InserterIterator const &);
        ~InserterIterator();

        InserterIterator operator ++(int);
        InserterIterator & operator ++();
        InserterIterator & operator =(InserterIterator const & right);
        int & operator *();
    private:
        int index;
        containers::DynArray * mas;

    };

//constructors
    InserterIterator::InserterIterator():
        index(0), mas(nullptr)
    {}
    InserterIterator::InserterIterator(containers::DynArray & obj):
            index(0), mas(&obj)
    {}

    InserterIterator::InserterIterator(InserterIterator const & obj):
            index(obj.index), mas(obj.mas)
    {}

    InserterIterator::~InserterIterator() {}

//metods

    InserterIterator & InserterIterator::operator++()
    {
        ++index;
        return *this;
    }

    InserterIterator InserterIterator::operator++(int)
    {
        InserterIterator obj = *this;
        ++(*this);
        return obj;
    }


    int & InserterIterator::operator *()
    {
        //std::cout << "*obj" << std::endl;
        return mas->add();
    }

    InserterIterator & InserterIterator::operator =(InserterIterator const & right)
    {
        index = right.index;
        mas = right.mas;
        return *this;
    }
}
//global functoins

bool operator ==(iterators::InputIterator const & left,
            iterators::InputIterator const & right)
{
    return left.end() == right.end();
}


bool operator !=(iterators::InputIterator const & left,
            iterators::InputIterator const & right)
{
    return left.end() != right.end();
}

#ifdef LEO
namespace algorithms
{
iterators::InserterIterator
copy(
    iterators::InputIterator iterator,
    iterators::InputIterator end,
    iterators::InserterIterator begin2)
{
    iterators::InserterIterator iterator2 = begin2;
    while (iterator != end) {
        *iterator2++ = *iterator++;
        //*iterator2 = *iterator;
        //iterator2++;
        //iterator++;
    }
    return iterator2;
}
}



int
main()
{
    containers::DynArray a;
    containers::DynArray b = a;
    iterators::InserterIterator c;
    c = algorithms::copy(
        iterators::InputIterator(std::cin),
        iterators::InputIterator(),
        iterators::InserterIterator(a));
    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i] << std::endl;
    }
}
#endif

