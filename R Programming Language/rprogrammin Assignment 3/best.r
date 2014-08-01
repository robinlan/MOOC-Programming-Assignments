best <- function(state, outcomes) {
## Read outcome data
## Check that state and outcome are valid
## Return hospital name in that state with lowest 30-day death
## rate

	outcome <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
	if(outcomes=="heart attack"){n<-11}
	else if(outcomes=="heart failure"){n<-17}
	else if(outcomes=="pneumonia"){n<-23}
	else{
	    stop("invalid outcome")
	}
	outcome[, n] <- as.numeric(outcome[, n])
	s<-split(outcome,outcome$State)
	la<-lapply(s,function(x) min(x[,n],na.rm=TRUE))
	n2<-la[[state]]  ##state's min
	if(is.null(n2)){stop("invalid state")}
	nmin<-which(outcome[n]==n2)  ##locations of minimun
	nmin_l<-length(nmin)
	nstate<-which(outcome$State==state)  ##range of state
	nstate_l<-length(nstate)
	nstate_max<-nstate[nstate_l]
	nstate_min<-nstate[1]
	locat<-NULL  ##available locations
	
	for(i in 1:nmin_l){
	    j<-1
	    if(nmin[i]<=nstate_max && nmin[i]>=nstate_min){locat[j]<-nmin[i]}
		j<-j+1
	}
	locat_l<-length(locat)
	locat_char<-NULL
	if(locat_l==1)result<-outcome[locat,"Hospital.Name"]
	else{
	    for(i in 1:locat_l){
		    locat_char[i]<-outcome[locat[i],"Hospital.Name"]
		}
		locat_order<-order(locat_char)
		result<-locat_char[which(locat_order==1)]
	}
    result

}