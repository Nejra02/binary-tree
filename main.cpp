#include <iostream>
#include "stablo.h"
using namespace std;

int main() {

    Stablo<int> s;
    //unos elemenata u stablo s
    /*s.Insert(27);
    s.Insert(31);
    s.Insert(99);
    s.Insert(74);
    cout<<"Stablo S : "<<endl<<s<<endl<<endl;*/

    //koristimo konstruktor kopije
    /*Stablo<int> s1(s);
    s1.Insert(14);
    s1.Insert(63);
    cout<<"Stablo S1 : "<<endl<<s1<<endl<<endl;*/

    //operator dodjele
    /*Stablo<int> s2;
    s2=s1;
    s2.Insert(20);
    s2.Insert(10);
    cout<<"Stablo S2 : "<<endl<<s2<<endl<<endl;*/

    //pomjerajuci konstruktor
    //sada vise nemamo pristup stablu s2, prazno je, sve smo elemente premjestili u s3
    /*Stablo<int> s3=move(s2);
    cout<<"Stablo S3 : "<<endl<<s3<<endl<<endl;*/

    //primjeri za funkciju Find();
    //treba da vrati nema elementa
    /*int x=14;
    if(s.Find(14)) cout<<"U stablu S ima elementa "<<x<<endl;
    else cout<<"U stablu S nema elementa "<<x<<endl<<endl;
    //treba da vrati ima elementa
    x=63;
    if(s1.Find(x)) cout<<"U stablu S1 ima elementa "<<x<<endl;
    else cout<<"U stablu S1 nema elementa "<<x<<endl<<endl;*/

    //primjeri za funkciju Insert();
    Stablo<int> s4;
    s4.Insert(1000);
    s4.Insert(765);
    s4.Insert(253);
    s4.Insert(999);
    s4.Insert(22);
    s4.Insert(455);
    s4.Insert(409);
    s4.Insert(501);
    s4.Insert(888);
    cout<<"Stablo S4 : "<<endl<<s4<<endl<<endl;

    //primjer za funkciju Delete();
    // ovo je sve radjeno zajedno i ako sam u komentaru navela sta bi se trebalo zamijeniti i slicno,
    // to se upraznjava na vec prethodno obrisane vrijednosti

    // 765 nema djece
    s4.Delete(765);
    //cout<<"Stablo S4 nakon brisanja broja 765: "<<endl<<s4<<endl<<endl;
    // 409 ima jedno(lijevo) dijete
    s4.Delete(409);
    //cout<<"Stablo S4 nakon brisanja broja 409: "<<endl<<s4<<endl<<endl;
    // 999 ima jedno(desno) dijete
    s4.Delete(999);
    //cout<<"Stablo S4 nakon brisanja broja 999: "<<endl<<s4<<endl<<endl;
    s4.Insert(620);
    //888 ima dva djeteta - 620 i 1000 i u ovom slucaju mijenja 888 i 1000
    //s4.Delete(888);
    //cout<<"Stablo S4 nakon brisanja broja 888: "<<endl<<s4<<endl<<endl;
/*    //501 ima dva djeteta - 22 i 888(zakomentirano s4.Delete(888);) i u ovom slucaju treba zamijeniti 501 i 620 !! ne radi
    s4.Delete(501);
    cout<<"Stablo S4 nakon brisanja broja 501: "<<endl<<s4<<endl<<endl;
*/


    //primjer za funkciju Separate();
/*    pair<Stablo<int>,Stablo<int>> par = Separate(s4,570);
    // u ovom podstablu trebaju biti vrijednosti : 501,22,455,409,253
    cout<<"Lijevo podstablo stabla s4 po kljucu 570 : "<<endl<<par.first;
    // u ovom podstablu trebaju biti vrijednosti : 888,999,1000,765
    cout<<"Desno podstablo stabla s4 po kljucu 570 : "<<endl<<par.second;
*/


}
