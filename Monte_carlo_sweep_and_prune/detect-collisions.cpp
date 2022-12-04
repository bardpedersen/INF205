#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "box.h"
#include "sphere.h"

int main(int argc, char** argv)
{
    assert(argc > 1);
    Box b;
    std::ifstream file_in{argv[1]};
    file_in >> b;
    file_in.close();
    std::multimap<double, int, std::greater<int>> &compon = b.get_components();
    std::vector<std::vector<Sphere>> &particle = b.get_particles(); 

    // New vector for spheres
    std::vector<Sphere> spheres_together;

    // Iterate through all spheres and append them to the new vector 
    
    

}