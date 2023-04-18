#include <iostream>
#include <string.h>
#include <conio.h>
#include <fstream>

using namespace std;

class Mystring {
    char* str;
public:
    Mystring();
    Mystring(char* val);
    Mystring(const Mystring& source);
    Mystring(Mystring&& source);
    ~Mystring() {
    //    cout<<"~str"<<str<<endl;
        delete[] str; }
    friend ostream& operator << (ostream &out, const Mystring &s);
    friend istream& operator >> (istream &is, Mystring &s);
    Mystring& operator = (const Mystring& sir){
        str = new char[strlen(sir.str) + 1];
        strcpy(str, sir.str);
        str[strlen(sir.str)] = '\0';
    }
    bool operator == (const Mystring &s);
};

Mystring::Mystring(): str{ nullptr }
{
    str = new char[1];
    str[0] = '\0';
}
Mystring::Mystring(char* val)
{
    if (val == nullptr) {
        str = new char[1];
        str[0] = '\0';
    }
    else {
        str = new char[strlen(val) + 1];
        strcpy(str, val);
        str[strlen(val)] = '\0';
    }
}
Mystring::Mystring(const Mystring& source)
{
    str = new char[strlen(source.str) + 1];
    strcpy(str, source.str);
    str[strlen(source.str)] = '\0';
}
ostream& operator << (ostream &out, const Mystring &s)
{
    for(int i = 0; i<strlen(s.str); i++)
        out << s.str[i];
    return out;
}
istream& operator >> (istream &is, Mystring &s)
{
    s.str = new char[20];
    is>>s.str;
    s.str[19] = '\0';
    return is;
}
bool Mystring::operator == (const Mystring &s){
    if(strlen(str)!=strlen(s.str))
        return false;
    else
        for(int i = 0; i<strlen(s.str); i++)
            if(str[i]!=s.str[i])
                return false;

}

class Profesor{
    Mystring nume;
    int cnp;
public:
    Profesor(){}
    Profesor(Mystring nume, int cnp): nume(nume), cnp(cnp){}
    ~Profesor(){};
    friend ostream& operator << (ostream &out, const Profesor p);
    Mystring getNume(){
        return nume;
    }
};
ostream& operator << (ostream &out, const Profesor p)
{
    out <<p.nume<<endl;
    return out;
}


class Disciplina{
    Mystring nume;
    Profesor* prof;
public:
    Disciplina(){}
    Disciplina(Mystring nume): nume(nume){prof = nullptr;}
    Disciplina(Mystring nume, Profesor* p): nume(nume), prof(p){}
    ~Disciplina(){}
    friend ostream& operator << (ostream &out, const Disciplina d);
    Mystring getNume(){
        return nume;
    }
    void setDisciplinaProf(Profesor* p){
        prof = p;
    }
    void setNume(Mystring n){
        nume = n;
    }
};
ostream& operator << (ostream &out, const Disciplina d)
{
    if(d.prof == nullptr)
        out<< d.nume<<": none"<<endl;
    else
        out << d.nume<<": "<<d.prof->getNume()<<endl;
    return out;
}

class Nota{
    int nota;
    Disciplina* disciplina;
public:
    Nota(){nota=0; disciplina=nullptr;}
    Nota(int nota, Disciplina* d): nota(nota), disciplina(d){}
    ~Nota(){}
    friend ostream& operator << (ostream &out, const Nota &n);
    int getNota(){
        return nota;
    }
};
ostream& operator << (ostream &out, const Nota &n)
{
    out << n.nota<<endl;
    return out;
}

class Student{
    Mystring nume;
    int cnp;
    Nota note[15];
    int nrnote;
public:
    Student(){}
    Student(Mystring nume, int cnp): nume(nume), cnp(cnp){nrnote = 0;}
    Mystring getNume(){
        return nume;
    }
    int getCnp(){
        return cnp;
    }
    void setNume(Mystring newnume){
        nume = newnume;
    }
    void addNota(Nota n){
        note[nrnote] = n;
        nrnote++;
    }
    void afisNote(){
        for(int i=0; i<nrnote; i++)
            cout<<note[i];
    }
    float medieNote(){
        int s=0;
        for(int i=0; i<nrnote; i++)
            s+=note[i].getNota();
        return s/nrnote;
    }
};

