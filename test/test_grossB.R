


# Teste de aga8 gross método B
gulf <- list(d=0.581078*1.0002, xN2=0.002595, xCO2=0.5956e-2, xH2=0, xCO=0, Hs=38.6022*1.0539)
amarillo <- list(d=0.608657*1.0002, xN2=3.1284e-2, xCO2=0.4676e-2, Hs=38.5574*1.0539, xCO=0, xH2=0)
ekofisk <- list(d=0.649521*1.0002, xN2=1.0068e-2, xCO2=1.4954e-2, Hs=41.2871*1.0539, xCO=0, xH2=0)
highN2 <- list(d=0.644869*1.0002, xN2=13.4650e-2, xCO2=0.9850e-2, Hs=33.7797*1.0539, xCO=0, xH2=0)
highCO2 <- list(d=0.686002*1.0002, xN2=5.7021e-2, xCO2=7.5851e-2, Hs=34.7672*1.0539, xCO=0, xH2=0)


tempF <- c(rep(32,8), rep(50,8), rep(100,8), rep(130,8))
temp <- (tempF - 32)*5/9
pressPSI <- rep(c(14.73, 100, 200, 400, 600, 800, 1000, 1200), 4)
press <- pressPSI /14.5038



setgrossB(gulf)
Zgulf <- round(Zgross(temp, press), 6)

setgrossB(amarillo)
Zamarillo <- round(Zgross(temp, press), 6)

setgrossB(ekofisk)
Zekofisk <- round(Zgross(temp, press), 6)

setgrossB(highN2)
ZhighN2 <- round(Zgross(temp, press), 6)


setgrossB(highCO2)
ZhighCO2 <- round(Zgross(temp, press), 6)


Z <- data.frame(Temp=tempF, Press=pressPSI, Gulf=Zgulf, Amarillo=Zamarillo, Ekofisk=Zekofisk, HighN2=ZhighN2, HighCO2=ZhighCO2)

