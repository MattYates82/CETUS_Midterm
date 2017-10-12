/****************************************************************************
**Program Filename:  CETUS_data.hpp
**Author:  Jason Fisher
**Date:  10/6/2017
**Description:  data.hpp File for CMD1 project.  Data files will control game
**data input from source files and data output to save files
****************************************************************************/
#ifndef CETUS_DATA_HPP
#define CETUS_DATA_HPP
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

//Will load source file data into map and return map
std::map<std::string, std::string> loadFile(std::string);
void saveFile(std::string, std::map<std::string, std::string>);

#endif