class Group {
private:
    int number;
    int size;
    Student* students;
public:
    Group() {
        size = 0;
        students = NULL;
    }
    Group(int number) {
        this->number = number;
        size = 0;
        students = NULL;
    }
    Group(const Group &other){
        size = other.size;
        number = other.number;
        students = new Student[size];
        for(int i=0; i<size; i++)
            students[i] = other.students[i];
    }
    Group(Group&& other){
        number = other.number;
        size = other.size;
        students = new Student[size];
        for(int i=0; i<size; i++)
            students[i] = other.students[i];
        other.number = 0;
        other.size = 0;
        other.students = nullptr;
    }
    Group& operator=(Group&& other) {
        if (this != &other) {
            if(students!=NULL)
                delete[] students;
            size = other.size;
            number = other.number;
            students = new Student[size];
            for(int i=0; i<size; i++)
                students[i] = other.students[i];
            other.number = 0;
            other.size = 0;
            other.students = nullptr;
        }
        return *this;
    }

    ~Group() {
        if(students!=NULL)
            delete[] students;
    }

    void addStudent(Student s) {
        Student* temp = new Student[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = students[i];
        }
        temp[size] = s;
        size++;
        if(students!=NULL)
            delete[] students;
        students = temp;
    }
    int getSize() {
        return size;
    }
    int getNumber(){
        return number;
    }
    Student getStudent(int i){
        return students[i];
    }
    Student& operator[](int index) {
        return students[index];
    }
    Group& operator=(const Group& other) {
        if (this != &other) {
            if(students!=NULL)
                delete[] students;
            size = other.size;
            number = other.number;
            students = new Student[size];
            for(int i=0; i<size; i++)
                students[i] = other.students[i];
        }
        return *this;
    }
    void printGroup() {
        cout << "Group: " << number << endl;
        for (int i = 0; i < size; i++) {
            cout << students[i].getNume() << endl;
        }
    }

};

class SpecialitateAn{
    Mystring nume;
    int an;
    int size;
    Group* groups;
public:
    SpecialitateAn() {
        size = 0;
        groups = NULL;
    }
    SpecialitateAn(Mystring nume, int an) {
        this->nume = nume;
        this->an = an;
        size = 0;
        groups = NULL;
    }
    SpecialitateAn(const SpecialitateAn& other) : nume(other.nume), an(other.an), size(other.size), groups(new Group[other.size]) {
        for (int i = 0; i < size; i++) {
            groups[i] = other.groups[i];
        }
    }
    ~SpecialitateAn() {
        if(groups != NULL)
            delete[] groups;
    }
    SpecialitateAn& operator=(const SpecialitateAn& other) {
        if (this == &other) {
            return *this;
        }
        if(groups!=NULL)
            delete[] groups;
        nume = other.nume;
        an = other.an;
        size = other.size;
        groups = new Group[size];
        for (int i = 0; i < size; i++) {
            groups[i] = other.groups[i];
        }
        return *this;
    }

    void addGroup(Group g) {
        Group* temp = new Group[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = groups[i];
        }
        temp[size] = g;
        size++;
        if(groups!=NULL)
            delete[] groups;
        groups = temp;
    }
    int getSize() {
        return size;
    }
    int getAn(){
        return an;
    }
    Mystring getName(){
        return nume;
    }
    void setName(Mystring newnume){
        nume = newnume;
    }
    Group& getGroup(int i){
        return groups[i];
    }
    Group& operator[](int index) {
        return groups[index];
    }
    void printSpecialitate() {
        cout << "Specialitate: " << nume << " An: "<< an << endl;
        for (int i = 0; i < size; i++) {
            cout << groups[i].getNumber() << endl;
        }
    }
};

class Facultate{
    Mystring nume;
    int size;
    SpecialitateAn* specialitati;
public:
    Facultate() {
        size = 0;
        specialitati = NULL;
    }
    Facultate(Mystring nume) {
        this->nume = nume;
        size = 0;
        specialitati = NULL;
    }
    Facultate(const Facultate& other) : nume(other.nume), size(other.size), specialitati(new SpecialitateAn[other.size]) {
        for (int i = 0; i < size; i++) {
            specialitati[i] = other.specialitati[i];
        }
    }
    ~Facultate() {
        if(specialitati != NULL)
            delete[] specialitati;
    }
    Facultate& operator=(const Facultate& other) {
        if (this == &other) {
            return *this;
        }
        if(specialitati!=NULL)
            delete[] specialitati;
        nume = other.nume;
        size = other.size;
        specialitati = new SpecialitateAn[size];
        for (int i = 0; i < size; i++) {
            specialitati[i] = other.specialitati[i];
        }
        return *this;
    }

