/*Rapcea Catalin 142
Codeblocks
CONSTANTIN GABRIEL MAJERI*/


#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Drum{
protected:
    string denumire;
    double lungime;
    int tronsoane;
public:
    Drum();
    Drum(string denumire, double lungime, int tronsoane);
    Drum(const Drum &ob);
    Drum& operator=(const Drum &ob);
    virtual ~Drum();
    string getDenumire() const;
    double getLungime() const;
    int getTronsoane() const;
    void setDenumire(const string nume);
    void setLungime(const double l);
    void setTronsoane(const int t);
    friend istream& operator>>(istream& is, Drum& ob);
    friend ostream& operator<<(ostream& os, Drum& ob);
};
Drum::Drum(){}
Drum::Drum(string denumire, double lungime, int tronsoane):denumire(denumire), lungime(lungime), tronsoane(tronsoane){}
Drum::Drum(const Drum &ob){
    this->denumire = ob.denumire;
    this->lungime = ob.lungime;
    this->tronsoane = ob.tronsoane;
}
Drum& Drum::operator=(const Drum &ob){
    denumire = ob.denumire;
    lungime = ob.lungime;
    tronsoane = ob.tronsoane;
    return *this;
}
Drum:: ~Drum(){
    denumire.clear();
    lungime = 0;
    tronsoane = 0;
}
string Drum::getDenumire() const{
    return denumire;
}
double Drum::getLungime() const{
    return lungime;
}
int Drum::getTronsoane() const{
    return tronsoane;
}
void Drum::setDenumire(const string nume){
    denumire = nume;
}
void Drum::setLungime(const double l){
    lungime = l;
}
void Drum::setTronsoane(const int t){
    tronsoane = t;
}
istream& operator>>(istream& is, Drum& ob){
    cout<<"Denumirea:";
    is>>ob.denumire;
    cout<<"Lungimea:";
    is>>ob.lungime;
    cout<<"Nr de tronsoane:";
    is>>ob.tronsoane;
//    try{
//        while(true){
//            is>>ob.tronsoane;
//            if(ob.tronsoane <= 0)
//                throw("Nr de tronsoane gresit");
//            else break;
//            }
//    }
//    catch(string s){cout<<s;}

    return is;
}
ostream& operator<<(ostream& os, Drum& ob){
    os<<"Denumirea:"<<ob.lungime<<"\n"<<"Lungimea:"<<ob.lungime<<"\n"<<"Nr de tronsoane:"<<ob.tronsoane;
    return os;
}




class National:virtual public Drum{
    int judete;
public:
    National();
    National(string denumire, double lungime, int tronsoane, int judete);
    National(const National &ob);
    National& operator=(const National &ob);
    virtual ~National();
        friend istream& operator>>(istream& is, National& ob);
    friend ostream& operator<<(ostream& os, National& ob);
};
National::National(){}
National::National(string denumire, double lungime, int tronsoane, int judete):Drum(denumire, lungime, tronsoane), judete(judete){}
National::National(const National &ob){
    this->denumire = ob.denumire;
    this->lungime = ob.lungime;
    this->tronsoane = ob.tronsoane;
    this->judete = ob.judete;
}
National& National::operator=(const National &ob){
    denumire = ob.denumire;
    lungime = ob.lungime;
    tronsoane = ob.tronsoane;
    judete = ob.judete;
    return *this;
}
National:: ~National(){
    denumire.clear();
    lungime = 0;
    tronsoane = 0;
    judete = 0;
}
istream& operator>>(istream& is, National& ob){
    cout<<"Denumirea:";
    is>>ob.denumire;
    cout<<"Lungimea:";
    is>>ob.lungime;
    cout<<"Nr de tronsoane:";
    is>>ob.tronsoane;
    cout<<"Nr de judete:";
    is>>ob.judete;
    return is;
}
ostream& operator<<(ostream& os, National& ob){
    os<<"Denumirea:"<<ob.lungime<<"\n"<<"Lungimea:"<<ob.lungime<<"\n"<<"Nr de tronsoane:"<<ob.tronsoane<<"\n"<<"Nr de judete:"<<ob.judete;
    return os;
}






