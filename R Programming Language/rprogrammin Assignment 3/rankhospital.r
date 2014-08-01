rankhospital <- function(state, outcomes, num = "best") {
## Read outcome data
## Check that state and outcome are valid
## Return hospital name in that state with the given rank
## 30-day death rate

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
	n2<-la[[state]]  ##state's sort sequence
	n2_l<-length(n2)
	if(is.null(n2)){stop("invalid state")}
	if(num == "best"){num<-1}
	else if(num == "worst"){num<-n2_l}
	else if(num > n2_l){
	    result<-NA
		result
		return(result)
	}
	rank_value<-n2[num]
	for(i in 1:n2_l){
        if(n2[i]==rank_value){
		    min_locat<-i
			break
		}
    }
    seq<-num-min_locat + 1
	rank_value_locat<-which(outcome[n]==rank_value)  ##confirm the place of target rank
	rank_value_locat_l<-length(rank_value_locat)
	nstate<-which(outcome$State==state)  ##range of state
	nstate_l<-length(nstate)
	nstate_max<-nstate[nstate_l]
	nstate_min<-nstate[1]
	locat<-NULL  ##available locations
	j<-1
	for(i in 1:rank_value_locat_l){
	    if(rank_value_locat[i]<=nstate_max && rank_value_locat[i]>=nstate_min){
		    locat[j]<-rank_value_locat[i]
			j<-j+1
		}
	}
	locat_l<-length(locat)
	locat_char<-NULL
	for(i in 1:locat_l){
		locat_char[i]<-outcome[locat[i],"Hospital.Name"]
    }
	locat_order<-order(locat_char)
	result<-locat_char[which(locat_order==seq)]
	result

}