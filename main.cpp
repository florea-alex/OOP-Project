#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list> //Pentru listele din STL
#include <vector> //Pentru vectorii din STL
#include <set> //Pentru multimile din STL
#include <map> //Pentru map-urile din STL
#include <iterator>
#include <iomanip> //Folosim manipulatorul sa afisam salariile de la clasa abstracta cu 2 zecimale
using namespace std;
ifstream f("Cabinet.in");
ofstream g("Cabinet.out");

//Interfata - clasa AnulNasterii -> O vom folosi pentru clasa Medic si clasa Pacient
class AnulNasterii{
public:
    virtual void AnNastere()=0; //Vom alege implicit anul 2021
};

//Clasa pacient - prima clasa - CODUL 1
class Pacient:public AnulNasterii{
protected:
    char *nume;
    string  prenume;
    char initiala_tata;
    int varsta;
    float inaltime;
    double greutate;
    const int id_pacient;
    bool asigurat; //Daca pacientul e asigurat vom avea valoarea True, daca nu e vom avea valoarea False
    int nr_afectiuni; //Cate afectiuni are un pacient
    string *afectiuni; //Afectiunile pe care le are un pacient
    int *perioada_afectiunii; //Vom tine minte in ani de cand un pacient are fiecare afectiune

public:
    static int nr_id;

    Pacient();
    Pacient (char *nume, string prenume); //Constructor_fara_toti_parametrii
    Pacient (char *nume, string prenume, char initiala_tata, int varsta, float inaltime, double greutate,
             bool asigurat, int nr_afectiuni, string *afectiuni, int *perioada_afectiunii); //Constructor_cu_toti_parametrii
    ~Pacient();
    Pacient (const Pacient& p);

    Pacient& operator=(const Pacient& p); //Operator=
    friend istream& operator>>(istream& in, Pacient& p); //Operator>>
    friend ostream& operator<<(ostream& out, const Pacient& p); //Operator<<
    const Pacient operator++ (int); //Postfixare pentru varsta
    const Pacient operator-- (int); //Postfixare pentru greutate cu --
    //const Pacient operator++ (float); //Postfixare pentru inaltime
    const Pacient& operator++ (); //Prefixare
    int& operator[](int); //Operatorul [] pentru int*

    friend ifstream& operator>> (ifstream& f, Pacient &p); //Citirea din fisier
    friend ofstream& operator<< (ofstream& g, const Pacient &p); //Afisarea din fisier

    char *get_nume();
    void set_nume(char *nume);
    string get_prenume();
    void set_prenume(string prenume);
    char get_initiala_tata();
    void set_initiala_tata(char initiala_tata);
    int get_varsta();
    void set_varsta(int varsta);
    float get_inaltimea();
    void set_inaltimea(float inaltime);
    double get_greutatea();
    void set_greutatea(double greutate);
    int get_id_pacient();
    bool get_asigurat();
    void set_asigurat(bool asigurat);
    int get_nr_afectiuni();
    void set_nr_afectiuni(int nr_afectiuni);
    string* get_afectiuni();
    void set_afectiuni(int nr_afectiuni,string* afectiuni);
    int* get_perioada_afectiunii();
    void set_perioada_afectiunii(int nr_afectiuni,int* perioada_afectiunii);

    /**functionalitate: Vedem cum este indicele de masa corporala al pacientului cu formula:
    greutate [kg]/(inaltime^2) [cm] * 10000
    **/
    void BMI();

    //Supraincarcarea operatorilor
    bool operator==(const Pacient& p)
    {
        if(!strcmp(this->nume,p.nume) && this->prenume==p.prenume && this->varsta==p.varsta)
            return true;
        return false;
    }

    bool operator<(const Pacient& p)
    {
        if(this->varsta<p.varsta)
            return true;
        return false;
    }

    bool operator>=(const Pacient& p)
    {
        if(this->varsta>=p.varsta)
            return true;
        return false;
    }

    Pacient operator+=(float inalt)
    {
        this->inaltime+=inalt;
        return *this;
    }

    Pacient operator+=(double greu)
    {
        this->greutate+=greu;
        return *this;
    }

    friend Pacient operator-(float x, Pacient p)
    {
        p.inaltime=p.inaltime-x;
        return p;
    }

    explicit operator int() // Adica (int)pacient
    {
        return (int)this->greutate;
    }

    //Metoda virtuala pura
    void AnNastere()
    {
        cout<<"Anul nasterii al pacientului "<<this->nume<<" "<<this->prenume<<" este "<<2021-this->varsta<<'\n';
    }
};

int& Pacient::operator[](int index)
{
    if(0<=index && index<this->nr_afectiuni)
        return perioada_afectiunii[index];
    else
        cout<<"INDEXUL ESTE GRESIT!";
}

//Functionalitatea
void Pacient::BMI()
{
    double bmi;
    bmi=greutate/((double)inaltime*(double)inaltime)*10000;
    if (bmi<18.5)
        cout<<"Underweight"<<'\n';
    else
    if (bmi>=18.5&&bmi<24.9)
        cout<<"Normal weight"<<'\n';
    else
    if (bmi>=24.9&&bmi<29.9)
        cout<<"Overweight"<<'\n';
    else
        cout<<"Obesity"<<'\n';
}

int Pacient::nr_id=1000;

const Pacient Pacient::operator++(int)
{
    Pacient aux(*this);
    this->varsta=this->varsta+1;
    return aux;
}

const Pacient& Pacient::operator++()
{
    this->varsta=this->varsta+1;
    return *this;
}

const Pacient Pacient::operator-- (int)
{
    Pacient aux(*this);
    this->greutate=this->greutate-0.5;
    return aux;
}

/**const Pacient Pacient::operator++(float)
{
    Pacient aux(*this);
    this->inaltime=this->inaltime+1;
    return aux;
}**/

istream& operator>>(istream& in, Pacient& p)
{
    cout<<"NUMELE: ";
    char s[31];
    in>>s;
    cout<<'\n';
    if (p.nume!=NULL)
        delete[] p.nume;
    p.nume=new char[strlen(s)+1];
    strcpy(p.nume,s);
    cout<<"PRENUMELE: ";
    in>>p.prenume;
    cout<<'\n';
    cout<<"VARSTA: ";
    in>>p.varsta;
    cout<<'\n';
    cout<<"INITIALA TATALUI: ";
    in>>p.initiala_tata;
    cout<<'\n';
    cout<<"INALTIMEA: ";
    in>>p.inaltime;
    cout<<'\n';
    cout<<"GREUTATE: ";
    in>>p.greutate;
    cout<<'\n';
    cout<<"ESTE ASIGURAT PACIENTUL? (1-DA / 0-NU): ";
    in>>p.asigurat;
    cout<<'\n';
    cout<<"NUMARUL DE AFECTIUNI PE CARE LE ARE PACIENTUL: ";
    in>>p.nr_afectiuni;
    cout<<'\n';
    cout<<"NUMELE AFECTIUNILOR PE CARE LE PREZINTA PACIENTUL: ";
    if (p.afectiuni!=NULL)
        delete[] p.afectiuni;
    p.afectiuni=new string[p.nr_afectiuni];
    for (int i=0;i<p.nr_afectiuni;++i)
        in>>p.afectiuni[i];
    cout<<'\n';
    cout<<"PERIOADA (in ani) DE CAND PACIENTUL ARE FIECARE AFECTIUNE: ";
    if (p.perioada_afectiunii!=NULL)
        delete[] p.perioada_afectiunii;
    p.perioada_afectiunii=new int[p.nr_afectiuni];
    for (int i=0;i<p.nr_afectiuni;++i)
        in>>p.perioada_afectiunii[i];
    cout<<'\n';
    return in;
}

ostream& operator<<(ostream& out,const Pacient& p)
{
    out<<"ID pacient: "<<p.id_pacient<<'\n';
    out<<"NUME: "<<p.nume<<'\n';
    out<<"PRENUME: "<<p.prenume<<'\n';
    out<<"VARSTA: "<<p.varsta<<'\n';
    out<<"INITIALA TATALUI: "<<p.initiala_tata<<'\n';
    out<<"INALTIME: "<<p.inaltime<<'\n';
    out<<"GREUTATE: "<<p.greutate<<'\n';
    if (!p.asigurat)
        out<<"ESTE ASIGURAT? NU!"<<'\n';
    else
        out<<"ESTE ASIGURAT? DA!"<<'\n';
    if (p.nr_afectiuni!=1)
    out<<"Pacientul are "<<p.nr_afectiuni<<" afectiuni: ";
    else
    out<<"Pacientul are o afectiune: ";
    for (int i=0;i<p.nr_afectiuni-1;++i)
        out<<p.afectiuni[i]<<" timp de "<<p.perioada_afectiunii[i]<<" ani, ";
    if(p.nr_afectiuni>0)
        out<<p.afectiuni[p.nr_afectiuni-1]<<" timp de "<<p.perioada_afectiunii[p.nr_afectiuni-1]<<" ani\n";
    return out;
}

ifstream& operator>>(ifstream& f, Pacient& p) //Citirea din fisier pt clasa pacient
{
    char s[31];
    f>>s;
    if (p.nume!=NULL)
        delete[] p.nume;
    p.nume=new char[strlen(s)+1];
    strcpy(p.nume,s);
    f>>p.prenume;
    f>>p.varsta;
    f>>p.initiala_tata;
    f>>p.inaltime;
    f>>p.greutate;
    f>>p.asigurat;
    f>>p.nr_afectiuni;
    if (p.afectiuni!=NULL)
        delete[] p.afectiuni;
    p.afectiuni=new string[p.nr_afectiuni];
    for (int i=0;i<p.nr_afectiuni;++i)
        f>>p.afectiuni[i];
    if (p.perioada_afectiunii!=NULL)
        delete[] p.perioada_afectiunii;
    p.perioada_afectiunii=new int[p.nr_afectiuni];
    for (int i=0;i<p.nr_afectiuni;++i)
        f>>p.perioada_afectiunii[i];
    return f;
}

ofstream& operator<<(ofstream& g,const Pacient& p) //Afisarea din fisier
{
    g<<"ID pacient: "<<p.id_pacient<<'\n';
    g<<"NUME: "<<p.nume<<'\n';
    g<<"PRENUME: "<<p.prenume<<'\n';
    g<<"VARSTA: "<<p.varsta<<'\n';
    g<<"INITIALA TATALUI: "<<p.initiala_tata<<'\n';
    g<<"INALTIME: "<<p.inaltime<<'\n';
    g<<"GREUTATE: "<<p.greutate<<'\n';
    if (!p.asigurat)
        g<<"ESTE ASIGURAT? NU!"<<'\n';
    else
        g<<"ESTE ASIGURAT? DA!"<<'\n';
    if (p.nr_afectiuni!=1)
    g<<"Pacientul are "<<p.nr_afectiuni<<" afectiuni: ";
    else
    g<<"Pacientul are o afectiune: ";
    for (int i=0;i<p.nr_afectiuni-1;++i)
        g<<p.afectiuni[i]<<" timp de "<<p.perioada_afectiunii[i]<<" ani, ";
    if(p.nr_afectiuni>0)
        g<<p.afectiuni[p.nr_afectiuni-1]<<" timp de "<<p.perioada_afectiunii[p.nr_afectiuni-1]<<" ani\n";
    if (p.nr_afectiuni==0)
        g<<"Nu are afectiuni!\n";
    return g;
}

Pacient& Pacient::operator= (const Pacient& p)
{
    if (this!=&p)
    {
        if (this->nume!=NULL)
            delete[] this->nume;
        if (this->afectiuni!=NULL)
            delete[] this->afectiuni;
        if (this->perioada_afectiunii!=NULL)
            delete[] this->perioada_afectiunii;
        this->nume=new char[strlen(p.nume)+1];
        strcpy(this->nume,p.nume);
        this->prenume=p.prenume;
        this->initiala_tata=p.initiala_tata;
        this->varsta=p.varsta;
        this->inaltime=p.inaltime;
        this->greutate=p.greutate;
        this->asigurat=p.asigurat;
        this->nr_afectiuni=p.nr_afectiuni;
        this->afectiuni=new string[p.nr_afectiuni];
        for (int i=0;i<p.nr_afectiuni;++i)
            this->afectiuni[i]=p.afectiuni[i];
        this->perioada_afectiunii=new int[p.nr_afectiuni];
        for (int i=0;i<p.nr_afectiuni;++i)
            this->perioada_afectiunii[i]=p.perioada_afectiunii[i];
    }
    return *this;
}

char * Pacient::get_nume()
{
    return this->nume;
}

