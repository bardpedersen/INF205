#include <iostream>
#include <vector> 

int main(){

    int x = 5;
    int &y = x;

    y = 10;
    std::cout << x << " "<< &y;


return 0;
}