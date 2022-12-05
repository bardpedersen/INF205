# MPI (Message Passing Interface)

MPI was used in this project as a possible improvant of our performance. The goal was to find an overall lower number of collisions. It was used with our basic
version of our solution (Monte_Carlo).  

There are 4 processes (modifiable when executing the mpi command) running at the same time. Each of them are performing the same amount of iterations. 

N_ is the total number of iterations (currently set to 100). So, each processes will perform 25 iterations of the program.

The benefit of this version is that each process are choosing different random spheres to move. By the end of the 25 (100 iterations/ 4 processes)

iterations, their might be a process with a lower number of collisions then on the other ones.

To run this version of the project. 


1. Make sure to have MPI setup on your computer
2. Open Terminal
3. Go in the x64/Debug folder
4. Run the following command: mpiexec -n 4 MPI_Monte_Carlo.exe example-data.dat

You can change the number of process by modifying the number after -n. 


### Example output:
(sphere nb: id of the sphere moved   i: iteration number (from 1 to 100 here)    Rank nb: id of the process    Nb collisions: number of collisions calculated)<br />

sphere nb: 34   i: 25    Rank nb : 1     Nb collisions : 3776<br />
sphere nb: 37   i: 26    Rank nb : 1     Nb collisions : 3552<br />
sphere nb: 40   i: 27    Rank nb : 1     Nb collisions : 3337<br />
sphere nb: 1    i: 28    Rank nb : 1     Nb collisions : 3129<br />
sphere nb: 4    i: 29    Rank nb : 1     Nb collisions : 2929<br />
sphere nb: 7    i: 30    Rank nb : 1     Nb collisions : 2841<br />
sphere nb: 10   i: 31    Rank nb : 1     Nb collisions : 2649<br />
sphere nb: 14   i: 32    Rank nb : 1     Nb collisions : 2569<br />
sphere nb: 17   i: 33    Rank nb : 1     Nb collisions : 2385<br />
sphere nb: 20   i: 34    Rank nb : 1     Nb collisions : 2217<br />
sphere nb: 23   i: 35    Rank nb : 1     Nb collisions : 2049<br />
sphere nb: 27   i: 36    Rank nb : 1     Nb collisions : 1891<br />
sphere nb: 30   i: 37    Rank nb : 1     Nb collisions : 1819<br />
sphere nb: 33   i: 38    Rank nb : 1     Nb collisions : 1755<br />
sphere nb: 36   i: 39    Rank nb : 1     Nb collisions : 1603<br />
sphere nb: 40   i: 40    Rank nb : 1     Nb collisions : 1604<br />
sphere nb: 0    i: 41    Rank nb : 1     Nb collisions : 1548<br />
sphere nb: 3    i: 42    Rank nb : 1     Nb collisions : 1405<br />
sphere nb: 7    i: 43    Rank nb : 1     Nb collisions : 1404<br />
sphere nb: 10   i: 44    Rank nb : 1     Nb collisions : 1404<br />
sphere nb: 13   i: 45    Rank nb : 1     Nb collisions : 1268<br />
sphere nb: 16   i: 46    Rank nb : 1     Nb collisions : 1220<br />
sphere nb: 20   i: 47    Rank nb : 1     Nb collisions : 1211<br />
sphere nb: 23   i: 48    Rank nb : 1     Nb collisions : 1211<br />
sphere nb: 26   i: 49    Rank nb : 1     Nb collisions : 1084<br />
sphere nb: 29   i: 50    Rank nb : 1     Nb collisions : 964<br />
sphere nb: 29   i: 50    Rank nb : 2     Nb collisions : 3776<br />
sphere nb: 33   i: 51    Rank nb : 2     Nb collisions : 3688<br />
sphere nb: 36   i: 52    Rank nb : 2     Nb collisions : 3464<br />
sphere nb: 39   i: 53    Rank nb : 2     Nb collisions : 3249<br />
...
...
...
