#include "box.h"
#include "sphere.h"
#include "small_box.h"

#include <cmath>
#include <iostream>
#include <cassert>


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
   
   for(auto Comp = this->boxes.begin(); Comp != this->boxes.end(); Comp++){
      if(Comp->get_particles().size() != 0){
         for(auto partic_1 = Comp->get_particles().begin();  std::next(partic_1) != Comp->get_particles().end(); partic_1++){
            for(auto partic_2 = std::next(partic_1); partic_2 != Comp->get_particles().end(); partic_2++){

               std::cout << partic_1->get_particle_id() << " " << partic_2->get_particle_id() <<"\n";
               overlaps += partic_1->check_collision(&(*partic_2), this->extension);
               std::cout << "overlaps: "<< overlaps <<"\n";
            }
         }
      }
   }
   return overlaps;
}


double Box::get_extension(int axis) const
{
   assert((axis == 0) || (axis == 1) || (axis == 2));
   return this->extension[axis];
}

int Box::move_sphere(int number_of_coll){

   int collision_before = number_of_coll;

   //Choose random sphere
   int random_sphere_from_list = rand() % this->N; 
   //if random number is 7 we know that it isnt in the first component, so
   //needs to have the size of each component to know wich component to go thru
   // pick a random index

   for(auto Comp = this->components.begin(); Comp != this->components.end(); Comp++){
      //comp list of the different components 
      for(auto partic = this->particles[Comp->second].begin(); partic != this->particles[Comp->second].end(); partic++){
      //list of particles in that componenet
         if(random_sphere_from_list == partic->get_particle_id()){
            double temp_coord[3];

            for(int d = 0; d < 3; d++)
            {
               temp_coord[d] = partic->get_coordinate(d);
            }

            double new_coords[3];

            for(int d = 0; d < 3; d++){

               new_coords[d] = (rand() % 10 + 1); 
               while((new_coords[d]) < 0.0) new_coords[d] += new_coords[d] ; //if pbc is true / increese with this->extension[d], got a case where box is 4**3 and sphere size is 2 and start in positsion (1,1,1) 
               while((new_coords[d]) > this->extension[d]) new_coords[d] -= new_coords[d]; 

               partic->set_coordinate(d, new_coords[d]); //need to move within perodic boundry.
               }


            //needs to move sphere from old to new box.


            int collisions_after = count_collisions();
            //std::cout << "\n";
            //std::cout << collision_before << " "<< collisions_after <<"\n";
            //std::cout << "\n";
            double probability_move  = exp(collision_before - collisions_after); // Number of collisions
            double random = (rand() % 100 + 1);
            //std::cout << probability_move << ">" << random/100;
            if(probability_move < random/100) {
               for(int d = 0; d < 3; d++){
                  partic->set_coordinate(d, temp_coord[d]);

               }
            }
            else{
               collision_before = collisions_after;
            }
         }
      }
   }
   return collision_before;
}

/////////////////////////////////////////////////////////////////////////////

void Box::split_boxes(int number_of_boxes){
   double size_of_small_box[3];

   for(int i=0; i<3;i++){
      size_of_small_box[i] = (this->extension[i] / number_of_boxes);
   }

   double coords_for_small_box[6];

   coords_for_small_box[0] = 0;
   coords_for_small_box[1] = size_of_small_box[0];

   coords_for_small_box[2] = 0;
   coords_for_small_box[3] = size_of_small_box[1];

   coords_for_small_box[4] = 0;
   coords_for_small_box[5] = size_of_small_box[2];

   for(int i = 0; i<number_of_boxes*number_of_boxes*number_of_boxes; i++){
      small_Box small; //create new box for each itteration

      //Increese x coords unless the itteration is on the number of boxes on one side, then it start from 0.
      //y increese when x is sett to zero.
      if((i)%(number_of_boxes) == 0){
         coords_for_small_box[0] = 0;
         coords_for_small_box[1] = size_of_small_box[0];
         if(i != 0){
         coords_for_small_box[2] += size_of_small_box[1];
         coords_for_small_box[3] += size_of_small_box[1];
         }
      } 

      //Z is increseing when one "layer" is filled up, the area.
      if(i == number_of_boxes * number_of_boxes){
         coords_for_small_box[4] += size_of_small_box[2];
         coords_for_small_box[5] += size_of_small_box[2];
         coords_for_small_box[2] = 0;
         coords_for_small_box[3]= size_of_small_box[1];
      } 

      //set coords for small box
      for(int i = 0; i < 6; i++){
         small.set_extension(i, coords_for_small_box[i]);
      }
      //set id for small box
      small.set_box_id(i);
      
      for(auto Comp = this->components.begin(); Comp != this->components.end(); Comp++){
         for(auto partic = this->particles[Comp->second].begin(); partic != this->particles[Comp->second].end(); partic++){
            int insert = 0;
            int a = -1;
            for(int d = 0; d < 5; d++){
               if(d %2 ==0){
                  a+=1;
               }
               if(((coords_for_small_box[d] <= (partic->get_size()*0.5 + partic->get_coordinate(a))) && ((partic->get_size()*0.5 + partic->get_coordinate(a)) <= coords_for_small_box[d+1]))||
               ((coords_for_small_box[d]<= (partic->get_coordinate(a) - partic->get_size() * 0.5)) && ((partic->get_coordinate(a) - partic->get_size() * 0.5) <= coords_for_small_box[d+1]))){
                  insert += 1;
               }
               if(insert==3){
                  partic->set_box_ID(i);
                  small.set_particles(*partic); //set particle in small_box
               }
            }
         }
      }
      
      coords_for_small_box[0] += size_of_small_box[0];
      coords_for_small_box[1] += size_of_small_box[0];

      //ad small box to vector
      this->boxes.push_back(small);

   }
   
   for(auto Comp = this->boxes.begin(); Comp != this->boxes.end(); Comp++){
      std::cout <<"box: " <<Comp->get_box_id() << ' ';
      std::vector<Sphere> &particle = Comp->get_particles();
      for (auto it = particle.begin(); it != particle.end(); it++){
        std::cout <<"particle: " <<it->get_particle_id() << " ";
      }
   std::cout << "\n";
   }
   
}  
/*
Needs a new function that splits box into 8, 27 or 64, the more boxes the faster butt more memory is used.
Then it only needs to check the collosions in these boxes. This wil limit the amout of calculations. Can aslo use
mpi to run multiple boxes at the same time.


create new struct with small boxes

each box needs start coords and end coords in all 3 directions
also needs each particle that is in that box.
total number of particles 

functions that add and remove particles

particles store witch box/boxes they are in. vector so we can add element on the go. min 1 max all boxes at once.


only calculate colissions in the boxes that changes.



done:
shpheres save box id and can delete them when move.

*/