    void addSpecialitate(SpecialitateAn s) {
        SpecialitateAn* temp = new SpecialitateAn[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = specialitati[i];
        }
        temp[size] = s;
        size++;
        if(specialitati!=NULL)
            delete[] specialitati;
        specialitati = temp;
    }
    int getSize() {
        return size;
    }
    Mystring getNume(){
        return nume;
    }
    SpecialitateAn& getSpecialitate(int i){
        return specialitati[i];
    }
    SpecialitateAn& operator[](int index) {
        return specialitati[index];
    }
    void printFacultate() {
        cout << "Facultatea: " << nume << endl;
        for (int i = 0; i < size; i++) {
            cout <<"Specializari: "<<endl;
            cout << specialitati[i].getName() << endl;
        }
    }
    int nrStudenti(){
        int s=0;
        for(int i=0; i<size; i++)
            for(int j=0; j<getSpecialitate(i).getSize(); j++)
                s+=getSpecialitate(i).getGroup(j).getSize();
        return s;
    }
};


void introducereFacultate(Facultate* facultati, int& ctr){
    Mystring name;
    cout<<"Denumire: ";
    cin>>name;
    facultati[ctr] = *new Facultate(name);
    ctr++;
}

void introducereSpecialitate(Facultate* facultati, int& ctr){
    int i, index;
    cout<<"-------------------------------------------------------\n";
    if(ctr==0){
       cout<<"Nu exista nici o facultate\n";
       return;
    }
    cout<<"In ce facultate vreti sa o adaugati\n";
    for(i=0; i<ctr; i++)
        cout<<"["<<i+1<<"] "<<facultati[i].getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>index;
    index--;
    Mystring name;
    int an;
    cout<<"Denumire: ";
    cin>>name;
    cout<<"An: ";
    cin>>an;
    facultati[index].addSpecialitate(SpecialitateAn(name, an));
}

void introducereGrupa(Facultate* facultati, int& ctr){
    int i, index, specialitate_index;
    cout<<"-------------------------------------------------------\n";
    if(ctr==0){
       cout<<"Nu exista nici o facultate\n";
       return;
    }
    cout<<"In ce facultate vreti sa o adaugati\n";
    for(i=0; i<ctr; i++)
        cout<<"["<<i+1<<"] "<<facultati[i].getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>index;
    index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSize()==0){
       cout<<"Nu exista nici o specializare la aceasta facultate\n";
       return;
    }
    cout<<"Specializarea:\n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(i).getName()<<" Anul: "<<facultati[index].getSpecialitate(i).getAn()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>specialitate_index;
    specialitate_index--;
    int number;
    cout<<"Numarul: ";
    cin>>number;
    facultati[index].getSpecialitate(specialitate_index).addGroup(Group(number));
}

void introducereProfesor(){
    Mystring name;
    cout<<"Nume Prenume: ";
    cin>>name;
    cout<<endl;
}

void introducereStudent(Facultate* facultati, int& ctr){
    int i, index, specialitate_index, group_index;
    cout<<"-------------------------------------------------------\n";
    if(ctr==0){
       cout<<"Nu exista nici o facultate\n";
       return;
    }
    cout<<"In ce facultate vreti sa o adaugati\n";
    for(i=0; i<ctr; i++)
        cout<<"["<<i+1<<"] "<<facultati[i].getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>index;
    index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSize()==0){
       cout<<"Nu exista nici o specializare la aceasta facultate\n";
       return;
    }
    cout<<"Specializarea:\n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(i).getName()<<" Anul: "<<facultati[index].getSpecialitate(i).getAn()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>specialitate_index;
    specialitate_index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSpecialitate(specialitate_index).getSize()==0){
       cout<<"Nu exista nici o grupa la aceasta specializare\n";
       return;
    }
    cout<<"Grupa:\n";
    for(i=0; i<facultati[index].getSpecialitate(specialitate_index).getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(specialitate_index).getGroup(i).getNumber()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>group_index;
    group_index--;

    int cnp;
    Mystring name;
    cout<<"Numele Prenumele: ";
    cin>>name;
    cout<<"CNP: ";
    cin>>cnp;
    facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).addStudent(Student(name, cnp));
}