class European:virtual public Drum{
protected:
    int tari;
public:
    European();
    European(string denumire, double lungime, int tronsoane, int tari);
    European(const European &ob);
    European& operator=(const European &ob);
    virtual ~European();
        friend istream& operator>>(istream& is, European& ob);
    friend ostream& operator<<(ostream& os, European& ob);
};
European::European(){}
European::European(string denumire, double lungime, int tronsoane, int tari):Drum(denumire, lungime, tronsoane), tari(tari){}
European::European(const European &ob){
    this->denumire = ob.denumire;
    this->lungime = ob.lungime;
    this->tronsoane = ob.tronsoane;
    this->tari = ob.tari;
}
European& European::operator=(const European &ob){
    denumire = ob.denumire;
    lungime = ob.lungime;
    tronsoane = ob.tronsoane;
    tari = ob.tari;
    return *this;
}
European:: ~European(){
    denumire.clear();
    lungime = 0;
    tronsoane = 0;
    tari = 0;
}
istream& operator>>(istream& is, European& ob){
    cout<<"Denumirea:";
    is>>ob.denumire;
    cout<<"Lungimea:";
    is>>ob.lungime;
    cout<<"Nr de tronsoane:";
    is>>ob.tronsoane;
    cout<<"Nr de tari:";
    is>>ob.tari;
    return is;
}
ostream& operator<<(ostream& os, European& ob){
    os<<"Denumirea:"<<ob.lungime<<"\n"<<"Lungimea:"<<ob.lungime<<"\n"<<"Nr de tronsoane:"<<ob.tronsoane<<"\n"<<"Nr de tari:"<<ob.tari;
    return os;
}




class Autostrada:virtual public Drum{
protected:
    int benzi;
public:
    Autostrada();
    Autostrada(string denumire, double lungime, int tronsoane, int benzi);
    Autostrada(const Autostrada &ob);
    Autostrada& operator=(const Autostrada &ob);
    virtual ~Autostrada();
        friend istream& operator>>(istream& is, Autostrada& ob);
    friend ostream& operator<<(ostream& os, Autostrada& ob);
};
Autostrada::Autostrada(){}
Autostrada::Autostrada(string denumire, double lungime, int tronsoane, int benzi):Drum(denumire, lungime, tronsoane), benzi(benzi){}
Autostrada::Autostrada(const Autostrada &ob){
    this->denumire = ob.denumire;
    this->lungime = ob.lungime;
    this->tronsoane = ob.tronsoane;
    this->benzi = ob.benzi;
}
Autostrada& Autostrada::operator=(const Autostrada &ob){
    denumire = ob.denumire;
    lungime = ob.lungime;
    tronsoane = ob.tronsoane;
    benzi = ob.benzi;
    return *this;
}
Autostrada:: ~Autostrada(){
    denumire.clear();
    lungime = 0;
    tronsoane = 0;
    benzi = 0;
}
istream& operator>>(istream& is, Autostrada& ob){
    cout<<"Denumirea:";
    is>>ob.denumire;
    cout<<"Lungimea:";
    is>>ob.lungime;
    cout<<"Nr de tronsoane:";
    is>>ob.tronsoane;
    cout<<"Nr de benzi:";
    is>>ob.benzi;
    return is;
}
ostream& operator<<(ostream& os, Autostrada& ob){
    os<<"Denumirea:"<<ob.lungime<<"\n"<<"Lungimea:"<<ob.lungime<<"\n"<<"Nr de tronsoane:"<<ob.tronsoane<<"\n"<<"Nr de benzi:"<<ob.benzi;
    return os;
}







class AutostradaEuropeana:public European, public Autostrada{
    int tari;
    int benzi;
public:
    AutostradaEuropeana();
    AutostradaEuropeana(string denumire, double lungime, int tronsoane, int tari, int benzi);
    AutostradaEuropeana(const AutostradaEuropeana &ob);
    AutostradaEuropeana& operator=(const AutostradaEuropeana &ob);
    virtual ~AutostradaEuropeana();
        friend istream& operator>>(istream& is, AutostradaEuropeana& ob);
    friend ostream& operator<<(ostream& os, AutostradaEuropeana& ob);
};
AutostradaEuropeana::AutostradaEuropeana(){}
AutostradaEuropeana::AutostradaEuropeana(string denumire, double lungime, int tronsoane, int tari, int benzi):European(denumire, lungime, tronsoane, tari),
        Autostrada(denumire, lungime, tronsoane, benzi){}
