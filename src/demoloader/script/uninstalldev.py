#!/usr/bin/python
import sys
koname = sys.argv[1]
devname = sys.argv[2]
print("start to rmmod " + devname)
import os
p = os.popen3("sudo rmmod " + koname, "r", 100)
if (None == p):
    print("sudo rmmod " + koname + " failed")

s = ""
s = p[2].read()

if (( 'not' in s ) or ('err' in s) or ('Err' in s ) or ('ERR' in s)):
    print("sudo rmmod " + koname+ " failed.")
    print(s)
    exit()
print("rmmod " + koname + " successful")

p = os.popen3("cd /dev ; sudo rm " + devname + "; cd -", "rw", 100)
if (None == p):
    print("sudo rm nod " + devname + " failed")

s = ""
s = p[2].read()
if (( 'not' in s ) or ('err' in s) or ('Err' in s ) or ('ERR' in s)):
    print("sudo rm nod " + devname+ " failed.")
    print(s)
    exit()

p = os.popen("cat /proc/devices", "r", 100)
flag = 0
import re

for ln in p:
    if(devname in ln):
        ln = re.compile("\s").split(ln)[0]
        flag = 1
        break


if (flag == 1):
    print("still find " + devname + " in /proc/devices, mknod failed")
    exit()
    
print("rm mod " + devname + " successful")

