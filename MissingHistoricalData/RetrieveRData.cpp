//
//  RetrieveRData.cpp
//  4727Project_MissingData
//
//  Created by Ellen Sun on 1/12/18.
//  Copyright © 2018 Ellen Sun. All rights reserved.
//

#include "RetrieveRData.h"

// get time range for RData/ES matching from user
void getUserTime(std::vector<int> &timeRange){
    std::string mystr;
    std::cout << "Enter start year (yyyy): ";
    std::cin >>mystr;
    timeRange.push_back(stoi(mystr));
    std::cout << "Enter start month (mm): ";
    std::cin >>mystr;
    timeRange.push_back(stoi(mystr));
    std::cout << "Enter start date (dd): ";
    std::cin >>mystr;
    timeRange.push_back(stoi(mystr));
    std::cout << "Enter end year (yyyy): ";
    std::cin >>mystr;
    timeRange.push_back(stoi(mystr));
    std::cout << "Enter end month (mm): ";
    std::cin >>mystr;
    timeRange.push_back(stoi(mystr));
    std::cout << "Enter end date (dd): ";
    std::cin >>mystr;
    timeRange.push_back(stoi(mystr));
}

// get product NAME for RData/ES matching from user
void getUserProduct(std::vector<std::string> &productName, std::string path){
    int indicator;
    std::cout << "Do you want to enter product directly(0) or read from txt file(1)? The txt file should be in the same directory as the RData files that you want to read.";
    while (!(std::cin >> indicator) || (indicator!=0 && indicator != 1))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        
        std::cout << "Please input a proper number (0 or 1): " << std::endl;
    }
    //std::cin>>indicator;
    if (indicator == 0){
        int counter;
        while (true){
            std::cout << "Enter the number of product: ";
            std::cin >> counter;
            if (counter >0){
                break;
            }
            else{
                std::cout<<"Invalid number. Try again."<<std::endl;
            }
        }
        for (int i=0; i<counter; i++){
            std::string mystr;
            int temp;
            temp = i+1;
            std::cout<< "Name"+std::to_string(temp)+": ";
            std::cin >>mystr;
            productName.push_back(mystr);
        }
    }
    else{
        std::string productTemp;
        std::ifstream inFile;
        //inFile.open("/Volumes/ELLEN\ 1/Fall\ 2017/Programming\ for\ FE/4727Project_MissingData/RData/productName.txt");
        inFile.open(path+"productName.txt");
        if (!inFile) {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }
        while (inFile >> productTemp) {
            productName.push_back(productTemp);
        }
        inFile.close();
    }
    
}

// search for an element in a vector
bool searchVector (std::string target, std::vector<std::string> &source){
    if(std::find(source.begin(), source.end(), target) != source.end()) {
        return true;
    }
    else {
        return false;
    }
}


// assemble file names
std::string assemble (int year, int month, int date, std::string product){
    std::string year_str = std::to_string(year);
    std::string month_str;
    if (month>=10){
        month_str = std::to_string(month);
    }
    else{
        month_str = "0"+std::to_string(month);
    }
    std::string date_str;
    if (date>=10){
        date_str =std::to_string(date);
    }
    else{
        date_str = "0"+std::to_string(date);
    }
    
    std::string filename = year_str+"."+month_str+"."+date_str+"."+product+"."+"RData";
    
    return filename;
}

//get all file names according to user input, ignore all dates&product combination that doesn't exist in the directory
void createFileNames (std::vector<std::string> &files, std::vector<int> &timeRange,std::vector<std::string> &productName, std::vector<std::string> &allfiles){
    int startyear = timeRange.at(0);
    int startmonth = timeRange.at(1);
    int startdate = timeRange.at(2);
    int endyear = timeRange.at(3);
    int endmonth = timeRange.at(4);
    int enddate = timeRange.at(5);
    std::string filename;
    
    for (int year = startyear; year<=endyear; year++){
        if (year == startyear){
            // check if start year = end year
            int mon_endindex;
            if (startyear == endyear){
                mon_endindex = endmonth;
            }
            else{
                mon_endindex = 12;
            }
            // iterate over all months
            for (int month = startmonth; month <= mon_endindex; month++){
                if (month == startmonth){
                    // check if start month = end month
                    int date_endindex;
                    if (startmonth == endmonth){
                        date_endindex = enddate;
                    }
                    else{
                        date_endindex = 31;
                    }
                    // iterate over all dates
                    for (int date = startdate; date<=date_endindex; date++){
                        for (int i = 0; i<productName.size();i++){
                            std::string product = productName[i];
                            filename = assemble(year, month, date, product);
                            if (searchVector(filename, allfiles)){
                                files.push_back(filename);
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
                else if (month == endmonth){
                    for (int date = enddate; date>=31; date--){
                        for (int i = 0; i<productName.size();i++){
                            std::string product = productName[i];
                            filename = assemble(year, month, date, product);
                            if (searchVector(filename, allfiles)){
                                files.push_back(filename);
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
                else{
                    for (int date = 1; date<=31; date++){
                        for (int i = 0; i<productName.size();i++){
                            std::string product = productName[i];
                            filename = assemble(year, month, date, product);
                            if (searchVector(filename, allfiles)){
                                files.push_back(filename);
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
            }
        }
        else if (year == endyear){
            for (int month = endmonth; month >= 1; month--){
                if (month == endmonth){
                    for (int date = enddate; date>=1; date--){
                        for (int i = 0; i<productName.size();i++){
                            std::string product = productName[i];
                            filename = assemble(year, month, date, product);
                            if (searchVector(filename, allfiles)){
                                files.push_back(filename);
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
                else{
                    for (int date = 1; date<=31; date++){
                        for (int i = 0; i<productName.size();i++){
                            std::string product = productName[i];
                            filename = assemble(year, month, date, product);
                            if (searchVector(filename, allfiles)){
                                files.push_back(filename);
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
            }
        }
        else{
            for (int month = 1; month <=12; month++){
                for (int date = 1; date<=31; date++){
                    for (int i = 0; i<productName.size();i++){
                        std::string product = productName[i];
                        filename = assemble(year, month, date, product);
                        if (searchVector(filename, allfiles)){
                            files.push_back(filename);
                        }
                        else{
                            continue;
                        }
                    }
                }
            }
        }
    }
}

// Given a filepath, such as yyyy.mm.dd.symbol.RData, return vector: {yyyymm, symbol}
std::vector<std::string> indexAndType(std::string filepath){
    std::vector<std::string> result;
    std::string delimiter = ".";
    
    std::vector<std::string> temp_str_array;
    size_t pos = 0;
    while ((pos = filepath.find("."))!= std::string::npos){
        temp_str_array.push_back(filepath.substr(0,pos));
        filepath.erase(0,pos+delimiter.length());
    }
    
    if(temp_str_array.size() != 4){
        std::cout << temp_str_array.size() << std::endl;
        throw std::invalid_argument("Invalid fileName. There should be 4 dots in the filename, including extension");
    }
    
    std::string year = temp_str_array[0];
    std::string month = temp_str_array[1];
    std::string day = temp_str_array[2];
    std::string product_name = temp_str_array[3];
    
    result.push_back(year+month);
    result.push_back(product_name);
    return result;
}



