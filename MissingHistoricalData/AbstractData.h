//
//  AbstractData.hpp
//  4727Project
//
//  Created by WangGuoan on 11/13/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#ifndef AbstractData_h
#define AbstractData_h

#include <stdio.h>

#include "json.h"
#include "loadRData.h"
#include <RInside.h>
#include <string>

/**
 class TradeData extends JsonObject class.
 */

const std::unordered_map<std::string, int> colnames_to_index ({{"bid.price",0},{"bid.size",1},{"ask.price",2},{"ask.size",3},{"trade.price",4},{"volume",5}});


class AbstractData: public Json::Object{
public:
    static Rcpp::CharacterVector default_colnames;
    
    //AbstractData();
    AbstractData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _securityID, std::string _symbol);
    
    //getter functions
    double get_price() const;
    int get_size() const;
    char get_side() const;
    std::string get_securityID() const;
    std::string get_symbol() const;
    long get_transactTime() const;
    std::string get_transactDateTime() const;
    
    //return the string format of TradeData
    std::string to_string() const;
    
    // return the json format of TradeData
    Json::Object to_json() const;
    
    /// Give access to member for this operator.
    friend std::ostream& operator<<(std::ostream& os, const AbstractData& AData);
    
    bool operator ==(const Json::Object& other);
    bool operator !=(const Json::Object& other);
    
    
protected:
    double price;
    int size;
    char side; // what does side mean for trading data?
    std::string securityID;
    std::string symbol;
    long transactTime; // timestamp
    std::string transactDateTime;
    
};

#endif /* AbstractData_h */
