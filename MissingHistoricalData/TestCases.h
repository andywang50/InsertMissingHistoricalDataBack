//
//  TestCases.hpp
//  4727Project_MissingData
//
//  Created by Ellen Sun, WangGuoan on 1/12/18.
//  Copyright © 2018 Ellen Sun,Guoan Wang. All rights reserved.
//

#ifndef TestCases_hpp
#define TestCases_hpp

#include <stdio.h>
#include "elasticsearch.h"
#include "TradeData.h"
#include "RHashTable.h"
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// test if ES works
void testES();

// test if TradeData class works
void testTradeData(Rcpp::NumericMatrix& Data,Rcpp::DatetimeVector& index);

// test if loadRData works
void testloadRData(Rcpp::NumericMatrix data);

// test if RHashTable class works
void testRHashTable(Rcpp::NumericMatrix& Data,Rcpp::DatetimeVector& index, std::string _index, std::string _type);

#endif /* TestCases_hpp */
