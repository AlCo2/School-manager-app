#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
//subjects:
#define Ar "arabic"
#define Eng "english"
#define Ma "Math"
#define Pc "Physiq"
#define Sport "sport"

//Working As :
#define O "Owner"
#define S "Student"
#define T "Teacher"




class Persone{
protected:
    string firstName;
    string lastName;
    int age;
    char gender;
public:
    Persone(){}
    Persone(string firstname, string lastname, int Age, char Gender){
        firstName = firstname;
        lastName = lastname;
        age = Age;
        gender = Gender;
    }
    void setFname(string name){
        firstName = name;
    }
    void setLname(string name){
        lastName = name;
    }
    void setAge(int Age){
        age = Age;
    }
    void setGender(char g){
        gender = g;
    }
    string getFname(){
        return firstName;
    }
    string getLname(){
        return lastName;
    }
    int getAge(){
        return age;
    }
    char getGender(){
        return gender;
    }
    void intro(){
        cout << "i am "<<firstName<< " "<< lastName<< " my age is "<< age;
    }
};
class Subjects{
protected:
    float arabic;
    float english;
    float math;
    float pc;
    float sport;
public:
    float moyenGeneral(){
        float result;
        result = (arabic*2+english*2+pc*5+sport*4+math*7)/20;
        return result;
    }
};



class Student:public Persone, public Subjects{
private:
    int Group;
public:
    Student(){}
    void setGroup(int grp){
        Group = grp;
    }
    int showGroup(){
        return Group;
    }
    void setAr(float ar){
        this->arabic = ar;
    }
    float getAr(){
        return arabic;
    }
    void setEng(float eng){
        this->english = eng;
    }
    float getEng(){
        return english;
    }
    void setPc(float pc){
        this->pc = pc;
    }
    float getPc(){
        return pc;
    }
    void setMath(float math){
        this->math = math;
    }
    float getMath(){
        return math;
    }
    void setSport(float sport){
        this->sport = sport;
    }
    float getSport(){
        return sport;
    }
    Student(string firstname, string lastname, int Age, char Gender, int group)
    :Persone(firstname, lastname, Age, Gender){
        Group = group;
    }
    void intro(){
        cout << "i am "<<firstName<< " "<< lastName<< " my age is "<< age << " and i am in group: "<< Group << endl;
    }
};



class Teacher:public Persone{
private:
    string Subject;
    vector<int> Groups;
public:
    Teacher(string firstname, string lastname, int Age, char Gender,vector<int> groups, string subject)
    :Persone(firstname, lastname, Age, Gender){
        Subject = subject;
        Groups = groups;
    }
    void setSubject(string subject){
        this->Subject = subject;
    }
    string showSubject(){
        return Subject;
    }
    void intro(){
        cout << "i am "<<firstName<< " "<< lastName<< " my age is "<< age << " i am the techer of "<< Subject;
    }
    void setGroups(vector<int> groups){
        this->Groups = groups;
    }
    void setStudentNote(Student& student, int note){
        bool access = false;
        for(int i=0;i<Groups.size();i++){
            if(student.showGroup()==Groups[i])
                access = true;
        }
        if(access){
            if(Subject==Ar){
                student.setAr(note);
            }
            if(Subject==Ma){
                student.setMath(note);
            }
            if(Subject==Sport){
                student.setSport(note);
            }
            if(Subject==Pc){
                student.setPc(note);
            }
            if(Subject==Eng){
                student.setEng(note);
            }
            cout << student.getFname() << " "<<student.getLname() <<" " <<Subject << " note: " << note << endl;
        }else{
            cout << "error, this student is not in your group!"<< endl;
        }
    }
};
class Auth{
private:
    string name;
    string gmail;
    string password;
    bool Access;
    string Work;
public:
    Auth(string name, string password){
        this->name = name;
        this->password = password;
    }
    Auth(string name, string gmail, string password){
        this->name = name;
        this->gmail = gmail;
        this->password = password;
        Access = false;
    }
    void setAccess(bool access){
        this->Access = access;
    }
    bool getAccess(){
        return Access;
    }
    void registerUser(){
        ifstream file;
        ofstream outfile;
        file.open("UserAuth.txt");
        string line;
        string fgmail;
        string fname;
        string fpassword;
        while(getline(file, line)){
            stringstream ss(line);
            ss >> fname >> fgmail >> fpassword;
            if(name == fname || gmail == fgmail){
                cout << "error, this user already registred" << endl;
                return;
            }
        }
        file.close();

        outfile.open("UserAuth.txt", ios::out | ios::app);
        outfile << name << " " << gmail << " " << password << endl;
        ofstream filex;
        filex.open("Student.txt");
        string studentName;
        string studentLastName;
        int age;
        char gender;
        cout << "first name: ";
        cin >> studentName;
        cout << "last name: ";
        cin >> studentLastName;
        cout << "age: ";
        cin >> age;
        cout << "gender: ";
        cin >> gender;
        filex << studentName << " "<<studentLastName<< " "<< to_string(age)<<" "<<gender << " "<< endl;
        filex.close();
        outfile.close();
        cout << "Registration successful!" << endl;
    }
    void loginUser(){
        ifstream file;
        file.open("UserAuth.txt");
        string line;
        string fgmail;
        string fname;
        string fpassword;
        while(getline(file, line)){
            stringstream ss(line);
            ss >> fname >> fgmail >> fpassword >> Work;
            if(name == fname && password == fpassword){
                cout << "login successful!" << endl;
                Access = true;
                return;
            }
        }
        cout << "error in password or name, please try again!" << endl;
        file.close();
    }
    void setWork(string work){
        this->Work = work;
    }
    string getWork(){
        return Work;
    }
};

