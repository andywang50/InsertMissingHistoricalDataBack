//
//  TradeData.h
//  4727Project
//
//  Created by WangGuoan on 11/6/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//

#ifndef TradeData_h
#define TradeData_h

#include "AbstractData.h"
#include "loadRData.h"
#include <RInside.h>
#include <string>

/**
 class TradeData extends AbstractData class.
 */

//const std::unordered_map<std::string, int> colnames_to_index ({{"bid.price",0},{"bid.size",1},{"ask.price",2},{"ask.size",3},{"trade.price",4},{"volume",5}});


class TradeData: public AbstractData::AbstractData{
public:
    //static Rcpp::CharacterVector default_colnames;
    
    //TradeData();
    TradeData(Rcpp::Datetime t, const Rcpp::NumericVector& data, std::string _securityID, std::string _symbol);
};


#endif /* TradeData_h */
