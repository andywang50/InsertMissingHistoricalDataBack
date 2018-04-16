//  main.cpp
//  tryRCpp
//
//  Created by Ellen Sun, WangGuoan on 10/10/17.
//  Copyright © 2017 Ellen Sun, Guoan Wang. All rights reserved.
//

#include "elasticsearch.h"
#include "loadRData.h"
#include "TradeData.h"
#include "TickData.h"
#include "InsertMissingData.h"
#include "TestCases.h"
#include "RetrieveRData.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <RInside.h>
#include <time.h>
#include <string>
#include <unordered_map>
#include <stdlib.h>     //for using the function sleep

/**
 Main Function, for a given directory that stores all RData:
 1. Accept product name and type as user input, find corresponding RData in the folder
 2. Read such RData files
 2. Save RData file into a hashtable (call RHashTable).
 3. Identify and correct discrepancies between ES data and RData
 (1) Upload Missing Data
 (2) Correct inaccurate data
 */

int main(int argc, const char * argv[]) {
    
    std::cout << "Welcome! Start Matching RData with ElasticSearch Data..." << std::endl;
    
    // Clear out ElasticSearch
    ElasticSearch ES ("localhost:9200");
    ES.deleteIndex("tradedata201712");
    
    // create an embedded R instance
    RInside R(argc, argv);
    
    // directory of the RData files
    std::string path =  "/Users/andy/Documents/XCode/4727/4727Project/4727Project/RData/";
    
    // store file names as a vector, all file names are in the form of yyyy.mm.dd.product.RData
    std::vector<std::string> files;  // vector of RData file names
    
    //get all RData file names in the directory
    std::vector<std::string> allfiles;
    get_all_files_in_dir(path,allfiles);
    
    // get time and product input from user
    std::vector<int> timeRange;
    getUserTime(timeRange);
    std::vector<std::string> productName;
    getUserProduct(productName,path);
    
    // get all file names according to user input
    createFileNames(files,timeRange,productName,allfiles);
    
    std::vector<Rcpp::NumericMatrix> AllData;
    
    // load RData files into a vector of Rcpp Matrices
    AllData = loadRData(path, R, files);
    
    for (int i =0; i < AllData.size(); ++i){
        std::vector<std::string> indexandtype = indexAndType(files[i]); //Get the date and symbol. E.g.  2017.12.10.CLF8 --> 201712, CLF8
        Rcpp::NumericMatrix Data = AllData[i];
        Rcpp::DatetimeVector index = get_index(Data); //Time index
        Rcpp::CharacterVector colnames = get_colnames(Data); // Column names
        
        /* perform simple tests on the functionality of several classes
         simpleTest(Data);
         testTradeData(Data,index);
         testRHashTable(Data,index,indexandtype[0],indexandtype[1]);
         */
        
        RHashTable rhash ("tradedata"+indexandtype[0],indexandtype[1]);
        rhash.toHashtable(index, Data,indexandtype[1], indexandtype[1]);
        std::cout << "Hashtable constructed with size " << rhash.get_hashtable().size() << std::endl;
        
        // Testing. Upload the data but missing some, or intentionally modify certain data fields. Cannot be used simultaneously with UploadTestData function.
        //UploadTestData(rhash);
        //TestCaseMissData(rhash);
        TestCaseFalseData(rhash);
        sleep(5);
        InsertMissingData(rhash); // Used with CreateTestCase. Find the missing data and insert it back.
        sleep(10);
        std::cout<<"\n"<<std::endl;
        
    }
    
    exit(0);
    
    
    return 0;
}




