#include <iostream>
#include <string>
#include <cctype>
using namespace std;
 
struct admin{
    string username, password;
};

struct karcis{
    int jamM, jamK;
    int menitM, menitK;
    int harga;
    int nomor;
}tiket[150];
        
struct kendaraan{
    string jenis;
    string platAwal, platAkhir;
    int lantai, platNomor, exit = 0;
}vehicle[150];

struct tempat{
    int lantai[3] = {1, 2, 3};
    int slot[3] = {50, 50, 50};
}parkir;

const int maxAcc = 100;
admin akun[maxAcc];
int jmlAcc = 0, jmlKendaraan = 0;
int durasiJam = 0;
bool log = false;

void mainMenu(); void login(); void regist(); void exit(); void sistemP();
void slotInfo(int l[], int s[]);
void masuk(kendaraan k[], int jK, karcis t[], int s[]);
void keluar(kendaraan k[], int jK, karcis t[], int l[], int s[]);
void ticket(); int harga(int d, string j);void dataTicket();

main(){
    if(log == false){
        mainMenu();
    }
    system("cls");
    sistemP();
}

void mainMenu(){
    system("cls");
    int pil;
    cout<<"\t\t==MAIN MENU==\n1) REGISTRATION\n2) LOGIN\n3) EXIT\n\nOPTION\t: ";
    cin>>pil;

    switch (pil){
    case 1:
        regist();
        break;
    case 2:
        login();
        break;
    case 3:
        exit();
        break;
    default:
        break;
    }
}

void login(){
    system("cls");
    string user,pass;
    cout<<"\t\t===LOGIN===\nUsername\t: ";
    cin>>user;
    cout<<"Password\t: ";
    cin>>pass;
    for (int i = 0; i < 100; i++){
        if (akun[i].username == user && akun[i].password == pass){
            cout<<"|L O G I N  S U C C E S S|\n";
            log = true;
            system("pause");main();
        }else{
            cout<<"|L O G I N  F A I L E D|\n";
            system("pause");main();
        }
    }
}

void regist(){
    system("cls");
    string user, pass;
    cout<<"\t\t===REGISTRATION===\nUsername\t: ";
    cin>>user;
    cout<<"Password\t: ";
    cin>>pass;

    for(int i = 0; i < jmlAcc; i++){
        if (akun[i].username == user){
            cout<<"USERNAME ALREADY USED";
            system("pause");mainMenu();
        }
        if (akun[i].password == pass){
            cout<<"PASSWORD ALREADY USED";
            system("pause");mainMenu();
        } 
    }
    akun[jmlAcc] = {user, pass};
    jmlAcc ++;
    cout<<"|R E G I S T R A T I O N  S U C C E S S|\n\t|PLEASE LOGIN FIRST|\n";
    system("pause");mainMenu();
}

void exit(){
    system("cls");
    cout<<"|T H A N K  Y O U|";
}

void sistemP(){
    int pil;
    system("cls");
    cout<<"\t\t===SYSTEM INFORMATION PARKING==\n1) Slot Information\n2) Vehicle Enters\n3) Vehicle Exits\n4) Data Tickets\n5) Log Out\n\nOption\t: ";
    cin>>pil;
    switch (pil){
    case 1:
        slotInfo(parkir.lantai, parkir.slot);
        break;
    case 2:
        masuk(vehicle, jmlKendaraan, tiket, parkir.slot);
        break;
    case 3:
        keluar(vehicle, jmlKendaraan, tiket, parkir.lantai, parkir.slot);
        break;
    case 4:
        dataTicket();
        break;
    case 5:
        log = false;
        main();
        break;
    default:
        system("cls");
        cout<<"PLEASE INPUT CORRECTLY!!";
        sistemP();
        break;
    }
}

