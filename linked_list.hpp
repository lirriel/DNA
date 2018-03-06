////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Sergey Shershakov, Leonid Dworzanski
// Version:      0.2.0
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

namespace xi {

template <class T>
LinkedList<T>::LinkedList() 
{
    //Creation of the dummy/sentinel element
    _preHead = new Node<T>;
    _preHead->next = nullptr;

    // TODO: Write your code here
    // ...
}

template <class T> 
LinkedList<T>::~LinkedList()
{
    // TODO: Write your code here

    // ...
    if (_preHead->next)
        deleteNodes(_preHead, getLastNode());
    // на забудьте удалить иск. элемент, например так:
    delete _preHead;
    _preHead = nullptr;
}


// TODO: Write your code here

template <class T>
Node<T>* LinkedList<T>::getPreHead()
{
    return _preHead;
}


template <class T>
Node<T>* LinkedList<T>::getLastNode()
{
    Node<T>* _node = getPreHead();

    while (_node->next)
        _node = _node->next;

    return _node;
}


template <class T>
void LinkedList<T>::swap(LinkedList <T> &linkedList)
{
    Node<T>* temp = _preHead;
    _preHead = linkedList._preHead;
    linkedList._preHead = temp;
}


template <class T>
LinkedList<T>::LinkedList(const LinkedList <T>& linkedList)
{
    Node<T>* _node = linkedList._preHead;
    _preHead = new Node<T>();

    while (_node->next)
    {
        addElementToEnd(_node->next->value);
        _node = _node->next;
    }
}

template <class T>
T& LinkedList<T>::operator[](int i)
{
    Node<T>* _node = getPreHead();
    int j = -1;

    while (_node->next && j != i)
    {
        _node = _node->next;
        j++;
    }

    if (j != i)
        return _preHead->value;

    return _node->value;
}


template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& linkedList)
{
    if (this != &linkedList)
    {
        LinkedList<T> temp(linkedList);
        swap(temp);
    }
    return *this;
}


template <class T>
int LinkedList<T>::size()
{
    Node<T>* _node = getPreHead();
    int _size = 0;

    while (_node->next)
    {
        _node = _node->next;
        _size++;
    }

    return _size;
}


template <class T>
void LinkedList<T>::addElementToEnd(T &value)
{
    Node<T>* _newNode = new Node<T>();
    _newNode->value = value;

    Node<T>* _endNode = getLastNode();

    _endNode->next = _newNode;
}

template <class T>
Node<T>* LinkedList<T>::removeNodeFromOther(Node <T> *prevNode)
{
    Node<T>* currentNode = prevNode->next;

    if (currentNode)
        prevNode->next = currentNode->next;

    return currentNode;
}

template <class T>
void LinkedList<T>::deleteNextNode(Node <T>* pNodeBefore)
{
    Node<T>* _currentNode = removeNodeFromOther(pNodeBefore);

    delete _currentNode;
    _currentNode = nullptr;
}


template <class T>
void LinkedList<T>::moveNodeAfter(Node <T> *pNode, Node <T> *pNodeBefore)
{
    Node<T>* _pNodeNext = pNode->next;
    Node<T>* _insertingNode = removeNodeFromOther(pNodeBefore);

    pNode->next = _insertingNode;
    _insertingNode->next = _pNodeNext;
}


template <class T>
void LinkedList<T>::moveNodeToEnd(Node <T> *pNodeBefore)
{
    Node<T>*  _currentNode = pNodeBefore->next;
    pNodeBefore->next = _currentNode->next;

    addElementToEnd(_currentNode->value);

    delete _currentNode;
    _currentNode = nullptr;
}


template <class T>
void LinkedList<T>::moveNodesToEnd(Node <T> *pNodeBefore, Node <T> *pNodeLast)
{
    Node<T>* endNode = getLastNode();
    endNode->next = pNodeBefore->next;

    pNodeBefore->next = pNodeLast->next;
    pNodeLast->next = nullptr;
}


template <class T>
void LinkedList<T>::deleteNodes(Node <T> *pNodeBefore, Node <T> *pNodeLast)
{
    while (pNodeBefore->next != pNodeLast)
        deleteNextNode(pNodeBefore);

    pNodeBefore->next = pNodeLast->next;

    delete pNodeLast;
    pNodeLast = nullptr;
}


template <class T>
void LinkedList<T>::moveNodesAfter(Node <T> *pNode, Node <T> *pNodeBefore, Node <T> *pNodeLast)
{
    Node<T>* pNodeNext = pNode->next;
    pNode->next = pNodeBefore->next;
    pNodeBefore->next = pNodeLast->next;
    pNodeLast->next = pNodeNext;
}


} // namespace xi