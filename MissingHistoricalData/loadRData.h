//
//  loadRData.h
//  4727Project
//
//  Created by WangGuoan on 10/28/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#ifndef loadRData_h
#define loadRData_h

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <RInside.h>
#include <iomanip>
#include <sys/types.h>
#include <dirent.h>

// "transform" a Rcpp:Datetime type into a c++ built-in time_t type
time_t RcppTime_to_timeT(Rcpp::Datetime& t);

// return the formatted string containing the information in Rcpp::Datetime, in local time
std::stringstream format_time_local(Rcpp::Datetime& t);

// return the formatted string containing the information in Rcpp::Datetime, in GMT time
std::stringstream format_time_GMT(Rcpp::Datetime& t);

// load R Data given a path (string)
std::vector<Rcpp::NumericMatrix> loadRData(std::string, RInside&, std::vector<std::string>&);

// very simple test case
void simpleTest(Rcpp::NumericMatrix);

// get the indices (leftmost column) of the NumericMatrix (in our case, indices are the times of each tick data)
Rcpp::DatetimeVector get_index(Rcpp::NumericMatrix);

// get the column names ("Bid.Price" "Bid.Size" "Ask.Price" "Ask.Size" "Trade.Price" "Volume")
Rcpp::CharacterVector get_colnames(Rcpp::NumericMatrix);

void get_all_files_in_dir(std::string path, std::vector<std::string>& files);



#endif /* loadRData_h */