void slotInfo(int l[], int s[]){
    system("cls");
    cout<<"\t\t===SLOT INFORMATION===\n";
    for (int i = 0; i < 3 ; i++)
    {
        if(i == 0){
            cout<<"Floor\t: "<<l[i]<<"\tSlot\t: "<<s[i]<<"\n";
        }else if(i == 1){
            cout<<"Floor\t: "<<l[i]<<"\tSlot\t: "<<s[i]<<"\n";
        }else if(i == 2){
            cout<<"Floor\t: "<<l[i]<<"\tSlot\t: "<<s[i]<<"\n";
        }
    }
    system("pause");system("cls");sistemP();
}

void masuk(kendaraan k[], int jK, karcis t[], int s[]){
    system("cls");
    cout<<"\t\t===VEHICLE ENTERS===";
    if(jmlKendaraan < 150){
        cout<<"\nType\t: ";
        cin>>k[jK].jenis;
        cout<<"Number Plate (XX 1234 XX)\t: ";
        cin>>k[jK].platAwal>>k[jK].platNomor>>k[jK].platAkhir;
        cout<<"Select Floor\t: ";
        cin>>k[jK].lantai;
        cout<<"Hours & Minutes\t: ";
        cin>>t[jK].jamM>>t[jK].menitM;
        t[jK].nomor = jK + 1;
        jmlKendaraan++;
        s[k[jK].lantai-1]--;
        cout<<"\t\t|S U C C E S S|";
    }else{
        cout<<"|P A R K I N G  F U L L ! !|\n\t\t|See Slot Information|\n";
    }
    system("pause"); system("cls");
    cout<<"\t\t===TICKET===";
    cout<<"\nType\t: "<<k[jK].jenis;
    cout<<"\nNumber Plate\t: "<<k[jK].platAwal<<" "<<k[jK].platNomor<<" "<<k[jK].platAkhir;
    cout<<"\nFloor\t: "<<k[jK].lantai;
    cout<<"\nEntry Time\t: "<<t[jK].jamM<<":"<<t[jK].menitM<<"\n";
    system("pause"); sistemP();
}

void keluar(kendaraan k[], int jK, karcis t[], int l[], int s[]){
    bool exit = false;
    string platAwal, platAkhir;
    int platNomor;
    system("cls");
    cout<<"\t\t===VEHICLE EXITS===\nNumber Plate\t: ";
    cin>>platAwal>>platNomor>>platAkhir;
    for(int i = 0; i < jK; i++){
        if(k[i].platAwal == platAwal && k[i].platNomor == platNomor && k[i].platAkhir == platAkhir){
            cout<<"Exit(Hours & Minutes)\t: ";
            cin>>t[i].jamK>>t[i].menitK;

            int totalMenitM = t[i].jamM * 60 + t[i].menitM;
            int totalMenitK = t[i].jamK * 60 + t[i].menitK;
            if(totalMenitK < totalMenitM){
                totalMenitK+= 24 * 60;
            }
            int durasiMenit = totalMenitK - totalMenitM;
            durasiJam = durasiMenit / 60;
            t[i].harga = harga(durasiJam, k[i].jenis);

    cout<<"\n|S U C C E S S|";
    exit = true;

            if(exit == true){
                system("pause"); system("cls");
                cout<<"\t\t===PARKING NOTE===\n";
                for(int i = 0; i < jK; i++){
                    if(k[i].platAwal == platAwal && k[i].platNomor == platNomor && k[i].platAkhir == platAkhir){
                        string jenis = k[i].jenis;
                        cout<<"Type\t: "<<k[i].jenis<<"\nNumber Plate\t: "<<k[i].platAwal<<k[i].platNomor<<k[i].platAkhir<<"\nEntry Time\t: "<<t[i].jamM<<":"<<t[i].menitM<<"\nExit Time\t: "<<t[i].jamK<<":"<<t[i].menitK<<"\nPrice\t: "<<harga(durasiJam, jenis);
                        t[i].harga = harga(durasiJam, jenis);
                        s[k[i].lantai-1]--;
                    }
                }
            }
            for(int j = i; j < jK; j++){
                k[j] = k[j + 1];
                t[j] = t[j + 1];
            }
        }
    }
    jK++;
    system("pause"); system("cls"); main();
}

