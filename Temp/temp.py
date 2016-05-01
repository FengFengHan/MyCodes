
a = 1
b= 1
n = 54
m = 27

for i in range(m):
    a = a * (n - i)
    b = b * (i+ 1)
#c = a//b
#print("%d" %c)
d = 1
for i in range(1,n+1):
    d *= i

aa = a
for i in range(1,1000):
    f = d / aa
    print("%.2f %d" %(f,i))
    aa *= a

