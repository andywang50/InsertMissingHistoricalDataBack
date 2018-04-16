//
//  TickData.cpp
//  4727Project
//
//  Created by WangGuoan on 11/13/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#include "TickData.h"
#include <stdio.h>

// exception
//Rcpp::CharacterVector TradeData::default_colnames({"Bid.Price","Bid.Size","Ask.Price","Ask.Size","Trade.Price","Volume"});


BidData::BidData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _symbol = "", std::string _securityID = ""):AbstractData(t,data,_symbol,_securityID){
    
    this->price = data[0]; this->addMemberByKey("price",data[0]);
    this->size = data[1]; this->addMemberByKey("size",static_cast<int>(data[1]));
    
}

//BidData::BidData():AbstractData(){}

AskData::AskData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _symbol = "", std::string _securityID = ""):AbstractData(t,data,_symbol,_securityID){
    
    this->price = data[2]; this->addMemberByKey("price",data[2]);
    this->size = data[3]; this->addMemberByKey("size",static_cast<int>(data[3]));
    
}

//AskData::AskData():AbstractData(){}
