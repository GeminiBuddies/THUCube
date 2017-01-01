from ctypes import *

C = CDLL("msvcrt.dll")

system = lambda x: C.system(x)

for i in xrange(1, 4) :
    system("..\\Cube < data%d.txt > .\\2016011349\\data%d.txt" % (i, i))
