////////////////////////////////////////////////////////////////////////////////
// Module Name:  dna_element.h/cpp
// Author:       Iskhakova Lyaysan
// Version:      0.2.0
// Date:         08.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <sstream>
#include "dna_element.h"

DNAElement::DNAElement()
{
    id = "";
    number = -1;
    base = "";
}


DNAElement::DNAElement(const std::string &description)
{
    readFromString(description);
}


void DNAElement::readFromString(const std::string &description)
{
    if (description.length() <  4)                                          // соответствующая формату длина больше 3
        throw std::invalid_argument("Length is incorrect!");

    id = description[0];
    if (!(id >= "a" && id <= "z"))                                          // идентификатор между 'a' и 'z'
        throw std::invalid_argument("Id must be a char between 'a' and 'z'!");

    if (description[description.length() - 2] != ':')                       // после номера нуклеотида идет ':'
        throw std::invalid_argument("Second symbol from the right must be ':'!");

    std::string subStr = description.substr(1, description.length() - 3);
    std::stringstream subNum(subStr);

    if (!(subNum >> number))                                                // между идентификатором и ':' номер нук-да
        throw std::invalid_argument("Second part must be integer!");

    base = description[description.length() - 1];
    std::string bases = "ATCG";
    if (bases.find_last_of(base) == std::string::npos)                                          // возможно одно из 4 оснований
        throw std::invalid_argument("Base doesn't correspond with the correct ones!");
}