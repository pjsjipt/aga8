# Programa exemplo que usa a aga8.
# Uma pequena modificacao do arquivo - teste do subversion
# Novo teste do subversion
require(aga8)
x1 <- c(0.006, 0.003, 0, 0, 0.965, 0.018, 0.0045, 0.001, 0.001, 0.0005,
        0.0003, 0.0007, 0, 0)


x2 <- c(0.005, 0.031, 0, 0, 0.907, 0.045, 0.0084, 0.001, 0.0015, 0.0003,
        0.0004, 0.0004, 0, 0)

x3 <- c(0.015, 0.01, 0, 0, 0.859, 0.085, 0.023, 0.0035, 0.0035, 0.0005,
        0.0005, 0, 0, 0)

x4 <- c(0.016, 0.1, 0.095, 0.01, 0.735, 0.033, 0.0074, 0.0012, 0.0012, 0.0004, 0.0004, 0.0002, 0.0001, 0.0001)

x5 <- c(0.076, 0.057, 0, 0, 0.812, 0.043, 0.009, 0.0015, 0.0015, 0,
        0, 0, 0, 0)

x6 <- c(0.011, 0.117, 0, 0, 0.826, 0.035, 0.0075, 0.0012, 0.0012, 0.0004, 0.0004, 0.0002, 0.0001, 0)


aga2aga <- function(x){
  y <- rep(0, 21)

  y[1] <- x[1]
  y[2] <- x[2]
  y[3] <- x[3]
  y[4] <- x[4]
  y[5] <- x[5]
  y[11] <- x[6]
  y[12] <- x[7]
  y[13] <- x[8]
  y[14] <- x[9]
  y[15] <- x[10]
  y[16] <- x[11]
  y[17] <- x[12]

  return(y)
}

iso2aga <- function(x){
  y <- rep(0, 21)

  y[1] <- x[5]
  y[2] <- x[2]
  y[3] <- x[1]
  y[4] <- x[6]
  y[5] <- x[7]
  y[8] <- x[3]
  y[9] <- x[4]
  y[11] <- x[8]
  y[12] <- x[9]
  y[13] <- x[10]
  y[14] <- x[11]
  y[15] <- x[12]
  y[16] <- x[13]
  y[17] <- x[14]

  return(y)
}
iso <- data.frame(x1=iso2aga(x1), x2=iso2aga(x2), x3=iso2aga(x3),
                  x4=iso2aga(x4), x5=iso2aga(x5), x6=iso2aga(x6))



gross <- list()

temp <- rep(c(-3.15, 6.85, 16.85, 36.85, 56.85), 2)
press <- c(rep(60, 5), rep(120, 5))

N <- length(temp)
zz <- rep(0, N)
Z1 <- data.frame(x1=double(N), x2=double(N), x3=double(N), x4=double(N),
                 x5=double(N), x6=double(N),t=double(N), p=double(N))

Z1$t <- temp
Z1$p <- press

Z2 <- Z1
erro <- Z1

Nc <- 6
maxerro <- double(6)



for(i in 1:Nc){

  setdetail(iso[[i]])
  gross[[i]] <- detail2grossA()
  setgrossA(gross[[i]])
  Z1[[i]] <- round(Zdetail(temp, press), 5)
  Z2[[i]] <- round(Zgross(temp, press), 5)
  erro[[i]] <- round((Z2[[i]] - Z1[[i]])/Z1[[i]] * 100, 1)
  maxerro[i] <- round(max(abs(erro[[i]])), 1)
}



gulf <- c(96.5222, 0.2595, 0.5956, 1.8186, .4596, .0977, .1007,
          .0473, .0324, .0664, 0, 0) / 100

amarillo <- c(90.6724, 3.1284, .4676, 4.5279, .8280, .1037, .1563,
              .0321, .0443, .0393, 0, 0)/100

ekofisk=c(85.9063, 1.0068, 1.4954, 8.4919, 2.3015, 0.3486, .3506,
  .0509, .0480, 0, 0, 0)/100

n2 <- c(81.441, 13.4650, .9850, 3.3, .6050, .1, .1, 0, 0, 0, 0, 0)/100

co2 <- c(81.211, 5.702, 7.585, 4.303, .8950, .151,.152, 0, 0, 0, 0, 0)/100





aga <- data.frame(gulf=aga2aga(gulf), amarillo=aga2aga(amarillo), ekofisk=aga2aga(ekofisk),
                  n2=aga2aga(n2), co2=aga2aga(co2))



temp <- c(rep(32,8), rep(50,8), rep(100,8), rep(130,8))
temp <- (temp - 32)*5/9
press <- rep(c(14.73, 100, 200, 400, 600, 800, 1000, 1200), 4)
press <- press/14.696 * 1.01325

N <- length(temp)
zz <- rep(0, N)
Z1aga <- data.frame(gulf=double(N), amarillo=double(N), ekofisk=double(N), n2=double(N),
                 co2=double(N), t=double(N), p=double(N))
grossaga <- list()

Z1aga$t <- temp
Z1aga$p <- press

Z2aga <- Z1aga
erroaga <- Z1aga
Rho <- data.frame(gulf=double(N), amarillo=double(N), ekofisk=double(N), n2=double(N), co2=double(N), t=double(N), p=double(N))

Nc <- 5
maxerroaga <- double(Nc)



for(i in 1:Nc){

  setdetail(aga[[i]])
  grossaga[[i]] <- detail2grossA()
  setgrossA(grossaga[[i]])
  Z1aga[[i]] <- round(Zdetail(temp, press), 6)
  Z2aga[[i]] <- round(Zgross(temp, press), 6)
  erroaga[[i]] <- round((Z2aga[[i]] - Z1aga[[i]])/Z1aga[[i]] * 100, 1)
  maxerroaga[i] <- max(abs(erroaga[[i]]))
  Rho[[i]] <- round(Rhodetail(temp, press), 2)
  
}



