#include <iostream>
#include "Sales_data.h"

using std::cerr; using std::cin; using std::cout; using std::endl;

int main()
{
    Sales_data data1, data2;
    read(cin, data1);
    read(cin, data2);
    if (data1.isbn() == data2.isbn()) {     // check isbns
        Sales_data sum = add(data1, data2); // add the transactions
        print(cout, sum);                   // print the results
        cout << endl;                       // followed by a newline
    }

    return 0;
}