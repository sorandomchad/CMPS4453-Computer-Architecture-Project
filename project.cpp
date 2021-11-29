/*  Chad Callender
    CMPS 4453
    Project
*/
// To compile use g++ project.cpp

#include<iostream>
#include<fstream>
#include<bitset>

using namespace std;

struct Set
{ // A set of two lines and a reference "bit"
    int line0;
    int line1;
    int ref;        // ref keeps track of the LRU line in the set

};

int main()
{
    ifstream f("spice.txt");
    struct Set cache[32];           // a cache of 32 sets
    int vCache[2] = {-1, -1};       // a victim's cache of 2 lines
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
        set = tag_set & 31;         // bitwise AND between tag_set and 11111 (31 decimal)

        // cout << hex << address << " " << tag << " ";
        // cout << set << endl;

        if(cache[set].line0 == -1)
        {   // line 0 in cache set empty, cache miss
            cache[set].line0 = tag_set;
            cache[set].ref = 1;
            misses++;
        }
        else if(cache[set].line0 == tag_set)
        { // block found in line 0 of the cahce set
            cache[set].ref = 1;
            continue;
        }
        else if(cache[set].line1 == -1)
        {   // line 1 in cache set empty, cache miss
            cache[set].line1 = tag_set;
            cache[set].ref = 0;
            misses++;
        }
        else if(cache[set].line1 == tag_set)
        {  // block found in line 1 of the cache set
            cache[set].ref = 0;
            continue;
        }
        else if(cache[set].ref == 0)
        { // block not found in cache line 0 is LRU
            for(int i = 0; i < 2; i++)
            { // checking victim's cache for block
                if(vCache[i] == tag_set)
                { // block found in victim's cache
                  // bring block back into the main cache
                    int temp = 0;
                    if(i == 0)
                        temp = vCache[1];
                    else
                        temp = vCache[0];

                    vCache[1] = cache[set].line0;
                    vCache[0] = temp;
                    cache[set].line0 = tag_set;
                    break;                
                }
                else if(vCache[i] == -1)
                {// empty victim's cache entry found, cache miss
                    vCache[i] = cache[set].line0;
                    cache[set].line0 = tag_set;
                    misses ++;
                    break;
                }
            
                if(i == 1)
                {// block is not in victim's cache, cache miss
                    misses ++;
                    
                    vCache[0] = vCache[1];
                    vCache[1] = cache[set].line0;   // add block to the end of the array (back of the queue)
                    cache[set].line0 = tag_set;
                    // first block brought to victim's occupuies position 0.
                    // FIFO algorithm consequently removes position 0 by
                    // copying the next element in the array to the current element
                    // i.e. moving the queue.
                }
            }
            cache[set].ref = 1;
        }
        else if(cache[set].ref == 1)
        { // block not found in cache line 1 is LRU
            for(int i = 0; i < 2; i++)
            { // checking victim's cache for block
                if(vCache[i] == tag_set)
                { // block found in victim's cache
                  // bring block back into the main cache
                    int temp = 0;
                    if(i == 0)
                        temp = vCache[1];
                    else
                        temp = vCache[0];

                    vCache[1] = cache[set].line1;
                    vCache[0] = temp;
                    cache[set].line1 = tag_set;
                    break;                
                }
                else if(vCache[i] == -1)
                {// empty victim's cache entry found, cache miss
                    vCache[i] = cache[set].line1;
                    cache[set].line1 = tag_set;
                    misses ++;
                    break;
                }
            
                if(i == 1)
                {// block is not in victim's cache, cache miss
                    misses ++;
                    
                    vCache[0] = vCache[1];
                    vCache[1] = cache[set].line1;   // add block to the end of the array (back of the queue)
                    cache[set].line1 = tag_set;
                    // first block brought to victim's occupuies position 0.
                    // FIFO algorithm consequently removes position 0 by
                    // copying the next element in the array to the current element
                    // i.e. moving the queue.
                }
            }
            cache[set].ref = 0;
        }
        
        // bitset<32> t(set);
        // cout << t << endl;

        
    }

    cout << "Cache misses: " << misses;

    f.close();
    
    return 0;
}