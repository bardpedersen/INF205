#include <iostream>
#include "collisions_low-level.h"
#include <list>

int main()
{
   int N = 0; // N will be the number of spheres
   std::cin >> N;  // input number of spheres
   srand(10);
   
   /*
    * array containing the diameter of each of the spheres;
    * for example, the diameter of the first sphere will be stored as size[0];
    * the diameter of the last sphere will be stored as size[N-1]
    */ 
   float *size = new float[N]();
   
   /*
    * three arrays for x, y, z coordinates of the spheres;
    * for example, the y coordinate of sphere with index 4 will be coordy[4]
    */
   float *coordx = new float[N]();
   float *coordy = new float[N]();
   float *coordz = new float[N]();
   
   /*
    * read all the data from standard input
    */
   for(int i = 0; i < N; i++)
   {
      std::cin >> size[i];
   }
   
   /*
    * how many collisions are there between the spheres?
    * 
    * note: collision here means "overlap" between spheres
    */
   
   float min_nb_collisions=100;
   int no_improvement_count=0;
   int count=0;
   int nb_simulations=10000;

   std::list<std::list<float>> sim_coord;

   // for(int i = 0; i < nb_simulations; i++)
   // {
   //    sim_coord.assign(coordX)
   // }

   // while(no_improvement_count<1000)
   // {
   //    for(int i = 0; i < N; i++)
   //    {
   //       coordx[N]=rand()%100;
   //       coordy[N]=rand()%100;   
   //       coordz[N]=rand()%100;

   //       std::cout << "Sphere N"<<i<< ": ("<< coordx[N]<<","<<coordy[N]<<","<<coordz[N]<<")\n";
   //    }

   //    float num_collisions = count_collisions(N, size, coordx, coordy, coordz);
   //    std::cout << num_collisions << " collisions were found.\n";
      
   //    if(num_collisions<min_nb_collisions)
   //    {
   //       min_nb_collisions=num_collisions;
   //       no_improvement_count=0;
   //    }
   //    else
   //    {
   //       no_improvement_count++;
   //    }
   //    count++;
   // }

   // std::cout<<"\nMinimum number of collisions: "<<min_nb_collisions<<"\n";
   // std::cout<<count;
   
   *size=10;
   std::cout << "Size: "<< *size << "\n";

   for(int i = 0; i < N; i++)
   {
      coordx[N]=rand()%10;
      coordy[N]=rand()%10;   
      coordz[N]=rand()%10;

      std::cout << "Sphere N"<<i<< ": ("<< coordx[N]<<","<<coordy[N]<<","<<coordz[N]<<")\n";
   }
   

   float num_collisions = count_collisions(N, &size, &coordx, &coordy, &coordz);

   std::cout << num_collisions << " collisions were found.\n";

   /*
    * deallocate all the arrays created with "new"
    */

   delete[] size;
   delete[] coordx;
   delete[] coordy;
   delete[] coordz;
}
