#include <iostream>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <memory>
#include <exception>
#include <algorithm>

using namespace std;



template <typename T, int Size>
class Array {
private:
    T elements[Size];

public:
    Array() {}
    ~Array() {}
    T& operator[](int index)  {
        return elements[index];
    }
    const T& operator[](int index) const {
        return elements[index];
    }
    int size() const {
        return Size;
    }
};

template <typename T, typename U>
void afisElemente(T obj, U tip){
    int ctr=1;
    for (int i=0; i<obj.getPersoane().size(); i++) {
        shared_ptr<U> ptr = dynamic_pointer_cast<U>(obj.getPersoane()[i]);
        if (ptr){
            cout << "["<<ctr<<"]"<< ptr->getNume() << " CNP: " << ptr->getCnp() << endl;
            ctr++;
        }
    }
}

template <typename T>
void afisElemente(T obj, int n){
    for(int i=0; i<n; i++)
        cout<<obj.getArrayNote()[i];
}

class TryCnp: public exception{
public:
    const char* what() const throw(){
        return "CNP invalid, introduceti din nou: ";
    }
};



class TryNota: public exception{
public:
    const char* what() const throw(){
        return "Nota gresita, introduceti din nou: ";
    }
};



class Persoana{
protected:
    string nume;
    int cnp;
public:
    Persoana(){}
    Persoana(string nume, int cnp): nume(nume){
        if(exceptioncnp(cnp))
            throw TryCnp();
        else this->cnp = cnp;
    }
    virtual ~Persoana(){}
    string getNume() const {
        return nume;
    }
    int getCnp()const{
        return cnp;
    }
    void setNume(string newnume){
        nume = newnume;
    }
 //   virtual void getInfo() = 0;
    static int exceptioncnp(int number){
        return (number/100<1 || number/100>=10);
    }
};


class Profesor: virtual public Persoana{
protected:
    int salariu;
    static int counter;
    int idProfesor;
public:
    Profesor(){}
    Profesor(string n, int cnp, int s): Persoana(n, cnp), salariu(s){ counter++; idProfesor=counter;}
    virtual ~Profesor(){};
//    friend ostream& operator << (ostream &out, const Profesor p);
    void getInfo()const {
        cout<<"Nume: "<<nume<<" CNP: "<<cnp<<" Salariu: "<<salariu;
    }
    int getSalariu()const{
        return salariu;
    }
    void setSalariu(int s){
        this->salariu = s;
    }
    int getId()const{
       return idProfesor;
    }
    static int getCount(){
        return counter;
    }
};

int Profesor::counter = 0;

class Disciplina{
    string nume;
    weak_ptr<Persoana> prof;
public:
    Disciplina(){}
    Disciplina(string nume): nume(nume){}
    Disciplina(string nume, weak_ptr<Persoana> p): nume(nume), prof(p){}
    ~Disciplina(){}
    string getNume()const{
        return nume;
    }
    void setDisciplinaProf(const weak_ptr<Persoana> p){
        prof = p;
    }
    void setNume(string n){
        nume = n;
    }
    string printProfesor()const{
        if(auto locked = prof.lock())
            return locked->getNume();
    }

};


class Nota{
    int nota;
    Disciplina* disciplina;
public:
    Nota(){nota=0; disciplina=nullptr;}
    Nota(int nota, Disciplina* d): disciplina(d){
        if(exceptionnota(nota))
            throw TryNota();
        else this->nota = nota;
    }
    ~Nota(){}
    friend ostream& operator << (ostream &out, const Nota &n);
    int getNota() const{
        return nota;
    }
    static int exceptionnota(int number){
        return (number<0 || number>10);
    }
};
ostream& operator << (ostream &out, const Nota &n)
{
    out << n.nota<<endl;
    return out;
}

