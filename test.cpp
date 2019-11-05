#include <iostream>
#include <fstream>

#include "filedb.h"
#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(Add_person) {

    fstream file;
    file.open("test.txt", ios_base::out);
    file.close();

    FileDB db("test.txt");
    Person a{1, "Login", "Name", "Email"};
    db.addPerson(a);
    BOOST_CHECK_EQUAL(db.getPerson(a.id), a);

}

BOOST_AUTO_TEST_CASE(Delete_person) {

    fstream file;
    file.open("test.txt", ios_base::out);
    file.close();

    FileDB db("test.txt");

    Person t1{1, "Login1", "Name1", "Email1"};
    db.addPerson(t1);

    Person t2{3, "Login3", "Name3", "Email3"};
    db.addPerson(t2);

    Person t3{7, "Login5", "Name5", "Email5"};
    db.addPerson(t3);

    db.delPerson(t2);
    BOOST_CHECK_EQUAL(db.getPerson(t1.id), t1);
    BOOST_CHECK_EQUAL(db.getPerson(t2.id), Person());
    BOOST_CHECK_EQUAL(db.getPerson(t3.id), t3);
}

BOOST_AUTO_TEST_CASE(Copy_filedb) {

    fstream file;
    file.open("test.txt", ios_base::out);
    file.close();

    FileDB db("test.txt");
    Person t1{1, "Login1", "Name1", "Email1"};
    db.addPerson(t1);

    Person t2{3, "Login3", "Name3", "Email3"};
    db.addPerson(t2);

    Person t3{7, "Login5", "Name5", "Email5"};
    db.addPerson(t3);

    db.copyFile("res.txt");
    FileDB newDB("res.txt");

    BOOST_CHECK_EQUAL(newDB.getPerson(t1.id), t1);
    BOOST_CHECK_EQUAL(newDB.getPerson(t2.id), t2);
    BOOST_CHECK_EQUAL(newDB.getPerson(t3.id), t3);

}

BOOST_AUTO_TEST_CASE(FileDB_union) {

    fstream file;
    file.open("first.txt", ios_base::out);
    file.close();

    FileDB db1("first.txt");
    Person t1{1, "Login1", "Name1", "Email1"};
    db1.addPerson(t1);

    Person t2{3, "Login3", "Name3", "Email3"};
    db1.addPerson(t2);

    Person t3{7, "Login5", "Name5", "Email5"};
    db1.addPerson(t3);

    db1.copyFile("second.txt");
    FileDB newDB("second.txt");

    newDB.delPerson(t2);
    Person t4{12, "Login12", "Name12", "Email12"};
    newDB.addPerson(t4);

    db1.fileUnion(newDB.pathToFile());

    BOOST_CHECK_EQUAL(db1.getPerson(t1.id), t1);
    BOOST_CHECK_EQUAL(db1.getPerson(t2.id), t2);
    BOOST_CHECK_EQUAL(db1.getPerson(t3.id), t3);
    BOOST_CHECK_EQUAL(db1.getPerson(t4.id), t4);

}
