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
long Box::count_collisions()
{
   long overlaps = 0;
   //////
   //////Use the particle box.id, and if the particles have the same box id only count one.
   //////
   int i = 0;
   for(auto Small_box = this->boxes.begin(); Small_box != this->boxes.end(); Small_box++){
      if(Small_box->get_particles().size() > 1){
         for(auto partic_1 = Small_box->get_particles().begin();  std::next(partic_1) != Small_box->get_particles().end(); partic_1++){
            for(auto partic_2 = std::next(partic_1); partic_2 != Small_box->get_particles().end(); partic_2++){
               Sphere * par1 = *partic_1;
               Sphere * par2 = *partic_2;
               overlaps += par1->check_collision(&(*par2), this->extension);
            }
         }
      }
   }
   
   for(auto Small_box = this->boxes.begin(); Small_box != this->boxes.end(); Small_box++){
      if(Small_box->get_particles().size() > 1){
         for(auto partic_1 = Small_box->get_particles().begin(); partic_1 != Small_box->get_particles().end(); partic_1++){
            Sphere * par1 = *partic_1;
            par1->erase_particle_collided_with();
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

               partic->set_coordinate(d, new_coords[d]);
            }

            //erase from old box
            for(auto box_in_box = this->boxes.begin(); box_in_box != this->boxes.end(); box_in_box++){
               for(auto box = partic->get_box_ID().begin(); box != partic->get_box_ID().end(); box++){
                  if(*box == box_in_box->get_box_id()){
                     box_in_box->remove_particles(*partic);
                  }
               }
            }

            /*
            for(auto Comp = this->boxes.begin(); Comp != this->boxes.end(); Comp++){
               std::cout <<"box: " <<Comp->get_box_id() << ' ';
               std::vector<Sphere*> &particle = Comp->get_particles();
               std::cout << Comp->get_particles().size() << " ";
            std::cout << "\n";
            }
            */

            partic->erase_box_ID(); 

            //assign to new box.
            for(auto box_in_box = this->boxes.begin(); box_in_box != this->boxes.end(); box_in_box++){
               int insert = 0;
               int a = -1;
               for(int d = 0; d < 5; d+=2){
                  if(d %2 ==0){
                     a+=1;
                  }
                  double sphere_minus_size = partic->get_coordinate(a) - partic->get_size()*0.5;
                  double sphere_plus_size = partic->get_coordinate(a) + partic->get_size()*0.5;

                  if(sphere_minus_size < 0){
                     sphere_minus_size += this->get_extension(a);
                     }

                  if(sphere_plus_size > this->get_extension(a)){
                     sphere_plus_size -= this->get_extension(a);
                     }

                  if(((box_in_box->get_extension(d) <= sphere_plus_size) && //coord_start <= particle
                  (sphere_plus_size <= box_in_box->get_extension(d+1)))||  //particle <= coord_stop
                  ((box_in_box->get_extension(d)<= sphere_minus_size) &&  //coord_start <= particle
                  (sphere_minus_size <= box_in_box->get_extension(d+1)))){ //particle <= coord_stop
                     insert += 1;
                  }
               }
               if(insert==3){
                  partic->set_box_ID(box_in_box->get_box_id());
                  box_in_box->set_particles(*partic); //set particle in small_box
               }
            }
            
            ///for debug
            /*
            for(auto Comp = this->boxes.begin(); Comp != this->boxes.end(); Comp++){
               std::cout <<"box: " <<Comp->get_box_id() << ' ';
               std::vector<Sphere*> &particle = Comp->get_particles();
               for (auto it = particle.begin(); it != particle.end(); it++){
                  Sphere * ite = *it;
                  std::cout <<"particle: " <<ite->get_particle_id() << " ";
               }
            std::cout <<"\n";
            }
            */
            
            

            int collisions_after = count_collisions();
            double probability_move  = exp(collision_before - collisions_after); // Number of collisions
            double random = (rand() % 100 + 1);
            //std::cout << probability_move << ">" << random/100;
            if(probability_move < random/100) {
               for(int d = 0; d < 3; d++){
                  partic->set_coordinate(d, temp_coord[d]);
                  //erase from old box
                  for(auto box_in_box = this->boxes.begin(); box_in_box != this->boxes.end(); box_in_box++){
                     for(auto box = partic->get_box_ID().begin(); box != partic->get_box_ID().end(); box++){
                        if(*box == box_in_box->get_box_id()){
                           box_in_box->remove_particles(*partic);
                        }
                     }
                  }
                  partic->erase_box_ID(); 

                  //assign to new box.
                  for(auto box_in_box = this->boxes.begin(); box_in_box != this->boxes.end(); box_in_box++){
                     int insert = 0;
                     int a = -1;
                     for(int d = 0; d < 5; d+=2){
                        if(d %2 ==0){
                           a+=1;
                        }
                        double sphere_minus_size = partic->get_coordinate(a) - partic->get_size()*0.5;
                        double sphere_plus_size = partic->get_coordinate(a) + partic->get_size()*0.5;

                        if(sphere_minus_size < 0){
                           sphere_minus_size += this->get_extension(a);
                           }

                        if(sphere_plus_size > this->get_extension(a)){
                           sphere_plus_size -= this->get_extension(a);
                           }

                        if(((box_in_box->get_extension(d) <= sphere_plus_size) && //coord_start <= particle
                        (sphere_plus_size <= box_in_box->get_extension(d+1)))||  //particle <= coord_stop
                        ((box_in_box->get_extension(d)<= sphere_minus_size) &&  //coord_start <= particle
                        (sphere_minus_size <= box_in_box->get_extension(d+1)))){ //particle <= coord_stop
                           insert += 1;
                        }
                     }
                     if(insert==3){
                        partic->set_box_ID(box_in_box->get_box_id());
                        box_in_box->set_particles(*partic); //set particle in small_box
                     }
                  }
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

            //find boxes.
            for(int d = 0; d < 5; d+=2){
               if(d %2 ==0){
                  a+=1;
               }
               double sphere_minus_size = partic->get_coordinate(a) - partic->get_size()*0.5;
               double sphere_plus_size = partic->get_coordinate(a) + partic->get_size()*0.5;

               
               if(sphere_minus_size < 0){
               sphere_minus_size += this->get_extension(a);
               }

               if(sphere_plus_size > this->get_extension(a)){
               sphere_plus_size -= this->get_extension(a);
               }
               

               if(((coords_for_small_box[d] <= sphere_plus_size) && //coord_start <= particle
                  (sphere_plus_size <= coords_for_small_box[d+1]))||  //particle <= coord_stop
                  ((coords_for_small_box[d]<= sphere_minus_size) &&  //coord_start <= particle
                  (sphere_minus_size <= coords_for_small_box[d+1]))){ //particle <= coord_stop
               insert += 1;
               }

            }
            if(insert==3){
               partic->set_box_ID(i);
               small.set_particles(*partic); //vector<int>& vecRef = *vecPtr //set particle in small_box //index thru vector from large box.
            }
         }
      }
      
      
      coords_for_small_box[0] += size_of_small_box[0];
      coords_for_small_box[1] += size_of_small_box[0];
      //ad small box to vector
      this->boxes.push_back(small);

   }
   
   /*
   for(auto Comp = this->boxes.begin(); Comp != this->boxes.end(); Comp++){
      std::cout <<"box: " <<Comp->get_box_id() << ' ';
      std::vector<Sphere*> &particle = Comp->get_particles();
      for (auto it = particle.begin(); it != particle.end(); it++){
         Sphere * ite = *it;
         std::cout <<"particle: " <<ite->get_particle_id() << " ";
      }
      std::cout <<"\n";
   }
   */
   
}  