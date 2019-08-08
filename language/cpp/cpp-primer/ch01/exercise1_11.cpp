#include <iostream>

int main()
{
    int v1, v2;
    std::cout << "Enter two number: ";
    std::cin >> v1 >> v2;

    int vmin, vmax;
    if (v1 < v2) {
        vmin = v1;
        vmax = v2;
    } else {
        vmin = v2;
        vmax = v1;
    }

    int sum = 0;
    while (vmin <= vmax) {
        sum += vmin; 
        ++vmin;
    }

    std::cout << "The sum of " << v1 << " to " << v2 << " inclusive is "
              << sum << std::endl;
    return 0;
}
