
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


### sphere-benchmark
Used to create a .dat file containing the box size and the number of spheres as well as their size and coordinates.



## Results

This is our results for the different scripts:
All the data is gathered with the same pc, 
A 2010 MacBook pro, with 10GB memory.

10'000 spheres, Collisions started with: 7522

10 iterations

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| --   | --- |
|Monte_carlo_split_box| ----     | ---  | 
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
|Monte_carlo| ---   | --- |
|Monte_carlo_split_box| ---     | ---  | 
|Monte_carlo_split_box_fast|--  | -- | 

10'000 itterations

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| 158m 20,761s    | 6112 |
|Monte_carlo_split_box| ---    | ---  | 
|Monte_carlo_split_box_fast| 8m 14,070s  | 6391 |

## Acknowledgements
Our code is built upon Martin Thomas Horsch code handed out in class.


## License

[CC BY-NC-SA 4.0 License.](https://creativecommons.org/licenses/by-nc-sa/4.0/)

