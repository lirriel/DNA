////////////////////////////////////////////////////////////////////////////////
// Module Name:  main.cpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "dna_repairer.h"

using namespace std;

// TODO: укажите здесь абсолютный путь к файлу с кусочками ДНК для восстановления
static const char* INP_FILENAME = "D:\\HSE\\C++\\4_project\\prj-1.0\\prj-1.0\\res\\test5.in";

int main (int argc, char* argv[])
{
//    xi::LinkedList<int> a;
//    for (int i = 0; i < 5; ++i) {
//        a.addElementToEnd(i);
//    }
//    for (int i = 0; i < a.size(); ++i) {
//        cout << a[i] << " ";
//    }
//    xi::LinkedList<int> b;
//    for (int i = 7; i < 10; ++i) {
//        b.addElementToEnd(i);
//    }
//    a = b;
//    cout <<endl;
//    for (int i = 0; i < a.size(); ++i) {
//        cout << a[i] << " ";
//    }
//    int i = 2;
//    xi::LinkedList<int> c;
//    c.addElementToEnd(i);
//    i = 1;
//    c.addElementToEnd(i);
//    i += 10;
//    c.addElementToEnd(i);
//    i+=1;
//    xi::Node<int>* node = c.insertNewElement(i, c.getPreHead());
//    xi::Node<int>* node1 = c.insertNewElement(i, c.getPreHead());
//    c.moveNodesAfter(a.getPreHead(), c.getPreHead(), node);
//    cout <<endl;
//    for (int i = 0; i < a.size(); ++i) {
//        cout << a[i] << " ";
//    }
//    a.deleteNodes(a.getPreHead(), node);
//    cout <<endl;
//    for (int i = 0; i < a.size(); ++i) {
//        cout << a[i] << " ";
//    }

    try{
        while (true)
        {
        DNARepairer dnarepairer;

        dnarepairer.readFile(INP_FILENAME);


        cout << "Broken DNAs" << endl;
        dnarepairer.printDNAStorage();

        dnarepairer.repairDNA();

        cout << "\nGood as it is" << endl;
        dnarepairer.printDNAStorage();
        }
    }
    catch(exception &e) {
        cout << e.what();
    }
    cout << endl;

    return EXIT_SUCCESS;
}

