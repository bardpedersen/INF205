#include "box.h"
#include "sphere.h"
#include <cmath>
#include <iostream>

void Box::in(std::istream* source)
{
   // first input size of the box
   *source >> this->extension[0] >> this->extension[1] >> this->extension[2];
   
   int cid = 0;
   size_t num_part_comp = 0;  // number of particles of a certain component
   this->N = 0;
   
   *source >> num_part_comp;  // input number of particles of component 0
   while(num_part_comp != 0)
   {
      // create new component
      double sphere_size = 0.0;
      *source >> sphere_size;
      this->components.insert({sphere_size, cid});
      this->particles.push_back(std::vector<Sphere>());
      
      // now read all the particles
      for(size_t i = 0; i < num_part_comp; i++)
      {
         // read the coordinates
         double x[3];
         for(int d = 0; d < 3; d++)
         {
            *source >> x[d];
            
            // apply periodic boundary condition
            while((x[d]) < 0.0) x[d] += this->extension[d]; //- sphere can be outside, but not senter?
            while((x[d]) > this->extension[d]) x[d] -= this->extension[d]; //+ sphere_size
         }
         
         // insert new particle
         this->particles[cid].push_back(Sphere(this->N++, sphere_size, x));
      }
      
      cid++;
      *source >> num_part_comp;  // input number of particles for next component
   }
}

std::istream& operator>>(std::istream& is, Box& b) {
   b.in(&is);
   return is;
}

// count the number of collisions between pairs of spheres
//
long Box::count_collisions()
{
   long overlaps = 0;
   
   // iterate over pairs of components A and B
   for(auto A = this->components.begin(); A != this->components.end(); A++)
      for(auto B = A; B != this->components.end(); B++)
      {
         if(A->second == B->second)  // same component: iterate over pairs of particles i and j
            for(auto i = this->particles[A->second].begin(); std::next(i) != this->particles[A->second].end(); i++)
               for(auto j = std::next(i); j != this->particles[B->second].end(); j++)
                  overlaps += i->check_collision(&(*j), this->extension);

         else  // different components: iterate over pairs of particles i and j
            for(auto i = this->particles[A->second].begin(); i != this->particles[A->second].end(); i++)
               for(auto j = this->particles[B->second].begin(); j != this->particles[B->second].end(); j++)
                  overlaps += i->check_collision(&(*j), this->extension);
      }
   return overlaps;
}

//Move the spheres systematic in box
void Box::start_phase(){
   double size_box_x = this->extension[0];
   double size_box_y = this->extension[1];
   double size_box_z = this->extension[2];
   double coordx = 0;
   double coordy = 0;
   double coordz = 0;
   double prev_size;
   double prev_size_z;
   int q = 0;
   for(auto A = this->components.begin(); A != this->components.end(); A++)
      for(auto i = this->particles[A->second].begin(); i != this->particles[A->second].end(); i++){
         double size = (i->get_size() * 0.5);

         if(q == 0){
            coordy = size;
            coordz = size;
            prev_size = size;
            prev_size_z = size;
         }

         coordx += size;

         if(coordx + size > size_box_x){
            coordx = size;
            coordy += prev_size + size;
            prev_size = size;
         }

         if(coordy > size_box_y){
            coordx = size;
            coordy = size;
            coordz += prev_size_z;
            coordz += size;
            prev_size_z = size;
         }

         i->set_coordinate(0, coordx);
         i->set_coordinate(1, coordy);
         i->set_coordinate(2, coordz);

         std::cout << "Partic id " << i->get_particle_id() << " Coords: " << i->get_coordinate(0)<< i->get_coordinate(1)<< i->get_coordinate(2)<<"\n";
         
         coordx += size;

         if(coordz > size_box_z){
            break;
         }
         q += 1;
   }
}

int Box::move_sphere(int number_of_coll){

   int collisions_before = number_of_coll;

   //Choose random sphere
   int random_sphere_from_list = rand() % this->N; 
   //if random number is 7 we know that it isnt in the first component, so
   //needs to have the size of each component to know wich component to go thru
   // pick a random index

   for(auto Comp = this->components.begin(); Comp != this->components.end(); Comp++){
      //comp list of the different components 
      for(auto particle = this->particles[Comp->second].begin(); particle != this->particles[Comp->second].end(); particle++){
      //list of particles in that componenet
         if(random_sphere_from_list == particle->get_particle_id()){
            double temp_coord[3];

            for(int d = 0; d < 3; d++)
            {
               temp_coord[d] = particle->get_coordinate(d);
            }

            double new_coords[3];

            for(int d = 0; d < 3; d++){

               new_coords[d] = (rand() % 10 + 1); 
               while((new_coords[d]) < 0.0) new_coords[d] += new_coords[d] ; //if pbc is true / increese with this->extension[d], got a case where box is 4**3 and sphere size is 2 and start in positsion (1,1,1) 
               while((new_coords[d]) > this->extension[d]) new_coords[d] -= new_coords[d]; 

               particle->set_coordinate(d, new_coords[d]); //need to move within perodic boundry.
               }

            int collisions_after = count_collisions();
            //std::cout << "\n";
            //std::cout << collisions_before << " "<< collisions_after <<"\n";
            //std::cout << "\n";
            double probability_move  = exp(collisions_before - collisions_after); // Number of collisions
            double random = (rand() % 100 + 1);
            //std::cout << probability_move << ">" << random/100;
            if(probability_move < random/100) {
               for(int d = 0; d < 3; d++){
                  particle->set_coordinate(d, temp_coord[d]);

               }
            }
            else{
               collisions_before = collisions_after;
            }
         }
      }
   }
   return collisions_before;
}