class Student: virtual public Persoana{
    Array<Nota, 15> note;
    int nrnote;
    static int counter;
    int idStudent;
public:
    Student(){}
    Student(string nume, int cnp): Persoana(nume, cnp) {nrnote = 0; counter++; idStudent=counter;}
    virtual ~Student(){}
    void addNota(Nota n){
        note[nrnote] = n;
        nrnote++;
    }
    float medieNote()const{
        int s=0;
        for(int i=0; i<nrnote; i++)
            s+=note[i].getNota();
        return s/nrnote;
    }
    void getInfo()const{
        cout<<"Nume: "<<nume<<" CNP: "<<cnp;
    }
    int getId()const{
       return idStudent;
    }
    static int getCount(){
        return counter  ;
    }
    Array<Nota, 15> getArrayNote() const{
        return note;
    }
    int getNrnote()const{
        return nrnote;
    }
};

int Student::counter = 0;

class StudentLaborant: public Student, public Profesor{
public:
    StudentLaborant(string n, int cnp, int s):  Student(n, cnp), Profesor(n, cnp, s), Persoana(n, cnp){}
    void getInfo()const{
        cout<<"Nume: "<<nume<<" CNP: "<<cnp<<" Salariu: "<<salariu;
    }
};


class Interfata{
protected:
    virtual void printInfo() = 0;
    virtual int nrStudenti() = 0;
//    virtual int getSize();
    virtual ~Interfata(){}
};


class Facultate: protected Interfata{
    string nume;
 //   vector<unique_ptr<Persoana>> persoane;
    vector<shared_ptr<Persoana>> persoane;
    vector<shared_ptr<Disciplina>> discipline;
    Facultate(string name) : nume(name){}
public:
    static Facultate create(string name) {return Facultate(name); }
    Facultate() {}
  /*  Facultate(string nume) {
        this->nume = nume;
    }
    Facultate(const Facultate& other) : nume(other.nume), persoane(other.persoane) {}
 */
    Facultate& addPersoane(const shared_ptr<Persoana> p){persoane.push_back(p); return *this;}
    Facultate& addDisciplina(const shared_ptr<Disciplina> d){discipline.push_back(d); return *this;}

    ~Facultate() {}

    void addPersoana(const shared_ptr<Persoana> p){
        persoane.push_back(p);
    }
    void printInfo(){
        cout << "Facultatea " << nume << ":" << endl;
    //    for (const auto& persoana : persoane) {
    //        cout << "- " << persoana->getNume() << " CNP: " << persoana->getCnp() << endl;
        for(int i=0; i<persoane.size(); i++)
            cout<<persoane[i]->getNume()<<" CNP: "<<persoane[i]->getCnp()<<endl;
//           persoane[i]->getInfo();
    }
/*
    void afisProfesori() const {
        int ctr=1;
        for (int i=0; i<persoane.size(); i++) {
            shared_ptr<Profesor> profesorPtr = dynamic_pointer_cast<Profesor>(persoane[i]);
            if (profesorPtr){
                cout << "["<<ctr<<"]"<< profesorPtr->getNume() << " CNP: " << profesorPtr->getCnp() << " Salariu: "<< profesorPtr->getSalariu() << endl;
                ctr++;
                getInfo(persoane[i]);
            }
        }
    }
    void afisStudenti() const {
        int ctr=1;
        for (int i=0; i<persoane.size(); i++) {
            shared_ptr<Student> studentPtr = dynamic_pointer_cast<Student>(persoane[i]);
            if (studentPtr){
                cout << "["<<ctr<<"]" << studentPtr->getNume() << " CNP: " << studentPtr->getCnp() << endl;
                ctr++;
            }
        }
    }

*/
    vector<shared_ptr<Persoana>> getPersoane() const{
        return persoane;
    }
    string getNume()const{
        return nume;
    }
    int nrStudenti(){
        int s = count_if(persoane.begin(), persoane.end(), [](const shared_ptr<Persoana> person) {
            return dynamic_pointer_cast<const Student>(person) != nullptr;
    });
        return s;
    }
    shared_ptr<Persoana> getProfesor(int idProf)const{
        int ctr=0;
        for (int i=0; i<persoane.size(); i++) {
            shared_ptr<Profesor> profesorPtr = dynamic_pointer_cast<Profesor>(persoane[i]);
            if (profesorPtr){
                ctr++;
                if(idProf == ctr)
                    return persoane[i];
            }
        }
    }
//    void addDisciplina(const shared_ptr<Disciplina> d){
//        discipline.push_back(d);
//    }
    void afisDiscipline()const{
        for(int i=0; i<discipline.size(); i++)
            cout<<"["<<i<<"]"<<discipline[i]->getNume()<<" "<<discipline[i]->printProfesor()<<endl;
    }
    void modifySalariu(float procent)const{
        for_each(persoane.begin(), persoane.end(), [procent](shared_ptr<Persoana> p){
            shared_ptr<Profesor> profesorPtr = dynamic_pointer_cast<Profesor>(p);
            if (profesorPtr)
                profesorPtr->setSalariu(int(procent*profesorPtr->getSalariu()));
             });
    }
};



