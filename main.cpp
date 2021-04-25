#include <iostream>

#include "DLL.h"

using namespace std;

void printValue(valueType value) {
    cout << value << endl;
}

valueType increment(valueType value) {
    return ++value;
}

bool isEven(valueType value) {
    return !(value % 2);
}

int main() {
    DLL lst;
   for (int i = 0; i < 7; ++i) {
       lst.pushBack(i);
   }
   lst.print();
   lst.filter(isEven);
   lst.forEach(printValue);
   lst.map(increment);
   lst.print();
   return 0;
}