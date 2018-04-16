#include "functions.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <math.h>  /* log & exp */
#include <stdio.h>
#include <sys/time.h>
#include <cstdlib>
#include <RInside.h>
#include <fstream>


using namespace std;

// const double PI = 4*atan(1.0);
// Pricing Black-Merton-Scholes via Simulation
//

double Normal_Marsaglia_Polar(long& idum){
    double v1,v2,r;
    do
    {
        v1 = 2*ran2_mod(&idum) - 1;
        v2 = 2*ran2_mod(&idum) - 1;
        r = v1*v1 + v2*v2;
    }
    while (r > 1.0);
    
    r = sqrt(-2*log(r)/r);
    //z2[i] = r*v1;
    //z2[i+nN/2] = r*v2;
    return r*v1;
}
double Normal_Box_Muller(long& idum){
    double u1 = ran2_mod(&idum);
    double u2 = ran2_mod(&idum);
    
    return sqrt(-2*log(u1))*cos(2*PI*u2);
}

int main(int argc, char*argv[])
{
    RInside R(argc, argv);		// create an embedded R instance
    R.parseEval("library(xts)");
    R.parseEval("colnames = c(\"time\",\"Bid.Price\",\"Bid.Size\",\"Ask.Price\",\"Ask.Size\",\"Trade.Price\",\"Volume\")");
    vector<string> product_names = {"CLF8","CLM8","CLX8"};
    vector<string> dates = {"2017-12-06","2017-12-07","2017-12-08"};
    std::ofstream file;
    long idum = atol(argv[1]);
    for (string date:dates){
        for (string product:product_names){
            cout << date << " " <<product << endl;
            string filename = "";
            for (int i = 0; i < date.length();++i){
                if(date[i] != '-') filename += date[i];
                else filename += '.';
            }
            string filename_noext = filename + "." + product;
            filename = filename + "." + product + ".txt";
            file.open(filename);

            double trade_occuring_probability = 1.0/pow(10,5);

            double   s0 = 100.0;
            double   sigma = 1.0/252;

            double   maturity = 1.0;

            double   rfr=0.010/252;
            double   div=0.015/252;

            int nSimulationPaths = 1;
            int nTimeSteps = 24*3600*1000;

            double dt = maturity/nTimeSteps;

            double drift = (rfr-div-sigma*sigma/2.0)*dt;

            int iI, jJ;
            double z1;
            double fd1, feed1;

            for (jJ = 0; jJ<nSimulationPaths; jJ++){
            
                fd1 = log(s0);
            
                for (iI = 0; iI<nTimeSteps; iI++){
                
                    z1 = Normal_Marsaglia_Polar(idum);
                    feed1 = sigma*sqrt(dt)*z1;
                    fd1 = fd1+feed1+drift;
                    double temp = ran2_mod(&idum);
                    if(temp < trade_occuring_probability){
                        int hour = iI/3600/1000;
                        int minute = (iI % (3600*1000))/60/1000;
                        int sec = (iI % (60 * 1000))/1000;
                        int millisec = iI % 1000;
                        double stock_price = exp(fd1);
                        //cout << hour << ":" << minute << ":" << sec << ":" <<millisec << " " << floor(stock_price*100+0.5)/100.0 << endl;
                        double display_price = floor(stock_price*100+0.5)/100.0;
                        file << date << " ";
                    
                        file << std::setw(2) << std::setfill('0') << hour << ":"
                        << std::setw(2) << minute << ":" << std::setw(2) << sec << "." << std::setw(3) << millisec;
                        file << "," << std::fixed << std::setprecision(2) << display_price;
                        file << "," << std::fixed << std::setprecision(0) << floor(ran2_mod(&idum)*3)+1; //bid
                        file << "," << std::fixed << std::setprecision(2) << display_price;
                        file << "," << std::fixed << std::setprecision(0) << floor(ran2_mod(&idum)*3)+1;//ask
                        file << "," << std::fixed << std::setprecision(2) << display_price;
                        file << "," << std::fixed << std::setprecision(0) << floor(ran2_mod(&idum)*3)+1 << endl;

                    }
                }
            
            
            }
            file.close();
            //R.parseEval("temp <- read.table(\"/Users/andy/Documents/XCode/4727/SimulateRData/SimulateRData/"+ filename + "\",sep=\",\",col.names = colnames)");
            R.parseEval("temp <- read.table(\""+ filename + "\",sep=\",\",col.names = colnames)");
            R.parseEval("temptime<-strptime(temp[,1],\"%Y-%m-%d %H:%M:%OS\",\"GMT\")");
            R.parseEval(product+"<-xts(temp[c(2:7)],temptime)");
            //R.parseEval("save(" + product + ",file=\"/Users/andy/Documents/XCode/4727/SimulateRData/SimulateRData/" + filename_noext + ".RData\")");
            R.parseEval("save(" + product + ",file=\"" + filename_noext + ".RData\")");

            R.parseEval("save.image()");
        }
    }
    cout << "Done!" << endl;
    
}
