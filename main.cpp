#include <iostream>
using namespace std;

class Verzameling{
private:
    int grootte;
    int *rij;
    int aantalIngevuld;

public:

    //gewone constructor
    Verzameling(){
        grootte = 10;
        aantalIngevuld = 0;
        rij = new int[10];
    }

    //constructor met grootte parameter
    Verzameling(int gr){
        grootte = gr;
        aantalIngevuld = 0;
        rij = new int[gr];
    }

    bool bevatGetal(int getal){
        //returnt 0 als het getal niet in de array zit
        //returnt 1 als het getal in de rij zit
        bool aanwezig = false;

        for(int i=0 ; i<aantalIngevuld; i++){
            if (rij[i] == getal){aanwezig = true;}
        }

        return aanwezig;
    }

    int pakGetalOpPlek(int i){
        return rij[i];
    }

    //destructor
    ~Verzameling(){
        //cout <<"destructor opgeroepen"<<endl;
        delete rij;
    }

    void add(int getal){
        //als aantalIngevuld < grootte-1 , dan is de rij al ingevuld, moeten we het 1tje vergroten
        if(aantalIngevuld >= grootte-1){
            //nog totaal niet zeker als dit juist is, zowieso nog aangepast
            //cout<<"de rij is te klein, het elem past er niet meer in"<<endl;
            cout<<"rij is te klein"<<endl;
            delete rij;
            //doe nog zaken, zoals maak nieuwe rij aan, kopieer alle elementen,...
        }
        else{
            //cout << "het element past der wel nog in"<<endl;
            //dus als de rij niet te klein is
            //misschien moet der hier nog sterretje ofzo
            rij[aantalIngevuld] = getal;
            aantalIngevuld ++;
        }
    }

    //output operator
    friend ostream& operator<< (ostream& os, Verzameling v);    //buiten de klasse verder afgewerkt

    //operator* overloading
    friend Verzameling operator*(Verzameling a, Verzameling b);

    //operator+ overloading
    friend Verzameling operator+(Verzameling a, Verzameling b);

    //operator+ overloading aan de hand van =/= paramters
    friend Verzameling operator+(Verzameling a, int getal);

    friend Verzameling operator+(int getal, Verzameling a);
};

ostream& operator<< (ostream& os, Verzameling v){
    cout <<"{";
    for(int i=0; i<v.aantalIngevuld ; i++){
        cout<< v.rij[i];
        if(i != v.aantalIngevuld-1){cout <<",";}
    }
    cout<<"}"<<endl;

    //return dit allemaal?
}

Verzameling operator*(Verzameling a, Verzameling b){
    Verzameling vres;

    for(int i=0; i<a.aantalIngevuld; i++){
        int getal = a.pakGetalOpPlek(i);

        if(b.bevatGetal(getal)){vres.add(getal);}
    }

    return vres;

}

Verzameling operator+(Verzameling a, Verzameling b){

    int grootte = a.grootte+b.grootte;

    Verzameling vres(grootte);

    for(int i=0; i<a.aantalIngevuld; i++){
        int getal = a.pakGetalOpPlek(i);

        vres.add(getal);
    }

    for(int j=0; j<b.aantalIngevuld; j++){
        int getal = b.pakGetalOpPlek(j);

        if(!a.bevatGetal(getal)){vres.add(getal);}
    }

    return vres;
}

Verzameling operator+(Verzameling a, int getal){
    //cout <<"de operator+  met op 2e plek een int"<<endl;

    int grootte = a.grootte+1;
    Verzameling vres(grootte);

    for(int i=0; i<a.aantalIngevuld; i++){
        int rijgetal = a.pakGetalOpPlek(i);

        vres.add(rijgetal);
    }

    vres.add(getal);

    return vres;
}

Verzameling operator+(int getal, Verzameling a){
    //cout <<"de operator+  met op 1e plek een int"<<endl;

    int grootte = a.grootte+1;
    Verzameling vres(grootte);

    vres.add(getal);

    for(int i=0 ; i<a.aantalIngevuld; i++){
        int rijgetal = a.pakGetalOpPlek(i);

        vres.add(rijgetal);
    }

    return vres;
}





int main()
{
    Verzameling v1; //default 10 plaatsen
    Verzameling v2(20); //parameter -> aantal plaatsen
    for (int i=1;i<10;i++) v1.add(i);
    for (int i=1;i<10;i++) v2.add(2*i);
    Verzameling v3 = v2;
    Verzameling v4,v5;
    v4 = v1 + v2; //unie
    v5 = v1 * v2; //doorsnede
    cout << v4 << endl; //getallen gescheiden door ,
                        //en omringd door {}
    cout << v5 << endl;

    v4 = v4 + 84; //casting
    v5 = 20 + v1;

    cout << v4 << endl;
    cout << v5 << endl;

    return 0;
}