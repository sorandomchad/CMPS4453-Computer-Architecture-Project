#include<iostream>
#include<fstream>

using namespace std;

struct Set
{
    unsigned int line1;
    unsigned int line2;

};

int main()
{
    ifstream f("test.txt");
    struct Set cache[32];
    unsigned int vCache[2] = {-1, -1};
    int misses = 0;
    unsigned int code, address, set, tag;

    for(int i = 0; i < 32; i++)
    {
        cache[i].line1 = -1;
        cache[i].line2 = -1;
    }

    while(f >> code >> hex >> address)
    {
        cout << hex << address << endl;
    }

    f.close();
    
    return 0;
}