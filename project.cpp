#include<iostream>
#include<fstream>
#include<bitset>

using namespace std;

struct Set
{
    int line0;
    int line1;
    int ref;

};

int main()
{
    ifstream f("test1.txt");
    struct Set cache[32];
    int vCache[2] = {-1, -1};
    int misses = 0;
    unsigned int code, address, set, tag, tag_set;

    for(int i = 0; i < 32; i++)
    {
        cache[i].line0 = -1;
        cache[i].line1 = -1;
        cache[i].ref = -1;
    }

    while(f >> code >> hex >> address)
    {
        tag_set = address >> 6;
        tag = address >> 11;
        set = tag_set & 31;

        cout << hex << address << " " << tag << " ";
        cout << set << endl;

        if(cache[set].line0 == -1)
        {
            cache[set].line0 = tag_set;
            misses++;
        } 
        else if(cache[set].line1 == -1)
        {
            cache[set].line1 = tag_set;
            misses++;
        }
        else if(cache[set].ref == 0)
        {
            for(int i = 0; i < 2; i++)
            {
                if(vCache[i] == tag_set)
                {// page found in victim's cache
                    int temp = 0;
                    if(i == 0)
                        temp = vCache[1];
                    else
                        temp = vCache[0];

                    vCache[1] = cache[set].line0;
                    vCache[0] = temp;
                    cache[set].line0 = tag_set;
                    cache[set].ref = 1;
                    break;                
                }
                else if(vCache[i] == -1)
                {// empty TLB entry found, TLB miss
                    vCache[i] = tag_set;
                    misses ++;
                    // cout << hex << page;
                    break;
                }
            
                if(i == 1)
                {// page is not in victim's cache, cache miss
                    misses ++;
                    
                    vCache[0] = vCache[1];
                    vCache[1] = cache[set].line0;
                    cache[set].line0 = tag_set;
                    // first page brought to TLB occupuies position 0.
                    // FIFO algorithm consequently removes position 0 by
                    // copying the next element in the array to the current element
                    // i.e. moving the queue.      // add page to the end of the array (back of the queue)
                }
            }
        }
        else if(cache[set].ref == 1)
        {
            for(int i = 0; i < 2; i++)
            {
                if(vCache[i] == tag_set)
                {// page found in victim's cache
                    int temp = 0;
                    if(i == 0)
                        temp = vCache[1];
                    else
                        temp = vCache[0];

                    vCache[1] = cache[set].line1;
                    vCache[0] = temp;
                    cache[set].line1 = tag_set;
                    cache[set].ref = 0;
                    break;                
                }
                else if(vCache[i] == -1)
                {// empty TLB entry found, TLB miss
                    vCache[i] = tag_set;
                    misses ++;
                    // cout << hex << page;
                    break;
                }
            
                if(i == 1)
                {// page is not in victim's cache, cache miss
                    misses ++;
                    
                    vCache[0] = vCache[1];
                    vCache[1] = cache[set].line1;
                    cache[set].line1 = tag_set;
                    // first page brought to TLB occupuies position 0.
                    // FIFO algorithm consequently removes position 0 by
                    // copying the next element in the array to the current element
                    // i.e. moving the queue.      // add page to the end of the array (back of the queue)
                }
            }
        }
        
        // bitset<32> t(set);
        // cout << t << endl;

        
    }

    cout << "Cache misses: " << misses;

    f.close();
    
    return 0;
}