int getIndexFacultate(Facultate* facultati, int& ctr){
    int i, index;
    cout<<"-------------------------------------------------------\n";
    if(ctr==0){
       cout<<"Nu exista nici o facultate\n";
       return -1;
    }
    cout<<"In ce facultate\n";
    for(i=0; i<ctr; i++)
        cout<<"["<<i+1<<"] "<<facultati[i].getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>index;
    index--;
    return index;
}


void introducereFacultate(Facultate* facultati, int& ctr){
    string name;
    cout<<"Denumire: ";
    cin>>name;
    facultati[ctr] = Facultate::create(name);
    ctr++;
}


void introducereProfesor(Facultate* facultati, int& ctr){
    int index;
    shared_ptr<Persoana> p;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    string name;
    int cnp, salariu;
    cout<<"Nume Prenume: ";
    cin>>name;
    cout<<"CNP: ";
    cin>>cnp;
    cout<<"Salariu: ";
    cin>>salariu;
    try{
        p = make_shared<Profesor>(name, cnp, salariu);
    } catch(TryCnp& e){
        cerr<<e.what();
        cin>>cnp;
        p = make_shared<Profesor>(name, cnp, salariu);
    }
 //   Persoana *p;
 //   Profesor prof(name, cnp, salariu);
   // p = &prof;
 //   Persoana* p = new Profesor(name, cnp, salariu);
    facultati[index].addPersoana(p);
}

void introducereStudent(Facultate* facultati, int& ctr){
    int index;
    shared_ptr<Persoana> p;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    int cnp;
    string name;
    cout<<"Numele Prenumele: ";
    cin>>name;
    cout<<"CNP: ";
    cin>>cnp;
   // Persoana *p;
   // Student prof(name, cnp);
  //  p = &prof;
 //   Persoana* p = new Profesor(name, cnp, salariu);

    try{
        p = make_shared<Student>(name, cnp);
    } catch(TryCnp& e){
        cerr<<e.what();
        cin>>cnp;
        p = make_shared<Student>(name, cnp);
    }

    facultati[index].addPersoana(p);
}

void introducereStudentLaborant(Facultate* facultati, int& ctr){
    int index;
    shared_ptr<Persoana> p;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    int cnp, salariu;
    string name;
    cout<<"Numele Prenumele: ";
    cin>>name;
    cout<<"CNP: ";
    cin>>cnp;
    cout<<"Salariu: ";
    cin>>salariu;
   // Persoana *p;
   // Student prof(name, cnp);
  //  p = &prof;
 //   Persoana* p = new Profesor(name, cnp, salariu);
    try{
        p = make_shared<StudentLaborant>(name, cnp, salariu);
    } catch(TryCnp& e){
        cerr<<e.what();
        cin>>cnp;
        p = make_shared<StudentLaborant>(name, cnp, salariu);
    }
    facultati[index].addPersoana(p);
}

