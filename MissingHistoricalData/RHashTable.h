//
//  RHashTable.hpp
//  4727Project_MissingData
//
//  Created by Ellen Sun on 11/9/17.
//  Copyright © 2017 Ellen Sun. All rights reserved.
//

#ifndef RHashTable_h
#define RHashTable_h

#include <stdio.h>
#include <RInside.h>
#include "json.h"
#include "TradeData.h"

class RHashTable{
public:
    // constructor
    RHashTable();
    RHashTable(std::string index, std::string type);
    
    // getter function
    std::unordered_map<long, TradeData> get_hashtable() const;
    std::string get_index() const;
    std::string get_type() const;
    
    // convert Rcpp into a hashtable
    void toHashtable(Rcpp::DatetimeVector& t, const Rcpp::NumericMatrix& data,std::string _symbol, std::string _securityID);
    
private:
    std::unordered_map<long, TradeData> hashtable;
    std::string index;
    std::string type;
};

#endif /* RHashTable_hpp */
