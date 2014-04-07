import csv
import math
import numpy as np
import matplotlib.pyplot as plt
import random
random.seed()
no_of_iterations=500
no_of_reruns=50
step1,step,iter,vel,pos,col,total,err,step_rand=list(),list(),list(),list(),list(),list(),list(),list(),list()
x,x1,x2,x3,y=np.loadtxt('./data/g32_lab09data_01.csv',delimiter=',',usecols=(2,3,4,5,6),unpack=True)
for i in range(no_of_iterations):
    c=list()
    for u in range(15):
	c.append(random.randint(0,49))
    sum1, sum2, sum3, sum4, sum5, sum6=0, 0, 0, 0, 0, 0
    for j in range(no_of_reruns):
	if(i==78):
	    step1.append(x[i*no_of_reruns+j])
	if(j in c):
	    sum6=sum6+x[i*no_of_reruns+j]
        sum1=sum1+x[i*no_of_reruns+j]
        sum2=sum2+y[i*no_of_reruns+j]
        sum3=sum3+x1[i*no_of_reruns+j]
        sum4=sum4+x2[i*no_of_reruns+j]
        sum5=sum5+x3[i*no_of_reruns+j]
    step_rand.append(sum6/15)
    step.append(sum1/no_of_reruns)
    iter.append(sum2/no_of_reruns)
    col.append(sum3/no_of_reruns)
    vel.append(sum4/no_of_reruns)
    pos.append(sum5/no_of_reruns)
    total.append((sum3+sum4+sum5)/no_of_reruns)

for i in range(no_of_iterations):
    error=0
    for j in range(no_of_reruns):
        error=error+(x[i*no_of_reruns+j]-step[i])*(x[i*no_of_reruns+j]-step[i])
    err.append(math.sqrt(error/no_of_reruns))

x=[i+1 for i in range(no_of_iterations)]

p1=plt.bar(x,step,0.35)
plt.plot(x,iter)
plt.xlabel('Time')
plt.ylabel('Freq(no of reruns)')
plt.title('Avg. step and loop time')
plt.legend(['step','loop'])
plt.savefig('./plots/g32_lab09_plot01.png')
plt.close()

plt.plot(x,step)
plt.plot(x,col)
plt.plot(x,vel)
plt.plot(x,pos)
plt.plot(x,total)
plt.title('Avg. step, collision, velocity, position and sum of col, vel and pos times ')
plt.xlabel('Time')
plt.ylabel('Freq(no of reruns)')
plt.legend(['step','col','vel','pos','col+vel+pos'])
plt.savefig('./plots/g32_lab09_plot02.png')
plt.close()

plt.errorbar(x, step, yerr=err)
plt.xlabel('Time')
plt.ylabel('Freq(no of reruns)')
plt.title('Avg. step time with eror bars')
plt.legend(['avg. step time with error bars'])
plt.savefig('./plots/g32_lab09_plot03.png')
plt.close()

r=np.histogram(step1,30)
s=np.cumsum(r[0])
t=r[1][1:]
plt.plot(t,s)
plt.hist(step1,30)
plt.title('Cumlative and frequency bar plot with iteration value=78')
plt.legend(['cumulative frequency','frequency plot'])
plt.xlabel('Time')
plt.ylabel('Freq(no of reruns)')
plt.savefig('./plots/g32_lab09_plot04.png')
plt.close()

xi=np.arange(1,no_of_iterations+1)
z1=np.polyfit(x,step,1)
line1 = z1[0]*xi+z1[1] 
z2=np.polyfit(x,step_rand,1)
line2 = z2[0]*xi+z2[1]
plt.plot(xi,line1,'r-',xi,step,'o')
plt.plot(xi,line2,'r-',xi,step_rand,'o')
plt.title('best fit lines for 50 and 15 random reruns')
plt.xlabel('no of iterations')
plt.ylabel('time')
plt.legend(['best fit line over all 50 reruns','over random 15 reruns'])
plt.savefig('./plots/g32_lab09_plot05.png')
plt.close()