int harga(int d, string j){
    if(d < 1){
        return d;
    }else{
        if(j == "Motor" || j == "motor" || j == "MOTOR"){
            return 2000 + harga(d-1, j);
        }else if(j == "Car" || j == "car" || j == "CAR"){
            return 5000 + harga(d-1, j);
        }else{
            return 10000 + harga(d-1, j);
        }
    }
}

void dataTicket(){
    system("cls");
    int i = 0, tempNomor;
    string tempAwal, tempAkhir;
    bool found = false;
    int pil;
    cout<<"==DATA TICKETS==\n1) All Tickets Information\n2) Odd Plate\n3) Even Plate\n4) Search Plate\n5) Exit";
    cout<<"\nOption\t: ";
    cin>>pil;
    switch (pil){
    case 1:
        cout<<"==ALL TICKETS INFORMATION==";
        for (int i = 0; i < jmlKendaraan; i++)
        {
            cout<<"\nNO\t: "<<tiket[i].nomor;
            cout<<"\nType\t: "<<vehicle[i].jenis;
            cout<<"\nNumber Plate\t: "<<vehicle[i].platAwal<<vehicle[i].platNomor<<vehicle[i].platAkhir;
            cout<<"\nFloor\t: "<<vehicle[i].lantai;
            cout<<"\nEntry Time\t: "<<tiket[i].jamM<<":"<<tiket[i].menitM<<"\n";
            cout<<"\nExit Time\t: "<<tiket[i].jamK<<":"<<tiket[i].menitK<<"\nPrice\t: "<<tiket[i].harga;
        }
        system("pause"); dataTicket();
        break;
    case 2:
        system("cls");
        cout<<"==ODD PLATE==\n";
        for (int i = 0; i < jmlKendaraan; i++)
        {
            if(vehicle[i].platNomor %2 == 1 ){
                cout<<vehicle[i].platAwal<<vehicle[i].platNomor<<vehicle[i].platAkhir<<"\t";
                if(i % 3 == 0) cout<<endl;
            }
        }
        system("pause");dataTicket();
        break;
    case 3:
        system("cls");
        cout<<"==EVEN PLATE==\n";
        for (int i = 0; i < jmlKendaraan; i++)
        {
            if(vehicle[i].platNomor %2 == 0 ){
                cout<<vehicle[i].platAwal<<" "<<vehicle[i].platNomor<<" "<<vehicle[i].platAkhir<<"\t";
                if(i % 3 == 0) cout<<endl;
            }
        }
        system("pause");dataTicket();
        break;
    case 4:
        system("cls");
        cout<<"==SEARCH PLATE==\nNumber Plate\t: ";
        cin>>tempAwal>>tempNomor>>tempAkhir;
        while (i < jmlKendaraan && !found)
        {
            if(vehicle[i].platAwal == tempAwal && vehicle[i].platNomor == tempNomor && vehicle[i].platAkhir == tempAkhir){
                found = true;
            }else{
                i++;
            }
        }
        if(found){
            cout<<"\nNO\t: "<<tiket[i].nomor;
            cout<<"\nType\t: "<<vehicle[i].jenis;
            cout<<"\nNumber Plate\t: "<<vehicle[i].platAwal<<vehicle[i].platNomor<<vehicle[i].platAkhir;
            cout<<"\nFloor\t: "<<vehicle[i].lantai;
            cout<<"\nEntry Time\t: "<<tiket[i].jamM<<":"<<tiket[i].menitM<<"\n";
            cout<<"\nExit Time\t: "<<tiket[i].jamK<<":"<<tiket[i].menitK<<"\nPrice\t: "<<tiket[i].harga;
            i = 0;
            system("pause");dataTicket();
        }else{
            i = 0;
            cout<<"|P L A T E  N O T  F O U N D ! !|";
            system("pause");dataTicket();
        }
        break;
    case 5:
        sistemP();
        break;
    default:
        break;
    }
}