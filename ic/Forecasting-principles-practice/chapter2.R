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
ibm_train <- ibmclose[1:300]
ibm_test <- ibmclose[301:369]
