#include <iostream>
#include <vector> 

int main(){

    int x = 0;
    while(x < 1'000'000'000)
     x++;
    std::cout << x << std::endl;
}