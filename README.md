
# Sphere overlap

This is our assignment in the course [INF205](https://www.nmbu.no/emne/INF205?studieaar=2022) at  
[Norwegian university of life sciences (NMBU)](https://www.nmbu.no). The Topic we chose is [Sphere overlap](https://home.bawue.de/~horsch/teaching/inf205/project/sphere-overlap.html). 

The problem is as follows. Given a box with a set size and n number of spheres with a diameter and coordinates. Calculate the number of collisions and move the spheres to reduce the number of collisions.

The code should be efficient and reduce the number of collisions to zero if possible, if not then to the lowest amount of collisions.

## Algorithm

To solve the task, we choose to go with the [Monte Carlo algorithm](https://en.wikipedia.org/wiki/Monte_Carlo_method). This algorithm works by picking one random sphere and moving it to a random location, then checking if that is an improvement or not. If not then we discard that move, if it does improve we keep that move. Then we do this a hundred times.


The time-consuming part of the code is to calculate all the collisions between all the spheres. So if we can implement a method to only calculate the collisions between spheres that are close to each other it would be much faster. We have a few options to solve this.
A uniform grid partition is when we split the box into equal size smaller boxes, and then assign the spheres to the boxes they are in. Spheres can be in multiple boxes at once. And then calculate collisions in each box and add them all up.

The sweep and Prune Algorithm is when we go along an axis, for example, the x-axis, and calculate collision between spheres that are within each other x-values. This can be done with multiple axes to get even fewer calculations. 

 KD Trees are when we choose one axis and split the box by the median of the number of spheres. We do this the same on a different axis. And repeat that until we meet our condition. This can either be the number of splits or max number of spheres in one cell.

A great video we used to understand theese concept better can be found [here](https://www.youtube.com/watch?v=eED4bSkYCB8).




## Directory

### Monte_carlo
This is the basic code. We start by calculating the number of collisions, and then we pick one random sphere and move it to a random location (Monte Carlo algorithm). We then check the number of collisions again and use a formula
to calculate if we keep the new position or move it. 

The formula is e^(Delta u /T), where e is Euler's number, delta u is the change in the number of collisions and T is 1. This formula is often used in similar problems where gas is simulated. Then T is the temperature of the environment, and for us, this has no meaning and is therefore set to one.

We do this for each iteration, and we save the coordinates each time we get the new lowest amount of collisions. This is to ensure that we always end with the lowest possible collisions. 

If we iterate thru and the number of collisions comes to zero, we break the loop. This is because it cant be more optimized and therefore not necessary to run more.

### Monte_carlo_split_box
This works the same as the Monte_carlo directory, but here we have implemented a way to split the box into smaller boxes. The  Monte_carlo code works, but it is slow, so we needed to find a way to make it more efficient. We implemented a uniform grid partition. When we implemented this we noticed that the code was faster but had a higher amount of collisions than the Monte_carlo. This is because if two spheres are in the same two boxes it will count as two collisions instead of one. So to solve this we added a list to each sphere with the id of which paricle it has collided with. So each time we calculate collisions now we go thru the particle list of previous collisions and check if those particles have collided before. 

Instead of improving the code, this made it even slower.


### Monte_carlo_split_box_fast
This is the same principle as the Monte_carlo_split_box. We split the box into smaller boxes, but we accept that it counts more collisions than it is. At the start of the script, we calculate the collisions between all spheres and the same at the end. We then get the true number of collisions as a result. 

This turns out to be the fastest.

### MPI_Monte_Carlo

MPI was used in this project as a possible improvant of our performance. The goal was to find an overall lower number of collisions. It was used with our basic version of our solution (Monte_Carlo).  

There are 4 processes (modifiable when executing the mpi command) running at the same time. Each of them are performing the same amount of iterations. 

N_ is the total number of iterations (currently set to 100). So, each processes will perform 25 iterations of the program.

The benefit of this version is that each process are choosing different random spheres to move. By the end of the 25 (100 iterations/ 4 processes) iterations, there might be a process with a lower number of collisions then on the other ones.

To run this version of the project. 


1. Make sure to have MPI setup on your computer
2. Open Terminal
3. Go in the x64/Debug folder
4. Run the following command: **mpiexec -n 4 MPI_Monte_Carlo.exe example-data.dat**

You can change the number of process by modifying the number after -n. 



### sphere-benchmark
Used to create a .dat file containing the box size and the number of spheres as well as their size and coordinates. 



## Results

### Timing of folders

This is our results for the different scripts:
All the data is gathered with the same pc, 
A 2010 MacBook pro, with 10GB memory.

10'000 spheres, Collisions started with: 7522

10 iterations

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| 0m 13,795   | 7520 |
|Monte_carlo_split_box| 1m 25,854s     | 7520  | 
|Monte_carlo_split_box_fast| 0m 7,216s   | 7520 | 


100 iterations

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| 1m 44,252s    | 7393 |
|Monte_carlo_split_box| 13m 55,505s     | 7393  | 
|Monte_carlo_split_box_fast| 0m 10,990s   | 7411 |


1'000 iterations

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| 20m 32,638s   | 6837 |
|Monte_carlo_split_box| 134m 53,192s     | 6837  | 
|Monte_carlo_split_box_fast| 1m 3,433s | 6915 | 

10'000 itterations

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| 158m 20,761s    | 6112 |
|Monte_carlo_split_box| 1278m 26,888s    | 6112  | 
|Monte_carlo_split_box_fast| 8m 14,070s  | 6391 |


As we can see the monte_carlo_split_box_fast is the best-performing one. It does have more collisions when done, but with the time it saves, it can run thru more iterations and then with the same amount of time it will have a lot fewer collisions. 
We can use the 1'000 and 10'000 iterations as an example. We see that monte_carlo_split_box_fast was faster on the 10'000 than the monte_carlo on the 1'000 and it has a lower amount of collisions.


<embed src="https://github.com/ErikTrier/INF205/blob/bard/plotting/timeplot.pdf" type="application/pdf">

#### Example output from MPI:
(sphere nb: id of the sphere moved   i: iteration number (from 1 to 100 here)    Rank nb: id of the process    Nb collisions: number of collisions calculated)<br />

...<br />
sphere nb: 23   i: 48    Rank nb : 1     Nb collisions : 1211<br />
sphere nb: 26   i: 49    Rank nb : 1     Nb collisions : 1084<br />
sphere nb: 29   i: 50    Rank nb : 1     Nb collisions : 964<br />
sphere nb: 29   i: 50    Rank nb : 2     Nb collisions : 3776<br />
sphere nb: 33   i: 51    Rank nb : 2     Nb collisions : 3688<br />
sphere nb: 36   i: 52    Rank nb : 2     Nb collisions : 3464<br />
sphere nb: 39   i: 53    Rank nb : 2     Nb collisions : 3249<br />
...<br />

## Acknowledgements
Our code is built upon Martin Thomas Horsch's code that he shared with the class. The folder "sphere-benchmark" is in its original state from Martin Thomas Horsch. The folder "Monte_carlo" is heavily based on Martin Thomas Horsch's code but we added the function to move the spheres around.The folders: "Monte_carlo_split_box" and "Monte_carlo_split_box_fast" are based on "Monte_carlo" folder which contains Martin Thomas Horsch's code.



## License

[CC BY-NC-SA 4.0 License.](https://creativecommons.org/licenses/by-nc-sa/4.0/)

