#include "filedb.h"

//------------Person-------------
std::istream& operator>>(std::istream& is, Person& p) {
    std::string id;
    if (std::getline(is, id, ';') &&
        std::getline(is, p.login, ';') &&
        std::getline(is, p.name, ';') &&
        std::getline(is, p.email)) {
        p.id = std::stoi(id);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.id << ';' << p.login << ';' << p.name << ';' << p.email;
    return os;
}

bool operator ==(const Person& lhs, const Person& rhs) {
    return lhs.login == rhs.login || lhs.id == rhs.id;
}

//Ids are unique, so we can store Persons in set with this
bool operator<(const Person& lhs, const Person& rhs) {
    return lhs.id < rhs.id;
}

//------------FileDB--------------
FileDB::FileDB(const std::string& pathToFile) : m_path(pathToFile)
{
    std::ifstream file(m_path);
    if (file.is_open()) {
        Person p;
        while(file >> p) {
            m_persons.emplace(p);
        }
    } else {
        std::cout << "File not found" << std::endl;
    }
}

bool FileDB::addPerson(const Person& person) {
    //Add new to set
    m_persons.emplace(person);

    //Write into file
    std::ofstream file(m_path, std::ios_base::app);
    if (file.is_open()) {
        file << person;
        return true;
    } else {
        return false;
    }
}

bool FileDB::delPerson(const Person& person) {
    //Delete person from set and re-write new file
    auto iter = m_persons.find(person);
    if (iter != m_persons.end()) {
        m_persons.erase(iter);
        return serialize(m_path);
    } else {
        return false;
    }
}

void FileDB::printAll() const {
    for(const auto& person : m_persons) {
        std::cout << person << std::endl;
    }
}

bool FileDB::copyFile(const std::string& newPath) const {
    return serialize(newPath);
}

bool FileDB::fileUnion(const std::string &otherPath) {
    FileDB otherDB(otherPath);

    for(const auto& person : otherDB.m_persons) {
        auto iter = m_persons.find(person);
        if (iter != m_persons.end()) {
            std::cout << "Duplicate found: " << person << std::endl;
        } else {
            m_persons.emplace(person);
        }
    }
    return serialize(m_path);
}

Person FileDB::getPerson(int id) {
    for (const auto& person : m_persons) {
        if (person.id == id) {
            return person;
        }
    }
    return Person();
}

bool FileDB::serialize(const std::string& pathToFile) const {
    //Trunc is used to remove old data
    std::ofstream file(pathToFile, std::ios_base::trunc);

    if(!file.is_open()) {
        return false;
    }
    for(const auto& person : m_persons)
        file << person << std::endl;
    return true;
}
