//
//  RHashTable.cpp
//  4727Project_MissingData
//
//  Created by Ellen Sun on 11/9/17.
//  Copyright © 2017 Ellen Sun. All rights reserved.
//

#include <iostream>
#include "RHashTable.h"
#include "json.h"
#include "TradeData.h"
#include <RInside.h>

// constructor
RHashTable::RHashTable():index(""),type(""){
    
}
RHashTable::RHashTable(std::string index, std::string type){
    this->index = index;
    this->type = type;
}

// getter function
std::unordered_map<long, TradeData> RHashTable::get_hashtable() const{
    return this->hashtable;
}
std::string RHashTable::get_index() const{
    return this->index;
}
std::string RHashTable::get_type() const{
    return this->type;
}

/*write function that takes Rcpp time, data and hash as arguments - make it a hashtable
 - declare an unordered map
 - for each row in Rcpp, make a tradedata if not NA
 - add each timestamp as key, tradedata as value into the unordered map*/
void RHashTable::toHashtable(Rcpp::DatetimeVector& t, const Rcpp::NumericMatrix& data,std::string _symbol, std::string _securityID){
    for (int i = 0; i<data.nrow(); i++){
        // for each row in Rcpp, make a tradeData object;
        if(std::isnan(data.row(i)[4])){ // Trade.Price column, comment out when dealing with tick data in the future
            continue;
        }
        TradeData TD(t[i],data.row(i), _symbol, _securityID);
        std::pair<long,TradeData> elementforHash (TD.get_transactTime(),TD);
        hashtable.insert(elementforHash);
    }
}