AutostradaEuropeana::AutostradaEuropeana(const AutostradaEuropeana &ob){
    this->denumire = ob.denumire;
    this->lungime = ob.lungime;
    this->tronsoane = ob.tronsoane;
    this->tari = ob.tari;
    this->benzi = ob.benzi;
}
AutostradaEuropeana& AutostradaEuropeana::operator=(const AutostradaEuropeana &ob){
    denumire = ob.denumire;
    lungime = ob.lungime;
    tronsoane = ob.tronsoane;
    tari = ob.tari;
    benzi = ob.benzi;
    return *this;
}
AutostradaEuropeana:: ~AutostradaEuropeana(){
    denumire.clear();
    lungime = 0;
    tronsoane = 0;
    tari = 0;
    benzi = 0;
}
istream& operator>>(istream& is, AutostradaEuropeana& ob){
    cout<<"Denumirea:";
    is>>ob.denumire;
    cout<<"Lungimea:";
    is>>ob.lungime;
    cout<<"Nr de tronsoane:";
    is>>ob.tronsoane;
    cout<<"Nr de tari:";
    is>>ob.tari;
    cout<<"Nr de benzi:";
    is>>ob.benzi;
    return is;
}
ostream& operator<<(ostream& os, AutostradaEuropeana& ob){
    os<<"Denumirea:"<<ob.lungime<<"\n"<<"Lungimea:"<<ob.lungime<<"\n"<<"Nr de tronsoane:"<<ob.tronsoane<<"\n"<<"Nr de tari:"<<ob.tari<<"\n"<<"Nr de benzi:"<<ob.benzi;
    return os;
}



class Contract{
    int id;
    static int nr;
    string nume;
    string cif;
    Drum* drum;
    int tronson;
public:
    Contract();
    Contract(string nume, string cif);
    Contract(const Contract &ob);
    Contract& operator=(const Contract &ob);
    ~Contract();
    int getId() const;
    string getNume() const;
    string getCIF() const;
    static int getNr(){return nr;cout<<nr;}
    void setNume(const string n);
    void setCIF(const string c);
    void setDrum(Drum* d, const int t){
        drum = d;
        tronson = t;
    }
    friend istream& operator>>(istream& is, Contract& ob);
    friend ostream& operator<<(ostream& os, Contract& ob);
};
int Contract::nr=0;
//int Contract::getNr(){
//    return nr;
//}
Contract::Contract(){}
Contract::Contract(string nume, string cif): nume(nume), cif(cif){nr++;cout<<"asa"<<nr; id=nr;}
Contract::Contract(const Contract &ob){
    this->id = ob.id;
    this->nume = ob.nume;
    this->cif = ob.cif;
}
Contract& Contract::operator=(const Contract &ob){
    id = ob.id;
    nume = ob.nume;
    cif = ob.cif;
    return *this;
}
Contract:: ~Contract(){
    nume.clear();
    id = 0;
    cif.clear();
}
string Contract::getNume() const{
    return nume;
}
int Contract::getId() const{
    return id;
}
string Contract::getCIF() const{
    return cif;
}
void Contract::setNume(const string n){
    nume = n;
}
void Contract::setCIF(const string c){
    cif = c;
}
//istream& operator>>(istream& is, Contract& ob){
//    cout<<"Nume:";
//    is>>ob.nume;
//    cout<<"CIF:";
//    is>>ob.cif;
//    cout<<ob.getNr();
//    ob.id = ob.getNr();
////    try{
////        while(true){
////            is>>ob.tronsoane;
////            if(ob.tronsoane <= 0)
////                throw("Nr de tronsoane gresit");
////            else break;
////            }
////    }
////    catch(string s){cout<<s;}
//
//    return is;
//}
//ostream& operator<<(ostream& os, Contract& ob){
//    os<<"Nume:"<<ob.nume<<"\n"<<"Id:"<<ob.id<<"\n"<<"CIF:"<<ob.cif;
//    return os;
//}


