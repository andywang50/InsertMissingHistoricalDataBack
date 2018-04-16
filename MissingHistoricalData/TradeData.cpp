//
//  TradeData.cpp
//  4727Project
//
//  Created by WangGuoan on 11/6/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#include <stdio.h>
#include "TradeData.h"

// exception
//Rcpp::CharacterVector TradeData::default_colnames({"Bid.Price","Bid.Size","Ask.Price","Ask.Size","Trade.Price","Volume"});


TradeData::TradeData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _symbol = "", std::string _securityID = ""):AbstractData(t,data,_symbol,_securityID){
    
    this->price = data[4]; this->addMemberByKey("price",data[4]);
    this->size = data[5]; this->addMemberByKey("size",static_cast<int>(data[5]));
    
}

//TradeData::TradeData():AbstractData(){}