void Pacient::set_nume(char *nume)
{
    if (this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}

string Pacient::get_prenume()
{
    return this->prenume;
}

void Pacient::set_prenume(string prenume)
{
    this->prenume=prenume;
}

char Pacient::get_initiala_tata()
{
    return this->initiala_tata;
}

void Pacient::set_initiala_tata(char initiala_tata)
{
    this->initiala_tata=initiala_tata;
}

int Pacient::get_varsta()
{
    return this->varsta;
}

void Pacient::set_varsta(int varsta)
{
    this->varsta=varsta;
}

float Pacient::get_inaltimea()
{
    return this->inaltime;
}

void Pacient::set_inaltimea(float inaltime)
{
    this->inaltime=inaltime;
}

double Pacient::get_greutatea()
{
    return this->greutate;
}

void Pacient::set_greutatea(double greutate)
{
    this->greutate=greutate;
}

int Pacient::get_id_pacient()
{
    return this->id_pacient;
}

bool Pacient::get_asigurat()
{
    return this->asigurat;
}

void Pacient::set_asigurat(bool asigurat)
{
    this->asigurat=asigurat;
}

int Pacient::get_nr_afectiuni()
{
    return this->nr_afectiuni;
}

void Pacient::set_nr_afectiuni(int nr_afectiuni)
{
    this->nr_afectiuni=nr_afectiuni;
}

string* Pacient::get_afectiuni()
{
    return this->afectiuni;
}

void Pacient::set_afectiuni(int nr_afectiuni, string* afectiuni)
{
    if (this->afectiuni!=NULL)
        delete[] this->afectiuni;
    this->afectiuni=new string[nr_afectiuni];
    for (int i=0;i<nr_afectiuni;++i)
        this->afectiuni[i]=afectiuni[i];
}

int* Pacient::get_perioada_afectiunii()
{
    return this->perioada_afectiunii;
}

void Pacient::set_perioada_afectiunii(int nr_afectiuni,int* perioada_afectiunii)
{
    if (this->perioada_afectiunii!=NULL)
        delete[] this->perioada_afectiunii;
    this->perioada_afectiunii=new int[nr_afectiuni];
    for (int i=0;i<nr_afectiuni;++i)
        this->perioada_afectiunii[i]=perioada_afectiunii[i];
}

//Constructorul fara parametrii
Pacient::Pacient(): id_pacient(nr_id++)
{
    this->nume=new char(strlen("Necunoscut")+1);
    strcpy(this->nume,"Necunoscut");
    this->prenume="Necunoscut";
    this->initiala_tata='Q';
    this->varsta=-1;
    this->inaltime=-1;
    this->greutate=-1;
    this->asigurat=false; //sau puteam pune 0
    this->nr_afectiuni=0;
    this->afectiuni=NULL;
    this->perioada_afectiunii=NULL;
}

Pacient::Pacient (char *nume, string prenume): id_pacient(nr_id++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->initiala_tata='Q';
    this->varsta=0;
    this->inaltime=0;
    this->greutate=0;
    this->asigurat=false; //sau puteam pune 0
    this->nr_afectiuni=0;
    this->afectiuni=NULL;
    this->perioada_afectiunii=NULL;
}

//Constructorul cu parametrii
Pacient::Pacient (char *nume, string prenume, char initiala_tata, int varsta, float inaltime, double greutate,
             bool asigurat, int nr_afectiuni, string *afectiuni, int *perioada_afectiunii): id_pacient(nr_id++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->initiala_tata=initiala_tata;
    this->varsta=varsta;
    this->inaltime=inaltime;
    this->greutate=greutate;
    this->asigurat=asigurat;
    this->nr_afectiuni=nr_afectiuni;
    this->afectiuni=new string[nr_afectiuni];
    for (int i=0;i<nr_afectiuni;++i)
        this->afectiuni[i]=afectiuni[i];
    this->perioada_afectiunii=new int[nr_afectiuni];
    for (int i=0;i<nr_afectiuni;++i)
        this->perioada_afectiunii[i]=perioada_afectiunii[i];
}

//Destructorul
Pacient::~Pacient()
{
    if (this->nume!=NULL)
        delete[] this->nume;
    if (this->afectiuni!=NULL)
        delete[] this->afectiuni;
    if (this->perioada_afectiunii!=NULL)
        delete[] this->perioada_afectiunii;
}

//Copy constructorul
Pacient::Pacient (const Pacient& p): id_pacient(p.id_pacient)
{
    this->nume=new char[strlen(p.nume)+1];
    strcpy(this->nume,p.nume);
    this->prenume=p.prenume;
    this->initiala_tata=p.initiala_tata;
    this->varsta=p.varsta;
    this->inaltime=p.inaltime;
    this->greutate=p.greutate;
    this->asigurat=p.asigurat;
    this->nr_afectiuni=p.nr_afectiuni;
    this->afectiuni=new string[p.nr_afectiuni];
    for (int i=0;i<p.nr_afectiuni;++i)
        this->afectiuni[i]=p.afectiuni[i];
    this->perioada_afectiunii=new int[p.nr_afectiuni];
    for (int i=0;i<p.nr_afectiuni;++i)
        this->perioada_afectiunii[i]=p.perioada_afectiunii[i];
}

//Clasa Medici - a doua clasa - CODUL 2 + Extinderea ei cu ajutorul clasei Rezident
class Medic:public AnulNasterii{
protected:
    char* nume;
    string prenume;
    int varsta;
    int nr_sectii; //Numarul de sectii la care lucreaza
    string* sectie; //Sectiile la care lucreaza
    bool* specialist; //Daca specialist = 0, atunci inseamna ca medicul este primar, daca nu, inseamna ca e specialist pe sectia respectiva

public:
    Medic();
    Medic(char* nume, string prenume);
    Medic(char* nume, string prenume, int varsta, int nr_sectii, string* sectie, bool* specialist);
    virtual ~Medic();
    Medic(const Medic& m);

    Medic& operator=(const Medic& m);
    friend istream& operator>>(istream& in, Medic& m);
    friend ostream& operator<<(ostream& out,const Medic& m);

    friend ifstream& operator>> (ifstream& f, Medic &m); //Citirea virtuala din fisier
    friend ofstream& operator<< (ofstream& g,const Medic& m); //Afisarea virtuala din fisier

    virtual istream& CitireVirtuala (istream& in); //Citirea virtuala pentru clasa extinsa cu IS-A
    virtual ostream& AfisareVirtuala(ostream& out)const; //Afisarea virtuala pentru clasa extinsa cu IS-A

    virtual ifstream& CitireVirtualaFisier(ifstream& f); //Citirea virtuala din fisier pentru clasa extinsa cu IS-A
    virtual ofstream& AfisareVirtualaFisier(ofstream& g)const; //Afisarea virtuala din fisier pentru clasa extinsa cu IS-A

    const Medic& operator++();//Prefixarea opratorului ++
    const Medic operator++(int);//Postfixarea operatorului ++
    bool& operator[](int); //Operatorul [] pentru bool*

    char* get_nume();
    void set_nume(char* nume);
    string get_prenume();
    void set_prenume(string prenume);
    int get_varsta();
    void set_varsta(int varsta);
    int get_nr_sectii();
    void set_nr_sectii(int nr_sectii);
    string* get_sectie();
    void set_sectie(int nr_sectii, string* sectie);
    bool* get_specialist();
    void set_specialist(int nr_sectii, bool* specialist);

    /**functionalitate: Vom calcula un bonus care ii revine medicului in functie la cate sectii lucreaza si daca este medic
    specialist sau primar cu formula: adunam 1000 daca este specialist la o sectie, respectiv 1500 daca este primar.
    **/
    void Bonus();

    //Metoda virtuala pura
    void AnNastere()
    {
        cout<<"Anul nasterii al medicului "<<this->nume<<" este "<<2021-this->varsta<<'\n';
    }
};

bool& Medic::operator[](int index)
{
    if(0<=index && index<this->nr_sectii)
        return specialist[index];
    else
        cout<<"INDEXUL ESTE GRESIT!";
}

//Functionalitatea
void Medic::Bonus()
{
    int bonus=0;
    for (int i=0;i<nr_sectii;++i)
        if (!specialist[i]) //inseamna ca e primar
            bonus+=1500;
        else
            bonus+=1000;
    cout<<"Medicul "<<nume<<" "<<prenume<<" castiga bonus "<<bonus<<" lei"<<'\n';

}

const Medic Medic::operator++(int) //postincrementare
{
    Medic aux(*this);
    this->varsta=this->varsta+1;
    return aux;
}

const Medic& Medic::operator++() //preincrementare
{
    this->varsta=this->varsta+1;
    return *this;
}

ofstream& operator<<(ofstream& g,const Medic& m) //Afisare din fisier
{
   return m.AfisareVirtualaFisier(g);
}

ifstream& operator>>(ifstream& f, Medic& m) //Citire din fisier
{
    return m.CitireVirtualaFisier(f);
}

istream& operator>>(istream& in, Medic& m)
{
    return m.CitireVirtuala(in);
}

ostream& operator<<(ostream& out,const Medic& m)
{
    return m.AfisareVirtuala(out);
}

istream& Medic::CitireVirtuala(istream& in)
{
    cout<<"NUMELE: ";
    char s[31];
    in>>s;
    cout<<'\n';
    if (this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(s)+1];
    strcpy(this->nume,s);
    cout<<"PRENUMELE: ";
    in>>this->prenume;
    cout<<'\n';
    cout<<"VARSTA: ";
    in>>this->varsta;
    cout<<'\n';
    cout<<"NUMARUL DE SECTII LA CARE LUCREAZA: ";
    in>>this->nr_sectii;
    cout<<'\n';
    cout<<"DENUMIREA SECTIILOR: ";
    if (this->sectie!=NULL)
        delete[] this->sectie;
    this->sectie=new string[this->nr_sectii];
    for (int i=0;i<this->nr_sectii;++i)
        in>>this->sectie[i];
    cout<<'\n';
    cout<<"SPECIALIST/PRIMAR: ";
    if (this->specialist!=NULL)
        delete[] this->specialist;
    this->specialist=new bool[this->nr_sectii];
    for (int i=0;i<this->nr_sectii;++i)
        in>>this->specialist[i];
    cout<<'\n';
    return in;
}

ostream& Medic::AfisareVirtuala (ostream& out)const
{
    out<<"NUMELE: "<<nume<<'\n';
    out<<"PRENUMELE: "<<prenume<<'\n';
    out<<"VARSTA: "<<varsta<<'\n';
    out<<"NUMARUL DE SECTII LA CARE LUCREAZ: "<<nr_sectii<<'\n';
    out<<"Sectiile: ";
    for (int i=0;i<nr_sectii-1;++i)
        out<<sectie[i]<<", ";
    if (nr_sectii>0)
    out<<sectie[nr_sectii-1];
    out<<'\n';
    out<<"Si este specialist/primar: ";
    for (int i=0;i<nr_sectii;++i)
        if (specialist[i]==true)
            out<<"Medic specialist in "<<sectie[i]<<'\n';
        else
            out<<"Medic primar in "<<sectie[i]<<'\n';
    return out;
}

ifstream& Medic::CitireVirtualaFisier(ifstream& f)
{
    char s[31];
    f>>s;
    if (this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(s)+1];
    strcpy(this->nume,s);
    f>>this->prenume;
    f>>this->varsta;
    f>>this->nr_sectii;
    if (this->sectie!=NULL)
        delete[] this->sectie;
    this->sectie=new string[this->nr_sectii];
    for (int i=0;i<this->nr_sectii;++i)
        f>>this->sectie[i];
    if (this->specialist!=NULL)
        delete[] this->specialist;
    this->specialist=new bool[this->nr_sectii];
    for (int i=0;i<this->nr_sectii;++i)
        f>>this->specialist[i];
    return f;
}

ofstream& Medic::AfisareVirtualaFisier(ofstream& g)const
{
    g<<"NUMELE: "<<this->nume<<'\n';
    g<<"PRENUMELE: "<<this->prenume<<'\n';
    g<<"VARSTA: "<<this->varsta<<'\n';
    g<<"NUMARUL DE SECTII LA CARE LUCREAZ: "<<this->nr_sectii<<'\n';
    g<<"Sectiile: ";
    for (int i=0;i<this->nr_sectii-1;++i)
        g<<this->sectie[i]<<", ";
    if (this->nr_sectii>0)
    g<<this->sectie[this->nr_sectii-1];
    g<<'\n';
    g<<"Si este specialist/primar: ";
    for (int i=0;i<this->nr_sectii;++i)
        if (this->specialist[i]==true)
            g<<"Medic specialist in "<<this->sectie[i]<<'\n';
        else
            g<<"Medic primar in "<<this->sectie[i]<<'\n';
    return g;
}

Medic::Medic()
{
    this->nume=new char(strlen("Necunoscut")+1);
    strcpy(this->nume,"Necunoscut");
    this->prenume="Necunoscut";
    this->varsta=-1;
    this->nr_sectii=-1;
    this->sectie=NULL;
    this->specialist=NULL;
}

Medic::Medic(char* nume, string prenume)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->varsta=-1;
    this->nr_sectii=-1;
    this->sectie=NULL;
    this->specialist=NULL;
}

