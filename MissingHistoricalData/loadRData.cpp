//
//  loadRData.cpp
//  4727Project
//
//  Created by WangGuoan on 10/28/17.
//  Copyright © 2017 Guoan Wang. All rights reserved.
//
#include "loadRData.h"


/**
 Returns the timezone offset (GMT vs EST, automatically adjusting for daylight saving).
 */
long tz_offset_hour(time_t t) {
    struct tm local = *localtime(&t);
    struct tm utc = *gmtime(&t);
    long diff = ((local.tm_hour - utc.tm_hour) * 60 + (local.tm_min - utc.tm_min))
    * 60L + (local.tm_sec - utc.tm_sec);
    int delta_day = local.tm_mday - utc.tm_mday;
    if ((delta_day == 1) || (delta_day < -1)) {
        diff += 24L * 60 * 60;
    } else if ((delta_day == -1) || (delta_day > 1)) {
        diff -= 24L * 60 * 60;
    }
    return diff/(60*60);
}

/**
 Convert a Rcpp::Datetime into time_t.
 */
time_t RcppTime_to_timeT(Rcpp::Datetime& t){
    long temp = static_cast<long>(t.getFractionalTimestamp());
    return (time_t) temp;
}

/**
 No longer in use.
 Format a Rcpp::Datetime object into something like "2017-08-16T21:39:29.629-04:00", assuming the input t is GMT time.
 */
std::stringstream format_time_GMT(Rcpp::Datetime& t){
    const time_t timer = RcppTime_to_timeT(t);
    struct tm* gmt_time = gmtime(&timer);
    std::stringstream res;
    long relative_to_GMT =tz_offset_hour(timer);
    res << std::to_string(gmt_time->tm_year+1900) << "-" << std::to_string(gmt_time->tm_mon+1) << "-"
    << std::to_string(gmt_time->tm_mday) << "T";
    
    res << std::setw(2) << std::setfill('0') << std::to_string(gmt_time->tm_hour) << ":"
    << std::setw(2) << std::to_string(gmt_time->tm_min) << ":" << std::setw(2) << std::to_string(gmt_time->tm_sec) << "." << std::setw(3) << std::to_string(t.getMicroSeconds()/1000);
    
    res << std::string(relative_to_GMT<0?1:0,'-') << std::string(std::abs(relative_to_GMT)<10?1:0,'0') << std::to_string(std::abs(relative_to_GMT)) << ":00";
    
    return res;
}

/**
 In use.
 Format a Rcpp::Datetime object into something like "2017-08-16T21:39:29.629-04:00", assuming the object t is in local time.
 */
std::stringstream format_time_local(Rcpp::Datetime& t){
    const time_t timer = RcppTime_to_timeT(t);
    struct tm* local_time = localtime(&timer);
    std::stringstream res;
    long relative_to_GMT =tz_offset_hour(timer);
    res << std::to_string(local_time->tm_year+1900) << "-" << std::to_string(local_time->tm_mon+1) << "-"
    << std::to_string(local_time->tm_mday) << "T";
    
    res << std::setw(2) << std::setfill('0') << std::to_string(local_time->tm_hour) << ":"
    << std::setw(2) << std::to_string(local_time->tm_min) << ":" << std::setw(2) << std::to_string(local_time->tm_sec) << "." << std::setw(3) << std::to_string(t.getMicroSeconds()/1000);
    
    res << std::string(relative_to_GMT<0?1:0,'-') << std::string(std::abs(relative_to_GMT)<10?1:0,'0') << std::to_string(std::abs(relative_to_GMT)) << ":00";
    
    return res;
}

/**
 Given a directory path, read all the RData files one by one. Save the Rcpp::NumericMatrices into a vector, which is returned at the end. Also, save the RData file names into the "files" vector (passing by reference).
 */
std::vector<Rcpp::NumericMatrix> loadRData(std::string path, RInside& R, std::vector<std::string>& files){
    std::vector<Rcpp::NumericMatrix>  res;
    for (std::string file:files){
        size_t lastdot = file.find_last_of(".");
        size_t second_last_dot = file.find_last_of(".",lastdot-1);
        std::string objectname = file.substr(second_last_dot+1,lastdot-second_last_dot-1);
        //std::cout<<"load(\"" + path + "" + file + "\")"<<"\n";
        R.parseEval("load(\"" + path + "" + file + "\")");
        res.push_back(R[objectname]);
        
    }
    return res;
}

/**
 Get the 0th column (index column, which is date and time)
 */
Rcpp::DatetimeVector get_index(Rcpp::NumericMatrix data){
    Rcpp::DatetimeVector time(Rcpp::NumericVector(data.attr("index")));
    return time;
}

/**
 Get the column names. (Bid.Price, Bid.Size, Ask.Price, Ask.Size, Trade.Price, Volume).
 */
Rcpp::CharacterVector get_colnames(Rcpp::NumericMatrix data){
    Rcpp::CharacterVector ch = Rcpp::colnames(data);
    return ch;
}

/**
 Get all RData files' names in the given directory
 */
void get_all_files_in_dir(std::string path, std::vector<std::string>& files){
    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::size_t found = static_cast<std::string>(dp->d_name).find("RData");
        if (found!=std::string::npos && static_cast<std::string>(dp->d_name).length()>6)
            files.push_back(dp->d_name);
    }
    closedir(dirp);
    //for (auto& f:files) std::cout<<f <<"\n";
}