class Owner:public Persone{
public:
    Owner(string firstName, string lastName, int Age, char Gender):Persone(firstName, lastName, age, gender){}
    void setStudentGroup(Student& student, int group){
        student.setGroup(group);
    }
    void setTeacherGroup(Teacher& teacher, vector<int> groups){
        teacher.setGroups(groups);
    }
    void setTeacherSubject(Teacher& teacher, string subject){
        teacher.setSubject(subject);
    };
    void setWork(Auth user, string work){
        user.setWork(work);
    }
};




int main(){
    int start = true;
    int choix;
    string name;
    string gmail;
    string password;
    string password2;
    while(start){
        cout << "1-login\n2-register\n3-stop App" << endl;
        cin >> choix;
        switch(choix){
        case 1:
            {
            cout << "name: ";
            cin >> name;
            cout << "password: ";
            cin >> password;
            Auth user = Auth(name, password);
            user.loginUser();
            while(user.getAccess()){
                int work;
                /*
                work = 1 : user is a owner
                work = 2 : user is a Teacher
                work = 3 : user is a Student
                */
                if(user.getWork()== O){
                    work = 1;
                    getchar();
                }
                else if(user.getWork()== T){
                    work = 2;
                    }
                else if(user.getWork()== S){
                    work = 3;
                    }
                else{
                    cout << "please wait for the owner to give you a role /2"<< endl;
                    getchar();
                    break;
                }
                switch(work){
                case 1:
                    {
                        Owner owner = Owner(name, name, 20, 'M');
                        int Ownerchoix;
                        cout << "Welcome " << owner.getFname() << endl;
                        cout << "1-Show Students List\n2-Show Teachers list\n3-edit Student\n4-edit teacher\n5-Logout" << endl;
                        cin >> Ownerchoix;
                        switch(Ownerchoix){
                        case 1:
                            {
                                cout << "student list: " << endl;

                            }
                            break;
                        case 2:
                            {
                                cout << "show Teacher: " << endl;

                            }
                            break;
                        case 3:
                            {
                                int c;
                                cout << "1-add A Student\n2-edit A Student" << endl;
                                cin >> c;
                                switch(c){
                                case 1:
                                    {
                                        ofstream file;
                                        file.open("Student.txt");
                                        string studentName;
                                        string studentLastName;
                                        int age;
                                        char gender;
                                        int group;
                                        cout << "Student name: ";
                                        cin >> studentName;
                                        cout << "last name: ";
                                        cin >> studentLastName;
                                        cout << "age: ";
                                        cin >> age;
                                        cout << "gender: ";
                                        cin >> gender;
                                        cout << "group: ";
                                        cin >> group;
                                        file << studentName << " "<<studentLastName<< " "<< to_string(age)<<" "<<gender << " "<< to_string(group) << endl;
                                        file.close();
                                        cout << "the student "<< studentName << " added to group: "<< group;

                                    }
                                    break;
                                case 2:
                                    {
                                        cout << "edit student" << endl;

                                    }
                                    break;
                                }

                            }
                            break;
                        case 4:
                            {
                                cout << "edit teacher: " << endl;

                            }
                            break;
                        case 5:
                            user.setAccess(false);
                            break;
                        }
                        break;
                    }
                case 2:
                    {
                    }
                    break;
                case 3:
                    {
                        Student student = Student(name, "test", 20, 'M', 2);
                        cout << "welcome " << student.getFname() << endl;
                        getchar();
                    }

                }
            }
            }
            break;
        case 2:
            {
            cout << "name: ";
            cin >> name;
            cout << "gmail: ";
            cin >> gmail;
            cout << "password: ";
            cin >> password;
            cout << "confirm password: ";
            cin >> password2;
            if(password!=password2){
                cout << "error in the password!"<< endl;
            }else{
                Auth newUser = Auth(name, gmail, password);
                newUser.registerUser();
            }
            }
            break;
        case 3:
            start = false;
            break;
        default:
            cout << "error in choice!!";
        }
    }
    return 0;
}