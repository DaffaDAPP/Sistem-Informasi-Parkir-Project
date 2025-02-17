#include <iostream>
using namespace std;

void mainMenu();

main(){
    struct tempat{
        int lantai[3];
        int slot[50];
    }parkir;
    
    struct karcis{
        int jam;
        int menit;
        int harga;
    }tiket[150];
    
    struct kendaraan{
        string jenis;
        string plat;
    }vehicle[150];
    
}

void mainMenu(){
     cout<<"\t\t==LOGIN==\n1) REGISTRATION\n2) LOGIN\n3) EXIT\n\nOPTION\t: ";
}