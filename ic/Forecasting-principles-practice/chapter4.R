require(fpp)

#
# EXERCICIO 1 DO CAPITULO 4
#

# a)
plot(Mwh ~ temp, data = econsumption)
(fit <- lm(Mwh ~ temp, data = econsumption))

#
# Temepratura mais baixa geralmente esta ligada a um consumo
# elevado de energia (aquecedores, etc)
#

# b)
plot(residuals(fit) ~ temp, data = econsumption)

#
# Os Residuios nao parecem estar correlacionados, logo podemos
# dizer que e um bom modelo
#

# c)
20.1995 -0.1452*10
20.1995 -0.1452*35
forecast(fit, newdata=data.frame(temp=c(10,35)))
plot(forecast(fit, newdata=data.frame(temp=c(10,35))))

#
# Ambos os valores são possíveis, embora o valor de 10C é mais
# acreditavel ja que ele esta dentro dos valores observados.
#

#
# EXERCICIO 2 DO CAPITULO 4
#

# a)
olympic = rbind(olympic, data.frame(Year = c(2000, 2004, 2008, 2012, 2016),
                                    time = c(43.84, 44.00, 43.75, 43.94, 43.04)))

# b)
plot(olympic)

#
# Entre os anos 1900 e 1960 temos um relacionamento mais ou menos
# linear entre os ano e tempo, após 1960 esse relacionamento é quebrado
# (1986 Outlier????)
#

# c)
(fit = lm(time ~ Year, data = olympics))

#
# Decreasing at the average of -0.064 per year
#

# d)
plot(residuals(fit) ~ Year, data = olympic)
abline(h = 0, col = "grey")

#
#
#

# e)
trainingSet <- olympic[1:23,]
testSet <- olympic[24:28,]
(fit <- lm(time ~ Year, data=trainingSet))
plot(forecast(fit, newdata=testSet[,"Year"]))
lines(time ~ Year, data = testSet, col = "red", type = "p")

#
# O metodo supoe que a velocidade diminui num ritmo constante, o que nao
# é verdade, assim, nao produz uma previsao muito boa. 
#