void introducereDate(Facultate* facultati, int& ctr){
    int k = 1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru a introduce o facultate\n";
        cout<<"Tasteaza [2] pentru a introduce o specialitate-an\n";
        cout<<"Tasteaza [3] pentru a introduce o grupa\n";
        cout<<"Tasteaza [4] pentru a introduce un profesor\n";
        cout<<"Tasteaza [5] pentru a introduce un student\n";
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
            case '2': // afisare date
            {
                introducereSpecialitate(facultati, ctr);
                break;
            }
            case '3':
            {
                 introducereGrupa(facultati, ctr);
                 break;
            }
            case '4':
            {
                 introducereProfesor();
                 break;
            }
            case '5':
            {
                 introducereStudent(facultati, ctr);
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

void afisToateSpecializari(Facultate* facultati, int& ctr){
    int i, index;
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
    if(facultati[index].getSize()==0){
        cout<<"Nu exista nici o specializare la aceasta facultate\n";
        return;
    }
    cout<<"Specialiati: \n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<facultati[index].getSpecialitate(i).getName()<<endl;
}

void afisGrupe(Facultate* facultati, int& ctr){
    int i, index, specialitate_index;
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
    if(facultati[index].getSize()==0){
       cout<<"Nu exista nici o specializare la aceasta facultate\n";
       return;
    }
    cout<<"Specializarea: \n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(i).getName()<<" Anul: "<<facultati[index].getSpecialitate(i).getAn()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>specialitate_index;
    specialitate_index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSpecialitate(specialitate_index).getSize()==0){
       cout<<"Nu exista nici o grupa la aceasta specializare\n";
       return;
    }
    cout<<"Grupele:\n";
    for(i=0; i<facultati[index].getSpecialitate(specialitate_index).getSize(); i++)
        cout<<facultati[index].getSpecialitate(specialitate_index).getGroup(i).getNumber()<<"\n";
    cout<<"-------------------------------------------------------\n";
}

void afisStudenti(Facultate* facultati, int& ctr){
    int i, index, specialitate_index, group_index;
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
    if(facultati[index].getSize()==0){
       cout<<"Nu exista nici o specializare la aceasta facultate\n";
       return;
    }
    cout<<"Specializarea: \n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(i).getName()<<" Anul: "<<facultati[index].getSpecialitate(i).getAn()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>specialitate_index;
    specialitate_index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSpecialitate(specialitate_index).getSize()==0){
       cout<<"Nu exista nici o grupa la aceasta specializare\n";
       return;
    }
    cout<<"Grupa:\n";
    for(i=0; i<facultati[index].getSpecialitate(specialitate_index).getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(specialitate_index).getGroup(i).getNumber()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>group_index;
    group_index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getSize()==0){
    cout<<"Nu exista nici un student in aceasta grupa\n";
       return;
    }
    cout<<"Studentii:\n";
    for(i=0; i<facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getSize(); i++)
        cout<<facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(i).getNume()<<"\n";
    cout<<"-------------------------------------------------------\n";
}

void afisToateDate(Facultate* facultati, int& ctr){
    int facultate_index, specialitate_index, group_index, student_index;
    for(facultate_index=0; facultate_index<ctr; facultate_index++){
        cout<<"Facultatea "<<facultati[facultate_index].getNume()<<": \n";
        for(specialitate_index=0; specialitate_index<facultati[facultate_index].getSize(); specialitate_index++){
            cout<<"    Specialitatea: "<<facultati[facultate_index].getSpecialitate(specialitate_index).getName()<<" Anul: "<<facultati[facultate_index].getSpecialitate(specialitate_index).getAn()<<"\n";
            for(group_index=0; group_index<facultati[facultate_index].getSpecialitate(specialitate_index).getSize(); group_index++){
                cout<<"         Grupa "<<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getNumber()<<":\n";
                for(student_index=0; student_index<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getSize(); student_index++)
                    cout<<"             "<<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).getNume()<<"\n";
            }
        }
    }
}

