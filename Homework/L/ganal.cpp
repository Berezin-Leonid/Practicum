#include <iostream>


char c;

void A();
void B();


using namespace std;

void gc() 
{
    cin >> c;
}


void S()
{
    cout << "S-->ABd, ";
    A();
    B();

    if (c == 'd') {
        gc();
    } else {
        throw c;
    }
}


void A() {
    if (c == 'a') {
        cout << "A-->a, ";
        gc();
    } else if (c == 'c') {
        cout << "A-->cA, ";
        gc();
        A();
    } else {
        throw c;
    }
}


void B() {
    if (c == 'b') {
        cout << "B-->bA, ";
        gc();
        A();
    } else {
        throw c;
    }
}


int
main()
{
    try {
        gc();
        S();
        if (std::cin.eof() == false) {
            throw c;
        }

        cout << "OK" << std::endl;
    } catch (char x)
    {
        cout << "FAIL: on lexeme "<< x << std::endl;
    }
    return 0;
}
