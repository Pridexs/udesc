library(forecast)
#
# EXERCICIO 1 DO CAPITULO 2
#
# 2.8.1.a)


data(dole, package="fma")
par(mfrow=c(2,2))
plot(dole)
lambda <- BoxCox.lambda(dole)
plot(BoxCox(dole,lambda))

# 2.8.1.b)
data(usdeaths, package="fma")
plot(usdeaths)

# 2.8.1.c)
data(bricksq, package="fma")
plot(bricksq)

#
# EXERCICIO 2 DO CAPITULO 2
#
# 2.8.2.a)
data(dowjones, package="fma")
plot(dowjones)

# 2.8.2.b)
plot(rwf(dowjones, 10, drift=TRUE))
# 2.8.2.c)
m <- (dowjones[length(dowjones)] - dowjones[1]) / (length(dowjones) - 1)
b <- dowjones[1] - (m * 1)
abline(b, m, lty=2, col=2, main='abline1')

# 2.8.2.d)
# snaive = naive?
lines(meanf(dowjones, h=11)$mean, col=3)
lines(naive(dowjones, h=11)$mean, col=5)
legend("topleft", lty=1, col=c(3,4,5),
         legend=c("mean", "drift", "naive"))
# naive é o mais adequado

#
# EXERCICIO 3 DO CAPITULO 2
#
# 2.8.3.a)
data(ibmclose, package='fma')
plot(ibmclose)

# 2.8.3.b)
ibm_train <- window(ibmclose, end=300)
ibm_test <- window(ibmclose, start=301)
plot(ibm_train)
plot(ibm_test)

# 2.8.3.c)
(ibm_train_fit1 <- meanf(ibm_train, h=69))
(ibm_train_fit2 <- rwf(ibm_train, h=69, drift=TRUE))
(ibm_train_fit3 <- naive(ibm_train, h=69))

# Mudando os limites do eixo y para ibm_train_fit1 aparecer.
plot(ibm_test, ylim=c(330, 510))

lines(ibm_train_fit1$mean, col=2)
lines(ibm_train_fit2$mean, col=3)
lines(ibm_train_fit3$mean, col=4)
legend("topright", lty=1, col=c(2,3,4),
       legend=c("meanf", "drift", "naive"))

accuracy(ibm_train_fit1, ibm_test)
accuracy(ibm_train_fit2, ibm_test)
accuracy(ibm_train_fit3, ibm_test)

# Analise resultados de accuracy
# meanf nao obteve resultados adequados
# drift obteve o melhor resultado em todos os testes
# naive obeteve um erro um pouco acima do metodo drift

#
# EXERCICIO 4 DO CAPITULO 2
#
# 2.8.4.a)
data(hsales, package='fma')
plot(hsales)

# 2.8.4.b)

#(hsales_train <- window(hsales, end=1994-.01))
(hsales_train <- window(hsales, end=c(1994,12)))
(hsales_test <- window(hsales, start=1994))

# 2.8.4.c)
(hsales_train_fit1 <- meanf(hsales_train, h=23))
(hsales_train_fit2 <- rwf(hsales_train, h=23, drift=TRUE))
(hsales_train_fit3 <- naive(hsales_train, h=23))
(hsales_train_fit4 <- snaive(hsales_train, h=23))

plot(hsales_test)
lines(hsales_train_fit1$mean, col=2)
lines(hsales_train_fit2$mean, col=3)
lines(hsales_train_fit3$mean, col=4)
lines(hsales_train_fit4$mean, col=5)
legend("topright", lty=1, col=c(2,3,4,5),
       legend=c("meanf", "drift", "naive", "season naive"))

accuracy(hsales_train_fit1, hsales_test)
accuracy(hsales_train_fit2, hsales_test)
accuracy(hsales_train_fit3, hsales_test)
accuracy(hsales_train_fit4, hsales_test)
# O metodo seasonal naive foi o melhor.

### Exercicio extra (RESOURCE) ###
# 1. a)
library(fpp)
#.99?
bricks1 <- window(bricksq, end=1987.99)
bricks2 <- window(bricksq, start=1988)

# b)
plot(bricksq)
lines(bricks1,col="red")
lines(bricks2,col="blue")

# c)
(bricks1_fit1 <- meanf(bricks1, h=27))
(bricks1_fit2 <- rwf(bricks1, h=27, drift=TRUE))
(bricks1_fit3 <- naive(bricks1, h=27))
(bricks1_fit4 <- snaive(bricks1, h=27))

plot(bricks2)
lines(bricks1_fit1$mean, col=2)
lines(bricks1_fit2$mean, col=51)
lines(bricks1_fit3$mean, col=56)
lines(bricks1_fit4$mean, col=117)
legend("topright", lty=1, col=c(2,51,56,117),
       legend=c("meanf", "drift", "naive", "season naive"))

# d)
accuracy(bricks1_fit1, bricks2)
accuracy(bricks1_fit2, bricks2)
accuracy(bricks1_fit3, bricks2)
accuracy(bricks1_fit4, bricks2)

# e)
# seasonal naive conseguiu prever melhor o conjunto de testes
# (erro menor)

# f)
res <- residuals(bricks1_fit4)
plot(res)
hist(res, breaks="FD")

#
# Sim, os dados não parecem estar correlacionados e estão normalmente
# distribuidos, o que leva a crer que o método de forecast é bom.
#