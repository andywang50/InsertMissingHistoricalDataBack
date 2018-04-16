//
//  TestCases.cpp
//  4727Project_MissingData
//
//  Created by Ellen Sun, WangGuoan on 1/12/18.
//  Copyright © 2018 Ellen Sun, Guoan Wang. All rights reserved.
//

#include "TestCases.h"

/**
 Test whether ElasticSearch works.
 */
void testES(){
    // Instanciate elasticsearch client.
    ElasticSearch es("localhost:9200");
    
    // Index one document.
    Json::Object jData;
    jData.addMemberByKey("user", "kimchy");
    jData.addMemberByKey("post_date", "2009-11-15T14:12:12");
    jData.addMemberByKey("message", "trying out Elasticsearch");
    if(!es.index("twitter", "tweet", "1", jData))
        std::cerr << "Index failed." << std::endl;
    
    // Get document.
    Json::Object jResult;
    if(!es.getDocument("twitter", "tweet", "1", jResult))
        std::cerr << "Failed to get document." << std::endl;
    
    if(jResult["_source"].getObject() != jData)
        std::cerr << "Oups, something did not work." << std::endl;
    
    std::cout << "Great we indexed our first document: " << jResult.pretty() << std::endl;
    
    // Update document
    Json::Object jUpdateData;
    jUpdateData.addMemberByKey("user", "cpp-elasticsearch");
    if(!es.update("twitter", "tweet", "1", jUpdateData))
        std::cerr << "Failed to update document." << std::endl;
    
    // Search document.
    Json::Object jSearchResult;
    long resultSize = es.search("twitter", "tweet", "{\"query\":{\"match_all\":{}}}", jSearchResult);
    std::cout << "We found " << resultSize << " result(s):\n" << jSearchResult.pretty() << std::endl;
    
    // Delete document.
    if(!es.deleteDocument("twitter", "tweet", "1"))
        std::cerr << "Failed to delete document." << std::endl;
    
    std::cout << "First test is over. Good Bye." << std::endl;
    
}

/**
 Test whether the TradeData class works.
 */
void testTradeData(Rcpp::NumericMatrix& Data,Rcpp::DatetimeVector& index){
    
    std::unordered_map<double, TradeData> m;
    int count = 0;
    for(int i = 0; i < Data.nrow(); ++i){
        if(std::isnan(Data.row(i)[4]) == false){ //4th column is "Trade.Price"
            // Constructor of TradeData
            TradeData TD(index[i],Data.row(i),"ARandomSecurityID","ARandomSymbol"); //CLZ8_index is a Rcpp::vector of trading times; CLZ8_Data is the Rcpp::matrix.
            std::pair<long,TradeData> elementforHash (TD.get_transactTime(),TD);
            m.insert(elementforHash);
            ++count;
        }
        
    }
    std::cout << "count:" << count << std::endl;
    std::cout << "size of hashtable:" << m.size() << std::endl;
    
    std::cout << "5 random sample from the hashtable: " << std::endl;
    
    count = 0;
    for ( auto it = m.begin(); it != m.end() && count < 5; ++it ){
        std::cout << " " << it->first << ":" << it->second << std::endl;
        ++count;
    }
    
}

/**
 Test whether the RHashTable class works. build a RHashTable object, print out value for a specific key
 */
void testRHashTable(Rcpp::NumericMatrix& Data,Rcpp::DatetimeVector& index, std::string _index, std::string _type){
    RHashTable testRHT("tradedata"+_index,_type);
    testRHT.toHashtable(index, Data,_type, _type);
    // std::cout<< testRHT.get_hashtable().at(1508964798) << std::endl;
    for (auto& x: testRHT.get_hashtable()) {
        std::cout << x.first << ": " << x.second << std::endl;
    }
}

/**
 Test the loadRData cpp.
 */
void testloadRData(Rcpp::NumericMatrix data){
    std::cout << "the data has " << data.ncol() <<" columns, and "<< data.nrow() << " rows.\n";
    
    Rcpp::NumericVector column = data.column(1);
    std::cout << "The first element in 2nd column is:" << column[0] << std::endl;
    
    //colnames
    Rcpp::CharacterVector ch = Rcpp::colnames(data);
    std::cout << "The column names are " << ch << std::endl;
    
    //times
    Rcpp::DatetimeVector time(Rcpp::NumericVector(data.attr("index")));
    std::cout << "The first 10 indexes are (in local time):" << std::endl;
    for (int i = 0; i < 10; ++i){
        Rcpp::Datetime t = time[i];
        //std::cout << t.getFractionalTimestamp() << "\n";
        //std::cout << t.getYear() << "-" << t.getMonth() << "-" << t.getDay() << " " << t.getHours() << ":" << t.getMinutes() << ":" << t.getSeconds() << "-----" << format_time_GMT(t).str() <<"\n";
        std::cout << format_time_local(t).str() <<"\n";
        
    }
    
}