//Constructorul cu parametrii
Medic::Medic(char* nume, string prenume, int varsta, int nr_sectii, string* sectie, bool* specialist)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->varsta=varsta;
    this->nr_sectii=nr_sectii;
    this->sectie=new string[nr_sectii];
    for (int i=0;i<nr_sectii;++i)
        this->sectie[i]=sectie[i];
    this->specialist=new bool[nr_sectii];
    for (int i=0;i<nr_sectii;++i)
        this->specialist[i]=specialist[i];
}

//Destructorul
Medic::~Medic()
{
    if (this->sectie!=NULL)
        delete[] this->sectie;
    if (this->specialist!=NULL)
        delete[] this->specialist;
}

//Copy constructor-ul
Medic::Medic(const Medic& m)
{
    this->nume=new char[strlen(m.nume)+1];
    strcpy(this->nume,m.nume);
    this->prenume=m.prenume;
    this->varsta=m.varsta;
    this->nr_sectii=m.nr_sectii;
    this->sectie=new string[m.nr_sectii];
    for (int i=0;i<m.nr_sectii;++i)
        this->sectie[i]=m.sectie[i];
    this->specialist=new bool[m.nr_sectii];
    for (int i=0;i<m.nr_sectii;++i)
        this->specialist[i]=m.specialist[i];
}

Medic& Medic::operator=(const Medic& m)
{
    if (this->sectie!=NULL)
        delete[] this->sectie;
    if (this->specialist!=NULL)
        delete[] this->specialist;
    this->nume=new char[strlen(m.nume)+1];
    strcpy(this->nume,m.nume);
    this->prenume=m.prenume;
    this->varsta=m.varsta;
    this->nr_sectii=m.nr_sectii;
    this->sectie=new string[m.nr_sectii];
    for (int i=0;i<m.nr_sectii;++i)
        this->sectie[i]=m.sectie[i];
    this->specialist=new bool[m.nr_sectii];
    for (int i=0;i<m.nr_sectii;++i)
        this->specialist[i]=m.specialist[i];
    return *this;
}

string Medic::get_prenume()
{
    return this->prenume;
}

void Medic::set_prenume(string prenume)
{
    this->prenume=prenume;
}

char * Medic::get_nume()
{
    return this->nume;
}

