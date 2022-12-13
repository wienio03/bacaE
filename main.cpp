//Wienczyslaw Wlodyga
#include <iostream>
using namespace std;
bool porownajNapisy(const char* napis1,const char* napis2){
    int i=0;
    int counter=0;
    while(napis1[i]!='\0'||napis2[i]!='\0'){
        if(napis1[i]==napis2[i]) counter++;
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
    int shelfLength;
};
struct rack{
    shelf polki[128];
    int rackLength;
};
struct warehouse{
    rack regaly[128];
    shelf handyShelf;
    int warehouseLength;
};
struct depot{
    warehouse magazyny[128];
    rack handyRack;
    shelf depot_handyShelf;
    int depotLength;
    long long int depotStock;
};

void Set_AP(int a, int b, int c, int d, depot& mainDepot){
    int shelfLength_before=mainDepot.magazyny[a].regaly[b].polki[c].shelfLength;
    mainDepot.magazyny[a].regaly[b].polki[c].shelfLength=d;
    for(int i=shelfLength_before; i<d; i++){
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[i].towar=0;
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[i].etykieta[0]='\0';
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[i].etykieta[1]='\0';

    }
    for(int j=d; j<128; j++){
        mainDepot.depotStock-=mainDepot.magazyny[a].regaly[b].polki[c].miejsca[j].towar;
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[j].towar=0;
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[j].etykieta[0]='\0';
        mainDepot.magazyny[a].regaly[b].polki[c].miejsca[j].etykieta[1]='\0';
    }
}
void Set_APHR(int a, int b, depot& mainDepot){
    int shelfLength_before=mainDepot.handyRack.polki[a].shelfLength;
    mainDepot.handyRack.polki[a].shelfLength=b;
    for(int i=shelfLength_before; i<b; i++){
        mainDepot.handyRack.polki[a].miejsca[b].towar=0;
        mainDepot.handyRack.polki[a].miejsca[b].etykieta[0]='\0';
        mainDepot.handyRack.polki[a].miejsca[b].etykieta[1]='\0';
    }
    for(int j=b; j<128; j++){
        mainDepot.depotStock-=mainDepot.handyRack.polki[a].miejsca[b].towar;
        mainDepot.handyRack.polki[a].miejsca[b].towar=0;
        mainDepot.handyRack.polki[a].miejsca[b].etykieta[0]='\0';
        mainDepot.handyRack.polki[a].miejsca[b].etykieta[1]='\0';
    }
}
void Set_AS(int a, int b, int c, int d, depot& mainDepot){
    int rackLength_before=mainDepot.magazyny[a].regaly[b].rackLength;
    mainDepot.magazyny[a].regaly[b].rackLength=c;
    for (int i = rackLength_before; i < c; i++) {
        mainDepot.magazyny[a].regaly[b].polki[i].shelfLength = d;
        for (int j = 0; j < d; j++) {
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].towar = 0;
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].etykieta[0] = '\0';
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].etykieta[1] = '\0';
        }
    }
    for(int i=c; i<rackLength_before; i++ ){
        for(int j=0; j<128; j++){
            mainDepot.depotStock-=mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].towar;
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].towar=0;
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].etykieta[0]='\0';
            mainDepot.magazyny[a].regaly[b].polki[i].miejsca[j].etykieta[1]='\0';
        }
    }
    if(rackLength_before<c) {
        for (int i = 0; i < rackLength_before; i++) {
            Set_AP(a, b, i, d, mainDepot);
        }
    }
    else{
        for (int i = 0; i < c; i++) {
            Set_AP(a, b, i, d, mainDepot);
        }
    }
}
void Set_AR(int a, int b, int c, int d, depot& mainDepot){
    int warehouseLength_before=mainDepot.magazyny[a].warehouseLength;
    mainDepot.magazyny[a].warehouseLength=b;
    for(int i=warehouseLength_before; i<b; i++){
        mainDepot.magazyny[a].regaly[i].rackLength=c;
        for(int j=0; j<c; j++){
            mainDepot.magazyny[a].regaly[i].polki[j].shelfLength=d;
            for(int k=0; k<d; k++){
                mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].towar=0;
                mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].etykieta[0]='\0';
                mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].etykieta[1]='\0';

            }
        }
    }
    for(int i=b; i<warehouseLength_before; i++){
        for(int j=0; j<128; j++){
            for(int k=0; k<128; k++){
                mainDepot.depotStock-=mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].towar;
                mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].towar=0;
                mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].etykieta[0]='\0';
                mainDepot.magazyny[a].regaly[i].polki[j].miejsca[k].etykieta[1]='\0';
            }
        }
    }
    if(warehouseLength_before<b){
        for(int i=0; i<warehouseLength_before; i++){
            Set_AS(a,i,c,d,mainDepot);
        }
    }
    else{
        for(int i=0; i<b; i++){
            Set_AS(a,i,c,d,mainDepot);
        }
    }
}
void Set_AW(int a, int b, int c, int d, depot& mainDepot){
    int depotLength_before=mainDepot.depotLength;
    mainDepot.depotLength=a;
    for(int i=depotLength_before; i<a; i++){
        mainDepot.magazyny[i].warehouseLength=b;
        for(int j=0; j<b; j++){
            mainDepot.magazyny[i].regaly[j].rackLength=c;
            for(int k=0; k<c; k++){
                mainDepot.magazyny[i].regaly[j].polki[k].shelfLength=d;
                for(int l=0; l<d; l++){
                    mainDepot.magazyny[i].regaly[j].polki[k].miejsca[l].towar=0;
                    mainDepot.magazyny[i].regaly[j].polki[k].miejsca[l].etykieta[0]='\0';
                    mainDepot.magazyny[i].regaly[j].polki[k].miejsca[l].etykieta[1]='\0';
                }
            }
        }
    }
    for(int i=a; i<depotLength_before; i++){
        for(int j=0; j<128; j++){
            for(int k=0; k<128; k++){
                for(int l=0; l<128; l++){
                    mainDepot.depotStock-= mainDepot.magazyny[i].regaly[j].polki[k].miejsca[l].towar;
                    mainDepot.magazyny[i].regaly[j].polki[k].miejsca[l].towar=0;
                    mainDepot.magazyny[i].regaly[j].polki[k].miejsca[k].etykieta[0]='\0';
                    mainDepot.magazyny[i].regaly[j].polki[k].miejsca[k].etykieta[1]='\0';

                }
            }
        }
    }
    if(depotLength_before<a){
        for(int i=0; i<depotLength_before; i++){
            Set_AR(i,b,c,d,mainDepot);
        }
    }
    else{
        for(int i=0; i<a; i++){
            Set_AR(i,b,c,d,mainDepot);
        }
    }
}
void Set_HW(int a, int b, depot& mainDepot){
    int handyShelf_length_before=mainDepot.magazyny[a].handyShelf.shelfLength;
    mainDepot.magazyny[a].handyShelf.shelfLength=b;
    for(int i=handyShelf_length_before; i<b; i++){
        mainDepot.magazyny[a].handyShelf.miejsca[i].towar=0;
        mainDepot.magazyny[a].handyShelf.miejsca[i].etykieta[0]='\0';
        mainDepot.magazyny[a].handyShelf.miejsca[i].etykieta[1]='\0';

    }
    for(int i=b; i<128; i++){
        mainDepot.depotStock-=mainDepot.magazyny[a].handyShelf.miejsca[i].towar;
        mainDepot.magazyny[a].handyShelf.miejsca[i].towar=0;
        mainDepot.magazyny[a].handyShelf.miejsca[i].etykieta[0]='\0';
        mainDepot.magazyny[a].handyShelf.miejsca[i].etykieta[1]='\0';
    }
}
void Set_HR(int a, int b, depot& mainDepot){
    int handyRack_length_before=mainDepot.handyRack.rackLength;
    mainDepot.handyRack.rackLength=a;
        for (int i = handyRack_length_before; i < a; i++) {
            mainDepot.handyRack.polki[i].shelfLength = b;
            for (int j = 0; j < b; j++) {
                mainDepot.handyRack.polki[i].miejsca[j].towar = 0;
                mainDepot.handyRack.polki[i].miejsca[j].etykieta[0] = '\0';
                mainDepot.handyRack.polki[i].miejsca[j].etykieta[1] = '\0';
            }
        }

    for (int i=a; i<128; i++){
        for (int j=0; j<128; j++){
            mainDepot.depotStock-= mainDepot.handyRack.polki[i].miejsca[j].towar;
            mainDepot.handyRack.polki[i].miejsca[j].towar=0;
            mainDepot.handyRack.polki[i].miejsca[j].etykieta[0]='\0';
            mainDepot.handyRack.polki[i].miejsca[j].etykieta[1]='\0';
        }
    }
    if(handyRack_length_before<a){
        for(int i=0; i<handyRack_length_before; i++){
            Set_APHR(i,b,mainDepot);
        }
    }
    else {
        for(int i=0; i<a; i++){
            Set_APHR(i,b,mainDepot);
        }
    }
}
void Set_HS(int a, depot& mainDepot) {
    int depot_handyShelf_length_before = mainDepot.depot_handyShelf.shelfLength;
    mainDepot.depot_handyShelf.shelfLength = a;
        for (int i = depot_handyShelf_length_before; i < a; i++) {
            mainDepot.depot_handyShelf.miejsca[i].towar = 0;
            mainDepot.depot_handyShelf.miejsca[i].etykieta[0] = '\0';
            mainDepot.depot_handyShelf.miejsca[i].etykieta[1] = '\0';
        }
    for (int i = a; i < 128; i++) {
        mainDepot.depotStock-=mainDepot.depot_handyShelf.miejsca[i].towar;
        mainDepot.depot_handyShelf.miejsca[i].towar = 0;
        mainDepot.depot_handyShelf.miejsca[i].etykieta[0] = '\0';
        mainDepot.depot_handyShelf.miejsca[i].etykieta[1] = '\0';
    }
}
depot sklad;
int main() {
    int wb, rb, sb, Pe, we, re, se, Se, Re, We;
    int w, r, s, p;
    int R, S, W, P;
    int A;
    char input[40];
    do {
        cin >> input;
        //FILL
        if (porownajNapisy(input, "FILL")) {
            cin >> W >> R >> S >> P >> A;
            if (W > 128 || R > 128 || S > 128 || P > 128) cout << "error" << endl;
            else {
                if (W == 0) sklad.depotLength = 0;
                if (S == 0) sklad.handyRack.rackLength = 0;
                if (P == 0) sklad.depot_handyShelf.shelfLength = 0;
                sklad.depotLength = W;
                sklad.depot_handyShelf.shelfLength = P;
                sklad.handyRack.rackLength = S;
                if (A > 65535)A = 65535;
                for (int i = 0; i < W; i++) {
                    sklad.magazyny[i].warehouseLength = R;
                    for (int j = 0; j < R; j++) {
                        sklad.magazyny[i].regaly[j].rackLength = S;
                        for (int k = 0; k < S; k++) {
                            sklad.magazyny[i].regaly[j].polki[k].shelfLength = P;
                            sklad.magazyny[i].handyShelf.shelfLength = P;
                            sklad.handyRack.polki[k].shelfLength = P;
                            for (int l = 0; l < P; l++) {
                                if (i == 0 & j == 0) {
                                    sklad.depotStock+=A;
                                    sklad.handyRack.polki[k].miejsca[l].towar = A;
                                    sklad.handyRack.polki[k].miejsca[l].etykieta[0] = '\0';
                                    sklad.handyRack.polki[k].miejsca[l].etykieta[1] = '\0';
                                }
                                if (i == 0 && j == 0 & k == 0) {
                                    sklad.depotStock+=A;
                                    sklad.depot_handyShelf.miejsca[l].towar = A;
                                    sklad.depot_handyShelf.miejsca[l].etykieta[0] = '\0';
                                    sklad.depot_handyShelf.miejsca[l].etykieta[1] = '\0';
                                }
                                if (j == 0 & k == 0) {
                                    sklad.depotStock+=A;
                                    sklad.magazyny[i].handyShelf.miejsca[l].towar = A;
                                    sklad.magazyny[i].handyShelf.miejsca[l].etykieta[0] = '\0';
                                    sklad.magazyny[i].handyShelf.miejsca[l].etykieta[1] = '\0';
                                }
                                sklad.depotStock+=A;
                                sklad.magazyny[i].regaly[j].polki[k].miejsca[l].towar = A;
                                sklad.magazyny[i].regaly[j].polki[k].miejsca[l].etykieta[0] = '\0';
                                sklad.magazyny[i].regaly[j].polki[k].miejsca[l].etykieta[1] = '\0';
                            }
                        }
                    }
                }
                for (int i = W; i < 128; i++) {
                    sklad.magazyny[i].handyShelf.shelfLength = 0;
                    sklad.magazyny[i].warehouseLength = 0;
                    for (int j = R; j < 128; j++) {
                        sklad.magazyny[i].regaly[j].rackLength = 0;
                        for (int k = S; k < 128; k++) {
                            sklad.magazyny[i].regaly[j].polki[k].shelfLength = 0;
                            for (int l = P; l < 128; l++) {
                                if (j == R && k == S) {
                                    sklad.depotStock-= sklad.magazyny[i].handyShelf.miejsca[l].towar;
                                    sklad.magazyny[i].handyShelf.miejsca[l].towar = 0;
                                    sklad.magazyny[i].handyShelf.miejsca[l].etykieta[0] = '\0';
                                    sklad.magazyny[i].handyShelf.miejsca[l].etykieta[1] = '\0';
                                }
                                if (i == W && j == R) {
                                    sklad.depotStock-=sklad.handyRack.polki[k].miejsca[l].towar;
                                    sklad.handyRack.polki[k].miejsca[l].towar = 0;
                                    sklad.handyRack.polki[k].miejsca[l].etykieta[0] = '\0';
                                    sklad.handyRack.polki[k].miejsca[l].etykieta[1] = '\0';
                                }
                                if (i == W && j == R && k == S) {
                                    sklad.depotStock-=sklad.depot_handyShelf.miejsca[l].towar;
                                    sklad.depot_handyShelf.miejsca[l].towar = 0;
                                    sklad.depot_handyShelf.miejsca[l].etykieta[0] = '\0';
                                    sklad.depot_handyShelf.miejsca[l].etykieta[1] = '\0';
                                }
                                sklad.depotStock-=sklad.magazyny[i].regaly[j].polki[k].miejsca[l].towar;
                                sklad.magazyny[i].regaly[j].polki[k].miejsca[l].towar = 0;
                                sklad.magazyny[i].regaly[j].polki[k].miejsca[l].etykieta[0] = '\0';
                                sklad.magazyny[i].regaly[j].polki[k].miejsca[l].etykieta[1] = '\0';
                            }
                        }
                    }
                }
            }
        }
        //SETY
        if (porownajNapisy(input, "SET-AP")) {
            cin >> wb >> rb >> sb >> Pe;
            if (wb >= sklad.depotLength || rb >= sklad.magazyny[wb].warehouseLength ||
                sb >= sklad.magazyny[wb].regaly[rb].rackLength || Pe > 128)
                cout << "error" << endl;
            else if (wb > 127 || rb > 127 || sb > 127 || Pe > 128) cout << "error" << endl;
            else Set_AP(wb, rb, sb, Pe, sklad);
        }
        if (porownajNapisy(input, "SET-AS")) {
            cin >> wb >> rb >> Se >> Pe;
            if (wb >= sklad.depotLength || rb >= sklad.magazyny[wb].warehouseLength || Se > 128 || Pe > 128)
                cout << "error" << endl;
            else Set_AS(wb, rb, Se, Pe, sklad);
        }
        if (porownajNapisy(input, "SET-AR")) {
            cin >> wb >> Re >> Se >> Pe;
            if (wb >= sklad.depotLength || Re > 128 || Se > 128 || Pe > 128) cout << "error" << endl;
            else Set_AR(wb, Re, Se, Pe, sklad);
        }
        if (porownajNapisy(input, "SET-AW")) {
            cin >> We >> Re >> Se >> Pe;
            if (We > 128 || Re > 128 || Se > 128 || Pe > 128) cout << "error" << endl;
            else Set_AW(We, Re, Se, Pe, sklad);
        }
        if (porownajNapisy(input, "SET-HW")) {
            cin >> w >> P;
            if (w >= sklad.depotLength || P > 128) cout << "error" << endl;
            else Set_HW(w, P, sklad);
        }
        if (porownajNapisy(input, "SET-HR")) {
            cin >> S >> P;
            if (S > 128 || P > 128) cout << "error" << endl;
            else Set_HR(S, P, sklad);
        }
        if (porownajNapisy(input, "SET-HS")) {
            cin >> P;
            if (P > 128) cout << "error" << endl;
            else Set_HS(P, sklad);
        }
        if (porownajNapisy(input, "PUT-W")) {
            cin >> w >> r >> s >> p >> A;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                s >= sklad.magazyny[w].regaly[r].rackLength || p >= sklad.magazyny[w].regaly[r].polki[s].shelfLength)
                cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].warehouseLength == 0 ||
                     sklad.magazyny[w].regaly[r].rackLength == 0 ||
                     sklad.magazyny[w].regaly[r].polki[s].shelfLength == 0)
                cout << "error" << endl;
            else {
                if (A > 65535)A = 65535;
                else if (A + sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar > 65535)
                    A = 65535 - sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar;
                sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar += A;
                sklad.depotStock+=A;
            }
        }
        if (porownajNapisy(input, "PUT-H")) {
            cin >> w >> p >> A;
            if (w >= sklad.depotLength || p >= sklad.magazyny[w].handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].handyShelf.shelfLength == 0) cout << "error" << endl;
            else {
                if (A + sklad.magazyny[w].handyShelf.miejsca[p].towar > 65535)
                    A = 65535 - sklad.magazyny[w].handyShelf.miejsca[p].towar;
                else if (A > 65535)A = 65535;
                sklad.magazyny[w].handyShelf.miejsca[p].towar += A;
                sklad.depotStock+=A;
            }
        }
        if (porownajNapisy(input, "PUT-R")) {
            cin >> s >> p >> A;
            if (s >= sklad.handyRack.rackLength || p >= sklad.handyRack.polki[p].shelfLength) cout << "error" << endl;
            else if (sklad.handyRack.rackLength == 0 || sklad.handyRack.polki[p].shelfLength == 0)
                cout << "error" << endl;
            else {
                if (A > 65535)A = 65535;
                else if (A + sklad.handyRack.polki[s].miejsca[p].towar > 65535)
                    A = 65535 - sklad.handyRack.polki[s].miejsca[p].towar;
                sklad.handyRack.polki[s].miejsca[p].towar += A;
                sklad.depotStock+=A;
            }
        }

        if (porownajNapisy(input, "PUT-S")) {
            cin >> p >> A;
            if (p >= sklad.depot_handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depot_handyShelf.shelfLength == 0) cout << "error" << endl;
            else {
                if (A > 65535)A = 65535;
                else if (A + sklad.depot_handyShelf.miejsca[p].towar > 65535)
                    A = 65535 - sklad.depot_handyShelf.miejsca[p].towar;
                sklad.depot_handyShelf.miejsca[p].towar += A;
                sklad.depotStock+=A;
            }
        }
        //POP
        if (porownajNapisy(input, "POP-W")) {
            cin >> w >> r >> s >> p >> A;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                s >= sklad.magazyny[w].regaly[r].rackLength || p >= sklad.magazyny[w].regaly[r].polki[s].shelfLength)
                cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].warehouseLength == 0 ||
                     sklad.magazyny[w].regaly[r].rackLength == 0 ||
                     sklad.magazyny[w].regaly[r].polki[s].shelfLength == 0)
                cout << "error" << endl;
            else {
                if (sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar < A)
                    A = sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar;
                sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar -= A;
                sklad.depotStock-=A;
            }
        }
        if (porownajNapisy(input, "POP-H")) {
            cin >> w >> p >> A;
            if (w >= sklad.depotLength || p >= sklad.magazyny[w].handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].handyShelf.shelfLength == 0) cout << "error" << endl;
            else {
                if (sklad.magazyny[w].handyShelf.miejsca[p].towar < A)A = sklad.magazyny[w].handyShelf.miejsca[p].towar;
                sklad.magazyny[w].handyShelf.miejsca[p].towar -= A;
                sklad.depotStock-=A;
            }
        }
        if (porownajNapisy(input, "POP-R")) {
            cin >> s >> p >> A;
            if (s >= sklad.handyRack.rackLength || p >= sklad.handyRack.polki[s].shelfLength) cout << "error" << endl;
            else if (sklad.handyRack.rackLength == 0 || sklad.handyRack.polki[s].shelfLength == 0)
                cout << "error" << endl;
            else {
                if (sklad.handyRack.polki[s].miejsca[p].towar < A)A = sklad.handyRack.polki[s].miejsca[p].towar;
                sklad.handyRack.polki[s].miejsca[p].towar -= A;
                sklad.depotStock-=A;
            }
        }
        if (porownajNapisy(input, "POP-S")) {
            cin >> p >> A;
            if (p >= sklad.depot_handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depot_handyShelf.shelfLength == 0) cout << "error" << endl;
            else {
                if (sklad.depot_handyShelf.miejsca[p].towar < A)A = sklad.depot_handyShelf.miejsca[p].towar;
                sklad.depot_handyShelf.miejsca[p].towar -= A;
                sklad.depotStock-=A;
            }
        }
        //ETYKIETY
        if (porownajNapisy(input, "SET-LW")) {
            cin >> w >> r >> s >> p;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                s >= sklad.magazyny[w].regaly[r].rackLength || p >= sklad.magazyny[w].regaly[r].polki[s].shelfLength)
                cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].warehouseLength == 0 ||
                     sklad.magazyny[w].regaly[r].rackLength == 0 ||
                     sklad.magazyny[w].regaly[r].polki[s].shelfLength == 0)
                cout << "error" << endl;
            else cin >> sklad.magazyny[w].regaly[r].polki[s].miejsca[p].etykieta;
        }
        if (porownajNapisy(input, "SET-LH")) {
            cin >> w >> p;
            if (w >= sklad.depotLength || p >= sklad.magazyny[w].handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].handyShelf.shelfLength == 0) cout << "error" << endl;
            else cin >> sklad.magazyny[w].handyShelf.miejsca[p].etykieta;
        }
        if (porownajNapisy(input, "SET-LR")) {
            cin >> s >> p;
            if (s >= sklad.handyRack.rackLength || p >= sklad.handyRack.polki[s].shelfLength) cout << "error" << endl;
            else if (sklad.handyRack.rackLength == 0 || sklad.handyRack.polki[s].shelfLength == 0)
                cout << "error" << endl;
            else cin >> sklad.handyRack.polki[s].miejsca[p].etykieta;
        }
        if (porownajNapisy(input, "SET-LS")) {
            cin >> p;
            if (p >= sklad.depot_handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depot_handyShelf.shelfLength == 0) cout << "error" << endl;
            else cin >> sklad.depot_handyShelf.miejsca[p].etykieta;
        }
        if (porownajNapisy(input, "GET-LW")) {
            cin >> w >> r >> s >> p;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                s >= sklad.magazyny[w].regaly[r].rackLength || p >= sklad.magazyny[w].regaly[r].polki[s].shelfLength)
                cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].warehouseLength == 0 ||
                     sklad.magazyny[w].regaly[r].rackLength == 0 ||
                     sklad.magazyny[w].regaly[r].polki[s].shelfLength == 0)
                cout << "error" << endl;
            else {
                int counter = 0;
                for (int i = 0; i < 2; i++) {
                    if (sklad.magazyny[w].regaly[r].polki[s].miejsca[p].etykieta[i] == '\0')counter++;
                }
                if (counter == 2) {
                    cout << "--" << endl;
                } else {
                    for (int i = 0; i < 2; i++) {
                        cout << sklad.magazyny[w].regaly[r].polki[s].miejsca[p].etykieta[i];
                    }
                    cout << endl;
                }
            }
        }
        if (porownajNapisy(input, "GET-LH")) {
            cin >> w >> p;
            if (w >= sklad.depotLength || p >= sklad.magazyny[w].handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].handyShelf.shelfLength == 0) cout << "error" << endl;
            else {
                int counter = 0;
                for (int i = 0; i < 2; i++) {
                    if (sklad.magazyny[w].handyShelf.miejsca[p].etykieta[i] == '\0')counter++;
                }
                if (counter == 2) {
                    cout << "--" << endl;
                } else {
                    for (int i = 0; i < 2; i++) {
                        cout << sklad.magazyny[w].handyShelf.miejsca[p].etykieta[i];
                    }
                    cout << endl;
                }
            }
        }
        if (porownajNapisy(input, "GET-LR")) {
            cin >> s >> p;
            if (s >= sklad.handyRack.rackLength || p >= sklad.handyRack.polki[s].shelfLength) cout << "error" << endl;
            else if (sklad.handyRack.rackLength == 0 || sklad.handyRack.polki[s].shelfLength == 0)
                cout << "error" << endl;
            else {
                int counter = 0;
                for (int i = 0; i < 2; i++) {
                    if (sklad.handyRack.polki[s].miejsca[p].etykieta[i] == '\0')counter++;
                }
                if (counter == 2) {
                    cout << "--" << endl;
                } else {
                    for (int i = 0; i < 2; i++) {
                        cout << sklad.handyRack.polki[s].miejsca[p].etykieta[i];
                    }
                    cout << endl;
                }
            }
        }
        if (porownajNapisy(input, "GET-LS")) {
            cin >> p;
            if (p >= sklad.depot_handyShelf.shelfLength) cout << "error" << endl;
            else if (sklad.depot_handyShelf.shelfLength == 0) cout << "error" << endl;
            else {
                int counter = 0;
                for (int i = 0; i < 2; i++) {
                    if (sklad.depot_handyShelf.miejsca[p].etykieta[i] == '\0')counter++;
                }
                if (counter == 2) {
                    cout << "--" << endl;
                } else {
                    for (int i = 0; i < 2; i++) {
                        cout << sklad.depot_handyShelf.miejsca[p].etykieta[i];
                    }
                    cout << endl;
                }
            }
        }
        //GETY WYSWIETLANIE
        if (porownajNapisy(input, "GET-E")) {
           cout << sklad.depotStock << endl;
        }
        if (porownajNapisy(input, "GET-W")) {
            cin >> w;
            long long int sumaMagazynu = 0;
            if (w >= sklad.depotLength) cout << "error" << endl;
            else if (sklad.depotLength == 0) cout << "error" << endl;
            else {
                if (sklad.magazyny[w].warehouseLength==0) {
                    for(int i=0; i<sklad.magazyny[w].handyShelf.shelfLength; i++){
                        sumaMagazynu+=sklad.magazyny[w].handyShelf.miejsca[i].towar;
                    }
                }
                else {
                    {
                        for (int i = 0; i < sklad.magazyny[w].warehouseLength; i++) {
                            for (int j = 0; j < sklad.magazyny[w].regaly[i].rackLength; j++) {
                                for (int k = 0; k < sklad.magazyny[w].regaly[i].polki[j].shelfLength; k++) {
                                    sumaMagazynu += sklad.magazyny[w].regaly[i].polki[j].miejsca[k].towar;
                                    if (i == 0 && j == 0)sumaMagazynu += sklad.magazyny[w].handyShelf.miejsca[k].towar;
                                }
                            }
                        }

                    }

                    cout << sumaMagazynu << endl;
                }
            }
        }
        if (porownajNapisy(input, "GET-RW")) {
            cin >> w >> r;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength) cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].warehouseLength == 0) cout << "error" << endl;
            else {
                long long int sumaRegalu = 0;
                for (int i = 0; i < sklad.magazyny[w].regaly[r].rackLength; i++) {
                    for (int j = 0; j < sklad.magazyny[w].regaly[r].polki[i].shelfLength; j++) {
                        sumaRegalu += sklad.magazyny[w].regaly[r].polki[i].miejsca[j].towar;
                    }
                }
                cout << sumaRegalu << endl;
            }
        }
        if (porownajNapisy(input, "GET-SW")) {
            cin >> w >> r >> s;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                s >= sklad.magazyny[w].regaly[r].rackLength)
                cout << "error" << endl;
            else if (sklad.depotLength == 0 || sklad.magazyny[w].warehouseLength == 0 ||
                     sklad.magazyny[w].regaly[r].rackLength == 0)
                cout << "error" << endl;
            else {
                long long int sumaPolki = 0;
                for (int i = 0; i < sklad.magazyny[w].regaly[r].polki[s].shelfLength; i++) {
                    sumaPolki += sklad.magazyny[w].regaly[r].polki[s].miejsca[i].towar;
                }
                cout << sumaPolki << endl;
            }
        }
        if (porownajNapisy(input, "GET-RH")) {
            int handy_sumaRegalu = 0;
            for (int i = 0; i < sklad.handyRack.rackLength; i++) {
                for (int j = 0; j < sklad.handyRack.polki[i].shelfLength; j++) {
                    handy_sumaRegalu += sklad.handyRack.polki[i].miejsca[j].towar;
                }
            }
            cout << handy_sumaRegalu << endl;
        }
        if (porownajNapisy(input, "GET-SH")) {
            cin >> w;
            if (w >= sklad.depotLength)cout << "error" << endl;
            else if (sklad.depotLength == 0)cout << "error" << endl;
            else {
                {
                    long long int handy_sumaPolki = 0;
                    for (int i = 0; i < sklad.magazyny[w].handyShelf.shelfLength; i++) {
                        handy_sumaPolki += sklad.magazyny[w].handyShelf.miejsca[i].towar;
                    }
                    cout << handy_sumaPolki << endl;
                }
            }
        }
        if (porownajNapisy(input, "GET-SR")) {
            cin >> s;
            if (s >= sklad.handyRack.rackLength) cout << "error" << endl;
            else if (sklad.handyRack.rackLength == 0) cout << "error" << endl;
            else {
                long long int handy_sumaRegalu = 0;
                for (int j = 0; j < sklad.handyRack.polki[s].shelfLength; j++) {
                    handy_sumaRegalu += sklad.handyRack.polki[s].miejsca[j].towar;
                }
                cout << handy_sumaRegalu << endl;
            }
        }
        if (porownajNapisy(input, "GET-S")) {
            long long int handy_sumaPolki_sklad = 0;
            for (int i = 0; i < sklad.depot_handyShelf.shelfLength; i++) {
                handy_sumaPolki_sklad += sklad.depot_handyShelf.miejsca[i].towar;
            }
            cout << handy_sumaPolki_sklad << endl;
        }
        if (porownajNapisy(input, "MOV-W")) {
            cin >> wb >> rb >> sb >> we >> re >> se >> p >> A;
            if (wb >= sklad.depotLength || rb >= sklad.magazyny[wb].warehouseLength ||
                sb >= sklad.magazyny[wb].regaly[rb].rackLength || we >= sklad.depotLength ||
                re >= sklad.magazyny[we].warehouseLength || se >= sklad.magazyny[wb].regaly[rb].rackLength ||
                p >= sklad.magazyny[wb].regaly[rb].polki[sb].shelfLength ||
                p >= sklad.magazyny[we].regaly[re].polki[se].shelfLength)
                cout << "error" << endl;
            else {
                if (A + sklad.magazyny[we].regaly[re].polki[se].miejsca[p].towar > 65535)
                    A = 65535 - sklad.magazyny[we].regaly[re].polki[se].miejsca[p].towar;
                else if (A > sklad.magazyny[wb].regaly[rb].polki[sb].miejsca[p].towar)
                    A = sklad.magazyny[wb].regaly[rb].polki[sb].miejsca[p].towar;
                sklad.magazyny[wb].regaly[rb].polki[sb].miejsca[p].towar -= A;
                sklad.magazyny[we].regaly[re].polki[se].miejsca[p].towar += A;
            }
        }
        if (porownajNapisy(input, "MOV-H")) {
            cin >> w >> r >> s >> p >> A;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                s >= sklad.magazyny[w].regaly[r].rackLength || p >= sklad.magazyny[w].regaly[r].polki[s].shelfLength ||
                p >= sklad.magazyny[w].handyShelf.shelfLength)
                cout << "error" << endl;
            else {
                if (A + sklad.magazyny[w].handyShelf.miejsca[p].towar > 65535)
                    A = 65535 - sklad.magazyny[w].handyShelf.miejsca[p].towar;
                else if (A > sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar)
                    A = sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar;
                sklad.magazyny[w].regaly[r].polki[s].miejsca[p].towar -= A;
                sklad.magazyny[w].handyShelf.miejsca[p].towar += A;
            }
        }
        if (porownajNapisy(input, "MOV-R")) {
            cin >> w >> r >> sb >> se >> p >> A;
            if (w >= sklad.depotLength || r >= sklad.magazyny[w].warehouseLength ||
                sb >= sklad.magazyny[w].regaly[r].rackLength || se >= sklad.handyRack.rackLength ||
                p >= sklad.magazyny[w].regaly[r].polki[sb].shelfLength ||
                p >= sklad.handyRack.polki[se].shelfLength)
                cout << "error" << endl;
            else {
                if (A + sklad.handyRack.polki[se].miejsca[p].towar > 65535)
                    A = 65535 - sklad.handyRack.polki[se].miejsca[p].towar;
                else if (A > sklad.magazyny[w].regaly[r].polki[sb].miejsca[p].towar)
                    A = sklad.magazyny[w].regaly[r].polki[sb].miejsca[p].towar;
                sklad.magazyny[w].regaly[r].polki[sb].miejsca[p].towar -= A;
                sklad.handyRack.polki[se].miejsca[p].towar += A;
            }
        }
        if (porownajNapisy(input, "MOV-S")) {
            cin >> s >> p >> A;
            if (s >= sklad.handyRack.rackLength || p >= sklad.depot_handyShelf.shelfLength ||
                p >= sklad.handyRack.polki[s].shelfLength)
                cout << "error" << endl;
            else {
                if (A + sklad.depot_handyShelf.miejsca[p].towar) A = 65535 - sklad.depot_handyShelf.miejsca[p].towar;
                else if (A > sklad.handyRack.polki[s].miejsca[p].towar)A = sklad.handyRack.polki[s].miejsca[p].towar;
                sklad.handyRack.polki[s].miejsca[p].towar -= A;
                sklad.depot_handyShelf.miejsca[p].towar += A;
            }
        }
    } while (!porownajNapisy(input, "END"));
    return 0;
}