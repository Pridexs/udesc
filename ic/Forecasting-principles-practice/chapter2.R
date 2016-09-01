library(forecast)

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

# 2.8.2.a)
data(dowjones, package="fma")
plot(dowjones)
plot(rwf(dowjones, 10, drift=TRUE))

# 2.8.2.b)
# ?

# 2.8.2.b)
# ?

# 2.8.3.a)
data(ibmclose, package='fma')
plot(ibmclose)

# 2.8.3.b)

ibm_train <- window(ibmclose, end=300)
ibm_test <- window(ibmclose, start=301)

ibm_train_fit1 <- mean(ibm_train, h=11)
ibm_train_fit2 <- rwf(ibm_train, h=11)
ibm_train_fit3 <- snaive(ibm_train, h=11)

par(mfrow=c(1,1))
plot(ivm_train_fit1, plot.conf=FALSE, main="Forecasts for quarterly beer production")
lines(ibm_train_fit2$mean, col=2)
lines(ibm_train_fit3$mean, col=3)
lines(ibm_train_fit3)