class MeniuInteractiv{
    vector<Contract> contracte;
    vector<Drum*> drumuri;
    static MeniuInteractiv* instanta;
    MeniuInteractiv() = default;
    MeniuInteractiv(const MeniuInteractiv& m) = default;
    MeniuInteractiv(MeniuInteractiv &m) = default;
    MeniuInteractiv& operator=(const MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(MeniuInteractiv& m) = default;
public:
    static MeniuInteractiv* getInstanta(){
        if(instanta==nullptr)
            instanta = new MeniuInteractiv();
        return instanta;
    }
    static void deleteInstanta(){
        if(instanta!=nullptr)
            delete instanta;
        instanta = nullptr;
    }
    ~MeniuInteractiv(){
        for(int i=0; i<drumuri.size(); i++)
            delete drumuri[i];
        drumuri.clear();
        contracte.clear();
    }

    void addContract();
    void addDrum();
    void afisContract();
    void afisDrumuri();
    void afisLungTotal();
    void afisLungAutostrada();
    void deleteContracte();
    void calculCost();
};
void MeniuInteractiv::addContract(){
    string nume, cif;
    cout<<"Nume:\n";
    cin>>nume;
    cout<<"CIF:\n";
    cin>>cif;

    contracte.push_back(Contract(nume, cif));
}
void MeniuInteractiv::afisContract(){
    for(int i=0; i<contracte.size();i++)
        cout<<i<<"."<<contracte[i].getNume()<<" "<<contracte[i].getCIF();
}
void MeniuInteractiv::addDrum(){
    string s;
    cout<<"tipul drumului:drum, nat, eu, aut, auteu";
    cin>>s;
    Drum* d;
    if(s=="drum"){
        Drum p;
        cin>>p;
            d = &p;
    drumuri.push_back(d);
    }
    else  if(s=="nat"){
        National p;
        cin>>p;
            d = &p;
    drumuri.push_back(d);
    }
    else  if(s=="eu"){
        European p;
        cin>>p;    d = &p;
    drumuri.push_back(d);
    }
    else  if(s=="aut"){
        Autostrada p;
        cin>>p;
            d = &p;
    drumuri.push_back(d);
    }
    else  if(s=="auteu"){
        AutostradaEuropeana p;
        cin>>p;
            d = &p;
    drumuri.push_back(d);
    }

}

void MeniuInteractiv::afisDrumuri(){
    for(int i=0; i<drumuri.size();i++)
        cout<<"Drum:"<<drumuri[i]->getDenumire();
}
void MeniuInteractiv::afisLungTotal(){}
void MeniuInteractiv::afisLungAutostrada(){}
void MeniuInteractiv::deleteContracte(){}
void MeniuInteractiv::calculCost(){}

MeniuInteractiv* MeniuInteractiv::instanta = nullptr;

int main() {

    int optiune;
    MeniuInteractiv* m = m->getInstanta();
    while(true){
        cout<<"0.Adauga contract\n";
        cout<<"1.Afis contracte\n";
        cout<<"2.Afis drumuri\n";
        cout<<"3.Afiseaza lungimea totala a drumurilor\n";
        cout<<"4.Afiseaza lungimea autostrazilor\n";
        cout<<"5.Sterge contractele cu o firma\n";
        cout<<"6.Afiseaza costul unui drum\n";
         cout<<"7.Adauga drum\n";
        cout<<"8.EXIT\n";

        try{
            cin >> optiune;
            if(optiune < 0 || optiune > 7)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->addContract();
                if (optiune == 1) m->afisContract();
                else if (optiune == 2) m->afisDrumuri();
                else if (optiune == 3) m->afisLungTotal();
                else if (optiune == 4) m->afisLungAutostrada();
                else if (optiune == 5)  m->deleteContracte();
                else if (optiune == 6)  m->calculCost();
                else if (optiune == 7)  m->addDrum();
                else if (optiune == 8) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}
