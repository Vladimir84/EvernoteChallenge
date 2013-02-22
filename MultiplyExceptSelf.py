#!/bin/python
#Enter your code here
import sys

def multUp(array):
    multUps=[array[-1],array[0]]
    for i in xrange(2,len(array)):
        multUps.append(multUps[i-1]*array[i-1])
    return multUps

def multDown(array,multDowns):
    for i in xrange(len(array)-2,0,-1):
         multDowns[i]*=multDowns[0]
         multDowns[0]*=array[i]  

def doIt():
    array=[int(x) for x in sys.stdin.readlines()]
    result=multUp(array[1:])
    multDown(array[1:],result)
    for elem in result: print elem
    
doIt()
