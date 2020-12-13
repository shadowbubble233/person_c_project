#include "search.h"


int binary_search(ElemType *base, int len, ElemType elem)
{
    int low = 0, high = len-1, mid;
    ElemType *item;
    assert(base);

    while(low < high)
    {
        mid = (low + high)/2;
        item = base + mid;
        if(*item == elem)
        {
            return mid;
        }
        else if(*item < elem)
        {
            high = mid -1;
        }
        else
        {
            low = mid + 1;
        }

    }
    return 0;
}

