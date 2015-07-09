#include "list.h"
 
int main()
{
//It's just a test
        TList<int> L;

        L.Push_to_end(5);
        L.Push_to_end(10);
        L.Push_to_end(15);

        L.Push_to_end(55);
        L.Push_to_end(130);
        L.Push_to_end(155);

        L.Push_to_front(553);
        L.Push(1, 5);

        L.Erase(10);
 
        L.PrintList();

        return 0;
}