require(aga8)

gas <- list()

gas[[1]] <- list(xCO2=0.006, xH2=0, d=0.581, Hs=40.66, xCO=0)
gas[[2]] <- list(xCO2=0.005, xH2=0, d=0.609, Hs=40.62, xCO=0)
gas[[3]] <- list(xCO2=0.015, xH2=0, d=0.650, Hs=43.53, xCO=0)
gas[[4]] <- list(xCO2=0.016, xH2=0.095, d = 0.599, Hs=34.16, xCO=0.0964*0.095)
gas[[5]] <- list(xCO2=0.076, xH2=0, d=0.686, Hs=36.64, xCO=0)
gas[[6]] <- list(xCO2=0.011, xH2=0, d=0.644, Hs=36.58, xCO=0)


n <- length(gas)

press <- c(rep(60, 5), rep(120, 5))
temp <- rep(c(-3.15, 6.85, 16.85, 36.85, 56.85), 2)


Z <- matrix(0, length(temp), n)
colnames(Z) <- c("Gas1", "Gas2", "Gas3", "Gas4", "Gas5", "Gas6")
for (i in 1:n){
  setgrossA(gas[[i]])
  Z[,i] <- round(Zgross(temp, press), 5)
}

Z <- cbind(press, temp, Z)


