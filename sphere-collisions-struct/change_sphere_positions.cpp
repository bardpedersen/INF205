#include <iostream>
#include "collisions_low-level.h"

int main()
{
   int N = 0; // N will be the number of spheres
   std::cin >> N;  // input number of spheres
   
   /*
    * array containing the diameter of each of the spheres;
    * for example, the diameter of the first sphere will be stored as size[0];
    * the diameter of the last sphere will be stored as size[N-1]
    */ 
   float* size = new float[N]();
   
   /*
    * three arrays for x, y, z coordinates of the spheres;
    * for example, the y coordinate of sphere with index 4 will be coordy[4]
    */
   float* coordx = new float[N]();
   float* coordy = new float[N]();
   float* coordz = new float[N]();
   
   /*
    * read all the data from standard input
    */
   for(int i = 0; i < N; i++)
   {
      std::cin >> size[i] >> coordx[i] >> coordy[i] >> coordz[i];
   }
   
   /*
    * how many collisions are there between the spheres?
    * 
    * note: collision here means "overlap" between spheres
    */
   for(int i=0;i<5;i++)
   {
        
        int num_collisions = count_collisions(N, size, coordx, coordy, coordz);
        std::cout << num_collisions << " collisions were found.\n";
        coordx[0]=coordx[0]+1;
        coordy[0]=coordy[0]+1;
        coordz[0]=coordz[0]+1;
   }

   
   /*
    * deallocate all the arrays created with "new"
    */
   delete[] size;
   delete[] coordx;
   delete[] coordy;
   delete[] coordz;
}
