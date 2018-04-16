Readme -- Missing Historical Data and Inserting it back.

IMPORTANT: one needs to link the RInside package in order to read the RData file. 
		
Main.cpp:
	main function and test functions.
	Main: std::string path is the path of the directory containing all RData files.
		The filename of RData files should be: yyyy.mm.dd.symbol.RData. For example: 2017.12.10.CLF8.RData

ElasticSearch cpp & header， http cpp & header
	The ElasticSearch API provided by Kai.  Works for ElasticSearch 2.4.6, doesn't work for version 5 or newer.

Json cpp & header
	Json object class provided by Kai. Needed by ElasticSearch API and TradeData class (as well as TickData class and Abstract Data class).
	
loadRData cpp & header
	RData file reader. Extract RData files into Rcpp::NumericMatrix and Rcpp::DatetimeVector.
	
AbstractData cpp & header
	Inherits from the Json Object class. The base class of TickData and TradeData.
	
TradeData cpp & header
	Inherits from AbstractData class. 

TickData cpp & header
	Not in use. Now we only care about tradedata. If in the future we also need to check tickdata, this could be done quite easily.
	
InsertMissingData cpp & header
	Three functions:
	1. Upload all data in the RHashTable onto ElasticSearch
	2. Create Test Case: Upload part of the data (as if we miss some data).
	3. Given a RHashtable, check whether ElasticSearch is missing any. If so, insert it back.

RHashTable cpp & header
	A class containing an unordered map. Timestamp as key, TradeData Object as value.

TestCases cpp & header
	Contains all test cases.

RetrieveRData cpp & header
	Contains functions that allow user to input the time range and product names. In “getUserProduct” product, the user has the option to read product names from the txt file. The txt file should have the same path as the RData files that need to be read. 

For detailed explanations, look at the comments in the code. 