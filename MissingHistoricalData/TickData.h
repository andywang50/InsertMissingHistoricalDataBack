//
//  TickData.hpp
//  4727Project
//
//  Created by WangGuoan on 11/13/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#ifndef TickData_h
#define TickData_h

#include <stdio.h>


#include "AbstractData.h"
#include "loadRData.h"
#include <RInside.h>
#include <string>

/**
 class BidData extends AbstractData class.
 */

//const std::unordered_map<std::string, int> colnames_to_index ({{"bid.price",0},{"bid.size",1},{"ask.price",2},{"ask.size",3},{"trade.price",4},{"volume",5}});


class BidData: public AbstractData::AbstractData{
public:
    //static Rcpp::CharacterVector default_colnames;
    
    //BidData();
    BidData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _securityID, std::string _symbol);
};

/**
 class AskData extends AbstractData class.
 */

class AskData: public AbstractData::AbstractData{
public:
    //static Rcpp::CharacterVector default_colnames;
    
    //AskData();
    AskData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _securityID, std::string _symbol);
};


#endif /* TickData_h */
