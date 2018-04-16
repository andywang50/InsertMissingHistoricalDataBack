//
//  AbstractData.cpp
//  4727Project
//
//  Created by WangGuoan on 11/13/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#include "AbstractData.h"

#include <stdio.h>
#include "TradeData.h"

// exception
//Rcpp::CharacterVector TradeData::default_colnames({"Bid.Price","Bid.Size","Ask.Price","Ask.Size","Trade.Price","Volume"});

/*
AbstractData::AbstractData():price(0.0),size(0),side('\0'),securityID(""),symbol(""),transactTime(0.0),transactDateTime(""){
    
}
*/

AbstractData::AbstractData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _symbol = "", std::string _securityID = ""){
    
    //this->price = data[4]; this->addMemberByKey("size",data[4]);//this->addMemberByKey("price", data[colnames_to_index.at("trade.price")]);
    //this->size = data[5]; this->addMemberByKey("size",static_cast<int>(data[5]));
    this->side = 'N'; this->addMemberByKey("side","N");
    this->symbol = _symbol; this->addMemberByKey("symbol",_symbol);
    this->securityID = _securityID; this->addMemberByKey("securityID",_securityID);
    
    long thetimestamp = floor(t.getFractionalTimestamp()*1000+0.5);
    this->transactTime = thetimestamp; this->addMemberByKey("transactTime",thetimestamp);
    this->transactDateTime = format_time_local(t).str(); this->addMemberByKey("transactDateTime",format_time_local(t).str());
    
    //this->addMemberByKey("price", data[4]);
    
}

double AbstractData::get_price() const{
    return this->price;
}



int AbstractData::get_size() const{
    return this->size;
}
char AbstractData::get_side() const{
    return this->side;
}


std::string AbstractData::get_securityID() const{
    return this->securityID;
}

std::string AbstractData::get_symbol() const{
    return this->symbol;
}
long AbstractData::get_transactTime() const{
    return this->transactTime;
}
std::string AbstractData::get_transactDateTime() const{
    return this->transactDateTime;
}

//return the string format of Data
std::string AbstractData::to_string() const{
    //return "";
    
    std::stringstream ss;
    ss << *this;
    return ss.str();
}
// return the json format of TradeData
Json::Object AbstractData::to_json() const{
    //return Json::Object();
    return *this;
}

/// Give access to member for this operator.
std::ostream& operator<<(std::ostream& os, const AbstractData& AData){
    os << "{";
    os << "\"price\":" << std::fixed << std::setprecision(2) <<  AData.price << ","
    << "\"size\":" << std::to_string(AData.size) << ","
    << "\"side\":" << AData.side << ","
    << "\"securityID\":" << AData.securityID << ","
    << "\"symbol\":" << AData.symbol << ","
    << "\"transactTime\":" << std::to_string(static_cast<long>(AData.transactTime)) << ","
    << "\"transactDateTime\":" << AData.transactDateTime;
    os << "}";
    
    return os;
    
}

bool AbstractData::operator==(const Json::Object& other){
    Json::Object temp = *this;
    return (temp == other);
}

bool AbstractData::operator!=(const Json::Object& other){
    Json::Object temp = *this;
    return (temp != other);
}
