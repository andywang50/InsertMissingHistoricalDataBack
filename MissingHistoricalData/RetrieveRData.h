//
//  RetrieveRData.hpp
//  4727Project_MissingData
//
//  Created by Ellen Sun on 1/12/18.
//  Copyright © 2018 Ellen Sun. All rights reserved.
//

#ifndef RetrieveRData_h
#define RetrieveRData_h

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <RInside.h>
#include <time.h>
#include <string>

// get time range for RData/ES matching from user
void getUserTime(std::vector<int> &timeRange);

// get product NAME for RData/ES matching from user
void getUserProduct(std::vector<std::string> &productName, std::string path);

// search for an element in a vector
bool searchVector (std::string target, std::vector<std::string> &source);

// assemble time and product into filenames
std::string assemble (int year, int month, int date, std::string product);

//get all file names according to user input
void createFileNames (std::vector<std::string> &files,std::vector<int> &timeRange,std::vector<std::string> &productName, std::vector<std::string> &allfiles);

// Given a filepath, such as yyyy.mm.dd.symbol.RData, return vector: {yyyymm, symbol}
std::vector<std::string> indexAndType(std::string filepath);


#endif /* RetrieveRData_h */
