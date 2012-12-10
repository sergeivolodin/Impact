from math import *
R1 = 2.5e-3
R2 = 4e-3
e = 24e-3
a = (e - 2 * R2) / 2
h = 4e-3
d1 = 2e-3
v0 = h * a * d1

Ix_q = Iy_q = pi * h / 4 * (R2 ** 4 - R1 ** 4 + h ** 2 / 3 * (R2 ** 2 - R1 ** 2))
Iz_q = pi * h / 2 * (R2 ** 4 - R1 ** 4)

DIx_q = 2 * v0 * h ** 2 / 12
DIz_q = 2 * (v0 * (R2 + a / 2) ** 2 + v0 * a ** 2 / 12)
DIy_q = DIx_q + DIz_q

def printInfo():
 print "(I0xI0yI0z)/q\t(" + str(Ix_q) + " " + str(Iy_q) + " " + str(Iz_q) + ")"

printInfo()

Ix_q += DIx_q
Iy_q += DIy_q
Iz_q += DIz_q

printInfo()
