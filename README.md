
# Sphere overlap

This is our assignment in the course [INF205](https://www.nmbu.no/emne/INF205?studieaar=2022) at  
[Norwegian university of life sciences (NMBU)](https://www.nmbu.no). The Topic we choise is [Sphere overlap](https://home.bawue.de/~horsch/teaching/inf205/project/sphere-overlap.html). 

The problem is as following. Given a box with a set size and n number of spheres with a diameter and coordinates. Calculate the number of collisions and move the spheres to reduce the amount of collisions.

The code should be efficent and reduce the amout of collisions to zero if possible, if not then to the lowest amout of collisions.

## Algorithm

To solve the task, we choose to go with the [Monte carlo algorithm](https://en.wikipedia.org/wiki/Monte_Carlo_method). This algorithm works by picking one random sphere and moving it to a random location, then check if that is an improvment or not. If not then we discard that move, if it does improve we keep that move. Then we do this hundreds of times.

We also implemented a methode for faster computation. This is 


### Monte_carlo
This is the basic code. We start by calculating the number of collisions, then we pick one random sphere and move it to a random location (Monte carlo algorithm). We then check the number of collisions again and use a fromula
to calculate if we keep the new position or move it. 

The formula is e^(Delta u /T), where e is eulers number , delta u is the change in number of collisions and T is 1. This formula is often used in similar problems where gas is simulated. Then T is the temperature of the enviroment, and for us this have no meaning and therfore set to one.

We do this for each itteration, and we save the coordinates each time we get a new lowest amount of collisions. This is to ensure that we always end with the lowest possible collisions. 

If we itterate thru and the number  og collisions come to zero, we break the loop. This is because it cant be more optimized and therefor not nessesary to run more.

### Monte_carlo_split_box



### Monte_carlo_split_box_fast


### sphere-benchmark
Used to create a .dat file containing the box size and the number of spheres as well as their size and coordinates.

## Results

This is our results for the different scripts:

With 10'000 spheres and 100 itterations
Collisions started with: 7522

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| 1m 44,252s    | 7393 |
|Monte_carlo_split_box| 13m 55,505s     | 7393  | 
|Monte_carlo_split_box_fast| 0m 10,990s   | 7411 | 

With 10'000 spheres and 10'000 itterations
Collisions started with: ---

|File        |Time           | Collisions after  |
|:---:|:-------------:|:-------------:|
|Monte_carlo| ---    | --- |
|Monte_carlo_split_box| ---    | ---  | 
|Monte_carlo_split_box_fast| ---  | --- |

## Acknowledgements
Our code is build upon Martin Thomas Horsch code handed out in class.

## License

[CC BY-NC-SA 4.0 License.](https://creativecommons.org/licenses/by-nc-sa/4.0/)

