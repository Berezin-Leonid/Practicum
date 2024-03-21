#include <iostream>
#include <cstring>

namespace containers {
    class DynArray {
    public:

        class Iterator {
        public:
 
            Iterator();
            Iterator(DynArray const & , int);
            Iterator(Iterator const &);
            ~Iterator();
 
            Iterator operator ++(int);
            Iterator & operator ++();
            Iterator & operator =(Iterator const & right);
            int const & operator *();
            bool operator ==(Iterator const & right);
            bool operator !=(Iterator const & right);
 
        private:
            
            const DynArray * mas;
            int index;
        };

        DynArray();
        DynArray(DynArray const &);
        ~DynArray();

        int & add();
        const int & operator [](int) const;
        int & operator [](int);
        DynArray & operator =(const DynArray&);
        int size() const;

        Iterator begin_iterator() const;
        Iterator end_iterator() const;
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

    DynArray::Iterator DynArray::begin_iterator() const
    {
        return Iterator(*this, 0);
    }

    DynArray::Iterator DynArray::end_iterator() const
    {
        return Iterator(*this, size_);
    }

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

    int & DynArray::operator [](int i)
    {
        if ((i >= capacity) || (i < 0)) {
            std::cout << "Out of DynArray: array[" << i << "]" << std::endl;
            exit(0);
        }
        return array[i];
    }
    
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

//classes
//constr DynArray::Interator
    DynArray::Iterator::Iterator()
    {
        index = 0;
        mas = nullptr;
    }

    DynArray::Iterator::Iterator(DynArray const & obj, int i)
    {
        index = i;
        mas = &obj;
    }

    DynArray::Iterator::Iterator(DynArray::Iterator const & obj)
    {
        index = obj.index;
        mas = obj.mas;
    }

    DynArray::Iterator::~Iterator() {}
//metods DynArray::Interator
    DynArray::Iterator & DynArray::Iterator::operator ++()
    {
        ++index;
        return *this;
    }

    DynArray::Iterator DynArray::Iterator::operator ++(int)
    {
        Iterator obj = *this;
        ++(*this);
        return obj;
    }

    DynArray::Iterator & DynArray::Iterator::operator =(DynArray::Iterator const & right)
    {
        index = right.index;
        mas = right.mas;
        return *this;
    }
    int const & DynArray::Iterator::operator *()
    {
        //std::cout << "*obj" << std::endl;
        return  (*mas)[index];
    }

    bool DynArray::Iterator::operator ==(DynArray::Iterator const & right)
    {
        return index == right.index;
    }


    bool DynArray::Iterator::operator !=(DynArray::Iterator const & right)
    {
        return this->index != right.index;
    }
}

namespace iterators {
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

//constructors InserterIterator
    InserterIterator::InserterIterator()
    {
        index = 0;
        mas = nullptr;
    }
    InserterIterator::InserterIterator(containers::DynArray & obj)
    {
        index = obj.size();
        mas = &obj;
    }

    InserterIterator::InserterIterator(InserterIterator const & obj)
    {
        index = obj.index;
        mas = obj.mas;
    }

    InserterIterator::~InserterIterator() {}

//metods InserterIterator

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
//constructors InputIterator

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

//metods InputIterator
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
class AddTo {
public:

    AddTo(int &);
    void operator ()(int);
    
private:
    int & val;
};

AddTo::AddTo(int &obj): val(obj) {}

void AddTo::operator ()(int x)
{
    val += x;
}



class IsEven {
public:

    IsEven(bool);
    IsEven(IsEven const &);
    bool operator ()(int)const;
private:
    bool val;
    bool val_bool;
};

IsEven::IsEven(bool x): val(x) {}

IsEven::IsEven(IsEven const & obj): val(obj.val) {}

bool IsEven::operator ()(int x) const
{
    return  (x % 2 == 0) == val;
}

}

#ifdef LEO

namespace algorithms
{
void
foreach_if(
    containers::DynArray::Iterator iterator,
    containers::DynArray::Iterator end,
    algorithms::IsEven condition,
    algorithms::AddTo action)
{
    while (iterator != end) {
        if (condition(*iterator)) {
            action(*iterator);
        }
        ++iterator;
    }
}
}

int
main()
{
    containers::DynArray a;
    algorithms::copy(
        iterators::InputIterator(std::cin),
        iterators::InputIterator(),
        iterators::InserterIterator(a));

    int even_summ = 0, odd_summ = 0;
    int all_summ = 0;
/*
    algorithms::foreach_if(
        a.begin_iterator(),
        a.end_iterator(),
        algorithms::IsEven(true),
        algorithms::AddTo(even_summ));

    algorithms::foreach_if(
        a.begin_iterator(),
        a.end_iterator(),
        algorithms::IsEven(false),
        algorithms::AddTo(odd_summ));

*/

    algorithms::foreach_if(
        a.begin_iterator(),
        a.end_iterator(),
        true,
        algorithms::AddTo(all_summ));
    std::cout <<"even_summ = " <<  even_summ << std::endl;
    std::cout << "odd_summ  = " << odd_summ << std::endl;
    std::cout << "all_summ = " <<  all_summ << std::endl;
}
#endif

