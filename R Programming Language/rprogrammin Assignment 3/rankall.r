rankall <- function(outcomes, num = "best") {
## Read outcome data
## Check that state and outcome are valid
## For each state, find the hospital of the given rank
## Return a data frame with the hospital names and the
## (abbreviated) state name

    outcome <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
	if(outcomes=="heart attack"){n<-11}
	else if(outcomes=="heart failure"){n<-17}
	else if(outcomes=="pneumonia"){n<-23}
	else{
	    stop("invalid outcome")
	}
	outcome[, n] <- as.numeric(outcome[, n])
	s<-split(outcome,outcome$State)
	la<-lapply(s,function(x) sort(x[,n]) )
	state_names<-names(la)
	result<-NULL
	for(i in 1:54){
	    result[i]<-rankhospital(state_names[i],outcomes,num)
	}
	data.frame( hospital=result , state=state_names)

}