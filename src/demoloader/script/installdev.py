#!/usr/bin/python
import sys
koname = sys.argv[1]
devname = sys.argv[2]
devminor = 0
print("start to insmod " + devname)
import os
p = os.popen3("sudo insmod " + koname, 't', 100)
if (None == p):
    print("sudo insmod " + koname + " failed")

s = ""
s = p[2].read()

if (("can't" in s) or ( 'not' in s ) or ('err' in s) or ('Err' in s ) or ('ERR' in s)):
    print("sudo insmod " + koname+ " failed.")
    print(s)
    exit()
print("insmod " + koname + " successful")

p = os.popen("cat /proc/devices", "r", 100)
flag = 0
import re

for ln in p:
    if(devname in ln):
        ln = re.compile("\s").split(ln)[0]
        devmajor = int(ln)
        flag = 1
        break

if (flag == 0):
    print("can't find " + devname + " in /proc/devices, mknod failed")
    exit()

p = os.popen3("cd /dev ; sudo mknod " + devname + " c " + str(devmajor) + " " + str(devminor) + "; cd -", 't', 100)
if (None == p):
    print("sudo mknode " + devname + " failed")

s = ""
s = p[2].read()
if (( 'not' in s ) or ('err' in s) or ('Err' in s ) or ('ERR' in s)):
    print("sudo mknod " + devname+ " failed.")
    print(s)
    exit()
print("mkmod " + devname + " successful")


p = os.popen3("cd /dev ; sudo chmod 666 " + devname +"; cd -", 't' , 100)
if (None == p):
    print("sudo chmod " + devname + " failed")

s = ""
s = p[2].read()
if (( 'not' in s ) or ('err' in s) or ('Err' in s ) or ('ERR' in s)):
    print("sudo chmod " + devname+ " failed.")
    print(s)
    exit()
print("chmod " + devname + " successful")
        
        
        