void introducereDisciplina(Facultate* facultati, int& ctr){
    int index, pindex;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    string name;
    cout<<"Nume: ";
    cin>>name;
    cout<<endl<<"Profesorul care va duce cursul:"<<endl;
//    facultati[index].afisProfesori();
    afisElemente(facultati[index], Profesor());
    cin>>pindex;
    weak_ptr<Persoana> p = facultati[index].getProfesor(pindex);
    shared_ptr<Disciplina> d = make_shared<Disciplina>(name, p);
    facultati[index].addDisciplina(d);
}


void introducereDate(Facultate* facultati, int& ctr){
    int k = 1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru a introduce o facultate\n";
        cout<<"Tasteaza [2] pentru a introduce un profesor\n";
        cout<<"Tasteaza [3] pentru a introduce un student\n";
        cout<<"Tasteaza [4] pentru a introduce un studentlaborant\n";
        cout<<"Tasteaza [5] pentru a introduce o disciplina\n";
        cout<<"Tasteaza [0] pentru a da inapoi\n";
        cout<<"-------------------------------------------------------\n";

        char comanda;
        comanda = getch();

        switch(comanda)
        {
            case '1':
            {
                introducereFacultate(facultati, ctr);
                break;
            }
            case '2':
            {
                 introducereProfesor(facultati, ctr);
                 break;
            }
            case '3':
            {
                 introducereStudent(facultati, ctr);
                 break;
            }
            case '4':
            {
                 introducereStudentLaborant(facultati, ctr);
                 break;
            }
            case '5':
            {
                 introducereDisciplina(facultati, ctr);
                 break;
            }
            case '0':
            {
                k = 0;
                break;
            }
            default:
            {
                cout<<"incorect\n";
                break;
            }
        }
    }

}

void afisToateFacultatile(Facultate* facultati, int& ctr){
    int i;
    cout<<"-------------------------------------------------------\n";
    if(ctr==0){
       cout<<"Nu exista nici o facultate\n";
       return;
    }

    cout<<"Facultati: \n";
    for(i=0; i<ctr; i++)
        cout<<facultati[i].getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
}



void afisStudenti(Facultate* facultati, int& ctr){
    int index;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    cout<<"-------------------------------------------------------\n";
    cout<<"Studentii: \n";
//    facultati[index].afisStudenti();
    afisElemente(facultati[index], Student());
}

void afisProfesori(Facultate* facultati, int& ctr){
    int index;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    cout<<"Profesorii: \n";
//    facultati[index].afisProfesori();
    afisElemente(facultati[index], Profesor());

}

void afisDiscipline(Facultate* facultati, int& ctr){
    int index;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    cout<<"Disciplinele: \n";
    facultati[index].afisDiscipline();

}

void afisNrStudenti(Facultate* facultati, int& ctr){
    int index;
    index = getIndexFacultate(facultati, ctr);
    if(index == -1)
        return;
    cout<<facultati[index].nrStudenti()<<" studenti\n";
}

void afisDate(Facultate* facultati, int& ctr){
    int k=1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru a afisa toate facultatile\n";
        cout<<"Tasteaza [2] pentru a afisa toti studentii dintro facultate\n";
        cout<<"Tasteaza [3] pentru a afisa profesorii dintro facultate\n";
        cout<<"Tasteaza [4] pentru a afisa toate disciplinele dintro facultate\n";
        cout<<"Tasteaza [5] pentru a afisa numarul total de studenti\n";
        cout<<"Tasteaza [0] pentru a da inapoi\n";
        cout<<"-------------------------------------------------------\n";

        char comanda;
        comanda = getch();

        switch(comanda)
        {
            case '1':
            {
                afisToateFacultatile(facultati, ctr);
                break;
            }
            case '2':
            {
                 afisStudenti(facultati, ctr);
                 break;
            }
            case '3':
            {
                 afisProfesori(facultati, ctr);
                 break;
            }
            case '4':
            {
                 afisDiscipline(facultati, ctr);
                 break;
            }
            case '5':
            {
                 afisNrStudenti(facultati, ctr);
                 break;
            }
            case '0':
            {
                k = 0;
                break;
            }
            default:
            {
                cout<<"incorect\n";
                break;
            }
        }
    }
}


