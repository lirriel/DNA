////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_repairer.h/cpp
// Author:       Iskhakova Lyaysan
// Version:      0.2.0
// Date:         08.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "dna_repairer.h"
#include "vector"
#include "algorithm"
#include <fstream>
#include <sstream>


using namespace std;        // допустимо писать в глобальном пространстве только в cpp-файлах!

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  Очень важно!!
//  Этот файл является лишь примером-подсказкой, который
//  показывает как обращаться со списком имея доступ лишь
//  к pPreHead.
//  Вы должны опираясь на его реализовать свое правильное решение.
//  Например в методе readFile не проверяется формат и не
//  возбуждаются исключения, а repairDNA делает вообще
//  неизвестно что!!!
//  Кроме того этот пример будет работать только если у вас
//  правильно реализован linked_list.h

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/// Поиск следующего по возрастанию соответствующего узла для \c firstNode
/// в списке \c dnaChain для последующей вставки элемента
DNARepairer::NodeDNA* findByNumber(DNARepairer::DNAChain* dnaChain, DNARepairer::NodeDNA* firstNode)
{
    DNARepairer::NodeDNA* nodeDNA = dnaChain->getPreHead();
    nodeDNA->value.number = -1;

    // поисе первого узла, значение которого больше \c firstNode
    while (nodeDNA->next && nodeDNA->next->value.number < firstNode->value.number)
        nodeDNA = nodeDNA->next;

    return nodeDNA;
}


/// Поиск части целой цепочки ДНК в испорченной, начиная с \c firstNode
DNARepairer::NodeDNA* findLast(DNARepairer::DNAChain& dnaChain, DNARepairer::NodeDNA* firstNode)
{
    DNARepairer::NodeDNA* nodeDNA = firstNode->next;
    DNARepairer::NodeDNA* current = firstNode;

    // поиск следующего по очередности нуклеотида с тем же основанием
    while (nodeDNA
           && nodeDNA->value.id == firstNode->value.id
           && nodeDNA->value.number - 1 == firstNode->value.number)
    {
        firstNode = nodeDNA;
        current = nodeDNA;
        nodeDNA = nodeDNA->next;
    }

    return current;
}


/// Исследование одной испорченной цепочки ДНК \c dnaChain
void repairChain(DNARepairer::Id2DnaMap &id2DnaMap, DNARepairer::DNAChain& dnaChain)
{
    DNARepairer::NodeDNA* headDnaChain = dnaChain.getPreHead();

    DNARepairer::DNAChain* newChain = nullptr;
    DNARepairer::NodeDNA* lastNode;

    // проход по цепочке ДНК
    while (headDnaChain->next)
    {
        // поиск целого куска ДНК
        lastNode = findLast(dnaChain, headDnaChain->next);

        if (id2DnaMap.count(lastNode->value.id) == 0)
        {
            newChain = new DNARepairer::DNAChain();
            newChain->moveNodesToEnd(headDnaChain, lastNode);
            id2DnaMap.insert(std::pair<string, DNARepairer::DNAChain*>(lastNode->value.id, newChain));
        }
        else
        {
            newChain = id2DnaMap.at(lastNode->value.id);
            DNARepairer::NodeDNA* toInsert = findByNumber(newChain, headDnaChain->next);
            newChain->moveNodesAfter(toInsert, headDnaChain, lastNode);
        }
    }
}


/// Копирование данных из Id2DnaMap в _dnaStorage по цепочке
void copyDnaChain(DNARepairer::DNAChain& dnaChain, DNARepairer::DNAChain* dnaChain1)
{
    xi::Node<DNAElement>* node = dnaChain1->getPreHead();

    while (node->next)
    {
        dnaChain.addElementToEnd(node->next->value);
        node = node->next;
    }

    delete node;
}


void DNARepairer::repairDNA()
{
    DNARepairer::Id2DnaMap id2DnaMap;

    // проход по испорченным цепочкам ДНК
    NodeDNAChain* headDnaChain = _dnaStorage.getPreHead();
    while (headDnaChain->next)
    {
        repairChain(id2DnaMap, headDnaChain->next->value);
        headDnaChain = headDnaChain->next;
    }

    // перенос данных из id2DnaMap в _dnaStorage
    ListOfDNAChains listOfDNAChains;
    for (auto const& x:id2DnaMap)
    {
        DNAChain* _dnaChain = id2DnaMap.at(x.first);
        DNAChain _chain;
        copyDnaChain(_chain, _dnaChain);
        listOfDNAChains.addElementToEnd(_chain);
    }

    _dnaStorage = listOfDNAChains;
}


void DNARepairer::printDNAStorage()
{
    xi::Node<DNARepairer::DNAChain>* node = _dnaStorage.getPreHead();
    while (node->next)
    {
        node = node->next;

        NodeDNA* node2 = node->value.getPreHead();

        while (node2->next)
        {
            node2 = node2->next;

            cout << node2->value.id;
            cout << node2->value.number << ":";
            cout << node2->value.base << "  ";
        }

        cout << endl;
    }
}


/// Проверка наличия всех нуклеотидов в существующей цепочке по номерам
bool checkNumbers(const vector<int>& vector1)
{
    for (unsigned int i = 0; i < vector1.size() - 1; ++i)
        if (vector1.at(i + 1) - 1 != vector1.at(i))
            return 0;
    return 1;
}


/// Заполнение \c data для проверки наличия всех нуклеотидов в цепочке
bool checkCorrect(map< string, vector<int> >& data)
{
    bool f = 1;
    vector<int> vector1;
    for (auto const& x:data)
    {
        vector1 = data.at(x.first);
        sort(vector1.begin(), vector1.end());
        if (!checkNumbers(vector1))
            return 0;
    }
    return 1;
}


/// Добавление данных в \c data для последующего оценивания
void addData(map< string, vector<int> >& data, DNAElement element)
{
    vector<int> vector1;

    if (data.count(element.id) == 0)
    {
        vector1.push_back(element.number);
        data.insert(std::pair<string, vector<int>>(element.id, vector1));
    }
    else
    {
        vector1 = data.at(element.id);
        vector1.push_back(element.number);
        data[element.id] = vector1;
    }
}


void DNARepairer::readFile(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
        throw std::runtime_error("Could not open file");


    // начинаем с головы
    NodeDNAChain* it = _dnaStorage.getPreHead();
    map<string, vector<int>> map1;

    string line;    
    while (getline(fin,line))
    {        
        // Создаем узел ДНК на куче
        NodeDNAChain* pNewNode = new NodeDNAChain;                

        //Создаем строковый поток для разбора
        istringstream istr(line);

        string strTmp;
        while (istr >> strTmp)                                  // разбиваем поток на слова
        {
            DNAElement tmpDNAElement(strTmp);                   // каждое слово читаем в DNAElement
            addData(map1, tmpDNAElement);
            pNewNode->value.addElementToEnd(tmpDNAElement);     // добавляем полученный DNAElement в ДНК
        }
        it->next = pNewNode;
        it = it->next;
    }

    if (!checkCorrect(map1))
        throw invalid_argument("Not enough data! Some dnaChains were lost!\n");
}


DNARepairer::ListOfDNAChains& DNARepairer::getDNAStorage()
{
    return _dnaStorage;
}