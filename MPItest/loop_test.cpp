#include "mpi.h"

int loop_test() {
    int test=0;
    for (int i = 0; i < 100; i++) {
        test++;
    }
    
    //MPI_Finalize();

    return test;
}
