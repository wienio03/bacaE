//Wienczyslaw Wlodyga
#include <iostream>
using namespace std;
bool compareStrings(char string1[20], char string2[20]){
    int i=0;
    int counter=0;
    while(string1[i]!='\0'||string2[i]!='\0'){
        if(string1[i]==string2[i]) counter++;
        i++;
    }
    if(counter==i) return true;
    else return false;
}
struct place{
    unsigned short towar;
    char etykieta[2];
};
struct shelf{
    place miejsca[128];
    int shelfLength=0;
};
struct rack{
    shelf polki[128];
    int rackLength=0;
};
struct warehouse{
    rack regaly[128];
    shelf handyShelf;
    int warehouseLength=0;
};
struct depot{
    warehouse magazyny[128];
    rack handyRack;
    shelf depot_handyShelf;
};
void Set_AP(int a, int b, int c, int d, depot mainDepot){
    int shelfLength_before=mainDepot.magazyny[a].regaly[b].polki[c].shelfLength;
    mainDepot.magazyny[a].regaly[b].polki[c].shelfLength=d;
    for(int i=shelfLength_before; i<d; i++){
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[i]={0,'0','0'};
    }
    for(int j=d; j<128; j++){
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[j]={0,'\0','\0'};
    }
}
void Set_AS(int a, int b, int c, int d, depot mainDepot){
    int rackLength_before=mainDepot.magazyny[a].regaly[b].rackLength;
    mainDepot.magazyny[a].regaly[b].rackLength=c;
    for(int i=rackLength_before; i<c; i++ ) {
        for (int j = 0; j < d; j++) {
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j] = {0, '0', '0'};
        }
    }
    for(int i=c; i<128; i++ ){
        for(int j=0; j<mainDepot.magazyny[a].regaly[b].polki[i].shelfLength; j++){
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j]={0,'\0','\0'};
        }
    }
    for(int i=0; i<rackLength_before; i++){
        Set_AP(a,b,i,d,mainDepot);
    }
}
void Set_AR(int a, int b, int c, int d, depot mainDepot){
    int warehouseLength_before=mainDepot.magazyny[a].warehouseLength;
    mainDepot.magazyny[a].warehouseLength=b;
}
depot sklad;
int main() {
    int wb,rb,sb,Pe,se,Se,Re;
    int w,r,s,p;
    unsigned short A;
    char input[20];
    do{
        cin >> input;
        if(compareStrings(input,"SET-AP")){
            cin >> wb >> rb >> sb >> Pe;
            Set_AP(wb,rb,sb,Pe,sklad);
        }
        if(compareStrings(input, "SET-AS")){
            cin >> wb >> rb >> se >> Pe;
            Set_AS(wb,rb,se,Pe,sklad);
        }
        if(compareStrings(input,"SET-AR")){
            cin >> wb >> Re >> Se >> Pe;
        }
        if(compareStrings(input,"PUT-W")){
            cin >> w >> r >> s >> p >> A;
            if(A>65535)A=65535;
            sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar=A;
        }
        if(compareStrings(input, "PUT-H")){
            cin >> w >> p >> A;
            if(A>65535)A=65535;
            sklad.magazyny[w].handyShelf.miejsca[p].towar=A;
        }
        if(compareStrings(input, "PUT-R")){
            cin >> s >> p >> A;
            if(A>65535)A=65535;
            sklad.handyRack.polki[s].miejsca[p].towar=A;
        }
        if(compareStrings(input, "PUT-S")){
            cin >> p >> A;
            if(A>65535)A=65535;
            sklad.depot_handyShelf.miejsca[p].towar=A;
        }
        cout << sklad.depot_handyShelf.miejsca[p].towar;
    }
    while (!compareStrings(input,"END"));
    return 0;
}
