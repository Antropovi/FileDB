#ifndef FILEDB_H
#define FILEDB_H

#include <string>
#include <set>

#include <fstream>
#include <iostream>

//Class Person represents lines in fileDB
//Each person is stored as line "<id>;<login>;<Name>;<Email>\n"
class Person
{
public:
    friend std::istream& operator>>(std::istream& is, Person& p);
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
    friend bool operator ==(const Person& lhs, const Person& rhs);
    friend bool operator<(const Person& lhs, const Person& rhs);

    int id;
    std::string login;
    std::string name;
    std::string email;
};

//Class to store Persons in file
class FileDB
{
public:
    FileDB(const std::string& pathToFile);

    bool addPerson(const Person& person);
    bool delPerson(const Person& person);

    void printAll() const;

    bool copyFile(const std::string& newPath) const;
    bool fileUnion(const std::string& otherPath);

    //Functions added for tests
    Person getPerson(int id);
    std::string pathToFile() const {
        return m_path;
    }

private:

    bool serialize(const std::string& pathToFile) const;

    std::string m_path;
    std::set<Person> m_persons;
};

#endif // FILEDB_H
