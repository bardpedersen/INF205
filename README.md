
# Sphere overlap

This is our assignment in the course [INF205](https://www.nmbu.no/emne/INF205?studieaar=2022) at  
[Norwegian university of life sciences (NMBU)](https://www.nmbu.no). The Topic we choise is [Sphere overlap](https://home.bawue.de/~horsch/teaching/inf205/project/sphere-overlap.html). 

This topic brings up the problem with 

## Algorithm

### Monte_carlo

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

[MIT](https://choosealicense.com/licenses/mit/)