void Medic::set_nume(char *nume)
{
    if (this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}

int Medic::get_varsta()
{
    return this->varsta;
}

void Medic::set_varsta(int varsta)
{
    this->varsta=varsta;
}

int Medic::get_nr_sectii()
{
    return this->nr_sectii;
}

void Medic::set_nr_sectii(int nr_sectii)
{
    this->nr_sectii=nr_sectii;
}

string* Medic::get_sectie()
{
    return this->sectie;
}

void Medic::set_sectie(int nr_sectii, string* sectie)
{
    if (this->sectie!=NULL)
        delete[] this->sectie;
    this->sectie=new string[nr_sectii];
    for (int i=0;i<nr_sectii;++i)
        this->sectie[i]=sectie[i];
}

bool* Medic::get_specialist()
{
    return this->specialist;
}

void Medic::set_specialist(int nr_sectii, bool* specialist)
{
    if (this->specialist!=NULL)
        delete[] this->specialist;
    this->specialist=new bool[nr_sectii];
    for (int i=0;i<nr_sectii;++i)
        this->specialist[i]=specialist[i];
}

//Extinderea IS-A a clasei Medic - etapa 2
class Rezident:public Medic{
private:
    bool rezident; //Daca e medic rezident -> 1, daca nu -> 0
    int ani; //Cati ani mai are de facut pana termina rezidentiatul
    int nr_note;
    float* note;
public:
    Rezident();
    Rezident(char* nume, string prenume, int varsta, int nr_sectii, string* sectie, bool* specialist,
             bool rezident, int ani, int nr_note, float* note); //Constructorul cu toti parametrii
    ~Rezident();
    Rezident(const Rezident& r); //Copy constructor-ul

    Rezident& operator=(const Rezident& r); //Operatorul de atribuire
    //Afisarea si citirea virtuala

    istream& CitireVirtuala (istream& in);
    ostream& AfisareVirtuala(ostream& out)const;

    ifstream& CitireVirtualaFisier(ifstream& f); //Citirea din fisier
    ofstream& AfisareVirtualaFisier(ofstream& g)const; //Afisarea din fisier

    /**functionalitate: Daca media rezidentului este mai mare sau egala cu 8.5, acesta va primi un bonus de 750 de lei
    la salariul standard, daca media este strict mai mica decat 5, rezidentului i se vor scadea 500 de lei din salariu,
    altfel acesta va primi un bonus de doar 200 de lei. -> CONDITIE: doar daca rezident==1
    **/
    void SalariuRezident()
    {
        float media=0,s=0;
        int SalariuStandard=ani*1000, SalariuBonus=200;
        if (rezident==1) //Doar ca medicul sa fie in stadiul de rezidentiat
        {
            for (int i=0;i<nr_note;++i)
                s+=note[i];
            media=s/nr_note;
            if (media>=8.5)
                SalariuBonus=750;
            else
                if (media<5)
                    SalariuBonus=-500;
            SalariuStandard+=SalariuBonus;
            cout<<"Salariul medicului rezident "<<this->nume<<" este de: "<<SalariuStandard<<" lei"<<'\n';
            return;
        }
        cout<<"Medicul nu este rezident!"<<'\n';
    }


};

istream& Rezident::CitireVirtuala(istream& in)
{
   Medic::CitireVirtuala(in);
   cout<<"Rezident? ";
    in>>this->rezident;
    if (this->rezident)
        cout<<"Este rezident."<<'\n';
    else
        cout<<"Nu este rezident."<<'\n';
    cout<<"A fost medic rezident timp de ";
    in>>this->ani;
    cout<<"A obtinut un numar de note: ";
    in>>this->nr_note;
    cout<<"Si a obtinut notele: ";
    if (this->note!=NULL)
        delete[] this->note;
    this->note=new float[this->nr_note];
    for (int i=0;i<this->nr_note;++i)
        in>>this->note[i];
    return in;
}

ostream& Rezident::AfisareVirtuala(ostream& out) const
{
    Medic::AfisareVirtuala(out);
    out<<"Rezident? ";
    if (rezident)
    out<<"Este rezident."<<'\n';
    else
    out<<"Nu este rezident."<<'\n';
    out<<"A fost medic rezident timp de "<<ani<<" ani"<<'\n';
    out<<"Are "<<nr_note<<" note"<<'\n';
    out<<"Si a obtinut notele: ";
    for (int i=0;i<nr_note-1;++i)
        out<<note[i]<<" , ";
    if (nr_note>0)
    out<<note[nr_note-1]<<'\n';
    return out;
}

ifstream& Rezident::CitireVirtualaFisier(ifstream& f)
{
    Medic::CitireVirtualaFisier(f);
    f>>this->rezident;
    f>>this->ani;
    f>>this->nr_note;
    if (this->note!=NULL)
        delete[] this->note;
    this->note=new float[this->nr_note];
    for (int i=0;i<this->nr_note;++i)
        f>>this->note[i];
    return f;
}

ofstream& Rezident::AfisareVirtualaFisier(ofstream& g)const
{
    Medic::AfisareVirtualaFisier(g);
    g<<"Rezident? ";
    if (this->rezident)
    g<<"Este rezident."<<'\n';
    else
    g<<"Nu este rezident."<<'\n';
    g<<"A fost medic rezident timp de "<<this->ani<<" ani"<<'\n';
    g<<"Are "<<this->nr_note<<" note"<<'\n';
    g<<"Si a obtinut notele: ";
    for (int i=0;i<this->nr_note-1;++i)
        g<<this->note[i]<<" , ";
    if (this->nr_note>0)
    g<<this->note[this->nr_note-1]<<'\n';
    return g;
}

Rezident::Rezident():Medic()
{
    this->rezident=0;
    this->ani=0;
    this->nr_note=0;
    this->note=nullptr;
}

//Constructorul cu parametrii
Rezident::Rezident(char* nume, string prenume, int varsta, int nr_sectii, string* sectie, bool* specialist,
             bool rezident, int ani, int nr_note, float* note):Medic(nume,prenume,varsta,nr_sectii,sectie,specialist)
{
    this->rezident=rezident;
    this->ani=ani;
    this->nr_note=nr_note;
    this->note=new float[nr_note];
    for (int i=0;i<nr_note;++i)
        this->note[i]=note[i];
}

//Destructorul ramane gol
Rezident::~Rezident()
{
    if (this->note!=NULL)
        delete[] this->note;
}

//Copy constructor-ul
Rezident::Rezident(const Rezident& r):Medic(r)
{
    this->rezident=r.rezident;
    this->ani=r.ani;
    this->nr_note=r.nr_note;
    this->note=new float[r.nr_note];
    for (int i=0;i<r.nr_note;++i)
        this->note[i]=r.note[i];
}

Rezident& Rezident::operator=(const Rezident& r)
{
    if(this!=&r)
    {
        Medic::operator=(r);
        if (this->note!=NULL)
            delete[] this->note;
        this->rezident=r.rezident;
        this->ani=r.ani;
        this->nr_note=r.nr_note;
        this->note=new float[r.nr_note];
        for (int i=0;i<r.nr_note;++i)
            this->note[i]=r.note[i];
    }
    return *this;
}

//Clasa Reteta - a treia clasa - CODUL 3 + Extinderea ei cu ajutorul clasei RetetaCompensata
class Reteta{
protected:
    string pacient;
    string medic;
    char* data;
    int varsta;
    int nr_medicamente;
    float* pret; //Pretul fiecarui medicament
    int* cantitate; //Cantitatea achizitionata din fiecare medicament
    string* denumire_comerciala; //Lista de medicamente
public:
    Reteta();
    Reteta(string pacient, string medic, char* data);
    Reteta(string pacient, string medic,char* data, int varsta, int nr_medicamente,
           float* pret,int* cantitate, string* denumire_comerciala);
    virtual ~Reteta();
    Reteta(const Reteta& r);

    Reteta& operator=(const Reteta& r);
    friend istream& operator>>(istream& in, Reteta& r);
    friend ostream& operator<<(ostream& out,const Reteta& r);

    virtual istream& CitireVirtuala (istream& in); //Citirea virtuala pentru clasa extinsa cu IS-A
    virtual ostream& AfisareVirtuala(ostream& out)const; //Afisarea virtuala pentru clasa extinsa cu IS-A

    friend ifstream& operator>>(ifstream& f, Reteta& r); //Citire din fisier
    friend ofstream& operator<<(ofstream& g,const Reteta& r); //Afisare din fisier

    virtual ifstream& CitireVirtualaFisier(ifstream& f); //Citirea virtuala din fisier pentru clasa extinsa cu IS-A
    virtual ofstream& AfisareVirtualaFisier(ofstream& g)const; //Afisarea virtuala din fisier pentru clasa extinsa cu IS-A

    const Reteta& operator++();//Prefixarea opratorului ++
    const Reteta operator++(int);//Postfixarea operatorului ++
    float& operator[](int); //Operatorul [] pentru float*

    string get_pacient();
    void set_pacient(string pacient);
    string get_medic();
    void set_medic(string medic);
    char* get_data();
    void set_data(char* data);
    int get_varsta();
    void set_varsta(int varsta);
    int get_nr_medicamente();
    void set_nr_medicamente(int nr_medicamente);
    float* get_pret();
    void set_pret(int nr_medicamente, float* pret);
    string* get_denumire_comerciala();
    void set_denumire_comerciala(int nr_medicamente, string* denumire_comerciala);
    int* get_cantitate();
    void set_cantitate(int nr_medicamente, int* cantitate);

    /**functionalitate: Va calcula suma pe care pacientul ar trebui sa o dea pentru
    medicamentele prescrise (suma cantitatilor*pret).
    **/
    void SumaMed();

    //Supraincarcarea operatorilor
    bool operator==(const Reteta& r)
    {
        if(this->pacient==r.pacient && this->varsta==r.varsta)
            return true;
        return false;
    }

    bool operator<(const Reteta& r) //Supraincarcarea operatorului < pentru data retetei
    {
        if(strcmp(this->data,r.data)<0)
            return true;
        return false;
    }

    bool operator>(const Reteta& r) //Supraincarcarea operatorului > pentru data retetei
    {
        if(strcmp(this->data,r.data)>0)
            return true;
        return false;
    }

    bool operator>=(const Reteta& r) //Supraincarcarea operatorului >= pentru data retetei
    {
        if(strcmp(this->data,r.data)>=0)
            return true;
        return false;
    }

    bool operator<=(const Reteta& r) //Supraincarcarea operatorului <= pentru data retetei
    {
        if(strcmp(this->data,r.data)<=0)
            return true;
        return false;
    }

    Reteta operator+(int x)
    {
        Reteta aux(*this);
        aux.varsta=aux.varsta+x;
        return aux;
    }

};

float& Reteta::operator[](int index)
{
    if(0<=index && index<this->nr_medicamente)
        return pret[index];
    else
        cout<<"INDEXUL ESTE GRESIT!";
}

//Functionalitatea
void Reteta::SumaMed()
{
    float s=0;
    for (int i=0;i<nr_medicamente;++i)
        s+=cantitate[i]*pret[i];
    cout<<"Suma cheltuita este de "<<s<<" lei"<<'\n';
}

const Reteta Reteta::operator++(int)
{
    Reteta aux(*this);
    this->varsta=this->varsta+1;
    return aux;
}

const Reteta& Reteta::operator++()
{
    this->varsta=this->varsta+1;
    return *this;
}

istream& Reteta::CitireVirtuala(istream& in)
{
    char s[31];
    cout<<"NUMELE DE FAMILIE AL PACIENTULUI: ";
    in>>this->pacient;
    cout<<'\n';
    cout<<"NUMELE DE FAMILIE AL MEDICULUI: Dr. ";
    in>>this->medic;
    cout<<'\n';
    cout<<"DATA: "; //Format la alegere, spre ex. DD.MM.YYYY sau DD/MM/YYYY (dar sa fie un caracter neaparat, nu space intre cifrele din data)
    in>>s;
    if (this->data!=NULL)
        delete[] this->data;
    this->data=new char[strlen(s)+1];
    strcpy(this->data,s);
    cout<<'\n';
    cout<<"VARSTA: ";
    in>>this->varsta;
    cout<<'\n';
    cout<<"NUMARUL DE MEDICAMENTE PRESCRISE: ";
    in>>this->nr_medicamente;
    cout<<'\n';
    cout<<"DENUMIREA MEDICAMENTELOR: ";
    if (this->denumire_comerciala!=NULL)
        delete[] this->denumire_comerciala;
    this->denumire_comerciala=new string[this->nr_medicamente];
    for (int i=0;i<this->nr_medicamente;++i)
        in>>this->denumire_comerciala[i];
    cout<<'\n';
    cout<<"PRETUL MEDICAMENTELOR: ";
    if (this->pret!=NULL)
        delete[] this->pret;
    this->pret=new float[this->nr_medicamente];
    for (int i=0;i<this->nr_medicamente;++i)
        in>>this->pret[i];
    cout<<'\n';
    cout<<"CANTITATEA PRESCRISA DIN FIECARE MEDICAMENT: ";
    if (this->cantitate!=NULL)
        delete[] this->cantitate;
    this->cantitate=new int[this->nr_medicamente];
    for (int i=0;i<this->nr_medicamente;++i)
        in>>this->cantitate[i];
    cout<<'\n';
    return in;
}

ostream& Reteta::AfisareVirtuala (ostream& out) const
{
    out<<"NUMELE PACIENTULUI: "<<pacient<<'\n';
    out<<"NUMELE MEDICULUI: Dr. "<<medic<<'\n';
    out<<"DATA: "<<data<<'\n';
    out<<"VARSTA PACIENTULUI: "<<varsta<<'\n';
    out<<"NUMARUL DE MEDICAMENTE: "<<nr_medicamente<<'\n';
    if (nr_medicamente>0)
    {out<<"Medicamentele: ";
    for (int i=0;i<nr_medicamente-1;++i)
        out<<denumire_comerciala[i]<<", ";
    out<<denumire_comerciala[nr_medicamente-1];
    out<<'\n';
    out<<"Cu pretul: ";
    for (int i=0;i<nr_medicamente-1;++i)
        out<<pret[i]<<" lei, ";
    if(nr_medicamente>0)
    out<<pret[nr_medicamente-1]<<" lei"<<'\n';
    out<<"In cantitati de: ";
    for (int i=0;i<nr_medicamente-1;++i)
        out<<cantitate[i]<<" bucati, ";
    if(nr_medicamente>0)
    out<<cantitate[nr_medicamente-1]<<" bucati"<<'\n';
    }
    return out;
}

istream& operator>>(istream& in, Reteta& r)
{
    return r.CitireVirtuala(in);
}

ostream& operator<<(ostream& out, const Reteta& r)
{
    return r.AfisareVirtuala(out);
}

ifstream& Reteta::CitireVirtualaFisier(ifstream& f)
{
    char s[31];
    f>>this->pacient;
    f>>this->medic;
    f>>s;
    if (this->data!=NULL)
        delete[] this->data;
    this->data=new char[strlen(s)+1];
    strcpy(this->data,s);
    f>>this->varsta;
    f>>this->nr_medicamente;
    if (this->denumire_comerciala!=NULL)
        delete[] this->denumire_comerciala;
    this->denumire_comerciala=new string[this->nr_medicamente];
    for (int i=0;i<this->nr_medicamente;++i)
        f>>this->denumire_comerciala[i];
    if (this->pret!=NULL)
        delete[] this->pret;
    this->pret=new float[this->nr_medicamente];
    for (int i=0;i<this->nr_medicamente;++i)
        f>>this->pret[i];
    if (this->cantitate!=NULL)
        delete[] this->cantitate;
    this->cantitate=new int[this->nr_medicamente];
    for (int i=0;i<this->nr_medicamente;++i)
        f>>this->cantitate[i];
    return f;
}

ofstream& Reteta::AfisareVirtualaFisier(ofstream& g)const
{
    g<<"NUMELE PACIENTULUI: "<<this->pacient<<'\n';
    g<<"NUMELE MEDICULUI: Dr. "<<this->medic<<'\n';
    g<<"DATA: "<<this->data<<'\n';
    g<<"VARSTA PACIENTULUI: "<<this->varsta<<'\n';
    g<<"NUMARUL DE MEDICAMENTE: "<<this->nr_medicamente<<'\n';
    if (this->nr_medicamente>0)
    {g<<"Medicamentele: ";
    for (int i=0;i<this->nr_medicamente-1;++i)
        g<<this->denumire_comerciala[i]<<", ";
    g<<this->denumire_comerciala[this->nr_medicamente-1];
    g<<'\n';
    g<<"Cu pretul: ";
    for (int i=0;i<this->nr_medicamente-1;++i)
        g<<this->pret[i]<<" lei, ";
    if(this->nr_medicamente>0)
    g<<this->pret[this->nr_medicamente-1]<<" lei"<<'\n';
    g<<"In cantitati de: ";
    for (int i=0;i<this->nr_medicamente-1;++i)
        g<<this->cantitate[i]<<" bucati, ";
    if(this->nr_medicamente>0)
    g<<this->cantitate[this->nr_medicamente-1]<<" bucati"<<'\n';
    }
    return g;
}

ifstream& operator>>(ifstream& f, Reteta& r) //Citire din fisier
{
    return r.CitireVirtualaFisier(f);
}

ofstream& operator<<(ofstream& g, const Reteta& r) //Afisare din fisier
{
    return r.AfisareVirtualaFisier(g);
}

Reteta::Reteta()
{
    this->pacient=" ";
    this->data=new char[2];
    strcpy(this->data," ");
    this->medic=" ";
    this->varsta=-1;
    this->nr_medicamente=0;
    this->pret=NULL;
    this->cantitate=NULL;
    this->denumire_comerciala=NULL;
}

Reteta::Reteta(string pacient, string medic, char* data)
{
    this->pacient=pacient;
    this->medic=medic;
    this->data=new char[strlen(data)+1];
    strcpy(this->data,data);
    this->medic=" ";
    this->varsta=-1;
    this->nr_medicamente=0;
    this->pret=NULL;
    this->cantitate=NULL;
    this->denumire_comerciala=NULL;
}

//Constructorul cu parametrii
Reteta::Reteta(string pacient, string medic,char* data, int varsta, int nr_medicamente,
           float* pret,int* cantitate, string* denumire_comerciala)
{
    this->pacient=pacient;
    this->medic=medic;
    this->data=new char[strlen(data)+1];
    strcpy(this->data,data);
    this->varsta=varsta;
    this->nr_medicamente=nr_medicamente;
    this->pret=new float[nr_medicamente];
    for (int i=0;i<nr_medicamente;++i)
        this->pret[i]=pret[i];
    this->cantitate=new int[nr_medicamente];
    for (int i=0;i<nr_medicamente;++i)
        this->cantitate[i]=cantitate[i];
    this->denumire_comerciala=new string[nr_medicamente];
    for (int i=0;i<nr_medicamente;++i)
        this->denumire_comerciala[i]=denumire_comerciala[i];
}

//Destructorul
Reteta::~Reteta()
{
    if (this->data!=NULL)
        delete[] this->data;
    if (this->pret!=NULL)
        delete[] this->pret;
    if (this->cantitate!=NULL)
        delete[] this->cantitate;
    if (this->denumire_comerciala!=NULL)
        delete[] this->denumire_comerciala;
}

//Copy constructor-ul
Reteta::Reteta(const Reteta& r)
{
    this->pacient=r.pacient;
    this->medic=r.medic;
    this->data=new char[strlen(r.data)+1];
    strcpy(this->data,r.data);
    this->varsta=r.varsta;
    this->nr_medicamente=r.nr_medicamente;
    this->pret=new float[r.nr_medicamente];
    for (int i=0;i<r.nr_medicamente;++i)
        this->pret[i]=r.pret[i];
    this->cantitate=new int[r.nr_medicamente];
    for (int i=0;i<r.nr_medicamente;++i)
        this->cantitate[i]=r.cantitate[i];
    this->denumire_comerciala=new string[r.nr_medicamente];
    for (int i=0;i<r.nr_medicamente;++i)
        this->denumire_comerciala[i]=r.denumire_comerciala[i];
}

Reteta& Reteta::operator=(const Reteta& r)
{
    if (this!=&r)
    {
        if (this->data!=NULL)
            delete[] this->data;
        if (this->pret!=NULL)
            delete[] this->pret;
        if (this->cantitate==NULL)
            delete[] this->cantitate;
        if (this->denumire_comerciala==NULL)
            delete[] this->denumire_comerciala;
        this->pacient=r.pacient;
        this->medic=r.medic;
        this->data=new char[strlen(r.data)+1];
        strcpy(this->data,r.data);
        this->varsta=r.varsta;
        this->nr_medicamente=r.nr_medicamente;
        this->pret=new float[r.nr_medicamente];
        for (int i=0;i<r.nr_medicamente;++i)
            this->pret[i]=r.pret[i];
        this->cantitate=new int[r.nr_medicamente];
        for (int i=0;i<r.nr_medicamente;++i)
            this->cantitate[i]=r.cantitate[i];
        this->denumire_comerciala=new string[r.nr_medicamente];
        for (int i=0;i<r.nr_medicamente;++i)
            this->denumire_comerciala[i]=r.denumire_comerciala[i];
    }
    return *this;

}

string Reteta::get_pacient()
{
    return this->pacient;
}

void Reteta::set_pacient(string pacient)
{
    this->pacient=pacient;
}

string Reteta::get_medic()
{
    return this->medic;
}

void Reteta::set_medic(string medic)
{
    this->medic=medic;
}

int Reteta::get_varsta()
{
    return this->varsta;
}

void Reteta::set_varsta(int varsta)
{
    this->varsta=varsta;
}

char* Reteta::get_data()
{
    return this->data;
}

void Reteta::set_data(char* data)
{
    if (this->data!=NULL)
        delete[] this->data;
    this->data=new char[strlen(data)+1];
    strcpy(this->data,data);
}

int Reteta::get_nr_medicamente()
{
    return this->nr_medicamente;
}

void Reteta::set_nr_medicamente(int nr_medicamente)
{
    this->nr_medicamente=nr_medicamente;
}

string* Reteta::get_denumire_comerciala()
{
    return this->denumire_comerciala;
}

void Reteta::set_denumire_comerciala(int nr_medicamente, string* denumire_comerciala)
{
    if (this->denumire_comerciala!=NULL)
        delete[] this->denumire_comerciala;
    this->denumire_comerciala=new string[nr_medicamente];
    for (int i=0;i<nr_medicamente;++i)
        this->denumire_comerciala[i]=denumire_comerciala[i];
}

int* Reteta::get_cantitate()
{
    return this->cantitate;
}

void Reteta::set_cantitate(int nr_medicamente, int* cantitate)
{
    if (this->cantitate!=NULL)
        delete[] this->cantitate;
    this->cantitate=new int[nr_medicamente];
    for (int i=0;i<nr_medicamente;++i)
        this->cantitate[i]=cantitate[i];
}

float* Reteta::get_pret()
{
    return this->pret;
}

void Reteta::set_pret(int nr_medicamente, float* pret)
{
    if (this->pret!=NULL)
        delete[] this->pret;
    this->pret=new float[nr_medicamente];
    for (int i=0;i<nr_medicamente;++i)
        this->pret[i]=pret[i];
}

//Extinderea IS-A a clasei Reteta - etapa 2
class RetetaCompensata:public Reteta{
private:
    bool compensata; //Daca e 1 - e reteta compensata, daca e 0 - e reteta necompensta
    int valabilitate; //Valabilitatea retetei (in luni)
public:
    RetetaCompensata();
    RetetaCompensata(string pacient, string medic,char* data, int varsta, int nr_medicamente,
           float* pret,int* cantitate, string* denumire_comerciala,
           bool compensata, int valabilitate); //Constructorul cu toti parametrii
    ~RetetaCompensata();
    RetetaCompensata(const RetetaCompensata& rc); //Copy constructor-ul

    RetetaCompensata& operator=(const RetetaCompensata& rc); //Operatorul de atribuire
    //Afisarea si citirea virtuala
    istream& CitireVirtuala (istream& in);
    ostream& AfisareVirtuala(ostream& out)const;

    ifstream& CitireVirtualaFisier(ifstream& f); //Citirea din fisier
    ofstream& AfisareVirtualaFisier(ofstream& g)const; //Afisarea din fisier

    /**functionalitate: Daca valabillitatea este mai mare de jumatate de an si reteta este compensata,
    atunci pacientul va trebui sa plateasca jumatate din pretul retetei, in celelalte cazuri, ori este
    doar compensata si nu plateste nimic, ori plateste pretul intreg, fiind necompensata si valabilitatea < 6 luni.
    **/
    void SumaCompensata()
    {
        float s=0,pret=0;
        for (int i=0;i<this->nr_medicamente;++i) //este functionalitatea din Reteta doar ca acolo afisam, nu returnam
            s+=this->cantitate[i]*this->pret[i];
        if (valabilitate>=6&&compensata==1)
            pret=s/2.0;
        else
            if (compensata==0)
            pret=s;
        cout<<"Pretul care trebuie platit este de: "<<pret<< " lei"<<'\n';
    }
};

istream& RetetaCompensata::CitireVirtuala(istream& in)
{
   Reteta::CitireVirtuala(in);
   cout<<"Compensata? ";
   in>>compensata;
   if (compensata)
    cout<<"DA"<<'\n';
   else
    cout<<"NU"<<'\n';
   cout<<"VALABILITATE DE UN NUMAR DE LUNI: ";
   in>>valabilitate;
   cout<<'\n';
   return in;
}

ostream& RetetaCompensata::AfisareVirtuala(ostream& out) const
{
    Reteta::AfisareVirtuala(out);
    out<<"COMPENSATA? ";
    if (compensata)
    out<<"DA"<<'\n';
    else
    out<<"NU"<<'\n';
    out<<"VALABILITATE DE "<<valabilitate<<" LUNI"<<'\n';
    return out;
}

ifstream& RetetaCompensata::CitireVirtualaFisier(ifstream& f)
{
   Reteta::CitireVirtualaFisier(f);
   f>>this->compensata;
   f>>this->valabilitate;
   return f;
}

ofstream& RetetaCompensata::AfisareVirtualaFisier(ofstream& g)const
{
    Reteta::AfisareVirtualaFisier(g);
    g<<"COMPENSATA? ";
    if (this->compensata)
    g<<"DA"<<'\n';
    else
    g<<"NU"<<'\n';
    g<<"VALABILITATE DE "<<this->valabilitate<<" LUNI"<<'\n';
    return g;
}

RetetaCompensata::RetetaCompensata():Reteta()
{
    this->compensata=0;
    this->valabilitate=0;
}

//Constructorul cu parametrii
RetetaCompensata::RetetaCompensata(string pacient, string medic,char* data, int varsta, int nr_medicamente,
           float* pret,int* cantitate, string* denumire_comerciala, bool compensata, int valabilitate):Reteta(pacient, medic, data, varsta, nr_medicamente,
           pret, cantitate, denumire_comerciala)
{
    this->compensata=compensata;
    this->valabilitate=valabilitate;
}

//Destructorul ramane gol
RetetaCompensata::~RetetaCompensata()
{
}

//Copy constructor-ul
RetetaCompensata::RetetaCompensata(const RetetaCompensata& rc):Reteta(rc)
{
    this->compensata=rc.compensata;
    this->valabilitate=rc.valabilitate;
}

RetetaCompensata& RetetaCompensata::operator=(const RetetaCompensata& rc)
{
    if(this!=&rc)
    {
        Reteta::operator=(rc);
        this->valabilitate=rc.valabilitate;
        this->compensata=rc.compensata;
    }
    return *this;
}

//Vom creea clasa Salon pentru relatia HAS-A: Sectie HAS-A Salon
class Salon{
private:
    int etaj;
    int camera;

public:
    Salon();
    Salon(int etaj, int camera);
    ~Salon();
    Salon(const Salon& s);

    Salon& operator=(const Salon& s);
    friend istream& operator>>(istream& in, Salon& s);
    friend ostream& operator<<(ostream& out,const Salon& s);

    friend ifstream& operator>>(ifstream& f, Salon& s); //Citire din fisier
    friend ofstream& operator<<(ofstream& g,const Salon& s); //Afisare din fisier


    int get_camera();
    void set_camera(int camera);
    int get_etaj();
    void set_etaj(int etaj);

    /** functionalitate: daca salonul in care se afla un pacient este la un etaj mai inalt, acesta va trebui sa plateasca
        mai putin, dupa formula: cu (etaj-1)*10 lei mai putin.**/
    void ReducereEtaj()
    {
        int red=0;
        red=(this->etaj-1)*10;
        cout<<"Pacientul va avea reducerea de "<<red<<" lei\n";
    }

};
Salon::Salon()
{
    this->etaj=0;
    this->camera=0;
}

Salon::Salon(int etaj, int camera)
{
    this->etaj=etaj;
    this->camera=camera;
}
istream& operator>>(istream& in, Salon& s)
{
    cout<<"CAMERA: ";
    in>>s.camera;
    cout<<'\n';
    cout<<"ETAJ: ";
    in>>s.etaj;
    cout<<'\n';
    return in;
}

ostream& operator<<(ostream& out,const Salon& s)
{
    out<<"CAMERA: "<<s.camera<<" la ";
    out<<"ETAJ: "<<s.etaj<<'\n';
    return out;
}

ifstream& operator>>(ifstream& f, Salon& s) //Citire din fisier
{
    f>>s.camera;
    f>>s.etaj;
    return f;
}

ofstream& operator<<(ofstream& g,const Salon& s) //Afisare din fisier
{
    g<<"CAMERA: "<<s.camera<<" la ";
    g<<"ETAJ: "<<s.etaj<<'\n';
    return g;
}

//Destructorul ramane gol
Salon::~Salon()
{
}

//Copy constructor-ul
Salon::Salon(const Salon& s)
{
    this->etaj=s.etaj;
    this->camera=s.camera;
}

Salon& Salon::operator=(const Salon& s)
{
    this->etaj=s.etaj;
    this->camera=s.camera;
    return *this;
}

int Salon::get_etaj()
{
    return this->etaj;
}

void Salon::set_etaj(int etaj)
{
    this->etaj=etaj;
}

int Salon::get_camera()
{
    return this->camera;
}

void Salon::set_camera(int camera)
{
    this->camera=camera;
}

//Clasa Sectie - a patra clasa - CODUL 4
class Sectie{
private:
    string denumire;
    string telefon;
    char* mail;
    int aparitie; //De cati ani exista sectia X
    int nr_dotari; //Numarul de dotari de la sectia X
    string* dotari; //Dotarile
    float* pret; //Cat costa fiecare dotare pentru pacienti
    int nr_saloane; //Numarul de saloane de la sectia X -> pentru relatia HAS-A
    Salon* saloane; //Relatia Sectie HAS-A Salon

public:
    Sectie();
    Sectie(string denumire, string telefon, char* mail);
    Sectie(string denumire, string telefon, char* mail, int aparitie, int nr_dotari, string* dotari, float* pret,
           int nr_saloane, Salon* saloane);
    ~Sectie();
    Sectie(const Sectie& s);

    Sectie& operator=(const Sectie& s);
    friend istream& operator>>(istream& in, Sectie& s);
    friend ostream& operator<<(ostream& out,const Sectie& s);
    const Sectie& operator++();//Prefixarea opratorului ++
    const Sectie operator++(int);//Postfixarea operatorului ++
    string& operator[](int); //Operatorul [] pentru string*

    friend ifstream& operator>>(ifstream& f, Sectie& s); //Citire din fisier
    friend ofstream& operator<<(ofstream& g,const Sectie& s); //Afisare din fisier

    string get_denumire();
    void set_denumire(string denumire);
    string get_telefon();
    void set_telefon(string telefon);
    char* get_mail();
    void set_mail(char* mail);
    int get_aparitie();
    void set_aparitie(int aparitie);
    int get_nr_dotari();
    void set_nr_dotari(int nr_dotari);
    string* get_dotari();
    void set_dotari(int nr_dotari, string* dotari);
    float* get_pret();
    void set_pret(int nr_dotari, float* dotari);
    int get_nr_saloane();
    void set_nr_saloane(int nr_saloane);
    Salon* get_saloane();
    void set_saloane(int nr_saloane,Salon* saloane);

    /**functionalitate: Vom calcula cat ar costa daca un pacient ar trebui sa faca toate consultatiile de la
    o sectie anume.
    **/
    void Consultatii();

    //Supraincarcarea operatorilor +, - si *
    friend Sectie operator+(int x, Sectie s)
    {
        s.aparitie=x+s.aparitie;
        return s;
    }

    friend Sectie operator-(int x, Sectie s)
    {
        s.aparitie=s.aparitie-x;
        return s;
    }

    friend Sectie operator*(int x, Sectie s)
    {
        s.aparitie=x*s.aparitie;
        return s;
    }

    explicit operator double() // Adica (double)sectie
    {
        return (double)this->aparitie;
    }
};

string& Sectie::operator[](int index)
{
    if(0<=index && index<this->nr_dotari)
        return dotari[index];
    else
        cout<<"INDEXUL ESTE GRESIT!";
}

//Functionalitatea
void Sectie::Consultatii()
{
    float s=0;
    for (int i=0;i<nr_dotari;++i)
        s+=pret[i];
    cout<<"Clientul ar trebui sa plateasca "<<s<<" lei pentru toate consultatiile de la sectia "<<denumire<<'\n';
}

const Sectie Sectie::operator++(int)
{
    Sectie aux(*this);
    this->aparitie=this->aparitie+1;
    return aux;
}

const Sectie& Sectie::operator++()
{
    this->aparitie=this->aparitie+1;
    return *this;
}

istream& operator>>(istream& in, Sectie& s)
{
    cout<<"SECTIA: ";
    in>>s.denumire;
    cout<<'\n';
    cout<<"TELEFON: ";
    in>>s.telefon;
    cout<<'\n';
    cout<<"ADERSA DE MAIL: ";
    char sir[31];
    in>>sir;
    cout<<'\n';
    if (s.mail!=NULL)
        delete[] s.mail;
    s.mail=new char[strlen(sir)+1];
    strcpy(s.mail,sir);
    cout<<"DE CATI ANI ESTE SECTIA IN FUNCTIUNE: ";
    in>>s.aparitie;
    cout<<'\n';
    cout<<"NUMARUL DE DOTARI: ";
    in>>s.nr_dotari;
    cout<<'\n';
    cout<<"DENUMIREA DOTARILOR: ";
    if (s.dotari!=NULL)
        delete[] s.dotari;
    s.dotari=new string[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        in>>s.dotari[i];
    cout<<'\n';
    cout<<"COSTUL DOTARILOR PENTRU CLIENTI: ";
    if (s.pret!=NULL)
        delete[] s.pret;
    s.pret=new float[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        in>>s.pret[i];
    cout<<'\n';
    cout<<"NUMARUL DE SALOANE: ";
    in>>s.nr_saloane;
    cout<<'\n';
    if(s.saloane!=NULL)
        delete[] s.saloane;
    s.saloane=new Salon[s.nr_saloane];
    cout<<"SALOANELE SUNT: ";
    for(int i=0; i<s.nr_saloane;++i)
        in>>s.saloane[i];
    cout<<'\n';
    return in;
}

ostream& operator<<(ostream& out,const Sectie& s)
{
    out<<"SECTIA: "<<s.denumire<<'\n';
    out<<"TELEFON: "<<s.telefon<<'\n';
    out<<"ADRESA E-MAIL: "<<s.mail<<'\n';
    out<<"SECTIA A APARUT DE "<<s.aparitie<<" ANI\n";
    out<<"ARE "<<s.nr_dotari<<" DOTARI \n";
    out<<"Dotarile: ";
    for (int i=0;i<s.nr_dotari-1;++i)
        out<<s.dotari[i]<<", ";
    if (s.nr_dotari>0)
    out<<s.dotari[s.nr_dotari-1];
    out<<'\n';
    out<<"Si costa: ";
    for (int i=0;i<s.nr_dotari-1;++i)
        out<<s.pret[i]<<" lei, ";
    if(s.nr_dotari>0)
    out<<s.pret[s.nr_dotari-1]<<" lei\n";
    out<<"NUMARUL DE SALOANE: "<<s.nr_saloane<<'\n';
    out<<"SALOANELE SUNT -> ";
    for(int i=0; i<s.nr_saloane;++i)
        out<<s.saloane[i]<<" ";
    out<<'\n';
    return out;
}

ifstream& operator>>(ifstream& f, Sectie& s) //Citire din fisier
{
    f>>s.denumire;
    f>>s.telefon;
    char sir[31];
    f>>sir;
    if (s.mail!=NULL)
        delete[] s.mail;
    s.mail=new char[strlen(sir)+1];
    strcpy(s.mail,sir);
    f>>s.aparitie;
    f>>s.nr_dotari;
    if (s.dotari!=NULL)
        delete[] s.dotari;
    s.dotari=new string[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        f>>s.dotari[i];
    if (s.pret!=NULL)
        delete[] s.pret;
    s.pret=new float[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        f>>s.pret[i];
    f>>s.nr_saloane;
    if(s.saloane!=NULL)
        delete[] s.saloane;
    s.saloane=new Salon[s.nr_saloane];
    for(int i=0; i<s.nr_saloane;++i)
        f>>s.saloane[i];
    return f;
}

ofstream& operator<<(ofstream& g,const Sectie& s) //Afisare din fisier
{
    g<<"SECTIA: "<<s.denumire<<'\n';
    g<<"TELEFON: "<<s.telefon<<'\n';
    g<<"ADRESA E-MAIL: "<<s.mail<<'\n';
    g<<"SECTIA A APARUT DE "<<s.aparitie<<" ANI\n";
    g<<"ARE "<<s.nr_dotari<<" DOTARI \n";
    g<<"Dotarile: ";
    for (int i=0;i<s.nr_dotari-1;++i)
        g<<s.dotari[i]<<", ";
    if (s.nr_dotari>0)
    g<<s.dotari[s.nr_dotari-1];
    g<<'\n';
    g<<"Si costa: ";
    for (int i=0;i<s.nr_dotari-1;++i)
        g<<s.pret[i]<<" lei, ";
    if(s.nr_dotari>0)
    g<<s.pret[s.nr_dotari-1]<<" lei\n";
    g<<"NUMARUL DE SALOANE: "<<s.nr_saloane<<'\n';
    g<<"SALOANELE SUNT -> ";
    for(int i=0; i<s.nr_saloane;++i)
        g<<s.saloane[i]<<" ";
    g<<'\n';
    return g;
}

Sectie::Sectie()
{
    this->denumire="Neexistent";
    this->telefon="Neexistent";
    this->mail=new char(strlen("Neexistent")+1);
    strcpy(this->mail,"Neexistent");
    this->aparitie=-1;
    this->nr_dotari=-1;
    this->dotari=NULL;
    this->pret=NULL;
    this->nr_saloane=-1;
    this->saloane=NULL;
}

Sectie::Sectie(string denumire, string telefon, char* mail)
{
    this->denumire=denumire;
    this->telefon=telefon;
    this->mail=new char[strlen(mail)+1];
    strcpy(this->mail,mail);
    this->aparitie=-1;
    this->nr_dotari=0;
    this->dotari=NULL;
    this->pret=NULL;
    this->nr_saloane = 0;
    this->saloane = nullptr;
}

//Constructorul cu parametrii
Sectie::Sectie(string denumire, string telefon, char* mail, int aparitie, int nr_dotari, string* dotari, float* pret,
               int nr_saloane, Salon* saloane)
{
    this->denumire=denumire;
    this->telefon=telefon;
    this->mail=new char[strlen(mail)+1];
    strcpy(this->mail,mail);
    this->aparitie=aparitie;
    this->nr_dotari=nr_dotari;
    this->dotari=new string[nr_dotari];
    for (int i=0;i<nr_dotari;++i)
        this->dotari[i]=dotari[i];
    this->pret=new float[nr_dotari];
    for (int i=0;i<nr_dotari;++i)
        this->pret[i]=pret[i];
    this->nr_saloane=nr_saloane;
    this->saloane=new Salon[nr_saloane];
    for (int i=0;i<nr_saloane;++i)
        this->saloane[i]=saloane[i];
}

//Destructorul
Sectie::~Sectie()
{
    if (this->dotari!=NULL)
        delete[] this->dotari;
    if (this->pret!=NULL)
        delete[] this->pret;
    if (this->saloane!=NULL)
        delete[] this->saloane;
}

//Copy constructor-ul
Sectie::Sectie(const Sectie& s)
{
    this->denumire=s.denumire;
    this->telefon=s.telefon;
    this->mail=new char[strlen(s.mail)+1];
    strcpy(this->mail,s.mail);
    this->aparitie=s.aparitie;
    this->nr_dotari=s.nr_dotari;
    this->dotari=new string[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        this->dotari[i]=s.dotari[i];
    this->pret=new float[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        this->pret[i]=s.pret[i];
    this->nr_saloane=s.nr_saloane;
    this->saloane=new Salon[s.nr_saloane];
    for (int i=0;i<s.nr_saloane;++i)
        this->saloane[i]=s.saloane[i];
}

Sectie& Sectie::operator=(const Sectie& s)
{
    if (this->dotari!=NULL)
        delete[] this->dotari;
    if (this->pret!=NULL)
        delete[] this->pret;
    if (this->saloane!=NULL)
        delete[] this->saloane;
    this->denumire=s.denumire;
    this->telefon=s.telefon;
    this->mail=new char[strlen(s.mail)+1];
    strcpy(this->mail,s.mail);
    this->aparitie=s.aparitie;
    this->nr_dotari=s.nr_dotari;
    this->dotari=new string[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        this->dotari[i]=s.dotari[i];
    this->pret=new float[s.nr_dotari];
    for (int i=0;i<s.nr_dotari;++i)
        this->pret[i]=s.pret[i];
    this->nr_saloane=s.nr_saloane;
    this->saloane=new Salon[s.nr_saloane];
    for(int i=0;i<s.nr_saloane;++i)
        this->saloane[i]=s.saloane[i];
    return *this;
}

string Sectie::get_denumire()
{
    return this->denumire;
}

void Sectie::set_denumire(string denumire)
{
    this->denumire=denumire;
}

string Sectie::get_telefon()
{
    return this->telefon;
}

void Sectie::set_telefon(string telefon)
{
    this->telefon=telefon;
}

char * Sectie::get_mail()
{
    return this->mail;
}

void Sectie::set_mail(char* mail)
{
    if (this->mail!=NULL)
        delete[] this->mail;
    this->mail=new char[strlen(mail)+1];
    strcpy(this->mail,mail);
}

int Sectie::get_aparitie()
{
    return this->aparitie;
}

void Sectie::set_aparitie(int aparitie)
{
    this->aparitie=aparitie;
}

int Sectie::get_nr_dotari()
{
    return this->nr_dotari;
}

void Sectie::set_nr_dotari(int nr_dotari)
{
    this->nr_dotari=nr_dotari;
}

string* Sectie::get_dotari()
{
    return this->dotari;
}

void Sectie::set_dotari(int nr_dotari, string* dotari)
{
    if (this->dotari!=NULL)
        delete[] this->dotari;
    this->dotari=new string[nr_dotari];
    for (int i=0;i<nr_dotari;++i)
        this->dotari[i]=dotari[i];
}

float* Sectie::get_pret()
{
    return this->pret;
}

void Sectie::set_pret(int nr_dotari, float* pret)
{
    if (this->pret!=NULL)
        delete[] this->pret;
    this->pret=new float[nr_dotari];
    for (int i=0;i<nr_dotari;++i)
        this->pret[i]=pret[i];
}

//Setterii si getterii pentru relatia HAS-A
int Sectie::get_nr_saloane()
{
    return this->nr_saloane;
}

void Sectie::set_nr_saloane(int nr_saloane)
{
    this->nr_saloane=nr_saloane;
}

Salon* Sectie::get_saloane()
{
    return this->saloane;
}

void Sectie::set_saloane(int nr_saloane, Salon* saloane)
{
    if (this->saloane!=NULL)
        delete[] this->saloane;
    this->saloane=new Salon[nr_saloane];
    this->nr_saloane=nr_saloane;
    for (int i=0;i<nr_saloane;++i)
        this->saloane[i]=saloane[i];
}

//Clasa abstracta
class Salariat {
protected:
    string nume;
    string prenume;
    double salariu; //Se va trece salariul fara nicio marire - folosim double pentru o precizie mai buna
    float sporuri; //Sporurile difera la fiecare angajat, in functie de sectia la care lucreaza etc., de aceea se vor seta manual
    int gradatia; //Sunt de la 1 la 5 (de fapt, in practica sunt intervale de ani de lucru), pe baza lor se va mai majora salariul cu putin

public:
    Salariat();
    Salariat(string nume, string prenume, double salariu, float sporuri, int gradatia);
    Salariat(const Salariat& slt);

    Salariat& operator=(const Salariat& slt);

    ~Salariat();

    virtual ostream& VirtualWriting(ostream& out) const;
    virtual istream& VirtualReading (istream& in);
    friend istream& operator>>(istream & in, Salariat& slt);
    friend ostream& operator<<(ostream & out, const Salariat& slt);

    friend ifstream& operator>>(ifstream & f, Salariat& slt); //Citire din fisier
    friend ofstream& operator<<(ofstream & g, const Salariat& slt); //Afisare din fisier

    virtual void SalariuFinal()=0;

    string get_nume()
    {
        return this->nume;
    }

    string get_prenume()
    {
        return this->prenume;
    }

    int get_gradatia()
    {
        return this->gradatia;
    }

    float get_salariu()
    {
        return this->salariu;
    }
};

ostream& Salariat::VirtualWriting(ostream& out) const
{
    out<<"NUMELE SALARIATULUI: "<<this->nume<<'\n';
    out<<"PRENUMELE SALARIATULUI: "<<this->prenume<<'\n';
    out<<"SALARIUL ESTE DE "<<this->salariu<<" LEI\n";
    out<<"Sporul este de "<<this->sporuri<<"%"<<'\n';
    out<<"Gradatia "<<this->gradatia<<'\n';
    return out;
}

istream& Salariat::VirtualReading(istream& in)
{
    cout<<"NUMELE SALARIATULUI: ";
    in>>this->nume;
    cout<<'\n';
    char sir[100];
    cout<<"PRENUMELE SALARIATULUI: ";
    in.get();
    in.getline(sir,100);
    string pren(sir);
    this->prenume=pren;
    cout<<'\n';
    cout<<"SALARIUL ESTE: ";
    in>>this->salariu;
    cout<<'\n';
    cout<<"Sporul este (%): ";
    in>>this->sporuri;
    cout<<'\n';
    cout<<"Gradatia ";
    in>>this->gradatia;
    cout<<'\n';
    return in;
}

istream& operator>> (istream& in, Salariat& slt)
{
    return slt.VirtualReading(in);
}

ostream& operator<< (ostream& out, const Salariat& slt)
{
    return slt.VirtualWriting(out);
}

ifstream& operator>>(ifstream & f, Salariat& slt) //Citire din fisier
{
    f>>slt.nume;
    cout<<'\n';
    char sir[100];
    f.get();
    f.getline(sir,100);
    string pren(sir);
    slt.prenume=pren;
    f>>slt.salariu;
    f>>slt.sporuri;
    f>>slt.gradatia;
    return f;
}

ofstream& operator<<(ofstream & g, const Salariat& slt) //Afisare din fisier
{
    g<<"NUMELE SALARIATULUI: "<<slt.nume<<'\n';
    g<<"PRENUMELE SALARIATULUI: "<<slt.prenume<<'\n';
    g<<"SALARIUL ESTE DE "<<slt.salariu<<" LEI\n";
    g<<"Sporul este de "<<slt.sporuri<<"%"<<'\n';
    g<<"Gradatia "<<slt.gradatia<<'\n';
    return g;

}
Salariat::Salariat()
{
    this->nume="-";
    this->prenume="-";
    this->salariu=0;
    this->sporuri=0;
}

Salariat::Salariat(string nume,string prenume,double salariu, float sporuri, int gradatia)
{
    this->nume=nume;
    this->prenume=prenume;
    this->salariu=salariu;
    this->sporuri=sporuri;
    this->gradatia=gradatia;
}

Salariat::Salariat (const Salariat& slt)
{
    this->nume=slt.nume;
    this->prenume=slt.prenume;
    this->salariu=slt.salariu;
    this->sporuri=slt.sporuri;
    this->gradatia=slt.gradatia;
}

Salariat& Salariat::operator=(const Salariat& slt)
{
    if (this!=&slt)
    {
        this->nume=slt.nume;
        this->prenume=slt.prenume;
        this->salariu=slt.salariu;
        this->sporuri=slt.sporuri;
        this->gradatia=slt.gradatia;
    }
    return *this;
}

Salariat::~Salariat() //Destructorul ramane gol
{
}

class Asistenta: public Salariat {
private:
    string data_angajarii;
public:
    Asistenta();
    Asistenta(string nume, string prenume, double salariu, float sporuri, int gradatia,
                        string data_angajarii);
    Asistenta(const Asistenta& asist);

    Asistenta& operator= (const Asistenta& asist);

    ~Asistenta();

    virtual ostream& VirtualWriting(ostream& out) const;
    virtual istream& VirtualReading(istream& in);

    friend ifstream& operator>>(ifstream & f, Asistenta& asist); //Citire din fisier
    friend ofstream& operator<<(ofstream & g, const Asistenta& asist); //Afisare din fisier

    void SalariuFinal()
    {
        double salar;
        salar=this->salariu+this->salariu*(this->sporuri/100);
        if (this->gradatia==1)
            salar+=salar*0.075;
        else
            if (this->gradatia==2||this->gradatia==3)
                salar+=salar*0.05;
        else
                salar+=salar*0.025;
        cout<<"Salariul cu sporuri este de "<<fixed<<setprecision(2)<<salar<<" lei -> salariat: "<<this->nume<<" "<<this->prenume<<'\n';
    }
};

istream& Asistenta::VirtualReading(istream& in)
{
    Salariat::VirtualReading(in);
    cout<<"Data la care s-a angajat asistenta este ";
    in>>this->data_angajarii;
    cout<<'\n';
    return in;
}

ostream& Asistenta::VirtualWriting(ostream& out) const
{
    Salariat::VirtualWriting(out);
    out<<"Data la care s-a angajat asistenta este "<<this->data_angajarii<<'\n';
    return out;
}

ifstream& operator>>(ifstream & f, Asistenta& asist) //Citire din fisier
{
    f>>(Salariat&)asist;
    f>>asist.data_angajarii;
    return f;
}

ofstream& operator<<(ofstream & g, const Asistenta& asist) //Afisare din fisier
{
    g<<(Salariat&)asist;
    g<<"Data la care s-a angajat asistenta este "<<asist.data_angajarii;
    return g;
}

Asistenta::Asistenta():Salariat()
{
    this->data_angajarii="dd.mm.yyyy"; //Data va fi de tipul zi/luna/an ori cu caracterul '/', ori cu '.' -> la alegere
}

Asistenta::Asistenta(string nume, string prenume, double salariu, float sporuri, int gradatia,
                     string data_angajarii): Salariat(nume, prenume, salariu, sporuri, gradatia)
{
    this->data_angajarii=data_angajarii;
}

Asistenta::Asistenta(const Asistenta& asist):Salariat(asist)
{
    this->data_angajarii=asist.data_angajarii;
}

Asistenta& Asistenta::operator=(const Asistenta& asist)
{
    if (this!=&asist)
    {
        Salariat::operator=(asist);
        this->data_angajarii=asist.data_angajarii;
    }
    return *this;
}
Asistenta::~Asistenta() //Destructorul ramane gol
{
}

class Brancardier: public Salariat {
private:
    string data_angajarii;
public:
    Brancardier();
    Brancardier(string nume, string prenume, double salariu, float sporuri, int gradatia,
                        string data_angajarii);
    Brancardier(const Brancardier& br);

    Brancardier& operator= (const Brancardier& br);

    ~Brancardier();

    virtual ostream& VirtualWriting(ostream& out) const;
    virtual istream& VirtualReading(istream& in);

    friend ifstream& operator>>(ifstream & f, Brancardier& br); //Citire din fisier
    friend ofstream& operator<<(ofstream & g, const Brancardier& br); //Afisare din fisier

    void SalariuFinal()
    {
        double salar;
        salar=this->salariu+this->salariu*(this->sporuri/100);
        if (this->gradatia==1) //Majorarile de gradatii sunt diferite la brancardieri fata de asistente
            salar+=salar*0.05;
        else
            if (this->gradatia==2||this->gradatia==3)
                salar+=salar*0.025;
        else
                salar+=salar*0.01;
        cout<<"Salariul cu sporuri este de "<<fixed<<setprecision(2)<<salar<<" lei -> salariat: "<<this->nume<<" "<<this->prenume<<'\n';
    }
};

istream& Brancardier::VirtualReading(istream& in)
{
    Salariat::VirtualReading(in);
    cout<<"Data la care s-a angajat brancardierul este ";
    in>>this->data_angajarii;
    cout<<'\n';
    return in;
}

ostream& Brancardier::VirtualWriting(ostream& out) const
{
    Salariat::VirtualWriting(out);
    out<<"Data la care s-a angajat brancardierul este "<<this->data_angajarii<<'\n';
    return out;
}

ifstream& operator>>(ifstream & f, Brancardier& br) //Citire din fisier
{
    f>>(Salariat&)br;
    f>>br.data_angajarii;
    return f;
}

ofstream& operator<<(ofstream & g, const Brancardier& br) //Afisare din fisier
{
    g<<(Salariat&)br;
    g<<"Data la care s-a angajat brancardierul este "<<br.data_angajarii;
    return g;
}

Brancardier::Brancardier():Salariat()
{
    this->data_angajarii="dd.mm.yyyy";
}

Brancardier::Brancardier(string nume, string prenume, double salariu, float sporuri, int gradatia,
                         string data_angajarii): Salariat(nume, prenume, salariu, sporuri, gradatia)
{
    this->data_angajarii=data_angajarii;
}

Brancardier::Brancardier(const Brancardier& br):Salariat(br)
{
    this->data_angajarii=br.data_angajarii;
}

Brancardier& Brancardier::operator=(const Brancardier& br)
{
    if (this!=&br)
    {
        Salariat::operator=(br);
        this->data_angajarii=br.data_angajarii;
    }
    return *this;
}

Brancardier::~Brancardier() //Destructorul ramane gol
{
}

template <class tip_clasa> //Pentru case 19 si case 20
int suma(int a, tip_clasa b)
{
    return a+b->get_varsta();
}

template <class tip_clasa> //Pentru case 21
int maxim(int a, tip_clasa b)
{
    return (a>b.get_nr_dotari())?a:b.get_nr_dotari();
}

template <class tip_clasa> //Pentru case 22
int minim(int a, tip_clasa b)
{
    return (a<b->get_nr_medicamente())?a:b->get_nr_medicamente();
}

template <class tip_clasa1,class tip_clasa2> //Pentru case 23
void func_swap(tip_clasa1 &arg1, tip_clasa2 &arg2)
{
  int temp1,temp2;
  temp1=arg1.get_varsta();
  temp2=arg2.get_varsta();
  arg1.set_varsta(temp2);
  arg2.set_varsta(temp1);
}

class Meniu{
private:
    static Meniu *obiect;
public:
    static Meniu* getInstance()
    {
        if(!obiect)
            obiect=new Meniu();
        return obiect;
    }

    void meniu()
    {//Pentru pacienti - list, pentru medici - vector, pentru retete - set, pentru sectii - map

         list <Pacient*> ListaPacienti;
         vector <Medic*> VectorMedici;
         set <Reteta*> SetRetete;
         map <int,Sectie> MapSectii;
        int k=1;
        int i=0, key=0;
        while(k==1)
            {
                cout<<"1 - Import pacient\n"; //Importul se face printr-o citire de la tastatura
                cout<<"2 - Import medic\n";
                cout<<"3 - Import reteta\n";
                cout<<"4 - Import sectie\n";
                cout<<"5 - Export pacienti\n"; //Exportul se va face in fisierul Cabinet.out
                cout<<"6 - Export medici\n";
                cout<<"7 - Export retete\n";
                cout<<"8 - Export sectii\n";
                cout<<"9 - Functionalitate pacienti\n"; //Functionalitatile se vor afisa pe ecran
                cout<<"10 - Functionalitate medici\n";
                cout<<"11 - Functionalitate retete\n";
                cout<<"12 - Functionalitate sectii\n";
                cout<<"13 - Export toate clasele\n"; //Se va afisa in Cabinet.out
                cout<<"14 - Salariul unui medic rezident\n";
                cout<<"15 - Salariul unei asistente medicale\n";
                cout<<"16 - Salariul unui brancardier\n";
                cout<<"17 - Cat costa o reteta semi-compensata\n";
                cout<<"18 - Reducerea pe camera a unui pacient\n";
                cout<<"19 - Suma varstelor pacientilor\n";
                cout<<"20 - Suma varstelor medicilor\n";
                cout<<"21 - Numarul maxim de dotari dintr-o sectie\n";
                cout<<"22 - Numarul minim de medicamente prescrise\n";
                cout<<"23 - Template swap varste\n"; //Citirea se face din Cabinet.in si se vor afisa integral in Cabinet.out si pe scurt pe consola
                cout<<"999 - EXIT\n";
                int comanda;
                cin>>comanda;
                switch(comanda)
                {
                    case 1:
                        {
                            Pacient* p=new Pacient;
                            cin>>*p;
                            ListaPacienti.push_back(p);
                            cout<<'\n';
                            break;
                        }
                    case 2:
                        {
                            Medic* m=new Medic;
                            cin>>*m;
                            VectorMedici.push_back(m);
                            cout<<'n';
                            break;
                        }
                    case 3:
                        {
                            Reteta* r=new Reteta;
                            cin>>*r;
                            SetRetete.insert(r);
                            cout<<'\n';
                            break;
                        }
                    case 4:
                        {
                            Sectie s;
                            cin>>s;
                            MapSectii.insert(pair<int,Sectie>(++key,s));
                            cout<<'\n';
                            break;
                        }
                    case 5:
                        {
                            list <Pacient*>::iterator it;
                            for(it=ListaPacienti.begin();it!=ListaPacienti.end();++it)
                                g<<*(*it)<<'\n';
                            break;
                        }
                    case 6:
                        {
                            for(auto ir=VectorMedici.begin();ir!=VectorMedici.end();++ir)
                                g<<(*(*ir))<<'\n';
                                break;
                        }
                    case 7:
                        {
                            set<Reteta*>::iterator itr;
                            for (itr=SetRetete.begin();itr!=SetRetete.end();++itr)
                                g<<*(*itr)<<'\n';
                            break;
                        }
                    case 8:
                        {
                            map<int, Sectie>::iterator iter;
                            for (iter=MapSectii.begin();iter!=MapSectii.end(); ++iter)
                                g<<"CHEIE: "<<iter->first<<'\n'<<iter->second<<'\n';
                            break;
                        }
                    case 9:
                        {
                            list <Pacient*>::iterator it;
                            for(it=ListaPacienti.begin();it!=ListaPacienti.end();++it)
                                (*it)->BMI();
                            cout<<'\n';
                            break;
                        }
                    case 10:
                        {
                            for(auto ir=VectorMedici.begin();ir!=VectorMedici.end();++ir)
                                (*ir)->Bonus();
                            cout<<'\n';
                            break;
                        }
                    case 11:
                        {
                            set<Reteta*>::iterator itr;
                            for (itr=SetRetete.begin();itr!=SetRetete.end();++itr)
                                (*itr)->SumaMed();
                            cout<<'\n';
                            break;

                        }
                    case 12:
                        {
                            map<int, Sectie>::iterator iter;
                            for (iter=MapSectii.begin();iter!=MapSectii.end(); ++iter)
                                {
                                    Sectie sec;
                                    sec=iter->second;
                                    sec.Consultatii();
                                }
                            cout<<'\n';
                            break;
                        }
                    case 13:
                        {
                            list <Pacient*>::iterator it;
                            for(it=ListaPacienti.begin();it!=ListaPacienti.end();++it)
                                g<<*(*it)<<'\n';

                            for(auto ir=VectorMedici.begin();ir!=VectorMedici.end();++ir)
                                g<<(*(*ir))<<'\n';

                            set<Reteta*>::iterator itr;
                            for (itr=SetRetete.begin();itr!=SetRetete.end();++itr)
                                g<<*(*itr)<<'\n';

                             map<int, Sectie>::iterator iter;
                            for (iter=MapSectii.begin();iter!=MapSectii.end(); ++iter)
                                g<<"CHEIE: "<<iter->first<<'\n'<<iter->second<<'\n';

                             break;
                        }
                    case 14:
                        {
                            Rezident rez;
                            cin>>rez;
                            rez.SalariuRezident();
                            break;
                        }
                    case 15:
                        {
                            Asistenta as;
                            cin>>as;
                            as.SalariuFinal();
                            break;
                        }
                    case 16:
                        {
                            Brancardier br;
                            cin>>br;
                            br.SalariuFinal();
                            break;
                        }
                    case 17:
                        {
                            RetetaCompensata rc;
                            cin>>rc;
                            rc.SumaCompensata();
                            break;
                        }
                    case 18:
                        {
                            Salon sal;
                            cin>>sal;
                            sal.ReducereEtaj();
                            break;
                        }
                    case 19:
                        {
                            int s=0;
                            list <Pacient*>::iterator it;
                            for(it=ListaPacienti.begin();it!=ListaPacienti.end();++it)
                                s=suma(s,*it);
                            cout<<"Suma varstelor pacientilori internati este: "<<s<<'\n';
                            break;
                        }
                    case 20:
                        {
                            int sum=0;
                            for(auto ir=VectorMedici.begin();ir!=VectorMedici.end();++ir)
                                sum=suma(sum,*ir);
                            cout<<"Suma varstelor medicilori angajati este: "<<sum<<'\n';
                            break;
                        }
                    case 21:
                        {
                            int maxi=INT_MIN;
                            map<int, Sectie>::iterator iter;
                            for (iter=MapSectii.begin();iter!=MapSectii.end(); ++iter)
                                {
                                    Sectie sec;
                                    sec=iter->second;
                                    maxi=maxim(maxi,sec);
                                }
                            cout<<"Avem maxim "<<maxi<<" dotari la o sectie!\n";;
                            break;
                        }
                    case 22:
                        {
                            int mini=INT_MAX;
                            set<Reteta*>::iterator itr;
                            for (itr=SetRetete.begin();itr!=SetRetete.end();++itr)
                                mini=minim(mini,*itr);
                            cout<<"S-au prescris minim "<<mini<<" medicamente pe o reteta!\n";
                            break;
                        }
                    case 23:
                        {
                            Pacient pacient1;
                            Medic medic1;
                            f>>pacient1;
                            f>>medic1;
                            if (pacient1.get_varsta()<medic1.get_varsta()/2)
                            {
                                func_swap(pacient1,medic1);
                                g<<pacient1<<'\n';
                                g<<medic1<<'\n';
                                cout<<"VARSTE INTRODUSE GRESIT!\n";
                                cout<<"Pacientul avea varsta de "<<medic1.get_varsta()<<" ani, acum are varsta de "<<pacient1.get_varsta()<<"!\n";
                                cout<<"Medicul avea varsta de "<<pacient1.get_varsta()<<" ani, acum are varsta de "<<medic1.get_varsta()<<"!\n";
                            }
                            else
                            {
                                g<<pacient1<<'\n';
                                g<<medic1<<'\n';
                                cout<<"Varstele nu s-au schimbat, deoarece nu au indeplinit conditia!\n";
                            }
                            break;
                        }
                    case 999:
                        {
                            k=0;
                            break;
                        }
                }
           }
        }

};
Meniu* Meniu::obiect=0;

int main()
{
    Meniu *meniulMeu=meniulMeu->getInstance(); //Meniu de tip Singletone
    meniulMeu->meniu();

    /**
     Pacient pa1;
                            f>>pa1;
                            g<<pa1<<'\n';
                            Medic me1;
                            f>>me1;
                            g<<me1<<'\n';
                            Rezident re1;
                            f>>re1;
                            g<<re1<<'\n';
                            Reteta rete1;
                            f>>rete1;
                            g<<rete1<<'\n';
                            RetetaCompensata reco1;
                            f>>reco1;
                            g<<reco1<<'\n';
                            Salon salo1;
                            f>>salo1;
                            g<<salo1<<'\n';
                            Sectie se1;
                            f>>se1;
                            g<<se1;
                            Asistenta asi1;
                            f>>asi1;
                            g<<asi1<<'\n';
                            g<<'\n';
                            Brancardier bra1;
                            f>>bra1;
                            g<<bra1<<'\n';
    **/

    /**cout<<"INTRODUCETI UN COD DIN MULTIMEA: {1, 2, 3, 4} PENTRU A VA ALEGE O CLASA"<<'\n';
    cout<<"1 - Clasa Pacient - informatii despre pacienti"<<'\n';
    cout<<"2 - Clasa Medic - informatii despre medici"<<'\n';
    cout<<"3 - Clasa Reteta - retetele prescrise de medici pacientilor"<<'\n';
    cout<<"4 - Clasa Sectie - informatii despre sectiile existente"<<'\n';
    cout<<"5 - Clasa abstracta -> Salariati: ASISTENTE SI BRANCARDIERI"<<'\n';
    cout<<"6 - Clasa Saloane - cea creata pentru relatia Sectie HAS-A Salon"<<'\n';
    cout<<"7 - EXIT"<<'\n';
    int cod;
    while (cod!=7)
    {
        cout<<"Introduceti codul: ";
        cin>>cod;
        cout<<'\n';
        if (cod==1)
        {
            char prenume[]="Alexandra";
            string boli1[]={"sinuzita","scolioza","astm"}, boli2[]={"carii","pneumonie"};
            int perioada1[]={2,6,1}, perioada2[]={1,2};
            Pacient p1("Florea",prenume,'F',19,165,48.5,1,3,boli1,perioada1); //Constructorul cu toti paramentrii
            Pacient p2("Stan",prenume); //Constructorul cu 2 parametrii
            Pacient p3(p1); //Copy constrctorul
            Pacient p4;
            p4=p1;//Operatorul =
            cout<<p1<<'\n'; //Operatorul <<
            cout<<p2<<'\n';
            cout<<p4<<'\n';
            //Getterii
            cout<<'\n';
            cout<<p1.get_nume()<<'\n';
            cout<<p1.get_prenume()<<'\n';
            cout<<p1.get_initiala_tata()<<'\n';
            cout<<p1.get_inaltimea()<<'\n';
            cout<<p1.get_greutatea()<<'\n';
            cout<<p1.get_id_pacient()<<'\n';
            cout<<p1.get_asigurat()<<'\n';
            cout<<p1.get_nr_afectiuni()<<'\n';
            string* afect=p1.get_afectiuni();
            int* per=p1.get_perioada_afectiunii();
            for (int i=0;i<p1.get_nr_afectiuni();++i)
                cout<<afect[i]<<" timp de "<<per[i]<<" ani"<<'\n';
            cout<<'\n';
            p1.BMI(); //Functionalitatea
            Pacient p5; //Constructorul fara param
            //Setterii
            char prenume2[]="Andrei";
            p5.set_prenume(prenume2);
            p5.set_nume("Georgescu");
            p5.set_initiala_tata('T');
            p5.set_inaltimea(189.5); //in cm
            p5.set_greutatea(90.7); //in kg
            p5.set_nr_afectiuni(1);
            string afect2[]={"astm"};
            int per2[]={2};
            p5.set_afectiuni(1,afect2);
            p5.set_perioada_afectiunii(1,per2);
            cout<<p5<<'\n';
        }
        else
        if (cod==3)
        {
            char nume1[]="Florea Alexandra", nume2[]="Florea Anca";
            char medic1[]="Paltin", medic2[]="Bornea";
            char data1[]="25/06/2020", data2[]="28/02/2021";
            float pret1[]={25.6,12,3};
            int cantitate1[]={2,1,2};
            string denumire1[]={"nurofen","decasept","paracetamol"};
            Reteta r1(nume1,medic1,data1,19,3,pret1,cantitate1,denumire1); //Constructorul cu toti paramentrii
            Reteta r2(nume2,medic2,data2); //Constructorul cu 2 parametrii
            Reteta r3(r1); //Copy constrctorul
            Reteta r4;
            r4=r1; //Operatorul =
            cout<<r1<<'\n'; //Operatorul <<
            cout<<r2<<'\n';
            cout<<r4<<'\n';
            //Getterii
            cout<<'\n';
            cout<<r1.get_pacient()<<'\n';
            cout<<r1.get_medic()<<'\n';
            cout<<r1.get_data()<<'\n';
            cout<<r1.get_varsta()<<'\n';
            cout<<r1.get_nr_medicamente()<<'\n';
            float* preturi=r1.get_pret();
            int* cant=r1.get_cantitate();
            string* denum=r1.get_denumire_comerciala();
            for (int i=0;i<r1.get_nr_medicamente();++i)
                cout<<"Medicamentul "<<denum[i]<<" in cantitate de "<<cant[i]<<" la pretul de "<<preturi[i]<<" lei"<<'\n';
            cout<<'\n';
            r1.SumaMed(); //Functionalitatea
            cout<<'\n';
            Reteta r5; //Constructorul fara param
            //Setterii
            char nume3[]="Florea Florin", medic3[]="Dragomir";
            r5.set_pacient(nume3);
            r5.set_medic(medic3);
            r5.set_varsta(59);
            r5.set_data("13/09/2019");
            r5.set_nr_medicamente(2);
            float pret3[]={12.7,8.9};
            int cant3[]={1,5};
            string den3[]={"algocalim","ibuprofen"};
            r5.set_pret(2,pret3);
            r5.set_cantitate(2,cant3);
            r5.set_denumire_comerciala(2,den3);
            cout<<r5<<'\n';
            r5=r5+1;
            cout<<r5<<'\n';
        }
        else
        if (cod==2)
        {
            char nume1[]="Dumitrescu", nume2[]="Grigorescu";
            char prenume1[]="Gheorghe", prenume2[]="Dan";
            string sectie1[]={"Cardiologie","UPU"};
            bool specialist1[]={1,0};
            Medic m1(nume1,prenume1,29,2,sectie1,specialist1); //Constructorul cu toti paramentrii
            Medic m2(nume2,prenume2); //Constructorul cu 2 parametrii
            Medic m3(m1); //Copy constrctorul
            Medic m4;
            m4=m1;//Operatorul =
            cout<<m1<<'\n'; //Operatorul <<
            cout<<m2<<'\n';
            cout<<m4<<'\n';
            //Getterii
            cout<<'\n';
            cout<<m1.get_nume()<<'\n';
            cout<<m1.get_prenume()<<'\n';
            cout<<m1.get_varsta()<<'\n';
            cout<<m1.get_nr_sectii()<<'\n';
            string* lucreaza=m1.get_sectie();
            bool* spec=m1.get_specialist();
            for (int i=0;i<m1.get_nr_sectii();++i)
                if (spec[i]) //inseamna ca e specialist
                    cout<<"Lucreaza la sectia "<<lucreaza[i]<<" si este medic specialist"<<'\n';
                else
                    cout<<"Lucreaza la sectia "<<lucreaza[i]<<" si este medic primar"<<'\n';
            cout<<'\n';
            m1.Bonus(); //Functionalitatea
            cout<<'\n';
            Medic m5; //Constructorul fara param
            //Setterii
            char nume3[]="Paltin", prenume3[]="Mariana";
            m5.set_nume(nume3);
            m5.set_prenume(prenume3);
            m5.set_varsta(54);
            m5.set_nr_sectii(2);
            string sectii3[]={"Oncologie","Ginecologie"};
            bool specialist3[]={1,1};
            m5.set_sectie(2,sectii3);
            m5.set_specialist(2,specialist3);
            cout<<m5<<'\n';
        }
        else
        if (cod==4)
        {
            char den1[]="Cardiologie", den2[]="Pediatrie";
            char tel1[]="0756432567", tel2[]="0789657434";
            char email1[]="cardio@gmail.ro",email2[]="pediatr@gmail.ro";
            Salon sal1(1,2); //intai e etajul, apoi camera
            cout<<sal1<<'\n';
            string dotari1[]={"ecocardiograf","electrocardiografe","ecg"},dotari2[]={"cantar","glucoteste"};
            float pret1[]={200,250,150}, pret2[]={30,50};
            Salon saloane[1];
            saloane[0] = sal1;
            Sectie s1(den1,tel1,email1,5,3,dotari1,pret1,1,saloane); //Constructorul cu toti paramentrii
            Sectie s2(den2,tel2,email2); //Constructorul cu 2 parametrii
            Sectie s3(s1); //Copy constrctorul
            Sectie s4;
            s4=s1;//Operatorul =
            cout<<s1<<'\n'; //Operatorul <<
            cout<<s2<<'\n';
            cout<<s4<<'\n';
            //Getterii
            cout<<'\n';
            cout<<s1.get_denumire()<<'\n';
            cout<<s1.get_telefon()<<'\n';
            cout<<s1.get_mail()<<'\n';
            cout<<s1.get_aparitie()<<'\n';
            string* dot=s1.get_dotari();
            float* preturi=s1.get_pret();
            for (int i=0;i<s1.get_nr_dotari();++i)
                cout<<dot[i]<<" costa "<<preturi[i]<<'\n';
            Salon* sali=s1.get_saloane();
            for (int i=0;i<s1.get_nr_saloane();++i)
                cout<<sali[i]<<" ";
            cout<<'\n';
            s1.Consultatii(); //Functionalitatea
            cout<<'\n';
            Sectie s5; //Constructorul fara param
            //Setterii
            char den3[]="UPU";
            s5.set_denumire(den3);
            s5.set_telefon("0786543787");
            s5.set_mail("urgente@gmail.ro");
            s5.set_aparitie(2);
            s5.set_nr_dotari(3);
            string dot3[]={"solutii perfuzabile","targi","monitoare"};
            float pret3[]={15,300,20};
            s5.set_dotari(3,dot3);
            s5.set_pret(3,pret3);
            s5.set_saloane(1,saloane);
            cout<<s5<<'\n';
        }
        else
        if (cod==5)
        {
            Asistenta as("Stan", "Veronica", 2500, 25, 3, "13.04.2016");
            as.SalariuFinal();
            Brancardier br("Popescu","Valentin",1800, 20, 5, "12.04.2018");
            br.SalariuFinal();
        }
        else
        if (cod==6)
        {
            Salon s1(2,3);
            cout<<s1<<'\n';
            s1.ReducereEtaj();
            cout<<'\n';
            Salon s2;
            s2.set_camera(5);
            s2.set_etaj(76);
            s2.ReducereEtaj();
            cout<<'\n';
            cout<<s2<<'\n';
            cout<<"Getteri: ";
            cout<<s1.get_camera()<<" "<<s1.get_etaj()<<'\n';
        }
        cout<<"EXIT"<<'\n';
    }**/

    return 0;
}
