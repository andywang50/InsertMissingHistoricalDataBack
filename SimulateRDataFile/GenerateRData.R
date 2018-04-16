rm(list=ls(all=TRUE))
library(xts)

colnames = c("time","Bid.Price","Bid.Size","Ask.Price","Ask.Size","Trade.Price","Volume")

temp<-read.table("/Users/andy/Documents/XCode/4727/SimulateRData/SimulateRData/2017.12.06.CLF8.txt"
                 ,sep=",",col.names = colnames)
temptime<-strptime(temp[,1],"%Y-%m-%d %H:%M:%OS","GMT")
CLF8<-xts(temp[c(2:7)],temptime)
save(CLF8,file="/Users/andy/Documents/XCode/4727/SimulateRData/SimulateRData/CLF8.RData")
save.image()

index(CLF8)

load("/Users/andy/Documents/XCode/4727/4727Project/4727Project/RData/2017.12.06.CLX8.RData")
