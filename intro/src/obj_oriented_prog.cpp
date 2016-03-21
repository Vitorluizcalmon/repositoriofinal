#include <iostream>
#include <string>

class Person
{
    /* Public members */
    public:
    
        /* Constructors and destructors */        
        Person();                                           // default constructor        
        Person(std::string newName, int newBirthYear);      // customized constructor        
        Person(const Person &other);                        // copy constructor
    
        /* Access private members */
        std::string getName();
        int getBirthYear();
    
        /* Edit private members */
        void setName(std::string newName);
        void setBirthYear(int newBirthYear);
    
        /* Other class functions */
        void introduce(std::string otherName);
        int computeAge(int currentYear);
    
    /* Private members */
    private:
        std::string name;
        int birthYear;
};

Person::Person()
{
    std::cout << "Creating a default Person" << std::endl;
    
    // assign default values to object's variables
    this-> name = "Default name";
    this->birthYear = 0;
}

Person::Person(std::string newName, int newBirthYear)
{
    std::cout << "Creating a customized Person: " << newName << ", " << newBirthYear << std::endl;
    
    // set object's variables as specified by arguments
    this-> name= newName;
    this-> birthYear= newBirthYear; 
}

Person::Person(const Person &other)
{
    std::cout << "Creating a copy of another Person: " << other.name << ", " << other.birthYear << std::endl;
    
    // set object's variables to be like the ones belonging to other
    this->name = other.name;
    this->birthYear = other.birthYear;
}

std::string Person::getName()
{
    // return name
    return this-> name;
}

int Person::getBirthYear()
{
    // return birth year
    return this-> birthYear;
}

void Person::setName(std::string newName)
{
    // set name to specified string
    this->name = newName;
}

void Person::setBirthYear(int newBirthYear)
{
    // set birth year to specified value
    this->birthYear = newBirthYear;
}

void Person::introduce(std::string otherName)
{
    // print sentence saying "hello" to otherName and telling this object's name
    std:: cout<<"Hello ,"<< otherName<<"! My name is  "<< this->name<<"."<<std::endl;
}

int Person::computeAge(int currentYear)
{
    // compute and return age
    return currentYear - this->birthYear; 
}

int main(int argc, char **argv)
{
    Person me;
    std::string myname;
    int myBirthYear;
    std::cout <<"Type your name and birth year:"<<std::endl;
    std::cin>>myname>>myBirthYear;
    me.setName(myname);
    me.setBirthYear(myBirthYear);
    std::cout<< "My name is "<< me.getName()<<" and I'm "<< me.computeAge(2016)<<" years old."<< std::endl;
    
    Person p1("Pedro", 1981);
    Person clone(me);
    clone.introduce(p1.getName());
    
    
    return 0;
}