void modifcStudent(Facultate* facultati, int& ctr){
    int i, index, specialitate_index, group_index, student_index;
    cout<<"-------------------------------------------------------\n";
    if(ctr==0){
       cout<<"Nu exista nici o facultate\n";
       return;
    }
    cout<<"Facultatea: \n";
    for(i=0; i<ctr; i++)
        cout<<"["<<i+1<<"] "<<facultati[i].getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>index;
    index--;
    cout<<"-------------------------------------------------------\n";
/**
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getSize()==0){
    cout<<"Nu exista nici un student in aceasta grupa\n";
       return;
    }
    cout<<"Studentul:\n";
    for(i=0; i<facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(i).getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>student_index;
    student_index--;
    string newnume;
    cout<<"Numele nou: ";
    cin>>newnume;
  //  cout<<facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).getNume();
    facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).setNume(newnume);
**/
}

void modificSalariu(Facultate* facultati, int& ctr){
    float procent;
    cout<<"Procentul cu cat sa se modifice salariul: ";
    cin>>procent;
    procent = procent/100+1;
    for(int i=0; i<ctr; i++)
        facultati[i].modifySalariu(procent);
}

void modificareDate(Facultate* facultati, int& ctr){
    int k = 1;

    while(k==1){
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru a modifica salariul profesorilor\n";
        cout<<"Tasteaza [2] pentru a modifica numele unui student\n";
        cout<<"Tasteaza [0] pentru a da inapoi\n";
        cout<<"-------------------------------------------------------\n";

        char comanda;
        comanda = getch();

        switch(comanda)
        {
            case '1': // afisare date
            {
                modificSalariu(facultati, ctr);
                break;
            }
            case '2': // afisare date
            {
                modifcStudent(facultati, ctr);
                break;
            }
            case '0':
            {
                k = 0;
                break;
            }
            default:
            {
                cout<<"incorect\n";
                break;
            }
        }
    }
}

void runmenu(Facultate* facultati, int& ctr){

    int k = 1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru a introduce date noi\n";
        cout<<"Tasteaza [2] pentru a afisa date\n";
        cout<<"Tasteaza [3] pentru a modifica date\n";
        cout<<"Tasteaza [0] pentru a iesi din program\n";
        cout<<"-------------------------------------------------------\n";

        char comanda;
        comanda = getch();

        switch(comanda)
        {
            case '1': // introducere date noi
            {
                introducereDate(facultati, ctr);
                break;
            }
            case '2': // afisare date
            {
                afisDate(facultati, ctr);
                break;
            }
            case '3':
            {
                 modificareDate(facultati, ctr);
                 break;
            }
            case '0':
            {
                cout<<"program incheiat\n";
                k = 0;
                break;
            }
            default:
            {
                cout<<"incorect\n";
                break;
            }
        }
    }
}



int main()
{
    static int ctr = -1;
    Facultate* facultati = new Facultate[100];
    string str;
    int number,facultate_index, specialitate_index, group_index, student_index;


    ctr++;

    runmenu(facultati, ctr);

    ofstream DataWrite("database.txt");



    if(facultati!=NULL)
    delete[] facultati;

    Facultate fmi = Facultate::create("fmi")
                                .addPersoane(make_shared<Student>("student1", 123))
                                .addPersoane(make_shared<Profesor>("prof1", 432, 131414));
    afisElemente(fmi, Student());


    return 0;
}
