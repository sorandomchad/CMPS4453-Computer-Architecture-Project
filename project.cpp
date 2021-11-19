#include<iostream>
#include<fstream>
#include<bitset>

using namespace std;

struct Set
{
    unsigned int line1;
    unsigned int line2;
    int referenced;

};

int main()
{
    ifstream f("test.txt");
    struct Set cache[32];
    unsigned int vCache[2] = {0, 0};
    int misses = 0;
    unsigned int code, address, set, tag, tag_set;

    for(int i = 0; i < 32; i++)
    {
        cache[i].line1 = 0;
        cache[i].line2 = 0;
        cache[i].referenced = -1;
    }

    while(f >> code >> hex >> address)
    {
        tag_set = address >> 6;
        tag = address >> 11;
        set = tag_set & 31;
        
        // bitset<32> t(set);
        // cout << t << endl;

        cout << tag << " ";
        cout << set << endl;
    }

    f.close();
    
    return 0;
}