##https://class.coursera.org/compinvesting1-003/lecture - Computational Investment Part 1 W1 Lecture024 Excel Demo in R version

pd_table<-read.csv("table.csv")
pd_table<-pd_table[order(pd_table$Date),]
pd_table1<-pd_table[,c(1,7)]
total_ret<-pd_table1[length(pd_table$Date),2]/pd_table1[1,2]
daily_ret<-0
for(i in 2:length(pd_table$Date))daily_ret_in_percentage<-c(daily_ret,pd_table1[i,2]-pd_table1[i-1,2])
pd_table1<-cbind(pd_table1,daily_ret_in_percentage)
pd_table1$daily_ret_in_percentage<-pd_table1$daily_ret_in_percentage/pd_table1$Adj.Close
avr_daily_ret<-mean(pd_table1$daily_ret_in_percentage)
sde_daily_ret<-sd(pd_table1$daily_ret_in_percentage)
sharpe_ratio<-sqrt(250)*avr_daily_ret/sde_daily_ret
pd_table2<-list(average_daily_return_in_percentage=avr_daily_ret,sdeviation_daily_return_in_percentage=sde_daily_ret,the_sharpe_ratio=sharpe_ratio)
pd_table2<-as.data.frame(pd_table2)
