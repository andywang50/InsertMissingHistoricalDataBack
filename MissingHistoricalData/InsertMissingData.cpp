//
//  InsertMissingData.cpp
//  4727Project
//
//  Created by Ellen Sun on 11/6/17.
//  Copyright © 2017 Ellen Sun. All rights reserved.
//

#include "InsertMissingData.h" // comments of these functions are in the header file.

/**
 Upload all data in the RHashTable onto ElasticSearch
 */
void UploadTestData(RHashTable rhash){
    // get index and type from RHashTable
    std::string index = rhash.get_index();
    std::string type = rhash.get_type();
    
    ElasticSearch es ("localhost:9200");
    
    //delete content in the index to avoid repetitive upload
    //es.deleteIndex(index);
    //std::cout << "All deleted\n";
    
    // iterate over RHashTable
    for(auto& x:rhash.get_hashtable()){
        es.index(index, type, x.second);
    }
    std::cout <<"All uploaded, index: " << index << ", type: " << type <<std::endl;
}

/**
 Upload part of the data and miss arbitrary data fields.
 The "missing" scheme is as follows:
 1. with probabiltiy 1%, start missing.
 2. Generate a random number n from 6 to 10 inclusive, do not upload the next n tradedata.
 */
void TestCaseMissData(RHashTable rhash){
    const double prob_start_missing = 0.01;
    const int min_consecutive_miss = 6;
    const int max_consecutive_miss = 10;
    // get index and type from RHashTable
    std::string index = rhash.get_index();
    std::string type = rhash.get_type();
    
    ElasticSearch es ("localhost:9200");
    
    //delete content in the same index from ES to avoid repetitive upload
    //es.deleteIndex(index);
    //std::cout << "All deleted\n";
    
    int i = 0;
    srand (time(NULL));
    int consecutive_miss = 0;
    for(auto& x:rhash.get_hashtable()){
        
        if (consecutive_miss > 0){
            consecutive_miss--;
            
        }
        else{
            es.index(index, type, x.second);
            int temp = rand()%100 + 1;
            if (1.0*temp/100 <= prob_start_missing) consecutive_miss = rand()%(max_consecutive_miss-min_consecutive_miss+1)+min_consecutive_miss;
        }
    }
    
    std::cout <<"Test Case uploaded, index: " << index << ", type: " << type <<std::endl;
    
}

/**
 Upload all data in the RHashTable onto ElasticSearch but intentionally modify a few data fields.
 */
void TestCaseFalseData(RHashTable rhash){
    
    // get index and type from RHashTable
    std::string index = rhash.get_index();
    std::string type = rhash.get_type();
    
    // Upload all test data to ElasticSearch
    UploadTestData(rhash);
    ElasticSearch es ("localhost:9200");
    
    // modify random data fields for 2017.12.06.CLF8 1512519643308
    if (index == "tradedata201712" && type == "CLF8"){
        Json::Object modifytest1;
        std::string query = "{\"query\":{\"match\":{\"transactTime\": 1512519643308}}}";
        es.search(index, type, query, modifytest1);
        //std::cout<< modifytest1.str()<<std::endl;
        Json::Array temparray = modifytest1.getValue("hits").getObject().getValue("hits").getArray();
        Json::Object tempobject = temparray.first().getObject();
        std::string id = tempobject.getValue("_id");
        std::string wrongprice = std::to_string(123);
        es.update(index, type, id, "price", wrongprice);
    }
    
    // modify random data fields for 2017.12.06.CLM8 1512520739848
    if (index == "tradedata201712" && type == "CLM8"){
        Json::Object modifytest2;
        std::string query = "{\"query\":{\"match\":{\"transactTime\": 1512520739848}}}";
        es.search(index, type, query, modifytest2);
        //std::cout<< modifytest2.str()<<std::endl;
        Json::Array temparray = modifytest2.getValue("hits").getObject().getValue("hits").getArray();
        Json::Object tempobject = temparray.first().getObject();
        std::string id = tempobject.getValue("_id");
        std::string wrongprice = std::to_string(456);
        es.update(index, type, id, "price", wrongprice);
    }
    
}

/**
 Given a RHashtable, check whether ElasticSearch is missing any. If so, insert it back.
 */
void InsertMissingData(RHashTable rhash){
    // get index and type from RHashTable
    std::string index = rhash.get_index();
    std::string type = rhash.get_type();
    // initiate ES
    ElasticSearch esinsert ("localhost:9200");
    
    // iterate over RHashTable. search - if exist, then check value matches etc. If not, insert.
    for(auto& x:rhash.get_hashtable()){
        // find the data corresponding to a timestamp, store in Json object "result"
        Json::Object result;
        std::string query = "{\"query\":{\"match\":{\"transactTime\":"+std::to_string(x.first)+"}}}";
        try{
            // get corresponding price of the timestamp in ES
            esinsert.search(index, type, query, result);
            Json::Array temparray = result.getValue("hits").getObject().getValue("hits").getArray();
            //Json::Array temparray2 = result.getValue("hits").getObject().getValue("hits").getArray();
            
            // if returns empty, the timestamp doesn't exist. Insert.
            if (temparray.empty()){
                //if (temparray.empty() && temparray2.empty()){
                //std::cout << result << std::endl;
                try{
                    esinsert.index(index, type, x.second);
                    std::cout<<"Yay. Inserted new data at timestamp："<< x.first <<std::endl;
                } catch(Exception &msg){
                    std::cout << "The index induces error." << "The timestamp is: "<<x.first<<std::endl;
                }
            }
            
            // if timestamp exists, compare with rdata. Update if necessary.
            else{
                Json::Object tempobject = temparray.first().getObject();
                double estradeprice = tempobject.getValue("_source").getObject().getValue("price");
                double rtradeprice = x.second.getValue("price");
                // compare es data and rdata
                if (estradeprice == rtradeprice){
                    continue;
                }
                else{
                    std::string id= tempobject.getValue("_id");
                    std::stringstream ss;
                    ss << std::setprecision(2) << std::fixed << rtradeprice;
                    std::string srtradeprice =ss.str();
                    try{
                        esinsert.update(index, type, id, "price", srtradeprice);
                        std::cout<<"Yay. Updated the trade price with timestamp " << x.first <<std::endl;
                    } catch (Exception &msg){
                        std::cout<<"The update failed. "<< "The timestamp is: "<<x.first<<std::endl;
                    }
                }
            }
            
        } catch (Exception &msg) {
            if(strcmp(msg.what(),"Search failed.")==0 ){
                std::cout<< "Search failed. Didn't go through. "<< "The timestamp is: "<<x.first<< std::endl;
            }
            else if(strcmp(msg.what(),"Search timed out.")==0){
                std::cout<< "Search timed out. " << "The timestamp is: "<<x.first<< std::endl;
            }
            else{
                std::cout<< "Something weird happened. Search not successful. "<< "The timestamp is: "<<x.first<<std::endl;
                
            }
        }
    }
}

