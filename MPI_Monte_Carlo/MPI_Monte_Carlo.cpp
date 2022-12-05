// MPItest.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <iostream>
#include <stdio.h>

#include "box.h"
#include "sphere.h"
#include "mpi.h"

using namespace std;

int main(int argc, char** argv) {

    assert(argc > 0);

    //Unique rank is assigned to each process in a communicator
    int rank;

    //Total number of ranks
    int size;

    //The machine we are on
    char name[128];

    //Length of the machine name
    int length;

    //Initializes thr MPI execution evironment
    MPI_Init(&argc, &argv);

    //Get this process' rank (process within a communicator)
    // MPI_COMM_WORLD is the default communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Get the total number of ranks in this communicator
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Gets the name of the processor
    //Implementation specific (may be gethostname, uname, or sysinfo)
    MPI_Get_processor_name(name, &length);

    int N_ = 100; //Total number of iterations
    float  partition = N_ / size; //Number of iterations per process

    Box b;
    std::ifstream file_in{ argv[1] };
    file_in >> b;
    file_in.close();

    
    std::multimap<double, int, std::greater<int>>& compon = b.get_components();
    std::vector<std::vector<Sphere>>& particle = b.get_particles();

    int collosions_start = b.count_collisions();
    int lowest_number_of_collisions = collosions_start;
    int collisions_to_funct = collosions_start;

    //int size = b.get_N();
    double coord[10000][3];
    int itteration = 0;

    for (int i = rank * partition; i <= rank * partition + partition; i++) //make same number of iterations in each loop
    {
        itteration++;

        int number_of_collisions = b.move_sphere(collisions_to_funct,i);

        if (number_of_collisions < lowest_number_of_collisions) {

            lowest_number_of_collisions = number_of_collisions;
            for (auto comp = compon.begin(); comp != compon.end(); comp++) {
                for (auto partic = particle[comp->second].begin(); partic != particle[comp->second].end(); partic++) {
                    int particle_number = partic->get_particle_id();

                    for (int c = 0; c < 3; c++) {
                        coord[particle_number][c] = partic->get_coordinate(c);
                    }
                }
            }
        }

        if (number_of_collisions == 0) { //if collsion == 0, break and stop. 
            break;
        }
        collisions_to_funct = number_of_collisions;

        cout << "\ti: " << i << "\t Rank nb : " << rank << "\t Nb collisions : " << number_of_collisions << "\n";

    }

    MPI_Finalize();

}


