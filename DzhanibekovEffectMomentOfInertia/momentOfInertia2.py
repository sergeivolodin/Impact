from math import *
h=5e-3
r1=5e-3
r2=7e-3
b=8e-3
a=1e-2
q=7800

m1=q*pi*h*(r2**2-r1**2)
m2=m1
m=m1+2*m2

b1=2*m2*b/(2*m2+m1)

A1=C1=m1/4*(r1**2+r2**2+h**2/3+4*b1**2)
B1=m1/2*(r1**2+r2**2)

A2=2*m2*(a**2+(b-b1)**2)
B2=2*m2*a**2
C2=2*m2*(b-b1)**2

A=A1+A2
B=B1+B2
C=C1+C2

print "mass m1="+str(m1)
print "mass m2="+str(m2)
print "mass m="+str(m)

print "b1="+str(b1)

print "A1="+str(A1)
print "B1="+str(B1)
print "C1="+str(C1)

print "A1="+str(A1)
print "B2="+str(B2)
print "C2="+str(C2)

print "A="+str(A)
print "B="+str(B)
print "C="+str(C)


