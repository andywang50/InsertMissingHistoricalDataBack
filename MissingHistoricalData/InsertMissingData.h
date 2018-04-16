//
//  InsertMissingData.h
//  4727Project
//
//  Created by Ellen Sun on 11/6/17.
//  Copyright © 2017 Ellen Sun. All rights reserved.
//

#ifndef InsertMissingData_h
#define InsertMissingData_h

#include "elasticsearch.h"
#include "TradeData.h"
#include "RHashTable.h"
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/** create a test case. Namely, start with an empty ES index, insert the raw RData into ES but "randomly" missing some of the data.
 @ RData is the raw RData, in the form of Rcpp::NumericMatrix type.
 @ Return a set of double, containing the timestamps of the "missed" data.
 */
void TestCaseMissData(RHashTable rhash);

void TestCaseFalseData(RHashTable rhash);

// create sample case, upload all CLZ8 to ES
void UploadTestData(RHashTable rhash);

// insert missing data, inserted_data is a set containing the timestamps of the missing data we inserted back.
void InsertMissingData(RHashTable rhash);



#endif /* InsertMissingData_h */


