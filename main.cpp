#include <iostream>

#include "DLL.h"

using namespace std;

int main() {
    DLL lst;
   for (int i = 0; i < 7; ++i) {
       lst.pushBack(i);
   }
   lst.print();
   lst.insert(0, 3);
   lst.print();
   return 0;
}
