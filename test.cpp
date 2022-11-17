#include <iostream>
#include <vector> 

int main(){
    std::vector<int> vect;
    vect.push_back(10);
    vect.push_back(20);
    vect.push_back(30);

    for(auto i = vect.begin(); i != vect.end(); i++)
    {   
        std::cout << *i << "\n";
    }

return 0;
}