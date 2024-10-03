### $Id: aga8.R,v 0.1 2003/07/24  pjabardo Exp $
###
### aga8 - Calculation of compression factors of natural gas
###
### You should have received a copy of the GNU General Public
### License along with this program; if not, write to the Free
### Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
### MA 02111-1307, USA

#'@useDynLib aga8
NULL


aga8.detail.composition <- c(1.0, rep(0.0, 20))
aga8.detail.MW <- 16.043
aga8.st.R <- 8314.41


aga8.st.press <- 1.01325  # Standard pressure MPa
aga8.st.temp <- 20.0 # Standard temperature oC

aga8.detail.heat <- c(890.63, 0,0, 1560.69, 2219.17, 0, 562.01, 285.83,
                      282.98, 0, 2868.20, 2877.4, 3528.83, 3535.77,
                      4194.95, 4853.43, 5511.8, 6171.15, 6829.77, 0, 0)



aga8.gross.compA <- list(xCO2=0.006, xH2=0.0, xCO=0.0, d=0.581, Hs=40.66)

 
#' @export
setdetail <- function(x){

	# x é a composição do gás natural
	ZB <- 0.0
	MW <- 0.0
	keep <- .C("R_setcomp", as.double(x), as.double(ZB), as.double(MW))
	#aga8.detail.MW <<- keep[[3]]
	#aga8.detail.composition <<- x
	return(list(Zb=keep[[2]], MW=keep[[3]]))
}


#' @export
Zdetail <- function(TT, PP){

	# Esta função calcula a compressibilidade do gãs natural
	nn <- c(length(TT), length(PP))
	N <- max(nn)
	Z <- array(0.0, N)
	keep <- .C("R_aga8_detail", as.double(TT), as.double(PP), as.double(Z), as.integer(nn))
	return(keep[[3]])
}


#' @export
MWdetail <- function()
	return(aga8.detail.MW)

#' @export
ZBdetail <- function()
	return( Zdetail(aga8.st.temp, aga8.st.press) )


#' @export
detailcomp <- function()
	return(aga8.detail.composition)

 
#' @export
Rhodetail <- function(TT, PP){
	# Calcular a compressibilidade
	Z <- Zdetail(TT, PP)
	return( PP*1e5 / (Z * aga8.st.R/aga8.detail.MW * (TT + 273.15)) )
}


#' @export
Hsdetail <- function(t=0, p=1.01325){
  mw <- MWdetail()
  
  H <- sum(aga8.detail.composition*aga8.detail.heat)
  rho <- Rhodetail(t, p)
  
  return(H*rho/mw)
}

#' @export
detail2grossA <-function() {
  # This function converts the composition into data that can be used by aga8 gross method A
  x <- aga8.detail.composition

  

  rhoair <- 1.292923
  rho <- Rhodetail(0, 1.01325)
  Hs <- Hsdetail()

  d <- rho/rhoair

  return(list(xCO2=x[3], xH2=x[8], xCO=x[9], d=d, Hs=Hs))
}



#' @export
setgrossA <- function(x){  #xCO2, xH2, d, Hs){
  .C("R_set_grossA", as.double(x$xCO2), as.double(x$xH2), as.double(x$d),
     as.double(x$Hs), as.double(x$xCO))
  
  aga8.gross.compA <- x

}
  
#' @export
setgrossB <- function(x){  #xCO2, xH2, d, Hs){
  .C("R_set_grossB", as.double(x$xCO2), as.double(x$xH2), as.double(x$d),
     as.double(x$xN2), as.double(x$xCO))
  
  aga8.gross.compB <- x

}

#' @export
grosscomp <- function(){
  # Função retorna a composição do gross

  #void R_conc_gross(double *N2, double *CO2, double *H2, double *CO){

  xCO2 <- double(1)
  xN2 <- double(1)
  xH2 <- double(1)
  xCO <- double(1)

  conc <- .C("R_conc_gross", as.double(xN2), as.double(xCO2), as.double(xH2), as.double(xCO))
  return(list(xN2=conc[[1]], xCO2=conc[[2]], xH2=conc[[3]], xCO=conc[[4]]))
  
}



#' @export
MWgross <- function(){
  mw <- 0.0

  keep <- .C("R_get_MW", as.double(mw))
  
  return(keep[[1]])
}



#' @export
Zgross <- function(TT, PP){

	# Esta função calcula a compressibilidade do gãs natural
	nn <- c(length(TT), length(PP))
	N <- max(nn)
	Z <- array(0.0, N)
	keep <- .C("R_aga8_gross", as.double(TT), as.double(PP), as.double(Z), as.integer(nn))
	return(keep[[3]])
}


#' @export
Rhogross <- function(TT, PP){

	# Esta função calcula a compressibilidade do gãs natural
	nn <- c(length(TT), length(PP))
	N <- max(nn)
	Rho <- array(0.0, N)
	keep <- .C("R_aga8_gross_rho", as.double(TT), as.double(PP), as.double(Rho), as.integer(nn))
	return(keep[[3]])
}


#' @export
Bgross <- function(TT){
  nn <- length(TT)
  B <- array(0.0, nn)

  keep <- .C("R_BVirial", as.double(TT), as.double(B), as.integer(nn))
  return(keep[[2]])
}

#' @export
Cgross <- function(TT){
  nn <- length(TT)
  C <- array(0.0, nn)

  keep <- .C("R_CVirial", as.double(TT), as.double(C), as.integer(nn))
  return(keep[[2]])
}

