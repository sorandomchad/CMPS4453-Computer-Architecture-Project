#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    ifstream f("spice.txt");
    ofstream out("test.txt");

    unsigned int a, num;
    int numOfLines = 0;

    while(f >> a >> hex >> num && numOfLines < 50)
    {
        out << a << " " << hex << num << endl;
        numOfLines++;
        // cout << ".";

    }

    f.close();
    out.close();

    return 0;
}