void afisNrStudenti(Facultate* facultati, int& ctr){
    int i, s=0;
    for(i=0; i<ctr; i++)
        s+=facultati[i].nrStudenti();
    cout<<s<<" studenti\n";
}

void afisDate(Facultate* facultati, int& ctr){
    int k=1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru a afisa toate facultatile\n";
        cout<<"Tasteaza [2] pentru a afisa toate specializarile dintro facultate\n";
        cout<<"Tasteaza [3] pentru a afisa toate grupele dintro specializare\n";
        cout<<"Tasteaza [4] pentru a afisa toti studentii dintro grupa\n";
        cout<<"Tasteaza [5] pentru a afisa toate datele\n";
        cout<<"Tasteaza [6] pentru a afisa numarul total de studenti\n";
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
            case '2': // afisare date
            {
                afisToateSpecializari(facultati, ctr);
                break;
            }
            case '3':
            {
                 afisGrupe(facultati, ctr);
                 break;
            }
            case '4':
            {
                 afisStudenti(facultati, ctr);
                 break;
            }
            case '5':
            {
                 afisToateDate(facultati, ctr);
                 break;
            }
            case '6':
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

void modifcSpecialitate(Facultate* facultati, int& ctr){
    int i, index, specialitate_index;
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
    if(facultati[index].getSize()==0){
       cout<<"Nu exista nici o specializare la aceasta facultate\n";
       return;
    }
    cout<<"Specializarea care sa fie modificata: \n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(i).getName()<<" Anul: "<<facultati[index].getSpecialitate(i).getAn()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>specialitate_index;
    specialitate_index--;

    Mystring newname;
    cout<<"Numele nou: ";
    cin>>newname;
    facultati[index].getSpecialitate(specialitate_index).setName(newname);

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
    if(facultati[index].getSize()==0){
       cout<<"Nu exista nici o specializare la aceasta facultate\n";
       return;
    }
    cout<<"Specializarea: \n";
    for(i=0; i<facultati[index].getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(i).getName()<<" Anul: "<<facultati[index].getSpecialitate(i).getAn()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>specialitate_index;
    specialitate_index--;
    cout<<"-------------------------------------------------------\n";
    if(facultati[index].getSpecialitate(specialitate_index).getSize()==0){
       cout<<"Nu exista nici o grupa la aceasta specializare\n";
       return;
    }
    cout<<"Grupa:\n";
    for(i=0; i<facultati[index].getSpecialitate(specialitate_index).getSize(); i++)
        cout<<"["<<i+1<<"] "<<facultati[index].getSpecialitate(specialitate_index).getGroup(i).getNumber()<<"\n";
    cout<<"-------------------------------------------------------\n";
    cin>>group_index;
    group_index--;
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
    Mystring newnume;
    cout<<"Numele nou: ";
    cin>>newnume;
  //  cout<<facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).getNume();
    facultati[index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).setNume(newnume);
}

void modificareDate(Facultate* facultati, int& ctr){
    int k = 1;

    while(k==1){
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza [1] pentru numele unei specialitati\n";
        cout<<"Tasteaza [2] pentru a modifica numele unui student\n";
        cout<<"Tasteaza [0] pentru a da inapoi\n";
        cout<<"-------------------------------------------------------\n";

        char comanda;
        comanda = getch();

        switch(comanda)
        {
            case '1':
            {
                modifcSpecialitate(facultati, ctr);
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
    Mystring str;
    int number,facultate_index, specialitate_index, group_index, student_index;

    ifstream Data("database.txt");
    while(Data>>str){
        if(str=="Facultatea:"){
            Data>>str;
            ctr++;
            facultati[ctr] = *new Facultate(str);
            specialitate_index=-1;
        }
        else if(str=="Specialitatea:"){
            Data>>str;
            Data>>number;
            facultati[ctr].addSpecialitate(SpecialitateAn(str, number));
            specialitate_index++;
            group_index=-1;
        }
        else if(str=="Grupa:"){
            Data>>number;
            facultati[ctr].getSpecialitate(specialitate_index).addGroup(Group(number));
            group_index++;
        }
        else if(str=="Studentii:"){
            Data>>str;
            Data>>number;
            facultati[ctr].getSpecialitate(specialitate_index).getGroup(group_index).addStudent(Student(str, number));
        }
        else{
            Data>>number;
            facultati[ctr].getSpecialitate(specialitate_index).getGroup(group_index).addStudent(Student(str, number));
        }
    }
    Data.close();
    ctr++;

    runmenu(facultati, ctr);

    ofstream DataWrite("database.txt");

    for(facultate_index=0; facultate_index<ctr; facultate_index++){
        DataWrite<<"Facultatea:"<<endl<<facultati[facultate_index].getNume()<<endl;
        for(specialitate_index=0; specialitate_index<facultati[facultate_index].getSize(); specialitate_index++){
            DataWrite<<"Specialitatea:"<<endl<<facultati[facultate_index].getSpecialitate(specialitate_index).getName()<<endl<<facultati[facultate_index].getSpecialitate(specialitate_index).getAn()<<endl;
            for(group_index=0; group_index<facultati[facultate_index].getSpecialitate(specialitate_index).getSize(); group_index++){
                DataWrite<<"Grupa:"<<endl<<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getNumber()<<endl<<"Studentii:"<<endl;
                for(student_index=0; student_index<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getSize(); student_index++)
                    DataWrite<<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).getNume()<<endl<<facultati[facultate_index].getSpecialitate(specialitate_index).getGroup(group_index).getStudent(student_index).getCnp()<<endl;
            }
        }
    }

    DataWrite.close();

    if(facultati!=NULL)
    delete[] facultati;
    return 0;
}

/**
Profesor p1("Profesor1", 299491419096);
    Profesor p2("Profesor2", 299431419096);
    cout<<p2.getNume()<<endl;
    cout<<p1<<endl;
    Student s5;
    Disciplina algebra("algebra", &p1);
    Disciplina analiza("analiza", &p1);
    Disciplina info("info");
    info.setDisciplinaProf(&p2);
    cout<<algebra;
    cout<<info;
        Student* temp = new Student[4];
    Nota n1(7, &algebra);
    Nota n2;
    cout<<n1;
    cout<<n2;
    cout<<n1.getNota();

    Student s1("Student1", 23193818);
    Student s2("Cata", 273371);
    cout<<s1.getNume()<<endl;
    s1.setNume("Student5");
    cout<<s1.getNume();

    s1.addNota(n1);
    Nota n3(9, &analiza);
    s1.addNota(n3);
    s1.addNota(Nota(8, &algebra));
    cout<<endl;
    s1.afisNote();
    cout<<endl<<"media: "<<s1.medieNote();

    Group g142(142);
    g142.addStudent(s1);
    g142.addStudent(s2);
    g142.addStudent(Student("Vica", 2342342));
    g142.printGroup();
    g142.getStudent(0).afisNote();
    cout<<g142.getSize()<<endl;

    SpecialitateAn informatica("info", 1);
    SpecialitateAn cti("cti", 2);

    informatica.addGroup(g142);
    informatica.printSpecialitate();
    Group g143(143);
    informatica.addGroup(g143);
    informatica.printSpecialitate();

    informatica.getGroup(0).addStudent(Student("s1", 241412));
    informatica.getGroup(0).addStudent(Student("s2", 2214124));
    g143.printGroup();


    Facultate fmi("Mate-Info");
    cout<<fmi.getNume()<<endl;
    fmi.addSpecialitate(informatica);
    fmi.addSpecialitate(cti);
    fmi.printFacultate();

    Student s7("s7", 21124);
    s7.addNota(Nota(7, &info));
    fmi.getSpecialitate(0).getGroup(0).addStudent(s7);

    Group g162(162);
    Student s8("s8", 3326366);
    g162.addStudent(s8);
    fmi.getSpecialitate(1).addGroup(g162);
    g162.printGroup();
    fmi.getSpecialitate(0).getGroup(1).printGroup();

    fmi.getSpecialitate(1).printSpecialitate();
    fmi.getSpecialitate(1).getGroup(0).printGroup();

    cout<<fmi.getSpecialitate(1).getSize();
    fmi.getSpecialitate(1).getGroup(0).printGroup();
    g143.printGroup();

    cout<<fmi.nrStudenti();
**/


