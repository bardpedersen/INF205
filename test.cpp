#include <iostream>
#include <vector>

class test
{
    private:
    std::vector<int*> vektr;


    public:
    std::vector<int*> &get_vektor() {return this->vektr;}
    void set_vektor(int &value){
        vektr.push_back(&value);
    }

    void change_value(){
        for(auto q = *vektr.begin(); q!= *vektr.end(); q++){
            *q = 2;
        }
    }
};

int main(){
    int x = 10;
    test a;
    a.set_vektor(x);
    a.change_value();
    for(auto q = a.get_vektor().begin(); q!= a.get_vektor().end(); q++){
            std::cout << *q;
        }

}